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
    ll n,m;
    cin>>n>>m;
    v2ll g1(n+1),g2(n+1);
    fr(i,0,m){
        ll a,b;
        cin>>a>>b;
        g1[a].pb(b);
        g2[b].pb(a);
    }
    auto bfs = [&](v2ll &g,ll src)->vll{
        vll dist(n+1,1e9),vis(n+1,0);
        dist[src] = 0;
        queue <ll> q;
        q.push(src);
        while(!q.empty()){
            ll x = q.front();
            q.pop();
            if(vis[x]) continue;
            vis[x] = 1;
            for(auto nei:g[x]){
                if(dist[nei]>dist[x]+1){
                    dist[nei] = dist[x]+1;
                    q.push(nei);
                }
            }
        }
        return dist;
    };

    vll d1 = bfs(g1,1),d2 = bfs(g2,1);
    ll ans= 1e9;
    fr(i,2,n+1){
        ans= min(ans,d1[i]+d2[i]);
    }
    if(ans>=1e9) ans = -1;
    cout<<ans<<en;
}

signed main(){
    fast
    solve();
    return 0;
}