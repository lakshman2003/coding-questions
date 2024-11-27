#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    indexed_set;

#define bigll __int128_t
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
#define v2ll vector<vector<ll>>
#define vpi vector<pii>
#define vpll vector<pll>
#define iset indexed_set
#define minpqll priority_queue<ll, vector<ll>, greater<ll>>
#define getv(v, n)             \
    for (ll i = 0; i < n; i++) \
        cin >> v[i];
#define get_pair(v, n)         \
    for (ll i = 0; i < n; i++) \
        cin >> v[i].ff >> v[i].ss;
#define fr(i, a, b) for (ll i = a; i < (b); i++)
#define fr_e(i, a, b) for (ll i = a; i <= b; i++)
#define fr_rev(i, a, b) for (ll i = (a); i >= b; i--)
#define all(v) v.begin(), v.end()
#define mod 1000000007
#define print(v) fr(i, 0, v.size()) cout << v[i] << " "
#define INF LLONG_MAX
#define yes cout << "YES\n"
#define no cout << "NO\n"
#define fast                      \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);
#define stp(n) cout << fixed << setprecision(n)
#define sz(v) 1LL * v.size()

inline ll add(ll a, ll b)
{
    a += b;
    if (a >= mod)
        a %= mod;
    return a;
}

inline ll mul(ll a, ll b)
{
    return ((a % mod) * (b % mod)) % mod;
}

inline ll bin_pow(ll a, ll b)
{
    ll ans = 1;
    while (b)
    {
        if (b % 2)
            ans = ans * a % mod;
        a = mul(a, a);
        b /= 2;
    }
    return ans;
}

inline ll inv(ll a)
{
    return bin_pow(a, mod - 2) % mod;
}

string a,b;
ll m;
map <vll,ll> mp;
ll req_len;
ll rec(ll lvl,ll lt,ll ht,ll prev,ll rem){
    if(lvl==-1){
        if(rem==0) return 1;
        else return 0;
    }
    if(mp.find({lvl,lt,ht,prev,rem})!=mp.end())
        return mp[{lvl, lt, ht, prev, rem}];
    ll ans = 0;
    if(lvl>=req_len){
        ll l = 0, r= 9;
        if (lt)
            l = max(l, (ll)(a[lvl] - '0'));
        if (ht)
            r = min(r, (ll)(b[lvl] - '0'));
        if(l==0){
            ll ntlo = 0, nthi = 0;
            if (lt and 0 == l)
                ntlo = 1;
            if (ht and 0 == r)
                nthi = 1;
            ans += rec(lvl - 1, ntlo, nthi, 0, (rem * 10 + 0) % m);
        }
    }
    else if(lvl<req_len and lvl>req_len/2)
    {
        ll l = max(prev, 1LL), r = 9;
        if (lt)
            l = max(l, (ll)(a[lvl] - '0'));
        if (ht)
            r = min(r, (ll)(b[lvl] - '0'));
        fr(i, l, r + 1)
        {
            ll ntlo = 0, nthi = 0;
            if (lt and i == l)
                ntlo = 1;
            if (ht and i == r)
                nthi = 1;
            ans += rec(lvl - 1, ntlo, nthi, i, (rem * 10 + i) % m);
        }
    }
    else if(lvl==req_len/2){
        ll l = prev+1,r = 9;
        if(lt) l = max(l,(ll)(a[lvl]-'0'));
        if(ht)
            r = min(r, (ll)(b[lvl] - '0'));
        fr(i,l,r+1) {
            ll ntlo = 0,nthi = 0;
            if(lt and i==l) ntlo = 1;
            if(ht and i==r) nthi = 1;
            ans+= rec(lvl-1,ntlo,nthi,i,(rem*10+i)%m);
        }
    }
    else if(lvl==req_len/2-1){
        ll l = 1, r = prev-1;
        if (lt)
            l = max(l, (ll)(a[lvl] - '0'));
        if (ht)
            r = min(r, (ll)(b[lvl] - '0'));
        fr(i, l, r + 1)
        {
            ll ntlo = 0, nthi = 0;
            if (lt and i == l)
                ntlo = 1;
            if (ht and i == r)
                nthi = 1;
            ans += rec(lvl-1, ntlo, nthi, i, (rem * 10 + i) % m);
        }
    }
    else{
        ll l = 1, r = prev;
        if (lt)
            l = max(l, (ll)(a[lvl] - '0'));
        if (ht)
            r = min(r, (ll)(b[lvl] - '0'));
        fr(i, l, r + 1)
        {
            ll ntlo = 0, nthi = 0;
            if (lt and i == l)
                ntlo = 1;
            if (ht and i == r)
                nthi = 1;
            ans += rec(lvl-1, ntlo, nthi, i, (rem * 10 + i) % m);
        }
    }
    
    return mp[{lvl, lt, ht, prev, rem}] = ans;
}

void solve(long long caseno)
{
    cin>>a>>b>>m;
    while(a.length()<20) a = '0'+a;
    while(b.length()<20) b= '0'+b;
    reverse(all(a));
    reverse(all(b));
    ll ans = 0;
    mp.clear();
    for (long long len = 1; len <= 20; len += 2)
    {
        req_len = len;
        mp.clear();
        ans+= rec(19,1,1,0,0);
    }
    cout << "Case #" << caseno << ": " << ans << en;
}


signed main()
{
    fast
        freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    long long t;
    cin >> t;
    fr(i, 1, t + 1)
    {
        solve(i);
    }
    return 0;
}