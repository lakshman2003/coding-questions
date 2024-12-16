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

ll dp[501][50001][2];
void solve()
{
    ll n,x,k;
    cin>>n>>x>>k;
    v2ll items(n);
    fr(i,0,n){
        ll p,u,c;
        cin>>p>>u>>c;
        items[i] = {c,p,u};
    }
    sort(all(items));
    items.pb({n+1,0,0});
    fr(i,0,n){
        fr(j,0,x+1){
            fr(l,0,2){
                dp[i][j][l] = -1;
            }
        }
    }
    auto rec = [&](auto &self,ll lvl,ll rem,ll flag)->ll{
        ll ans = 0;
        if (flag and lvl and items[lvl][0] != items[lvl - 1][0])
            ans += k;
        if(lvl==n) return ans;
        if(dp[lvl][rem][flag]!=-1) return dp[lvl][rem][flag];
        ll new_flag = flag;
        if(lvl and items[lvl][0]!=items[lvl-1][0]) new_flag =0;
        ll p = items[lvl][1],u = items[lvl][2];
        ll maxi = self(self,lvl+1,rem,new_flag);
        if(p<=rem) maxi = max(maxi,self(self,lvl+1,rem-p,1)+u);
        return dp[lvl][rem][flag] = maxi+ans;
    };
    cout<<rec(rec,0,x,0)<<en;
}

signed main(){
    fast
    solve();
    return 0;
}