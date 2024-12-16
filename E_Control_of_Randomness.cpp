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

class Segtree
{
    public:
    ll n;
    vll v,t;
    Segtree(ll x = 0)
    {
        n = x;
        t.resize(4*n+1);
    }

    ll merge(ll x,ll y)
    {
        return x+y;
    }
    void build(ll ind,ll l,ll r)
    {
        if(l==r)
        {
            t[ind] = v[l];
            return;
        }
        ll mid = (l+r)>>1;
        build(ind<<1,l,mid);
        build(ind<<1|1,mid+1,r);
        t[ind] = merge(t[ind<<1],t[ind<<1|1]);
    }


    void update(ll ind,ll l,ll r,ll pos,ll val)
    {
        if(l>pos or r<pos) return;
        if(l==r)
        {
            t[ind] = val;
            v[l]= val;
            return;
        }
        ll mid = (l+r)>>1;
        update(ind<<1,l,mid,pos,val);
        update(ind<<1|1,mid+1,r,pos,val);
        t[ind] = merge(t[ind<<1],t[ind<<1|1]);
    }

    ll query(ll ind,ll l,ll r,ll lq,ll rq)
    {
        if(l>rq or r<lq) return 0;
        if(l>=lq and r<=rq) return t[ind];
        ll mid = (l+r)>>1;
        return merge(query(ind<<1,l,mid,lq,rq),query(ind<<1|1,mid+1,r,lq,rq));
    }
};
const ll maxn = 2e3+1;
ll dp[maxn][maxn][2];
void solve()
{
    ll n,q;
    cin>>n>>q;
    v2ll g(n);
    fr(i, 0, n - 1) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        g[u].pb(v);
        g[v].pb(u);
    }
    fr_e(j,1,n){
        fr_e(k,0,1) dp[0][j][k] = 0;
    }
    auto dfs = [&](auto &self,ll node,ll p)->void{
        if(node){
            ll neicnt = g[node].size();
            fr_e(power,0,n){
                dp[node][power][1] = 1+dp[p][power][0];
                dp[node][power][0] = 2*neicnt-1+dp[p][power][1];
                if(power and dp[p][power-1][1]+1<dp[node][power][0]) {
                    dp[node][power][0] = dp[p][power-1][1]+1;
                }
            }
        }
        for(auto nei:g[node]){
            if(nei==p) continue;
            self(self,nei,node);
        }
    };
    dfs(dfs,0,-1);
    while(q--){
        ll v,p;
        cin>>v>>p;
        v--;
        cout<<dp[v][p][1]<<en;
    }
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