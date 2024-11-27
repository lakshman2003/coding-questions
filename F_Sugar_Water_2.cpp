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
    ll n,m,k;
    cin>>n>>m>>k;
    vpll arr1(n),arr2(m);
    fr(i,0,n) cin>>arr1[i].ff>>arr1[i].ss;
    fr(i,0,m) cin>>arr2[i].ff>>arr2[i].ss;
    long double lo = 0;
    long double hi = 100;
    long double ans = lo;
    while(abs(lo-hi)>1e-10){
        long double mid = (lo+hi)/2;
        long double p = mid/100;
        vector <long double> t;
        fr(i,0,m) t.push_back(arr2[i].ff*(1-p)-arr2[i].ss*p);
        sort(all(t));
        ll c = 0;
        fr(i,0,n){
            long double val = arr1[i].ff*(p-1)+p*arr1[i].ss;
            ll x = t.end()-lower_bound(all(t),val);
            c+=x;
        }
        if(c>=k){
            ans = mid;
            lo = mid+1e-10;
        }
        else hi= mid-1e-10;
    }
    cout<<ans<<en;
}

signed main(){
    fast
    stp(20);
    solve();
    return 0;
}