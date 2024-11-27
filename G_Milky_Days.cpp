#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<int>, rb_tree_tag,
tree_order_statistics_node_update> indexed_set;

#define ll long long
#define ldd long double
#define en '\n'
#define MP make_pair
#define pb push_back
#define pii pair<int, int>
#define pll pair<ll, ll>
#define ff first
#define ss second
#define vi vector<int>
#define vll vector<ll>
#define v2i vector<vector<int>>
#define v2ll vector< vector<ll>>
#define vpi vector<pii>
#define vpll vector<pll>
#define iset indexed_set
#define minpqll priority_queue<ll,vector<ll>,greater<ll>>
#define getv(v, n) for(ll i = 0; i < n; i++) cin >> v[i];
#define get_pair(v,n) for (ll i=0;i<n;i++) cin>>v[i].ff>>v[i].ss;
#define fr(i,a,b) for(ll i=a;i<(b);i++)
#define fr_e(i,a,b) for(ll i=a;i<=b;i++)
#define fr_rev(i,a,b) for(ll  i=(a);i>=b;i--)
#define all(v) v.begin(),v.end()
#define mod 1000000007
#define print(v) fr(i,0,v.size()) cout<<v[i]<<" "
#define INF LLONG_MAX
#define yes cout<<"YES\n"
#define no cout<<"NO\n"
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define stp(n) cout<<fixed<<setprecision(n)
#define sz(v) 1LL*v.size()
 
inline ll add(ll a,ll b)
{
    a+=b;
    if(a>=mod) a%=mod;
    return a;
}

inline ll mul(ll a,ll b)
{
    return ((a%mod)*(b%mod))%mod;
}

inline ll bin_pow(ll a,ll b)
{
    ll ans=1;
    while(b)
    {
        if(b%2) ans=ans*a%mod;
        a=mul(a,a);
        b/=2;
    }
    return ans;
}

inline ll inv(ll a)
{
    return bin_pow(a,mod-2)%mod;
}

struct node
{
    ll val,lazy;
    node(){
        val = lazy = 0;
    }
};
class Segtree
{
    public:
    ll n;
    vector <node> t;
    Segtree(ll x = 0)
    {
        n = x;
        t.resize(4*n+1);
    }

    void push(ll ind,ll l,ll r){
        if(l!=r){
            t[ind<<1].lazy = t[ind].lazy;
            t[ind<<1|1].lazy = t[ind].lazy;
        }
        if(t[ind].lazy) t[ind].val = 0;
        t[ind].lazy= 0;
    }

    node merge(node x,node y)
    {
        node ans;
        ans.val = x.val+y.val;
        return ans;
    }

    void update(ll ind,ll l,ll r,ll pos,ll val)
    {
        push(ind,l,r);
        if(l>pos or r<pos) return;
        if(l==r)
        {
            t[ind].val+= val;
            return;
        }
        ll mid = (l+r)>>1;
        update(ind<<1,l,mid,pos,val);
        update(ind<<1|1,mid+1,r,pos,val);
        t[ind] = merge(t[ind<<1],t[ind<<1|1]);
    }

    void setzero(ll ind, ll l, ll r, ll lq,ll rq)
    {
        push(ind, l, r);
        if (l > lq or r < rq)
            return;
        if (l>=lq and r<=rq)
        {
            t[ind].val = 0;
            t[ind].lazy = 1;
            push(ind,l,r);
            return;
        }
        ll mid = (l + r) >> 1;
        update(ind << 1, l, mid, lq,rq);
        update(ind << 1 | 1, mid + 1, r, lq,rq);
        t[ind] = merge(t[ind << 1], t[ind << 1 | 1]);
    }

    node query(ll ind,ll l,ll r,ll lq,ll rq)
    {
        push(ind,l,r);
        node temp;
        if(l>rq or r<lq) return temp;
        if(l>=lq and r<=rq) return t[ind];
        ll mid = (l+r)>>1;
        return merge(query(ind<<1,l,mid,lq,rq),query(ind<<1|1,mid+1,r,lq,rq));
    }
};
void solve()
{
    ll n,m,k;
    cin>>n>>m>>k;
    vll milk(n,0);
    fr(i,0,m){
        ll d,x;
        cin>>d>>x;
        milk[d-1] = x;
    }

    Segtree sg(n);
    ll ans = 0;
    fr(i,0,n){
        // sg.update(1,0,n-1,i,milk[i]);
        ll lo = 0;
        ll hi = i;
        ll ind = -1;
        // while(lo<=hi){
        //     ll mid = (lo+hi)>>1;
        //     if(sg.query(1,0,n-1,mid,i).val>=m){
        //         ind= mid;
        //         lo = mid+1;
        //     }
        //     else hi = mid-1;
        // }
        // if(ind==-1) {
        //     sg.setzero(1,0,n-1,0,i);
        // }
        // else
        // {
        //     ans++;
        //     ll curr= sg.query(1,0,n-1,ind,i).val;
        //     sg.update(1, 0, n-1,ind,-(curr-m));
        //     if (ind + 1 <= i) sg.setzero(1, 0, n - 1, ind + 1, i);
        // }
    }
    cout<<ans<<en;
}

signed main(){
    fast
    ll t;
    cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}