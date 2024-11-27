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

const ll maxn = 1e3+10;
pll arr[maxn][5];
ll n,m,dp[maxn][5];
string wanted = "narek";
ll rec(ll lvl,ll curr){
    if(lvl==n) {
        return -curr;
    }
    if(dp[lvl][curr]!=-1e15) return dp[lvl][curr];
    ll ans = rec(lvl+1,curr);
    ans = max(ans,rec(lvl+1,arr[lvl][curr].ss)+arr[lvl][curr].ff);
    return dp[lvl][curr] = ans;
}

void solve()
{
    cin>>n>>m;
    fr(k,0,n){
        string s;
        cin>>s;
        fr(i,0,5){
            ll curr = i;
            ll sc = 0;
            fr(j,0,s.size()){
                if(s[j]==wanted[curr]){
                    curr++;
                    if(curr==5){
                        sc+= 5;
                        curr=0;
                    }
                }
                else if(s[j]=='n' or s[j]=='a' or s[j]=='r' or s[j]=='e' or s[j]=='k') sc--;
            }
            arr[k][i] = MP(sc,curr);
        }
    }

    fr(i,0,n+1){
        fr(j,0,5) dp[i][j] = -1e15;
    }

    ll ans = rec(0,0);
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