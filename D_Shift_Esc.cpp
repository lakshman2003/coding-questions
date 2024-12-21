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

ll dp[201][201][201][2];
void solve()
{
    ll n,m,k;
    cin>>n>>m>>k;
    v2ll grid(n,vll(m));
    fr(i,0,n)
    {
        fr(j,0,m)
        {
            cin>>grid[i][j];
            fr(rot, 0, m)
            {
                fr(f, 0, 2)
                {
                    dp[i][j][rot][f] = -1;
                }
            }
        }
    }
    auto rec = [&](auto &self,ll i,ll j,ll rot,ll f)->ll{
        if(rot==m) return INF;
        if (dp[i][j][rot][f] != -1)
            return dp[i][j][rot][f];
        if(!f)
            return dp[i][j][rot][f] = min(k * rot + self(self, i, j, rot, 1), 
                                            self(self, i, j, rot + 1, 0));
        if(i==n-1 and j==m-1) {
            return grid[i][(j+rot)%m];
        }
        ll ans = INF;
        if(j+1<m) ans = min(ans,self(self,i,j+1,rot,1));
        if(i+1<n) ans = min(ans,self(self,i+1,j,0,0));
        return dp[i][j][rot][f] = ans+grid[i][(j+rot)%m];
    };
    cout<<rec(rec,0,0,0,0)<<en;
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