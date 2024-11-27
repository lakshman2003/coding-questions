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

ll v[10];
pair <vll,ll> dp[10][2010];
pair <vll,ll> rec(ll lvl,ll rem){
    if(lvl==0){
        if(rem) return MP(vll(10,0),-1);
        return MP(vll(10,0),0);
    }
    if(dp[lvl][rem].ss!=-100) return dp[lvl][rem];
    pair <vll,ll> ans = MP(vll(10,0),-1);
    pair <vll,ll> ans1= rec(lvl-1,rem);
    if(ans1.ss!=-1) ans = ans1;
    fr_e(i,1,rem/v[lvl]){
        pair<vll, ll> ans2 = rec(lvl, rem - i*v[lvl]);
        if (ans2.ss != -1 and ans.ss<=ans2.ss+i)
        {
            ans = ans2;
            ans.ss+= i;
            ans.ff[lvl]+= i;
        }
    }
    return dp[lvl][rem] = ans;
}
void solve()
{
    ll k;
    cin>>k;
    fr(i,1,10) cin>>v[i];
    fr(i,0,10){
        fr(j,0,k+5) dp[i][j] = MP(vll(10,0),-100);
    }
    
    string ans = "IMPOSSIBLE";
    if(rec(9,k).ss!=-1) {
        ans = "";
        vll freq = rec(9,k).ff;
        fr_rev(i,9,1) {
            fr(j,1,freq[i]+1) ans+= char('0'+i);
        }
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