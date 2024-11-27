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
    vll v(n);
    getv(v,n);
    vll dp(n,1e14);
    map <ll,ll> mp;
    fr(i,0,k) mp[v[i]-i]++;
    map <ll,set<ll>> freq;
    for(auto [x,y]:mp) freq[y].insert(x);
    fr(i,k,n){
        dp[i-k] = k-freq.rbegin()->ff;
        ll curr_freq = mp[v[i-k]-(i-k)];
        mp[v[i-k]-(i-k)]--;
        if(mp[v[i-k]-(i-k)]==0) mp.erase(v[i-k]-(i-k));
        freq[curr_freq].erase(v[i-k]-(i-k));
        if(freq[curr_freq].size()==0) freq.erase(curr_freq);
        curr_freq--;
        if(curr_freq) freq[curr_freq].insert(v[i-k]-(i-k));

        curr_freq = mp[v[i]-i];
        mp[v[i]-i]++;
        if(curr_freq) {
            freq[curr_freq].erase(v[i]-i);
            if(freq[curr_freq].size()==0) freq.erase(curr_freq);
        }
        freq[curr_freq+1].insert(v[i]-i);
    }
    dp[n- k] = k - freq.rbegin()->ff;

    vll pre(n,0);
    pre[0]= dp[0];
    fr(i,1,n) pre[i] = pre[i-1]+dp[i];
    while(q--){
        ll l,r;
        cin>>l>>r;
        l--;r--;
        cout<<pre[r-k+1]-((l)?pre[l-1]:0)<<en;
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