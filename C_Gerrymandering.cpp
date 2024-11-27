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
const ll maxn = 1e5+10;
ll dp[maxn][2][2][2][2];
ll n;
vll v1,v2;
ll rec(ll lvl,ll p1,ll p2,ll q1, ll q2){
    if(lvl==n){
        if(p1 or p2 or q1 or q2) return -1e9;
        return 0;
    }
    if (dp[lvl][p1][p2][q1][q2] != -1) return dp[lvl][p1][p2][q1][q2];
    ll ans = -1e9;
    auto find = [](ll a,ll b,ll c)->ll{
        vll cnt(3,0);
        cnt[a]++;cnt[b]++;cnt[c]++;
        return cnt[1]>cnt[2];
    };
    if (p1 and p2)
    {
        if(q1 and q2){
            ans = max(ans, find(v1[lvl - 2], v1[lvl - 1], v1[lvl]) + find(v2[lvl - 2], v2[lvl - 1], v2[lvl]) + rec(lvl + 1, 0, 0, 0, 0));
            ans = max(ans, find(v1[lvl - 2], v2[lvl - 2], v2[lvl - 1]) + find(v1[lvl - 1], v1[lvl], v2[lvl]) + rec(lvl + 1, 0, 0, 0, 0));
            ans = max(ans, find(v1[lvl - 2], v2[lvl - 2], v1[lvl - 1]) + find(v2[lvl - 1], v1[lvl], v2[lvl]) + rec(lvl + 1, 0, 0, 0, 0));
        }
        if(q1) ans = max(ans, find(v1[lvl - 2], v2[lvl - 2], v1[lvl - 1]) + rec(lvl + 1, 0, q2, 1, 1));
        if(q2) ans = max(ans, find(v1[lvl - 2], v2[lvl - 2], v2[lvl - 1]) + rec(lvl + 1, q1, 0, 1, 1));
    }
    else if(p1){
        if (q1) ans = max(ans, find(v1[lvl - 2], v1[lvl - 1], v1[lvl]) + rec(lvl + 1, 0, q2, 0, 1));
        if(q1 and q2) ans = max(ans, find(v1[lvl - 2], v1[lvl - 1], v2[lvl - 1]) + rec(lvl + 1, 0, 0, 1, 1));
    }
    else if(p2){
        if(q2) ans = max(ans, find(v2[lvl - 2], v2[lvl - 1], v2[lvl]) + rec(lvl + 1, q1, 0, 1, 0));
        if (q1 and q2) ans = max(ans, find(v2[lvl - 2], v2[lvl - 1], v1[lvl - 1]) + rec(lvl + 1, 0, 0, 1, 1));
    }
    else if(q1){
        if(!q2) ans =  max(ans,find(v1[lvl-1],v1[lvl],v2[lvl])+rec(lvl+1,0,0,0,0));
        ans = max(ans,rec(lvl + 1, q1, q2, 1, 1));
    }
    else if(q2){
        ans = max(ans,rec(lvl + 1, q1, q2, 1, 1));
        if(!q1) ans = max(ans, find(v2[lvl - 1], v1[lvl], v2[lvl]) + rec(lvl + 1, 0, 0, 0, 0));
    }
    else ans = max(ans,rec(lvl+1,q1,q2,1,1));
    return dp[lvl][p1][p2][q1][q2] = ans;
}
void solve()
{
    cin>>n;
    v1.clear();
    v2.clear();
    string t1,t2;
    cin>>t1>>t2;
    for(auto x:t1) {
        if(x=='A') v1.pb(1);
        else v1.pb(2);
    }
    for (auto x : t2)
    {
        if (x == 'A')
            v2.pb(1);
        else
            v2.pb(2);
    }
    fr(i,0,n){
        fr(p1,0,2){
            fr(p2,0,2){
                fr(q1,0,2){
                    fr(q2,0,2)
                        dp[i][p1][p2][q1][q2]= -1;
                }
            }
        }
    }
    ll ans = rec(0,0,0,0,0);
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