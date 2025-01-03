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
    ll n,q;
    cin>>n>>q;
    v2ll grid(n,vll(n));
    fr(i,0,n){
        fr(j,0,n){
            cin>>grid[i][j];
        }
    }
    v2ll p1(n,vll(n)),p2(n,vll(n)),p3(n,vll(n));
    fr(i,0,n){
        fr(j,0,n){
            p1[i][j] = grid[i][j];
            p2[i][j] = grid[i][j]*i;
            p3[i][j] = grid[i][j]*j;
            if(i) {
                p1[i][j] += p1[i-1][j];
                p2[i][j] += p2[i-1][j];
                p3[i][j] += p3[i-1][j];
            }
            if(j){
                p1[i][j] += p1[i][j-1];
                p2[i][j] += p2[i][j-1];
                p3[i][j] += p3[i][j-1];
            }
            if(i and j){
                p1[i][j] -= p1[i-1][j-1];
                p2[i][j] -= p2[i-1][j-1];
                p3[i][j] -= p3[i-1][j-1];
            }
        }
    }
    while(q--){
        ll x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        x1--,y1--,x2--,y2--;
        ll col = y2-y1+1;

        ll s1 = p1[x2][y2];
        if(x1) s1 -= p1[x1-1][y2];
        if(y1) s1 -= p1[x2][y1-1];
        if(x1 and y1) s1 += p1[x1-1][y1-1];

        ll s2 = p2[x2][y2];
        if(x1) s2 -= p2[x1-1][y2];
        if(y1) s2 -= p2[x2][y1-1];
        if(x1 and y1) s2 += p2[x1-1][y1-1];

        ll s3 = p3[x2][y2];
        if(x1) s3 -= p3[x1-1][y2];
        if(y1) s3 -= p3[x2][y1-1];
        if(x1 and y1) s3 += p3[x1-1][y1-1];

        ll ans = s3+s2*col-(col*x1+y1-1)*s1;
        cout<<ans<<" ";
    }
    cout<<en;
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