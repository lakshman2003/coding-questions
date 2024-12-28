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
#define mod 1000000007
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


void solve()
{
    ll n;
    cin>>n;
    v2ll g(n+1);
    fr(i,0,n-1){
        ll u,v;
        cin>>u>>v;
        g[u].pb(v);
        g[v].pb(u);
    }
    vll par(n+1,0),indp(n+1,0);
    auto dfs = [&](auto &self,ll u,ll p)->void{
        par[u] = p;
        indp[u] = 1;
        for(auto x:g[u]){
            if(x==p)
                continue;
            self(self,x,u);
            indp[u]+=indp[x];
        }
    };
    dfs(dfs,1,0);
    ll ans = n;
    fr(i,1,n+1){
        vpll arr;
        ll tot = 0;
        for(auto x:g[i]){
            ll sz = indp[x],lf = g[x].size()-1;
            if(par[x]!=i) {
                sz = n-indp[i];
            }
            arr.pb({lf,sz});
            tot+= sz;
        }
        sort(all(arr));
        ll cnt = arr.size();
        ll s = 0;
        ll mini = 1e18;
        fr(j,0,cnt){
            ll rem = tot-(cnt-j)*(arr[j].ff+1);
            rem+= s;
            if(arr[j].ff) mini = min(mini,rem);
            s+= arr[j].ss;
            tot-= arr[j].ss;
        }
        ans = min(ans,mini);
    }
    cout<<ans<<en;

}

signed main(){
    fast
    solve();
    return 0;
}