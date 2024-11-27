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
    ll n,m,L;
    cin>>n>>m>>L;
    map <ll,vpll> mp;
    fr(i,0,n)
    {
        ll x,y;
        cin>>x>>y;
        mp[x].pb(MP(y,-1));
    }
    fr(i,0,m)
    {
        ll x,y;
        cin>>x>>y;
        mp[x].pb(MP(y,1));
    }
    mp[L].pb(MP(0,0));
    multiset <ll> st;
    ll curr = 1;
    ll cap = 1;
    ll s = 0;
    ll ans = 0;
    while(curr<L){
        if(mp[curr].size()){
            if(mp[curr].size()==1 and mp[curr][0].ss==-1){
                ll y = mp[curr][0].ff;
                if(s+cap<y-curr+2){
                    cout<<-1<<en;
                    return;
                }
                while (cap < y - curr + 2)
                {
                    auto it = --st.end();
                    s -= *it;
                    cap += *it;
                    st.erase(it);
                    ans++;
                }
                curr = y+1;
            }
            else {
                for(auto [x,y]:mp[curr]){
                    st.insert(x);
                    s+= x;
                }
                curr = mp.upper_bound(curr)->ff;
            }
        }
        else if(curr<L) curr = mp.upper_bound(curr)->ff;
    }
    cout<<ans<<en;
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