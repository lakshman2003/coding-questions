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


void solve()
{
    ll n;
    cin>>n;
    v2ll g(n+1);
    vll a(n+1);
    fr(i,1,n+1){
        ll p;
        cin>>p>>a[i];
        if(p!=-1){
            g[p].pb(i);
        }
    }
    v2ll dp(n+1,vll(2,0));
    auto dfs = [&](auto &self,ll node,ll p)->void{
        vpll arr;
        for(auto nei:g[node]){
            self(self,nei,node);
            arr.pb({dp[nei][0],dp[nei][1]});
        }
        sort(all(arr),[&](pll a,pll b){
            return a.ss-a.ff>b.ss-b.ff;
        });
        ll t0 = 0;
        ll ch = arr.size();
        for(auto &[x,y]:arr) t0+=x;
        dp[node][0] = t0;
        ll t1 = 0;
        fr(i,0,ch){
            t0-=arr[i].ff;
            t1+= arr[i].ss;
            if(i&1) dp[node][0] = max(dp[node][0],t0+t1);
            else dp[node][1] = max(dp[node][1],t0+t1);
        }
        dp[node][1] = max(dp[node][1],a[node]+dp[node][0]);
    };

    dfs(dfs,1,-1);
    cout<<max(dp[1][0],dp[1][1])<<en;

}

signed main(){
    fast
    solve();
    return 0;
}