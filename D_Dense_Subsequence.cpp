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
    ll m;
    cin>>m;
    string s;
    cin>>s;
    ll n = s.length();
    v2ll pos(26);
    fr(i,0,n) pos[s[i]-'a'].pb(i);
    vll vis(n,0);
    string ans = "";
    fr(j,0,26){
        bool f = true;
        v2ll dp(n+10,vll(2,1e10));
        multiset <ll> mt1,mt2;
        fr(i,0,n){
            if((s[i]-'a')==j){
                dp[i][1] = 1 + ((i>m-1) ? *mt1.begin() : 0);
                dp[i][0] = ((i>=m-1 and mt2.size()) ? *mt2.begin() : 1e10);
            }
            else
            {
                if(vis[i])
                    dp[i][1] = ((i >m-1) ? *mt1.begin() : 0);
                else
                    dp[i][0] = ((i >= m - 1 and mt2.size()) ? *mt2.begin() : 1e10);
            }
            mt1.insert(dp[i][1]);
            if (i - m >= 0){
                mt1.erase(mt1.find(dp[i - m][1]));
            }
            mt2.insert(dp[i][1]);
            if (i - m + 1 >= 0)
            {
                mt2.erase(mt2.find(dp[i - m + 1][1]));
            }
        }
        ll req = min(dp[n-1][1],dp[n-1][0]);
        if(req>=1e6) {
            req = pos[j].size();
            f = false;
        }
        fr(i,0,req) ans+= ('a'+j);
        if(f) break;
        for(auto x:pos[j]) vis[x] = 1;
    }
    cout<<ans<<en;
}

signed main(){
    fast
    ll t =1;
    while(t--)
    {
        solve();
    }
    return 0;
}