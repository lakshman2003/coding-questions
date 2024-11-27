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

vector <vpll> g;
vll vis,depth;
const ll maxn = 1e5+10;
ll par[maxn][25];
ll pre_maxi[maxn][25];

void dfs(ll node,ll p,ll w,ll comp,ll d){
    vis[node] = comp;
    depth[node] = d;
    par[node][0]= p;
    pre_maxi[node][0] = w;
    fr(i,1,25) {
        par[node][i] = par[par[node][i-1]][i-1];
        pre_maxi[node][i] = max(pre_maxi[node][i-1],pre_maxi[par[node][i-1]][i-1]);
    }
    for(auto [nei,w]:g[node]){
        if(nei==p) continue;
        dfs(nei,node,w,comp,d+1);
    }
}

vll lca(ll a,ll b){
    if(a==b) return {a,0};
    if(depth[b]<depth[a]) swap(a,b);
    ll diff = (depth[b]-depth[a]);
    ll maxi = -1;
    for(ll i = 24;i>=0;i--){
        if(diff&(1LL<<i)) {
            maxi = max(maxi,pre_maxi[b][i]);
            b = par[b][i];
        }
    }

    if(a==b) return {a,maxi};
    for(ll i= 24;i>=0;i--){
        if(par[a][i]!=par[b][i]) {
            maxi = max({maxi,pre_maxi[a][i],pre_maxi[b][i]});
            a = par[a][i];
            b = par[b][i];
        }
    }
    return {par[a][0],max({maxi,pre_maxi[a][0],pre_maxi[b][0]})};
}

void solve()
{
    ll n,q;
    cin>>n>>q;
    vector <vector <ll>> arr;
    ll c = 0;
    vll root(n+1,1);
    map <ll,pll> mp;
    fr(i,0,q){
        ll ch;
        cin>>ch;
        if(ch==1){
            ll a,b;
            cin>>a>>b;
            arr.pb({1,a,b,i});
            root[a] = 0;
        }
        else if(ch==2){
            c++;
            ll a;
            cin>>a;
            mp[c] = MP(a,i);
        }
        else
        {
            ll a,b;
            cin>>a>>b;
            arr.pb({3,a,b,i});
        }
    }
    g.clear();
    g.resize(n+1);
    vis.resize(n+1,0);
    depth.resize(n+1,0);
    fr(i,0,arr.size()){
        if(arr[i][0]==1){
            g[arr[i][2]].pb(MP(arr[i][1],arr[i][3]));
        }
    }
    ll comp = 0;
    fr(i,1,n+1){
        if(!vis[i] and root[i]) dfs(i,-1,-1,++comp,0);
    }

    fr(i,0,arr.size()){
        vll &v = arr[i];
        if(v[0]==3){
            ll x = v[1],d = v[2];
            auto res = lca(x,mp[d].ff);
            ll anc = res[0],maxi = res[1];
            if(res[0]==x and maxi<=mp[d].ss) yes;
            else no;
        }
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