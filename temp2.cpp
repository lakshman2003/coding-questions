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

vector <pair<ll,ll>>pos;
ll n;
ll dp[2010][2010][3];
ll rec(ll lvl,ll ind,ll who){
    if(lvl==n+2) return 0;
    if(dp[lvl][ind][who]!=-1)
        return dp[lvl][ind][who];
    auto dist = [](pll p1, pll p2) -> ll
    {
        return abs(p1.ff - p2.ff) + abs(p1.ss - p2.ss);
    };
    pair<long,long> alice, bob;
    ll ans = 1e16;
    if(who==0) {
        alice= pos[ind];
        bob = pos[lvl-1];
        ans = min(ans, rec(lvl + 1, ind, 0) + dist(bob, pos[lvl]));
        ans = min(ans,rec(lvl+1,lvl-1,1)+dist(alice,pos[lvl]));
    }
    else{
        bob = pos[ind];
        alice = pos[lvl - 1];
        ans = min(ans, rec(lvl + 1, ind, 1) + dist(alice, pos[lvl]));
        ans = min(ans, rec(lvl + 1, lvl - 1, 0) + dist(bob, pos[lvl]));
    }
    return dp[lvl][ind][who] = ans;
}

void solve()
{
    cin>>n;
    pll alice,bob;
    cin>>alice.ff>>alice.ss>>bob.ff>>bob.ss;
    pos.clear();
    pos.pb(alice);
    pos.pb(bob);
    fr(i,0,n){
        ll x,y;
        cin>>x>>y;
        pos.pb(MP(x,y));
    }
    fr(i,0,n+3){
        fr(j,0,n+3) {
            fr(k,0,3) dp[i][j][k] = -1;
        }
    }
    ll ans = rec(2,0,0);
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