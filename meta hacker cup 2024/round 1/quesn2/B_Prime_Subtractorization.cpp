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

const ll maxn = 1e7+5;
bool isprime[maxn+1];
ll ans[maxn+1];

void pre(){
    isprime[0] = false;
    isprime[1] = false;
    fr(i,2,maxn) isprime[i] = true;
    for(ll i = 4;i<maxn;i+=2) isprime[i] = false;
    for(ll i = 3;i*i<=maxn;i++){
        if(isprime[i]){
            for(ll j = i*i;j<=maxn;j+=i){
                isprime[j] = false;
            }
        }
    }

    vll all_primes;
    fr(i,2,maxn) if(isprime[i]) all_primes.pb(i);

    vll mini(maxn,1e9);
    mini[2] = 5;
    for(auto x:all_primes){
        if(isprime[x-2]) {
            mini[x - 2] = x;
        }
    }

    fr(i,1,maxn) {
        if(mini[i]!=1e9) ans[mini[i]]++;
    }

    fr(i,2,maxn) ans[i]+= ans[i-1];
}
void solve(ll caseno)
{
    ll n;
    cin>>n;
    cout<<"Case #"<<caseno<<": "<<ans[n]<<en;
}

signed main()
{
    fast
    pre();
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ll t;
    cin >> t;
    fr(i, 1, t + 1)
    {
        solve(i);
    }
    return 0;
}