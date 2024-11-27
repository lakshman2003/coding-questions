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

ll arr[101][101][101];
void solve()
{
    ll n;
    cin>>n;
    fr(i,0,n){
        fr(j,0,n){
            fr(k,0,n) cin>>arr[i][j][k];
        }
    }
    fr(k,0,n){
        fr(i,0,n){
            fr(j,0,n) {
                if(i) arr[i][j][k]+= arr[i-1][j][k];
                if(j) arr[i][j][k]+= arr[i][j-1][k];
                if(i and j) arr[i][j][k]-= arr[i-1][j-1][k];
            }
        }
    }
    ll q;
    cin>>q;
    while(q--){
        ll a,b,c,p,q,r;
        cin>>a>>p>>b>>q>>c>>r;
        a--;b--;c--;p--;q--;r--;
        ll ans = 0;
        fr(k,c,r+1){
            ans+= arr[p][q][k];
            if(a) ans-= arr[a-1][q][k];
            if(b) ans-= arr[p][b-1][k];
            if(a and b) ans+= arr[a-1][b-1][k];
        }
        cout<<ans<<en;
    }
}

signed main(){
    fast
    solve();
    return 0;
}