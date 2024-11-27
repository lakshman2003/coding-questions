#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<int>, rb_tree_tag,
tree_order_statistics_node_update> indexed_set;

#define ll long long
#define int ll
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
int findMaxSum(vll  arr, int n)
{
    // Arrays for maintaining left and right count
    vll CL(n,0), CR(n,0);

    // Stack for storing the indexes
    stack<int> q;

    // Calculate left count for every index
    for (int i = 0; i < n; i++)
    {
        while (q.size() != 0 && arr[q.top()] <= arr[i])
        {
            CL[i] += CL[q.top()] + 1;
            q.pop();
        }
        q.push(i);
    }

    // Clear the stack
    while (q.size() != 0)
        q.pop();

    // Calculate right count for every index
    for (int i = n - 1; i >= 0; i--)
    {
        while (q.size() != 0 && arr[q.top()] < arr[i])
        {
            CR[i] += CR[q.top()] + 1;
            q.pop();
        }
        q.push(i);
    }

    // Clear the stack
    while (q.size() != 0)
        q.pop();

    // To store the required sum
    int ans = 0;

    // Calculate the final sum
    for (int i = 0; i < n; i++)
        ans += (CL[i] + 1) * (CR[i] + 1) * arr[i];

    return ans;
}

void solve()
{
    ll n;
    cin>>n;
    vll v(n);
    getv(v,n);
    ll ans = findMaxSum(v,n);
    cout<<ans<<en;
    fr(i,0,n)
    {
        ans+= (i+1) - ((i+1)*(i+2))/2;
    }
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