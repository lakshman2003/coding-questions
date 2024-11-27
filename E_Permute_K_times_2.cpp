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

inline ll mul(ll a,ll b,ll m)
{
    return ((a%m)*(b%m))%m;
}

inline ll bin_pow(ll a,ll b,ll m)
{
    ll ans=1;
    while(b)
    {
        if(b%2) ans=ans*a%m;
        a=mul(a,a,m);
        b/=2;
    }
    return ans;
}

inline ll inv(ll a)
{
    return bin_pow(a,mod-2,mod)%mod;
}


void solve()
{
    ll n,k;
    cin>>n>>k;
    vll v(n);
    getv(v,n);
    fr(i,0,n) v[i]--;
    vll vis(n,0);
    vll ans(n);
    fr(i,0,n){
        if(vis[i]) continue;
        vll ind,val;
        ind.pb(i);
        vis[i] = 1;
        ll curr = v[i];
        while(1){
            if(vis[curr]) break;
            ind.pb(curr);
            vis[curr] = 1;
            curr = v[curr];
        }
        ll offset = (bin_pow(2,k,ind.size())-1+ind.size())%ind.size();
        fr(j,0,ind.size()){
            ans[ind[j]] = v[ind[(j+offset)%ind.size()]];
        }
    }
    fr(i,0,n) ans[i]++;
    print(ans);
    cout<<en;
}

signed main(){
    fast
    solve();
    return 0;
}