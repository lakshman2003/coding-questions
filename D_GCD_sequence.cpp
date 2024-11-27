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
    ll n;
    cin>>n;
    vll v(n);
    getv(v,n);
    vll b(n);
    fr(i,0,n-1) b[i] = __gcd(v[i],v[i+1]);
    vll suff(n);
    suff[n-1] = suff[n-2] = 1;
    fr_rev(i,n-3,0)
    {
        suff[i] = suff[i+1]&(b[i]<=b[i+1]);
    }

    bool ans = false;
    fr(i,0,n)
    {
        bool ok = true;
        if(i>=2) 
        {
            if(i+1<n and b[i-2]>__gcd(v[i-1],v[i+1])) ok = false;
            if(i+2<n and __gcd(v[i-1],v[i+1])>b[i+1]) ok = false;
        }
        if(i==1 and i+2<n)
        {
            if(__gcd(v[i-1],v[i+1])>b[i+1]) ok = false;
        }
        if(i<n-1) if(!suff[i+1]) ok = false;
        if(ok) ans = true;
        if(i>=2) if(b[i-2]>b[i-1]) break;
        // if(ans) cout<<i<<en;
    }
    if(ans) yes;
    else no;
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