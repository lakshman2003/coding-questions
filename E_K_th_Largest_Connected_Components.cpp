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

v2ll arr;
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
        fr(i,0,n) {
            par[i] = i;
            arr[i] = {i};
        }
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
        vll temp;
        for(auto x:arr[b]) temp.pb(x);
        for(auto x:arr[a]) temp.pb(x);
        sort(all(temp));
        reverse(all(temp));
        while(temp.size()>10) temp.pop_back();
        arr[a] = temp;
        comp--;
    }
};

void solve()
{
    ll n,q;
    cin>>n>>q;
    arr.resize(n);
    Union_Find uf(n);
    while(q--){
        ll op;
        cin>>op;
        if(op==1){
            ll u,v;
            cin>>u>>v;
            u--;v--;
            uf.unite(u,v);
        }
        else
        {
            ll u,k;
            cin>>u>>k;
            u--;
            u = uf.find(u);
            if(arr[u].size()<k) cout<<-1<<en;
            else cout<<arr[u][k-1]+1<<en;
        }
        
    }
}

signed main(){
    fast
    solve();
    return 0;
}