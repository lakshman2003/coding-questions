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


void solve()
{
    ll n,m;
    cin>>n>>m;
    vll v(n+1);
    fr_e(i,1,n) cin>>v[i];
    v2ll g(n+1),rev_g(n+1);
    fr_e(i,1,n){
        g[i].pb(v[i]);
        rev_g[v[i]].pb(i);
    }
    vll cycle_node(n+1,0),vis(n+1,0),par(n+1,0);
    v2ll cycles;
    auto dfs = [&](auto &self, ll node,ll p){
        if(vis[node]==2) return;
        if(vis[node]==1){
            vll cycle;
            cycle.pb(node);
            for(ll i = p; i!=node; i = par[i]){
                cycle.pb(i);
            }
            cycles.pb(cycle);
            for(auto x:cycle) cycle_node[x] = 1;
            return;
        }
        vis[node] = 1;
        par[node] = p;
        for(auto x:g[node]){
            self(self,x,node);
        }
        vis[node] = 2;
    };
    fr_e(i,1,n){
        if(!vis[i]) dfs(dfs,i,0);
    }

    v2ll dp(n+1,vll(m+1,-1));
    auto rec = [&](auto &self,ll node,ll prev)->ll{
        if(prev<=0) return 0;
        if(dp[node][prev]!=-1) return dp[node][prev];
        ll ans1 = self(self,node,prev-1),ans2 = 1;
        for(auto x:rev_g[node]){
            if(!cycle_node[x]){
                ans2 = mul(ans2,self(self,x,prev));
            }
        }
        return dp[node][prev] = (ans1+ans2)%mod;
    };
    ll ans = 1;
    for(auto cycle:cycles){
        ll cnt = 0;
        fr(col,1,m+1){
            ll ways = 1;
            for(auto x:cycle){
                for(auto y:rev_g[x]){
                    if(!cycle_node[y]){
                        ways = mul(ways,rec(rec,y,col));
                    }
                }
            }
            (cnt+=ways)%=mod;
        }
        ans = mul(ans,cnt);
    }
    cout<<ans<<en;
}

signed main(){
    fast
    solve();
    return 0;
}