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
    ll n;
    cin>>n;
    vll v(n);
    getv(v,n);
    map <ll,ll> mp;
    fr(i,0,n) mp[v[i]]++;
    vll arr,pre;
    for(auto [x,y]:mp)
    {
        arr.pb(x);
        pre.pb(y);
    }
    n = arr.size();
    fr(i,1,n) pre[i]+= pre[i-1];
    ll ans = 0;
    fr(i,0,n)
    {
        ll x = 1;
        while(1)
        {
            ll l = lower_bound(all(arr),arr[i]*x)-arr.begin();
            if(l==n) break;
            if(arr[l]/arr[i]!=x)
            {
                x = arr[l]/arr[i];
                continue;
            }
            ll r= lower_bound(all(arr),arr[i]*(x+1))-arr.begin();
            r--;
            if(r>=l) ans+= x*(pre[i]-((i>0)?pre[i-1]:0))*(pre[r]-((l>0)?pre[l-1]:0));
            if(l==i) 
            {
                ll c =(pre[i] - ((i > 0) ? pre[i - 1] : 0));
                ans-= ((c+1)*(c))/2;
            }
            x++;
        }
    }
    cout<<ans<<en;
}

signed main(){
    fast
    solve();
    return 0;
}