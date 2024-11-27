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
    ll x1,y1,x2,y2;
    cin>>x1>>y1>>x2>>y2;
    vll pre_even = {2,1,0,1};
    vll pre_odd= {1,2,1,0};
    ll n_odd,n_even;
    n_odd = n_even = (y2-y1)/2;
    if((y2-y1)&1) 
    {
        if(y1&1) n_odd++;
        else n_even++;
    }

    ll odd_extra = 0;
    ll even_extra = 0;
    ll r1 = x1 % 4;
    if (x1 < 0)
        r1 = 4 + r1;

    ll r2 = x2%4;
    if(x2<0) r2 = 4+r2;
    if(r1)
    {
        for (int i = r1; i < 4; i++)
        {
            odd_extra += pre_odd[i];
            even_extra += pre_even[i];
        }
    }
    if(r2)
    {
        for (int i = 0; i < r2; i++)
        {
            odd_extra += pre_odd[i];
            even_extra += pre_even[i];
        }
    }

    ll ans = (x2- (r2?r2:0) - (x1+(r1?(4-r1):0)));
    ans*= (y2-y1);
    ans+= odd_extra*n_odd + even_extra*n_even;
    cout<<ans<<en;
}

signed main(){
    fast
    solve();
    return 0;
}