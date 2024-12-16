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


class Union_Find
{
    public:
    ll n;
    vll par,rank;
    ll comp;
    
    Union_Find(ll x = 0)
    {
        n = x;
        par.resize(n);
        rank.resize(n,1);
        fr(i,0,n) par[i] = i;
        comp = n;
    }

    ll find(ll x)
    {
        if(par[x]==x) return x;
        return par[x] = find(par[x]);
    }

    void unite(ll a,ll b)
    {
        a = find(a);
        b = find(b);
        if(a==b) return;
        if(rank[a]<rank[b]) swap(a,b);
        rank[a]+= rank[b];
        par[b] = a;
        comp--;
    }
};


void solve()
{
    ll n,m,k;
    cin>>n>>m>>k;
    v2ll edges;
    fr(i,0,m){
        ll a,b,w;
        cin>>a>>b>>w;
        a--,b--;
        edges.pb({w,a,b});
    }
    sort(all(edges));
    Union_Find dsu(n);
    vll cnta(n,0),cntb(n,0);
    vll a(k),b(k);
    getv(a,k);
    getv(b,k);
    fr(i,0,k) {
        a[i]--;
        b[i]--;
    }
    fr(i,0,k){
        cnta[a[i]]++;
        cntb[b[i]]++;
    }
    ll ans = 0;
    for(auto arr:edges){
        ll w = arr[0],u = arr[1],v = arr[2];
        u = dsu.find(u);
        v = dsu.find(v);
        if(u!=v){
            ll ta = cnta[u]+cnta[v];
            ll tb = cntb[u]+cntb[v];
            ll t = min(ta,tb);
            ans+= t*w;
            if(dsu.rank[u]<dsu.rank[v]) swap(u,v);
            cnta[u]+=cnta[v]-t;
            cntb[u]+=cntb[v]-t;
            dsu.unite(u,v);
        }
    }
    cout<<ans<<en;
}

signed main(){
    fast
    solve();
    return 0;
}