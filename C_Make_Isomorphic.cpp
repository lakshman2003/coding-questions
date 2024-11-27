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
    v2ll g1(n,vll(n,0)),g2(n,vll(n,0));
    v2ll cost(n,vll(n,0));
    ll m1;
    cin>>m1;
    set <pll> edges;
    fr(i,0,m1){
        ll a,b;
        cin>>a>>b;
        a--;b--;
        g1[a][b] = g1[b][a] = 1;
        edges.insert(MP(a,b));
    }
    ll m2;
    cin>>m2;
    fr(i,0,m2){
        ll a,b;
        cin>>a>>b;
        a--;b--;
        g2[a][b] = g2[b][a] = 1;
    }

    fr(i,0,n){
        fr(j,i+1,n){
            cin>>cost[i][j];
            cost[j][i] = cost[i][j];
        }
    }
    vll p;
    fr(i,0,n) p.pb(i);
    ll ans = 1e18;
    do{
        ll c = 0;
        fr(i,0,n){
            fr(j,i+1,n){
                if((g2[p[i]][p[j]] ^ g1[i][j])){
                    c+= cost[p[i]][p[j]];
                }
            }
        }
        ans = min(ans,c);
    }while(next_permutation(all(p)));

    cout<<ans<<en;
}

signed main(){
    fast
    solve();
    return 0;
}