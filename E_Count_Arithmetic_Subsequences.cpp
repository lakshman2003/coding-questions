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
vll v;
ll dp[81][81][81][81];
ll rec(ll level,ll p1, ll p2,ll cnt){
    if(cnt==0) return 1;
    if(level==v.size()) 
    {
        if(cnt) return 0;
        else return 1;
    }
    if(dp[level][p1][p2][cnt]!=-1) return dp[level][p1][p2][cnt];
    ll ans = rec(level+1,p1,p2,cnt);
    if(p1==-1){
        (ans+= rec(level+1,level,p1,cnt-1))%=mod;
    }
    else
    {
        if(p2==-1) (ans+= rec(level+1,level,p1,cnt-1))%=mod;
        else
        {
            if(v[level]-v[p1]==v[p1]-v[p2]) (ans+= rec(level+1,level,p1,cnt-1))%=mod;
        }
    }
    return dp[level][p1][p2][cnt]= ans;
}
void solve()
{
    ll n;
    cin>>n;
    v.resize(n);
    getv(v,n);
    memset(dp,-1,sizeof(dp));
    fr(i,1,n+1){
        cout<<rec(0,-1,-1,i)<<" ";
    }
}

signed main(){
    fast
    solve();
    return 0;
}