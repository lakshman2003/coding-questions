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

ll n;
v2ll g;
const ll maxn = 2e5+10;
ll par[maxn][22],depth[maxn];
void dfs(ll node,ll p,ll d){
    par[node][0] = p;
    fr(i,1,21) par[node][i] = par[par[node][i-1]][i-1];
    depth[node] = d;
    for(auto nei:g[node]){
        if(nei==p) continue;
        dfs(nei,node,d+1);
    }
}

ll lca(ll a,ll b){
    if(a==b) return a;
    if(depth[a]>depth[b]) swap(a,b);
    ll diff = depth[b] - depth[a];
    fr_rev(i,20,0) {
        if(diff&(1LL<<i)){
            b = par[b][i];
        }
    }
    if(a==b) return a;
    fr_rev(i,20,0){
        if(par[a][i]!=par[b][i]){
            a = par[a][i];
            b = par[b][i];
        }
    }
    return par[a][0];
}


void solve()
{
    cin>>n;
    g.clear();
    g.resize(n+1);
    fr(i,0,n-1){
        ll a,b;
        cin>>a>>b;
        g[a].pb(b);
        g[b].pb(a);
    }
    fr(i,1,n+1) {
        depth[i] = 0;
    }

    fr(i,1,n+1){
        fr(j,0,21) par[i][j] = 0;
    }
    dfs(1,0,0);

    ll q;
    cin>>q;
    while(q--){
        ll x;
        cin>>x;
        vll v(x);
        getv(v,x);
        bool ok = true;
        auto comp = [&](ll a,ll b){
            return depth[a]>depth[b];
        };
        sort(all(v),comp);
        vll v1,v2;
        fr(i,0,x){
            if(v1.empty()) v1.pb(v[i]);
            else
            {
                if(lca(v1.back(),v[i])==v[i]) v1.pb(v[i]);
                else if(v2.empty()) v2.pb(v[i]);
                else if(lca(v2.back(),v[i])==v[i]) v2.pb(v[i]);
                else {
                    ok = false;
                    break;
                }
            }
        }
        if(!v1.empty() and !v2.empty()){
            if (lca(v1[0], v2[0]) != lca(v1.back(), v2.back())) ok = false;
        }
        if(ok) yes;
        else no;
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