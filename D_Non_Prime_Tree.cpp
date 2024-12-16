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

const ll maxn = 4e5+10;
vector<bool> primes(maxn,true);
vll choices;
void pre(){
    primes[1] = 0;
    for(ll i = 2; i*i<maxn;i++){
        if(primes[i]){
            for(ll j = i*i;j<maxn;j+=i){
                primes[j] = 0;
            }
        }
    }
    fr(i,1,maxn){
        if(!primes[i]) choices.pb(i);
    }
}
void solve()
{
    ll n;
    cin>>n;
    v2ll g(n);
    fr(i, 0, n - 1) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        g[u].pb(v);
        g[v].pb(u);
    }
    set <ll> avail;
    fr(i,1,2*n+1) avail.insert(i);
    vll ans(n,0);
    ll maxi = 0;
    auto dfs = [&](auto &self,ll node,ll p)->void{
        ll ind = 0;
        for(auto nei:g[node]){
            if(nei==p) continue;
            while(avail.find(ans[node]+choices[ind])==avail.end()) ind++;
            ans[nei] = ans[node]+choices[ind];
            avail.erase(ans[nei]);
        }
        for(auto nei:g[node]){
            if(nei==p) continue;
            self(self,nei,node);
        }
    };
    ans[0] = 1;
    avail.erase(1);
    dfs(dfs,0,-1);
    print(ans);
    cout<<en;
}

signed main(){
    fast
    pre();
    ll t;
    cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}