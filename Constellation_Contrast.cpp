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
    ll n,m;
    cin>>n>>m;
    vll a(n+1),b(m+1);
    fr(i,1,n+1) cin>>a[i];
    fr(i,1,m+1) cin>>b[i];
    vll maxa(n+1),mina(n+1,1e18),maxb(m+1),minb(m+1,1e18);
    fr(i,1,n+1) {
        maxa[i] = max(maxa[i-1],a[i]);
        mina[i] = min(mina[i-1],a[i]);
    }
    fr(i, 1, m + 1)
    {
        maxb[i] = max(maxb[i - 1], b[i]);
        minb[i] = min(minb[i - 1], b[i]);
    }
    v2ll dp(n+m+10,vll(n+2,-1));
    auto rec = [&](auto &self,ll lvl,ll pa)->ll{
        ll pb = lvl-pa+1;
        if(lvl==n+m+1) return 0;
        if(dp[lvl][pa]!=-1) return dp[lvl][pa];
        ll ans = 0;
        if(pa<=n) {
            ll maxi = max(maxa[pa],maxb[pb-1]);
            ll mini = min(mina[pa],minb[pb-1]);
            ans = max(ans,self(self,lvl+1,pa+1)+maxi-mini);
        }
        if(pb<=m){
            ll maxi = max(maxa[pa-1], maxb[pb]);
            ll mini = min(mina[pa-1], minb[pb]);
            ans = max(ans, self(self, lvl + 1, pa) + maxi - mini);
        }
        return dp[lvl][pa] = ans;
    };
    ll ans = rec(rec,1,1);
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