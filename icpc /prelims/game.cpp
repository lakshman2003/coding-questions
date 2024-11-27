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
#define mod 998244353
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

const ll maxn = 4000100;
int dp[maxn][25];
ll cost[25];

ll rec (ll score, ll lvl) 
{
    if (score==0)
        return 1;
    if(lvl>=22 or score<4)
        return 0; 
    if(dp[score][lvl]!=-1)
        return dp[score][lvl];
    ll ans = rec(score,lvl+1);
    ll currscore = cost[lvl];
    if(currscore!=0 and currscore<=score)
        (ans += (rec(score - currscore, lvl))) %= mod;
    return dp[score][lvl] = ans;
};

signed main(){
    fast
    ll t;
    cin>>t;
    cost[1]= 0;
    fr(i,2,25){
        cost[i] = (1LL<<i)+2*cost[i-1];
    }
    
    fr(i,0,23) dp[0][i] = 1;
    fr(i,4,maxn){
        fr_rev(j,22,2){
            dp[i][j] = dp[i][j+1];
            ll currscore = cost[j];
            if(i>=currscore){
                (dp[i][j]+= dp[i-currscore][j])%=mod;
            }
        }
    }

    while(t--)
    {
        ll n;
        cin>>n;
        if(n<4)
        {
            cout<<0<<en;
            continue;
        }
        cout<<dp[n][2]<<en;
    }
    return 0;
}