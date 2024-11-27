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
    ll n, m, h;
    vector<vector<pll>> g;
    cin >> n >> m >> h;
    vll pos(n,0);
    fr(i,0,h){
        ll x;
        cin>>x;
        x--;
        pos[x] = 1;
    }
    g.clear();
    g.resize(n);
    fr(i,0,m){
        ll a,b,w;
        cin>>a>>b>>w;
        a--;b--;
        g[a].pb(MP(b,w));
        g[b].pb(MP(a,w));
    }

    priority_queue<vll> pq;
    pq.push({0, 0,0});
    v2ll dist1(n, vll(2,1e16));
    v2ll vis(n, vll(2,0));
    dist1[0][0] = 0;
    while (!pq.empty())
    {
        vll v = pq.top();
        ll w = -v[0],x = v[1],horse = v[2];
        pq.pop();
        if (vis[x][horse])
            continue;
        vis[x][horse] = 1;
        for (auto [nei, wei] : g[x])
        {
            if (dist1[nei][horse] > dist1[x][horse] + ((horse)?wei/2:wei))
            {
                dist1[nei][horse] = dist1[x][horse] + ((horse)?wei/2:wei);
                pq.push({-dist1[nei][horse], nei,horse});
            }
        }
        if (pos[x])
        {
            dist1[x][1] = min(dist1[x][1], w);
            pq.push({-dist1[x][1], x, 1});
        }
    }

    v2ll dist2(n, vll(2, 1e16));
    vis.clear();
    vis.assign(n,vll(2,0));
    dist2[n-1][0] = 0;
    pq.push({0, n-1, 0});
    while (!pq.empty())
    {
        vll v = pq.top();
        ll w = -v[0], x = v[1], horse = v[2];
        pq.pop();
        if (vis[x][horse])
            continue;
        vis[x][horse] = 1;
        for (auto [nei, wei] : g[x])
        {
            if (dist2[nei][horse] > dist2[x][horse] + ((horse) ? wei / 2 : wei))
            {
                dist2[nei][horse] = dist2[x][horse] + ((horse) ? wei / 2 : wei);
                pq.push({-dist2[nei][horse], nei, horse});
            }
        }
        if (pos[x]){
            dist2[x][1] = min(dist2[x][1],w);
            pq.push({-dist2[x][1], x, 1});
        }
    }

    ll mini = 1e16;
    fr(i,0,n){
        mini = min(mini,max(min(dist1[i][0],dist1[i][1]),min(dist2[i][0],dist2[i][1])));
    }
    if(mini>=1e16) mini = -1;
    cout<<mini<<en;
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