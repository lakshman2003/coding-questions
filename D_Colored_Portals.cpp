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
    ll n,q;
    cin>>n>>q;
    map <char,ll> mp;
    mp['B'] = 0;
    mp['G'] = 1;
    mp['R'] = 2;
    mp['Y'] = 3;
    v2ll g;
    g.resize(n);
    map <vll,vll> arr;
    fr(i,0,n){
        string s;
        cin>>s;
        g[i].pb(mp[s[0]]);
        g[i].pb(mp[s[1]]);
        sort(all(g[i]));
        arr[g[i]].pb(i);
    }  

    while(q--){
        ll a,b;
        cin>>a>>b;
        a--;b--;
        if(a>b) swap(a,b);
        ll ans = 1e9;
        for(auto x:g[a]){
            for(auto y:g[b]){
                if(x==y) {
                    ans = min(ans,b-a);
                    break;
                }
            }
        }
        if(ans==1e9){
            for(auto i:g[a]){
                for(auto j:g[b]){
                    vll temp;
                    temp.pb(i);
                    temp.pb(j);
                    sort(all(temp));
                    vll &v = arr[temp];
                    if(v.size()){
                        auto it = upper_bound(all(v),a);
                        if(it!=v.end()){
                            ans = min(ans,abs(*it-a)+abs(*it-b));
                        }
                        it = lower_bound(all(v), a);
                        if (it != v.begin())
                        {
                            it--;
                            ans = min(ans, a - *it + b - *it);
                        }
                    }
                }
            }
        }
        if(ans==1e9) ans = -1;
        cout<<ans<<en;
    }
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