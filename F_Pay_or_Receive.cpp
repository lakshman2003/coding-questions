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
    ll n,m,q;
    cin>>n>>m>>q;
    vector <vector <pair<ll,ll>>> g(n+1);
    fr(i,0,m){
        ll a,b,c;
        cin>>a>>b>>c;
        g[a].pb(MP(b,c));
        g[b].pb(MP(a,-c));
    }
    vll comp(n+1,-1),pos_cycle(n+1,0),vis(n+1,0),dist(n+1,0);
    auto dfs = [&](auto &self,ll node,ll p,ll c,ll w){
        comp[node] = c;
        if(vis[node]==1){
            if(w!=dist[node])
                pos_cycle[c] = 1;
            return;
        }
        if(vis[node]==2) return;
        vis[node] = 1;
        dist[node] = w;
        for(auto [nei,wei]:g[node]){
            self(self,nei,node,c,w+wei);
        }
        vis[node] = 2;
    };
    ll col = 0;
    fr(i,1,n+1){
        if(!vis[i]){
            col++;
            dfs(dfs,i,0,col,0);
        }
    }

    vis.resize(n+1,0);
    auto dfs2 = [&](auto &self,ll node,ll p,ll w,ll d)->void{
        dist[node] = w;
        vis[node] = 1;
        for(auto [nei,wei]:g[node]){
            if(vis[nei] or nei==p) continue;
            self(self,nei,node,w+wei,d+1);
        }
    };

    vll done(col+2,0);
    fr(i,1,n+1){
        if(!pos_cycle[comp[i]] and !done[comp[i]]){
            dfs2(dfs2,i,0,0,0);
            done[comp[i]] = 1;
        }
    }

    while(q--){
        ll a,b;
        cin>>a>>b;
        if(comp[a]!=comp[b]) cout<<"nan"<<en;
        else if(pos_cycle[comp[a]]) cout<<"inf"<<en;
        else{
            ll ans = dist[b]-dist[a];
            cout<<ans<<en;
        }
    }
}

signed main(){
    fast
    solve();
    return 0;
}