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

ll dp[2010][2010][3][2];
string s;
ll rec(ll l,ll r,ll lead,ll move,ll prev)
{
    if(l>r) return lead;
    if(dp[l][r][lead][prev]!=-1) return dp[l][r][lead][prev];
    ll ans = 0;
    if(move==0)
    {
        ll c1 = rec(l+1,r,lead,move^1,0);
        ll c2 = rec(l,r-1,lead,move^1,1);
        if(c1==1 or c2==1) ans = 1;
        else if(c1==0 or c2==0) ans = 0;
        else ans = 2;
    }

    else
    {
        char x = ((prev==0)?s[l-1]:s[r+1]);
        ll c1,c2;
        ll l1 = lead;
        if(s[l]>x) l1 = 2;
        else if(s[l]<x) l1 = 1;

        ll l2 = lead;
        if(s[r]>x) l2 = 2;
        else if(s[r]<x) l2 = 1;
        c1= rec(l+1,r,l1,move^1,0);
        c2 = rec(l,r-1,l2,move^1,1);

        if (c1 == 2 or c2 == 2)
            ans = 2;
        else if (c1 == 0 or c2 == 0)
            ans = 0;
        else
            ans = 1;
    }
    return dp[l][r][lead][prev] = ans;
}
void solve()
{
    cin>>s;
    ll n = s.length();
    fr(i,0,n+1)
    {
        fr(j,0,n+1)
        {
            fr(k,0,3)
            {
                fr(l,0,2) dp[i][j][k][l] = -1;
            }
        }
    }
    ll ans = rec(0,n-1,0,0,0);
    if(ans==1) cout<<"Alice"<<en;
    else if(ans==2) cout<<"Bob"<<en;
    else cout<<"Draw"<<en;
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