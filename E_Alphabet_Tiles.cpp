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
#define mod 998244353
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

ll k;
ll dp[26][1010],fac[1010],invfac[1010],c[26];
ll rec(ll level,ll tot)
{
    if(tot>k) return 0;
    if(level==26) 
    {
        if(tot) return fac[tot];
        else return 0;
    }
    if(dp[level][tot]!=-1) return dp[level][tot];
    ll ans = 0;
    fr(i,0,min(k-tot,c[level])+1)
    {
        (ans+= mul(rec(level+1,tot+i),invfac[i]))%=mod;
    }
    return dp[level][tot] = ans;
}
void solve()
{
    cin>>k;
    fr(i,0,26) cin>>c[i];
    fr(i,0,26) fr(j,0,k+1) dp[i][j] = -1;
    ll ans = rec(0,0);
    cout<<ans<<en;
}

signed main(){
    fast
    fac[0] = fac[1] = 1;
    fr(i,2,1010) fac[i] = mul(fac[i-1],i);
    fr(i,0,1010) invfac[i] = inv(fac[i]);
    solve();
    return 0;
}