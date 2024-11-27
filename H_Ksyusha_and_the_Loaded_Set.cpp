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

struct node{
    ll maxi,last,first,sz;
    node(){
        maxi = last = first = sz  = 0;
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

    node merge(node x,node y)
    {
        node ans;
        ans.maxi = max({x.maxi,y.maxi,x.last+y.first});
        ans.sz = x.sz+y.sz;
        ans.first = x.first;
        if(x.first==x.sz) ans.first+= y.first;
        ans.last = y.last;
        if(y.last==y.sz) ans.last+= x.last;
        return ans;
    }

    void build(ll ind,ll l,ll r)
    {
        if(l==r) {
            t[ind].sz = t[ind].first = t[ind].last = t[ind].maxi = 1;
            return;
        }
        ll mid = (l+r)>>1;
        build(ind<<1,l,mid);
        build(ind<<1|1,mid+1,r);
        t[ind] = merge(t[ind<<1],t[ind<<1|1]);
    }


    void add(ll ind,ll l,ll r,ll pos)
    {
        if(l>pos or r<pos) return;
        if(l==r)
        {
            t[ind].first = t[ind].last = t[ind].maxi = 0;
            t[ind].sz= 1;
            return;
        }
        ll mid = (l+r)>>1;
        add(ind<<1,l,mid,pos);
        add(ind<<1|1,mid+1,r,pos);
        t[ind] = merge(t[ind<<1],t[ind<<1|1]);
    }

    void remove(ll ind, ll l, ll r, ll pos)
    {
        if (l > pos or r < pos)
            return;
        if (l == r)
        {
            t[ind].sz = t[ind].first = t[ind].last = t[ind].maxi = 1;
            return;
        }
        ll mid = (l + r) >> 1;
        remove(ind << 1, l, mid, pos);
        remove(ind << 1 | 1, mid + 1, r, pos);
        t[ind] = merge(t[ind << 1], t[ind << 1 | 1]);
    }

    node query(ll ind,ll l,ll r,ll lq,ll rq)
    {
        node temp;
        if(l>rq or r<lq) return temp;
        if(l>=lq and r<=rq) return t[ind];
        ll mid = (l+r)>>1;
        return merge(query(ind<<1,l,mid,lq,rq),query(ind<<1|1,mid+1,r,lq,rq));
    }
};
const ll maxn = 4e6 + 10;
Segtree sg(maxn+1);
void solve()
{
    ll n;
    cin>>n;
    set<ll> st;
    fr(i,0,n){
        ll x;
        cin>>x;
        sg.add(1,1,maxn,x);
        st.insert(x);
    }
    ll m;
    cin>>m;
    fr(i,0,m){
        char ch;
        cin>>ch;
        if(ch=='+'){
            ll x;
            cin >> x;
            sg.add(1, 1, maxn, x);
            st.insert(x);
        }
        else if(ch=='-'){
            ll x;
            cin >> x;
            sg.remove(1, 1, maxn, x);
            st.erase(x);
        }
        else{
            ll k;
            cin>>k;
            ll lo= 1;
            ll hi = maxn-k+1;
            ll ans = hi;
            while(lo<=hi){
                ll mid = (lo+hi)>>1;
                node q = sg.query(1,1,maxn,1,mid+k-1);
                if(q.maxi>=k){
                    ans = mid;
                    hi = mid-1;
                }
                else lo = mid+1;
            }
            cout<<ans<<" ";
        }
    }
    cout<<en;
    for(auto x:st){
        sg.remove(1,1,maxn,x);
    }
}

signed main(){
    fast
    sg.build(1, 1, maxn);
    ll t;
    cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}