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
    vll waiting;
    fr(i,0,m){
        ll u,v;
        cin>>u>>v;
        if(u and v){
            g[u].pb(v);
            g[v].pb(u);
        }
        else{
            waiting.pb(u+v);
        }
    }
    sort(all(waiting));
    vll distn(n+1,1e9),dist1(n+1,1e9);
    dist1[1] = 0;
    queue<ll> q;
    q.push(1);
    while(!q.empty()){
        ll u = q.front();
        q.pop();
        for(auto v:g[u]){
            if(dist1[v] > dist1[u] + 1){
                dist1[v] = dist1[u] + 1;
                q.push(v);
            }
        }
    }
    distn[n] = 0;
    q.push(n);
    while(!q.empty()){
        ll u = q.front();
        q.pop();
        for(auto v:g[u]){
            if(distn[v] > distn[u] + 1){
                distn[v] = distn[u] + 1;
                q.push(v);
            }
        }
    }
    ll mn1 = 1e9,mnn = 1e9;
    for(auto x:waiting){
        mn1 = min(mn1,dist1[x]);
        mnn = min(mnn,distn[x]);
    }
    ll ind = -1;
    fr(i,1,n+1){
        ll ans = dist1[n];
        ll d1 = min(dist1[i],mn1+1);
        ll d2 = min(distn[i],mnn+1);
        ans = min(ans,d1+d2);
        if(ans>m) ans = -1;
        cout<<ans<<" ";
    }
}

signed main(){
    fast
    solve();
    return 0;
}