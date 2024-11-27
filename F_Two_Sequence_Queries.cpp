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
#define pb push_back
#define pii pair<int, int>
#define pll pair<ll, ll>
#define MP make_pair
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
#define mod 998244353
#define print(v) fr(i,0,v.size()) cout<<v[i]<<" "
#define INF LLONG_MAX
#define yes cout<<"Yes\n"
#define no cout<<"No\n"
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
    ll rem,suma,sumb,lazya,lazyb;
    node()
    {
        rem = suma = sumb = lazya = lazyb = 0;
    }
};
class Segtree
{
    public:
    ll n;
    vll a,b;
    vector <node> t;
    Segtree(ll x = 0)
    {
        n = x;
        t.resize(4*n+1);
    }


    void push(ll ind,ll l,ll r)
    {
        if(l!=r)
        {
            t[ind<<1].lazya+= t[ind].lazya;
            t[ind << 1].lazyb += t[ind].lazyb;

            t[ind<<1|1].lazya+= t[ind].lazya;
            t[ind << 1|1].lazyb += t[ind].lazyb;
        }

        (t[ind].rem+= mul(t[ind].lazya , t[ind].sumb) + mul(t[ind].lazyb,t[ind].suma) + 
        mul((r-l+1),mul(t[ind].lazya,t[ind].lazyb))) %= mod;
        (t[ind].suma+= mul((r-l+1),t[ind].lazya))%=mod;
        (t[ind].sumb+= mul((r - l + 1), t[ind].lazyb))%= mod;
        t[ind].lazya = 0;
        t[ind].lazyb = 0;
    }


    node merge(node a,node b)
    {
        node ans;
        ans.rem = (a.rem+b.rem)%mod;
        ans.suma = (a.suma+b.suma)%mod;
        ans.sumb = (a.sumb+b.sumb)%mod;
        return ans;
    }

    void build(ll ind,ll l,ll r)
    {
        if(l==r)
        {
            t[ind].suma = a[l];
            t[ind].sumb = b[l];
            t[ind].rem = mul(a[l],b[l]);
            return;
        }
        ll mid = (l+r)>>1;
        build(ind<<1,l,mid);
        build(ind<<1|1,mid+1,r);
        t[ind] = merge(t[ind<<1],t[ind<<1|1]);
    }


    void update(ll ind,ll l,ll r,ll lq,ll rq,ll sa,ll sb)
    {
        push(ind, l, r);
        if(l>rq or r<lq) return;
        if(l>=lq and r<=rq)
        {
            t[ind].lazya+= sa;
            t[ind].lazyb+= sb;
            push(ind,l,r);
            return;
        }
        ll mid = (l+r)>>1;
        update(ind<<1,l,mid,lq,rq,sa,sb);
        update(ind << 1 | 1, mid + 1, r, lq, rq, sa, sb);
        t[ind] = merge(t[ind<<1],t[ind<<1|1]);
    }

    node query(ll ind,ll l,ll r,ll lq,ll rq)
    {
        push(ind,l,r);
        if(l>rq or r<lq) 
        {
            node t;
            return t;
        }
        if(l>=lq and r<=rq) return t[ind];
        ll mid = (l+r)>>1;
        return merge(query(ind<<1,l,mid,lq,rq),query(ind<<1|1,mid+1,r,lq,rq));
    }
};
void solve()
{
    ll n,q;
    cin>>n>>q;
    vll a(n),b(n);
    getv(a,n);
    getv(b,n);
    Segtree sg(n);
    sg.a = a;
    sg.b = b;
    sg.build(1,0,n-1);
    while(q--)
    {
        ll ch;
        cin>>ch;
        if(ch==1)
        {
            ll l,r,x;
            cin>>l>>r>>x;
            l--;r--;
            sg.update(1,0,n-1,l,r,x,0);
        }
        else if(ch==2)
        {
            ll l, r, x;
            cin >> l >> r >> x;
            l--;
            r--;
            sg.update(1, 0, n - 1, l, r, 0,x);
        }
        else
        {
            ll l,r;
            cin>>l>>r;
            l--;r--;
            cout<<sg.query(1,0,n-1,l,r).rem<<en;
        }
        
    }
}

signed main(){
    fast
    solve();
    return 0;
}