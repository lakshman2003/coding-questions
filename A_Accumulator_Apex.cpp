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
    ll x, k;
    cin >> x >> k;
    v2ll arr(k);
    fr(i, 0, k) {
        ll n;
        cin >> n;
        arr[i].resize(n);
        fr(j, 0, n) cin >> arr[i][j];
    }
    multiset<vll> mt;
    vll pos(k + 1, -1);
    auto inc = [&](auto &v, ll ind) -> vll {
        ll sc = 0, maxi = 0;
        while (sc <= 0 && ind + 1 < v.size()) {
            sc += v[ind + 1];
            maxi = max(maxi, -sc);
            ind++;
        }
        return sc > 0 ? vll{maxi, sc, ind} : vll{-1, -1, -1};
    };
    fr(i, 0, k) {
        vll v = inc(arr[i], -1);
        if (v[1] > 0) mt.insert({v[0], v[1], v[2], i});
        pos[i] = v[2];
    }
    ll curr = x;
    while (!mt.empty()) {
        auto x = *mt.begin();
        mt.erase(mt.begin());
        ll maxi = x[0], sc = x[1], ind = x[2], i = x[3];
        if (curr >= maxi) {
            curr += sc;
            vll v = inc(arr[i], ind);
            if (v[1] > 0) mt.insert({v[0], v[1], v[2], i});
            pos[i] = v[2];
        } else break;
    }
    cout << curr << en;
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