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

v2ll points;
ll n,s,t;
ldd dist(ll x1,ll y1,ll x2,ll y2){
    return sqrt((ldd)(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
ldd dp[1LL<<7][7][2];
ldd rec(ll mask,ll last,ll end){
    if(mask==0) return 0;
    if(dp[mask][last][end]!=-1)
        return dp[mask][last][end];
    ll x= points[last][2*end],y = points[last][2*end+1];
    ldd ans = 1e9;
    fr(i,0,n+1){
        if(mask&(1LL<<i)){
            ll xx1 = points[i][0],yy1 = points[i][1];
            ll xx2 = points[i][2],yy2 = points[i][3];
            ldd t3 = dist(xx1,yy1,xx2,yy2)/t;
            ldd t1 = dist(xx1,yy1,x,y)/s;
            ldd t2 = dist(xx2,yy2,x,y)/s;
            ans= min(ans,t3+t1+rec(mask^(1LL<<i),i,1));
            ans = min(ans,t3+t2+rec(mask^(1LL<<i),i,0));
        }
    }
    return dp[mask][last][end] = ans;
}
void solve()
{
    cin>>n>>s>>t;
    points.pb({0,0,0,0});
    fr(i,0,n){
        ll x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        points.pb({x1,y1,x2,y2});
    }
    fr(i,0,1LL<<7){
        fr(j,0,7) {
            fr(k,0,2) dp[i][j][k] =-1.0;
        }
    }
    ll mask = (1LL<<(n+1))-1;
    mask = mask^1;
    ldd ans = rec(mask,0,0);
    cout<<ans<<en;
}

signed main(){
    fast
    stp(12);
    solve();
    return 0;
}