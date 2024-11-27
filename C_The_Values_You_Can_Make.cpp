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
    ll n,k;
    cin>>n>>k;
    vll v(n);
    getv(v,n);
    vector <vector<vector <bool>>> dp;
    dp.resize(2);
    for(int i = 0;i<2;i++){
        dp[i].resize(501);
        for(int j= 0;j<501;j++) dp[i][j].resize(501,false);
    }
    dp[0][0][0] = true;
    for(int i = 1;i<=n;i++){
        for(int j=0;j<501;j++){
            for(int k = 0;k<501;k++){
                dp[i&1][j][k] = dp[(i-1)&1][j][k];
                if (v[i - 1] <= j and dp[(i - 1) & 1][j - v[i - 1]][k])
                    dp[i & 1][j][k] = true;
                if (v[i - 1] <= k and dp[(i - 1) & 1][j][k - v[i - 1]])
                    dp[i & 1][j][k] = true;
            }
        }
    }
    vll ans;
    fr_e(i,0,k){
        if(dp[n&1][i][k-i]) ans.pb(i);
    }
    cout<<ans.size()<<en;
    print(ans);
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