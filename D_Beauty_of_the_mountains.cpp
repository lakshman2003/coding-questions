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

ll gcd(ll a,ll b){
    if(a==0 or b==0) return a+b;
    if(a<b) swap(a,b);
    return gcd(a%b,b);
}
void solve()
{
    ll n,m,k;
    cin>>n>>m>>k;
    v2ll grid(n,vll(m));
    fr(i,0,n)
    {
        fr(j,0,m) cin>>grid[i][j];
    }
    ll sa =0,sb = 0;
    v2ll cnt(n,vll(m,0));
    fr(i,0,n){
        fr(j,0,m){
            char x;
            cin>>x;
            cnt[i][j] = (x-'0');
            if(cnt[i][j]) sa+= grid[i][j];
            else sb+= grid[i][j];
            if(i) cnt[i][j]+= cnt[i-1][j];
            if(j) cnt[i][j]+= cnt[i][j-1];
            if(i and j) cnt[i][j]-= cnt[i-1][j-1];
        }
    }
    ll g = -1;
    fr(i,0,n)
    {
        fr(j,0,m)
        {
            if(i+k-1>=n) break;
            if(j+k-1>=m) break;
            ll x = cnt[i+k-1][j+k-1];
            if(i) x-= cnt[i-1][j+k-1];
            if(j) x-=cnt[i+k-1][j-1];
            if(i and j) x+= cnt[i-1][j-1];
            x = abs(2*x-k*k);
            if(g==-1) g = x;
            else g = gcd(g,x);
        }
    }
    if(abs(sa-sb)){
        if(g and abs(sa-sb)%g==0) yes;
        else no;
    }
    else yes;
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