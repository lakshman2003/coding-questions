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
ll dp[110][110][3];
vll val;
ll n,tot,tot_odd;
vll pre_sum;
ll rec(ll lvl,ll odd,ll pre)
{
    if(lvl==n) return 0;
    if(pre!=-1 and dp[lvl][odd][pre]!=-1) return dp[lvl][odd][pre];
    ll even = (tot-tot_odd)-(((lvl)?pre_sum[lvl-1]:0)-(tot_odd-odd));
    ll ans = 1e10;
    if(val[lvl]!=0) ans= rec(lvl+1,odd,val[lvl]&1)+(pre!=-1 and pre!=(val[lvl]&1));
    else
    {
        if(odd) 
        {
            if(pre==-1) ans = min(ans,rec(lvl+1,odd-1,1));
            else ans = min(ans,(rec(lvl+1,odd-1,1)+(pre!=1)));
        }
        if(even)
        {
            if (pre == -1)
                ans = min(ans, rec(lvl + 1, odd , 0));
            else
                ans = min(ans, rec(lvl + 1, odd, 0) + (pre!=0));
        }
    }
    return dp[lvl][odd][pre] = ans;
}
void solve()
{
    cin>>n;
    val.resize(n);
    getv(val,n);
    tot = 0;
    fr(i,0,n) if(val[i]==0) tot++;
    ll odd = 0;
    set <ll> st;
    fr(i,0,n) st.insert(val[i]);
    fr(i,1,n+1) if(i&1LL and st.find(i)==st.end()) odd++;
    tot_odd = odd;
    memset(dp,-1,sizeof(dp));
    pre_sum.resize(n);
    pre_sum[0] = (val[0]==0);
    fr(i,1,n) pre_sum[i] = pre_sum[i-1]+(val[i]==0);
    cout<<rec(0,odd,-1)<<en;
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