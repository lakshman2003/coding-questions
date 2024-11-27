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

v2ll v;
ll dp[1010][110];
ll rec(ll lvl,ll left){
    if(left<=0) return 0;
    if(lvl==v.size()) return 1e16;
    if(dp[lvl][left]!=-1) return dp[lvl][left];
    ll ans = rec(lvl+1,left);
    ll s = 0;
    fr(i,0,v[lvl].size()){
        s+= v[lvl][i];
        ll rem = left-(i+1);
        if(i==v[lvl].size()-1) rem--;
        ans = min(ans,rec(lvl+1,rem)+s);
    }
    return dp[lvl][left] = ans;
}
void solve()
{
    ll n,k;
    cin>>n>>k;
    v.clear();
    v.resize(n);
    fr(i,0,n){
        ll a,b;
        cin>>a>>b;
        if(b<a) swap(a,b);
        while(a){
            v[i].pb(a);
            b--;
            if(b<a) swap(a,b);
        }
    }
    fr(i,0,n+1){
        fr(j,0,k+1) dp[i][j] = -1;
    }
    ll ans = rec(0,k);
    if(ans>=1e12) ans = -1;
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