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


ll dp[25][2][2][12];
string l,r;
ll rec(ll lvl,ll lti,ll hti,ll first){
    if(lvl==l.length()) return 1;
    if(dp[lvl][lti][hti][first]!=-1) return dp[lvl][lti][hti][first];
    ll lo = 0, hi = 9;
    if(lti) lo = l[lvl]-'0';
    if(hti) hi = r[lvl]-'0';
    if(first) hi = min(hi,first-1);
    ll ans = 0;
    fr_e(i,lo,hi) ans+= rec(lvl+1,lti&&(i==lo),hti&&(i==r[lvl]-'0'),max(first,i));
    return dp[lvl][lti][hti][first] = ans;
}

void solve()
{   
    cin>>l>>r;
    ll maxi = max(l.length(),r.length());
    while(l.length()<maxi) l = '0'+l;
    while(r.length()<maxi) r = '0'+r;
    memset(dp,-1,sizeof(dp));
    cout<<rec(0,1,1,0)<<en;
}

signed main(){
    fast
    solve();
    return 0;
}