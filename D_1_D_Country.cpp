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
    vll x(n);
    vll p(n);
    getv(x,n);
    getv(p,n);
    map <ll,ll> comp;
    fr(i,0,n) comp[x[i]];
    ll sz= 0;
    for(auto &[x,y]:comp) y = sz++;
    vll pre(sz,0);
    fr(i,0,n) pre[comp[x[i]]]+= p[i];
    fr(i,1,sz) pre[i]+= pre[i-1];
    ll q;
    cin>>q;
    while(q--){
        ll a,b;
        cin>>a>>b;
        ll l,r;
        auto it1 = comp.upper_bound(b);
        if(it1==comp.end())  r = sz-1;
        else if(it1==comp.begin()) {
            cout<<0<<en;
            continue;
        }
        else {
            it1--;
            r = it1->ss;
        }
        auto it2 = comp.lower_bound(a);
        if(it2==comp.end()) {
            cout<<0<<en;
            continue;
        }
        else l = it2->ss;
        if(l<=r) cout<<pre[r] - ((l)?pre[l-1]:0)<<en;
        else cout<<0<<en;
    }
}

signed main(){
    fast
    solve();
    return 0;
}