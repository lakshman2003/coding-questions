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

v2ll g;
vll dist,par;
void dfs(ll node,ll p,ll d){
    par[node] =p;
    dist[node] = d;
    for(auto nei:g[node]){
        if(nei==p) continue;
        dfs(nei,node,d+1);
    }
}

void solve()
{
    ll n;
    cin>>n;
    g.clear();
    g.resize(n+1);
    map <pll,ll> mp;
    map <ll,pll> rev_mp;
    fr(i,0,n-1){
        ll a,b;
        cin>>a>>b;
        g[a].pb(b);
        g[b].pb(a);
        mp[MP(a,b)] = i;
        mp[MP(b,a)] = i;
        rev_mp[i] = MP(a,b);
    }
    par.resize(n+1,0);
    dist.resize(n+1,0);
    dfs(1,0,0);
    ll maxi = 0;
    ll maxi_node = 0;
    fr(i,1,n+1){
        if(maxi<dist[i]){
            maxi = dist[i];
            maxi_node = i;
        }
    }
    dfs(maxi_node,0,0);
    ll end_node = 0;
    maxi = 0;
    fr(i,1,n+1){
        if(maxi<dist[i]){
            maxi = dist[i];
            end_node= i;
        }
    }
    
    vll covered(n-1,0);
    ll curr = end_node;
    ll c = n-1;
    while(curr!=maxi_node){
        covered[mp[MP(curr,par[curr])]] = 1;
        c--;
        curr = par[curr];
    }

    cout<<
    vll extra_nodes;
    fr(i,0,n-1){
        if(!covered[i])
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