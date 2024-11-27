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

    auto query = [](ll l,ll r){
        cout<<"xor "<<l<<" "<<r<<endl;
        ll ans;
        cin>>ans;
        return ans;
    };

    ll abc = query(1,n);
    map<ll, ll> mp;
    mp[n] = abc;
    ll lo = 1, hi = n;
    ll c = hi;
    
    while(lo<=hi){
        ll m1 = lo+ (hi-lo)/3,m2 = lo+2*(hi-lo)/3;
        ll q1,q2;
        if(mp.find(m1)!=mp.end()) q1 = mp[m1];
        else q1 = query(1,m1);
        mp[m1] = q1;
        if (mp.find(m2)!=mp.end()) q2 = mp[m2];
        else q2 = query(1,m2);
        mp[m2] = q2;
        if(q2==abc and q1!=abc){
            c = m2;
            hi = m2-1;
            lo = m1+1;
        }
        else if(q2==abc and q1==abc){
            c = m2;
            lo = m2+1;
        }
        else lo = m2+1;
    }
    ll ab = query(1,c-1);
    mp[c-1] = ab;
    lo = 2,hi = c-1;
    ll b = hi;
    while (lo <= hi)
    {
        ll mid = (lo + hi) >> 1;
        ll q;
        if(mp.find(mid)!=mp.end()) q = mp[mid];
        else q = query(1, mid);
        mp[mid] = q;
        if (q == ab)
        {
            b = mid;
            hi = mid - 1;
        }
        else
            lo = mid + 1;
    }
    ll a = query(1,b-1);
    cout<<"ans "<<a<<" "<<b<<" "<<c<<endl;
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