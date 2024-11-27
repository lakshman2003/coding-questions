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

const ll maxn = 2e5+10;
ll par[maxn][31];
ll path[maxn][31];
ll depth[maxn];
vector <vector<pll>> g;
void dfs(ll node,ll p,ll w,ll d){
    depth[node] = d;
    par[node][0] = p;
    path[node][0] = w;
    fr_e(i,1,30){
        par[node][i]= par[par[node][i-1]][i-1];
        path[node][i] = path[node][i-1] & path[par[node][i-1]][i-1];
    }

    for(auto [nei,wei]:g[node]){
        if(nei==p) continue;
        dfs(nei,node,wei,d+1);
    }
}

pll lca(ll a,ll b){
    if(a==b) return MP(a,0);
    if(depth[a]<depth[b]) swap(a,b);
    ll ans = (1LL<<62)-1;
    ll diff= depth[a]-depth[b];
    fr_rev(i,30,0){
        if(diff&(1LL<<i)){
            ans = ans&path[a][i];
            a = par[a][i];
        }
    }

    if(a==b) return MP(a,ans);
    fr_rev(i,30,0){
        if(par[a][i]!=par[b][i]){
            ans = ans&path[a][i];
            ans = ans&path[b][i];
            a = par[a][i];
            b = par[b][i];
        }
    }
    return MP(par[a][0],ans&path[a][0]&path[b][0]);
}

void solve()
{
    ll n;
    cin>>n;
    g.resize(n);
    fr(i,0,n-1){
        ll a,b,w;
        cin>>a>>b>>w;
        a--;b--;
        g[a].pb(MP(b,w));
        g[b].pb(MP(a,w));
    }
    dfs(0,-1,0,0);
    ll q;
    cin>>q;
    while(q--){
        ll a,b;
        cin>>a>>b;
        a--;b--;
        auto [anc,ans] = lca(a,b);
        cout<<ans<<en;
    }
}

signed main(){
    fast
    ll t = 1;
    while(t--)
    {
        solve();
    }
    return 0;
}