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


void solve()
{
    ll n, m, t0, t1, t2;
    cin>>n>>m>>t0>>t1>>t2;
    vector <vector <pll>> g1(n+1),g2(n+1);
    fr(i,0,m){
        ll a,b,l1,l2;
        cin>>a>>b>>l1>>l2;
        g1[a].pb(MP(b,l1));
        g1[b].pb(MP(a,l1));
        g2[a].pb(MP(b,l2));
        g2[b].pb(MP(a,l2));
    }

    auto dijkstra = [&](ll src, vector<vector<pll>> &g){
        vll dist(n+1,1e18);
        priority_queue <pll> pq;
        pq.push(MP(0,src));
        dist[src] = 0;
        while(!pq.empty()){
            auto [x,y] = pq.top();
            pq.pop();
            for(auto [nei,wei]:g[y]){
                if(dist[nei]>dist[y]+wei){
                    dist[nei] = dist[y]+wei;
                    pq.push(MP(-dist[nei],nei));
                }
            }
        }
        return dist;
    };

    auto distb1 = dijkstra(1,g1);
    auto distbn = dijkstra(n,g1);

    auto check = [&](ll mid){
        vll nodes;
        fr(i,1,n+1) if(distb1[i]<=max(0LL,t1-mid))nodes.pb(i);
        for(auto x:nodes){
            g2[x].pb(MP(0,distb1[x]));
            g2[0].pb(MP(x, distb1[x]));
        }
        auto dist = dijkstra(0,g2);
        bool flag = false;
        fr(i,1,n+1) if(distbn[i]+max(dist[i],t2-mid)<=t0-mid) flag = true;
        g2[0].clear();
        for(auto x:nodes){
            g2[x].pop_back();
        }
        return flag;
    };

    ll lo= 0;
    ll hi = t0;
    ll ans = -1;
    while(lo<=hi){
        ll mid = (lo+hi)/2;
        if(check(mid)){
            ans = mid;
            lo = mid+1;
        }
        else hi = mid-1;
    }
    cout<<ans<<en;
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