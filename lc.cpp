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

class Solution
{
public:
    int subsequencesWithMiddleMode(vector<int> &nums)
    {
        ll ans = 0;
        ll n = nums.size();
        for (ll i = 2; i <= n - 3; i++)
        {
            unordered_map<ll, ll> leftmp, rightmp;
            for (ll j = 0; j < i; j++)
            {
                leftmp[nums[j]]++;
            }
            for (ll j = i + 1; j < n; j++)
            {
                rightmp[nums[j]]++;
            }
            ll left = i, right = n - i - 1;

            ll c1 = 0;
            for (auto &[x, y] : leftmp)
            {
                if(x==nums[i])
                    continue;
                ll on_right = right - rightmp[x];
                if (nums[i] != x)
                    on_right -= rightmp[nums[i]];
                c1 += ((on_right * (on_right - 1)) / 2) * y;
            }

            ll c2 = 0;
            for (auto &[x, y] : rightmp)
            {
                if(x==nums[i])
                    continue;
                ll on_left = left - leftmp[x] - ((nums[i]!=x)?leftmp[nums[i]]:0);
                c2 += ((on_left * (on_left - 1)) / 2) * y;
            }

            ll t = right - rightmp[nums[i]];
            ll c3 = ((leftmp[nums[i]] * (leftmp[nums[i]] - 1)) / 2) * (t * (t - 1) / 2);

            t = left - leftmp[nums[i]];
            ll c4 = ((rightmp[nums[i]] * (rightmp[nums[i]] - 1)) / 2) * (t * (t - 1) / 2);

            ll c5 = leftmp[nums[i]] * (left - leftmp[nums[i]]) * (right - rightmp[nums[i]]) * rightmp[nums[i]];

            t = leftmp[nums[i]];
            ll t2 = right - rightmp[nums[i]];
            ll c6 = ((t * (t - 1)) / 2) * ((t2 * (t2 - 1)) / 2);

            t = rightmp[nums[i]];
            t2 = left - leftmp[nums[i]];
            ll c7 = ((t * (t - 1)) / 2) * (t2 * (t2 - 1) / 2);

            t = (leftmp[nums[i]] * (leftmp[nums[i]] - 1)) / 2;
            t2 = (rightmp[nums[i]] * (rightmp[nums[i]] - 1)) / 2;
            ll c8 = t * t2;

            cout<<c1<<" "<<c2<<" "<<c3<<" "<<c4<<" "<<c5<<" "<<c6<<" "<<c7<<" "<<c8<<en;
            ans += c1 + c2 + c3 + c4 + c5 + c6 + c7 + c8;
            ans %= mod;
        }
        return ans;
    }
};

int main(){
    Solution s;
    vector<int> v = {1, 2, 2, 3, 3, 4};
    cout << s.subsequencesWithMiddleMode(v) << en;
    return 0;
}