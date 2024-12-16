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
    ll h,w,x;
    cin>>h>>w>>x;
    ll p, q;
    cin >> p >> q;
    p--;q--;
    v2ll grid(h, vll(w));
    fr(i,0,h){
        fr(j,0,w){
            cin>>grid[i][j];
        }
    }
    ll curr = grid[p][q];
    ll dx[] = {1,-1,0,0};
    ll dy[] = {0,0,1,-1};
    priority_queue <pair<ll,pll>, vector<pair<ll,pll>>, greater<pair<ll,pll>>> pq;
    fr(i,0,4){
        ll nx = p + dx[i];
        ll ny = q + dy[i];
        if(nx>=0 && nx<h && ny>=0 && ny<w){
            pq.push({grid[nx][ny],{nx,ny}});
        }
    }
    vector <vector<bool>> vis(h,vector<bool>(w,false));
    vis[p][q] = true;
    while(!pq.empty()){
        auto top = pq.top();
        ll val = top.first;
        pll curr_pos = top.second;
        pq.pop();
        if(vis[curr_pos.ff][curr_pos.ss]) continue;
        vis[curr_pos.ff][curr_pos.ss] = true;
        __int128_t t = x;
        t*=val;
        if(t>= curr) continue;
        curr += val;
        fr(i,0,4){
            ll nx = curr_pos.ff + dx[i];
            ll ny = curr_pos.ss + dy[i];
            if(nx >= 0 && nx < h && ny >= 0 && ny < w ){
                pq.push({grid[nx][ny],{nx,ny}});
            }
        }
    }
    cout<< curr << en;
    
}

signed main(){
    fast
    solve();
    return 0;
}