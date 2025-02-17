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

ll dist[1005][1005][2];
void solve()
{
    ll h,w;
    cin>>h>>w;
    vector <string> grid(h);
    fr(i,0,h) cin>>grid[i];
    ll xs,ys,xg,yg;
    fr(i,0,h){
        fr(j,0,w){
            if(grid[i][j]=='S') xs = i, ys = j;
            if(grid[i][j]=='G') xg = i, yg = j;
        }
    }
    queue <vll> q;
    auto check = [&](ll x, ll y){
        if(x>=0 && x<h && y>=0 && y<w and grid[x][y]!='#') return 1;
        return 0;
    };
    fr(i,0,h){
        fr(j,0,w){
            dist[i][j][0] = dist[i][j][1] = INF;
        }
    }
    dist[xs][ys][0] = 0;
    dist[xs][ys][1] = 0;
    ll dx[]= {0,0,1,-1};
    ll dy[]= {1,-1,0,0};
    q.push({xs,ys,0});
    q.push({xs,ys,1});
    while(!q.empty()){
        vll cur = q.front();
        q.pop();
        ll x = cur[0], y = cur[1], z = cur[2];
        if(z==0){
            fr(i,0,2){
                ll nx = x+dx[i], ny = y+dy[i];
                if(check(nx,ny) and dist[nx][ny][z^1]>dist[x][y][z]+1){
                    dist[nx][ny][z^1] = dist[x][y][z]+1;
                    q.push({nx,ny,z^1});
                }
            }
        }
        else{
            fr(i,2,4){
                ll nx = x+dx[i], ny = y+dy[i];
                if(check(nx,ny) and dist[nx][ny][z^1]>dist[x][y][z]+1){
                    dist[nx][ny][z^1] = dist[x][y][z]+1;
                    q.push({nx,ny,z^1});
                }
            }
        }
    }
    ll ans = min(dist[xg][yg][0],dist[xg][yg][1]);
    if(ans==INF) cout<<-1<<en;
    else cout<<ans<<en;

}

signed main(){
    fast
    solve();
    return 0;
}