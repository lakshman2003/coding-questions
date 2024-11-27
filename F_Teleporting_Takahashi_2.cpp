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

v2ll g;
ll n,m,k;
vll special,comp,rev_comp;
const ll maxn = 2e5+10;
ll dp[110][maxn];
ll dist(ll x,ll y){
    if(y>x) return y-x;
    return y+1+(n-1-x);
}

ll rec(ll ind,ll left){
    if(left<=0) return 1;
    if(dp[ind][left]!=-1) return dp[ind][left];
    ll curr = comp[ind];
    auto it = upper_bound(all(special),curr);
    if(it==special.end()) it = special.begin();
    ll ans = rec(rev_comp[*it],left-dist(curr,*it));
    for(auto nei:g[curr]){
        (ans+= rec(rev_comp[nei],left-1))%=mod;
    }
    return dp[ind][left] = ans;
}

void solve()
{
    cin>>n>>m>>k;
    g.resize(n);
    comp.resize(n);
    rev_comp.resize(n);
    vll t(n,0);
    t[0] = 1;
    fr(i,0,m){
        ll a,b;
        cin>>a>>b;
        a--;b--;
        g[a].pb(b);
        t[a] = t[b] = 1;
    }   
    fr(i,0,110){
        fr(j,0,k+1) dp[i][j] = -1;
    }
    fr(i,0,n) if(t[i]) special.pb(i);
    for(ll i=0;i<1LL*special.size();i++) {
        comp[i] = special[i];
        rev_comp[special[i]] = i;
    }
    if(m==0) cout<<1<<en;
    else cout<<rec(0,k)<<en;
}

signed main(){
    fast
    solve();
    return 0;
}