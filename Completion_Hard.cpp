#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    indexed_set;

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
#define mod 998244353
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

const ll maxn = 4e5 + 10;
ll fac[maxn];

void solve()
{
    ll n;
    cin >> n;
    vll v(2 * n, 0);
    getv(v, 2 * n);
    ll r1 = n, r2 = n, c = 0;
    fr(i, 0, 2 * n)
    {
        if (v[i])
        {
            if (v[i] <= n)
                r1--;
            else
                r2--;
        }
        else
            c++;
        i++;
    }

    ll ans = 1;
    ans = mul(ans, mul(fac[r2], inv(fac[r1 + r2 - n])));
    ans = mul(ans, mul(fac[r1], inv(fac[r1 + r2 - n])));
    ans = mul(ans, fac[c]);
    ans = mul(ans, fac[c]);
    ans = mul(ans, bin_pow(2, c));
    cout << ans << en;
}

signed main()
{
    fast
        fac[0] = 1;
    fr(i, 1, maxn) fac[i] = mul(fac[i - 1], i);
    ll t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}