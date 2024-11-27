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


void solve()
{
    ll n,a,b;
    cin>>n>>a>>b;
    string s;
    cin>>s;
    ll x = 0,y = 0;
    fr(i,0,n) {
        if(s[i]=='N') y++;
        else if(s[i]=='S') y--;
        else if(s[i]=='E') x++;
        else x--;
    }
    ll p = 0,q = 0;
    fr(i,0,n){
        if (s[i] == 'N')
            q++;
        else if (s[i] == 'S')
            q--;
        else if (s[i] == 'E')
            p++;
        else p--;
        if(p==a and q==b){
            yes;
            return;
        }
        if(x==0 and y==0) continue;
        if(x==0){
            if((b-q)%y==0 and (b-q)/y>=0 and p==a) {
                yes;
                return;
            }
        }
        else if(y==0){
            if((a-p)%x==0 and (a-p)/x>=0 and q==b){
                yes;
                return;
            }
        }
        else{
            if((a-p)%x==0 and (b-q)%y==0 and (a-p)/x==(b-q)/y and (a-p)/x>=0){
                yes;
                return;
            }
        }
    }
    no;
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