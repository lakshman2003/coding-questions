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
    ll n,m;
    cin>>n>>m;
    v2ll g(n+1);
    fr(i,0,n-1){
        ll a,b;
        cin>>a>>b;
        g[a].pb(b);
        g[b].pb(a);
    };
    v2ll par(n+1,vll(21));
    vll depth(n+1,0);
    auto dfs1 = [&](auto &self,ll node,ll p,ll d)->void{
        par[node][0] = p;
        depth[node] = d;
        fr(i,1,20){
            par[node][i] = par[par[node][i-1]][i-1];
        }
        for(auto nei:g[node]){
            if(nei==p) continue;
            self(self,nei,node,d+1);
        }
    };

    dfs1(dfs1,1,0,0);
    auto find_lca = [&](ll a,ll b)->ll{
        if(a==b) return a;
        if(depth[a]<depth[b]) swap(a,b);
        ll d = depth[a]-depth[b];
        fr_rev(i,20,0){
            if(d&(1<<i)) a = par[a][i];
        }
        if(a==b) return a;
        fr_rev(i,20,0){
            if(par[a][i]!=par[b][i]){
                a = par[a][i];
                b = par[b][i];
            }
        }
        return par[a][0];
    };


    vll val(n+1);
    fr(i,0,m){
        ll a,b;
        cin>>a>>b;
        ll lca = find_lca(a,b);
        val[a]++;
        val[b]++;
        val[lca]--;
        val[par[lca][0]]--;
    }

    auto dfs2 = [&](auto &self,ll node,ll p)->void{
        for(auto nei:g[node]){
            if(nei==p) continue;
            self(self,nei,node);
            val[node]+=val[nei];
        }
    };

    dfs2(dfs2,1,0);
    fr_e(i,1,n) cout<<val[i]<<" ";
}

signed main(){
    fast
    solve();
    return 0;
}