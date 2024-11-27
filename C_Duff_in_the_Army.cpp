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

const ll maxn = 1e5+10;
ll par[maxn][22],depth[maxn];
vll mini[maxn][22];
v2ll g,pos;
ll n,m,q;
vll merge(vll &a,vll &b){
    vll temp;
    for(auto &x:a) temp.pb(x);
    for(auto &x:b) temp.pb(x);
    sort(all(temp));
    vll ans;
    fr(i,0,min((ll)10,(ll)temp.size())){
        ans.pb(temp[i]);
    }
    return ans;
}

void dfs(ll node,ll p,ll d){
    depth[node] = d;
    par[node][0] = p;
    fr(i,1,21) par[node][i] = par[par[node][i-1]][i-1];
    mini[node][0] = pos[node];
    fr(i,1,21) mini[node][i] = merge(mini[node][i-1],mini[par[node][i-1]][i-1]);
    for(auto nei:g[node]){
        if(nei==p) continue;
        dfs(nei,node,d+1);
    }
}

vll lca(ll a,ll b){
    if(a==b) return pos[a];
    if(depth[a]>depth[b]) swap(a,b);
    ll diff = depth[b]- depth[a];
    vll temp;
    fr_rev(i,20,0){
        if(diff&(1LL<<i)){
            temp = merge(temp,mini[b][i]);
            b = par[b][i];
        }
    }

    if(a==b) return merge(temp,pos[a]);
    fr_rev(i,20,0){
        if(par[a][i]!=par[b][i]){
            temp = merge(temp,mini[a][i]);
            temp = merge(temp,mini[b][i]);
            a = par[a][i];
            b = par[b][i];
        }
    }
    temp = merge(temp,mini[a][0]);
    temp = merge(temp,mini[b][0]);
    temp = merge(temp,mini[par[a][0]][0]);
    return temp;
}

void solve()
{
    cin>>n>>m>>q;
    g.resize(n+1);
    pos.resize(n+1);
    fr(i,0,n-1){
        ll a,b;
        cin>>a>>b;
        g[a].pb(b);
        g[b].pb(a);
    }
    fr(i,0,m){
        ll x;
        cin>>x;
        pos[x].pb(i+1);
    }
    dfs(1,0,0);
    while(q--){
        ll u,v,a;
        cin>>u>>v>>a;
        vll ans = lca(u,v);
        cout<<min((ll)ans.size(),a)<<" ";
        fr(i,0,min(a,(ll)ans.size())) cout<<ans[i]<<" ";
        cout<<en;
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