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
    ll n,k;
    cin>>n>>k;
    vll poss2(3*n+1,0),pre2(3*n+1,0);
    fr(i,2,2*n+1){
        ll l = max(i-n,1LL),r = min(i-1, n);
        poss2[i] = (r-l+1);
    }
    fr(i,2,3*n+1){
        pre2[i] = pre2[i-1]+poss2[i];
    }
    vll poss3(3*n+1,0),pre3(3*n+1,0);
    fr(i,3,3*n+1){
        ll l = max(i-n,2LL),r = min(i-1, 2*n);
        poss3[i] = pre2[r]-pre2[l-1];
        pre3[i] = pre3[i-1]+poss3[i];
    }
    auto it = lower_bound(all(pre3),k);
    ll sum = it-pre3.begin();
    k-=pre3[sum-1];
    ll lo = 1, hi = n, x1 = 0;
    while(lo<=hi){
        ll mid = (lo+hi)/2;
        ll cnt = pre2[sum-1]-((sum-mid-1>=0)?pre2[sum-mid-1]:0);
        if(cnt<k){
            x1 = mid;
            lo = mid+1;
        }
        else hi = mid-1;
    }
    x1++;
    if(x1-1>=1){
        k-= pre2[sum-1]-((sum-x1>=0)?pre2[sum-x1]:0);
    }
    sum-=x1;
    ll l = max(sum-n,1LL),r = min(sum-1,n);
    ll x2 = l+k-1;
    ll x3= sum-x2;
    cout<<x1<<" "<<x2<<" "<<x3<<en;
}

signed main(){
    fast
    solve();
    return 0;
}