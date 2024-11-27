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
    ll n,x;
    cin>>n>>x;
    vll a(n),p(n),b(n),q(n);
    fr(i,0,n) cin>>a[i]>>p[i]>>b[i]>>q[i];
    
    auto find_min = [](ll a,ll p,ll b,ll q,ll req)->ll{
        ll ans = INT64_MAX;
        fr(i,0,b+1){
            ll c1 = i*p;
            ll c2 = ((max(0LL,req-i*a)+b-1)/b)*q;
            ans = min(ans,c1+c2);
        }
        fr(i, 0, a + 1)
        {
            ll c1 = i * q;
            ll c2 = ((max(0LL,req - i * b) + a - 1) / a) * p;
            ans = min(ans, c1 + c2);
        }
        return ans;
    };
    ll lo = 0;
    ll hi = mod;
    ll ans = 0;
    while(lo<=hi){
        ll mid = (lo+hi)>>1;
        ll s = 0;
        fr(i,0,n){
            s+= find_min(a[i],p[i],b[i],q[i],mid);
            if(s>x) break;
        }
        if(s<=x){
            ans = mid;
            lo = mid+1;
        }
        else hi = mid-1;
    }
    cout<<ans<<en;
}

signed main(){
    fast
    solve();
    return 0;
}