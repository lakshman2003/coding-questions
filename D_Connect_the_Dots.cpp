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

vll dp[15][15];
vpll updates[15][15];
class Union_Find
{
    public:
    ll n;
    vll par,rank;
    ll comp;
    
    Union_Find(ll x = 0)
    {
        n = x;
        par.resize(n+1);
        rank.resize(n+1,1);
        fr(i,1,n+1) par[i] = i;
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
    ll n,m;
    cin>>n>>m;
    fr(i,0,11) {
        fr(j,0,11) {
            dp[i][j].clear();
            updates[i][j].clear();
        }
    }
    fr(i,1,n+1){
        fr(j,1,11) dp[j][i%j].pb(i);
    }

    fr(i,0,m){
        ll a,d,k;
        cin>>a>>d>>k;
        updates[d][a%d].pb(MP(a,1));
        updates[d][a%d].pb(MP(a+d*k,-1));
    }

    Union_Find dsu(n);
    fr(i,1,11){
        fr(j,0,i){
            vpll &arr = updates[i][j];
            sort(all(arr));
            deque<ll> dq;
            map <ll,vll> mp;
            for(auto [x,y]:arr) mp[x].pb(y);
            for(auto &[x,y]:mp) sort(y.rbegin(),y.rend());
            for(auto x:dp[i][j]){
                if(dq.size()) {
                    dsu.unite(dq.front(), x);
                }
                if (mp.find(x) != mp.end())
                {
                    for (auto y : mp[x])
                    {
                        if (y == 1)
                            dq.push_back(x);
                        else
                            dq.pop_front();
                    }
                }
            }
        }
    }

    cout<<dsu.comp<<en;

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