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
    ll n,k,q;
    cin>>n>>k>>q;
    v2ll v(k,vll(n,0));
    fr(i,0,n){
        fr(j,0,k) {
            cin>>v[j][i];
            if(i) v[j][i]|= v[j][i-1];
        }
    }
    while(q--){
        ll m;
        cin>>m;
        ll lo= 0,hi = n-1;
        fr(i,0,m){
            ll r,c;
            char ch;
            cin>>r>>ch>>c;
            r--;
            if(ch=='<'){
                auto it = lower_bound(all(v[r]),c);
                if(it==v[r].begin()) hi = -1;
                else hi = min(hi,(ll)(it-v[r].begin())-1);
            }
            else{
                auto it = upper_bound(all(v[r]), c);
                if (it == v[r].end())
                    lo = n;
                else
                    lo = max(lo,(ll)(it-v[r].begin()));
            }
        }
        if(lo<=hi) cout<<lo+1<<en;
        else cout<<-1<<en;
    }
}

signed main(){
    fast
    ll t = 1;
    while(t--)
    {
        solve();
    }
    return 0;
}