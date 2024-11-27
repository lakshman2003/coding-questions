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

vector <set <ll>> g;
void dfs(ll node,ll p,vll &dist,ll d){
    dist[node] = d;
    for(auto nei:g[node]){
        if(nei==p) continue;
        dfs(nei,node,dist,d+1);
    }
}   

void solve()
{
    ll n;
    cin>>n;
    g.resize(n+1);
    vpll edges;
    fr(i,0,n-1){
        ll a,b;
        cin>>a>>b;
        g[a].insert(b);
        g[b].insert(a);
        edges.pb(MP(a,b));
    }

    auto get_largest = [&](ll node){
        vll dist(n+1,-1);
        dfs(node,0,dist,0);
        ll maxi = 0;
        fr(i,1,n+1) {
            if(dist[i]!=-1){
                if(maxi==0) maxi = i;
                else if(dist[i]>dist[maxi]) maxi = i;
            }
        }
        dist.resize(n+1,-1);
        dfs(maxi,0,dist,0);
        maxi = *max_element(all(dist));
        return maxi;
    };
    
    ll ans = 0;
    for(auto [a,b]:edges){
        g[a].erase(b);
        g[b].erase(a);
        ll x = get_largest(a),y= get_largest(b);
        ans = max(ans,x*y);
        g[a].insert(b);
        g[b].insert(a);
    }
    cout<<ans<<en;

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