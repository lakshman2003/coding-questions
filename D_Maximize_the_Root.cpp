#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    indexed_set;
#define iset indexed_set
#define ll long long int
#define ull unsigned long long int
#define f first
#define sec second
#define rep(i, st, end) for (ll i = st; i < end; i++)
const ll mod = 1e9 + 7;
const ll maxi = 1e18;
using ii = pair<ll, ll>;

vector<vector<ll>> g;
vector<ll> a;
ll dfs(ll node, ll par, ll add)
{
    ll ans = 1, ch = 0;
    if(add>1e15){
        return 0;
    }
    for (auto v : g[node])
    {
        if (v == par)
            continue;
        ll nadd = add;
        if (a[v] - add < 0)
        {
            nadd += abs(a[v] - add);
        }
        ans &= dfs(v, node, nadd);
        ch++;
    }
    if (!ch)
    {
        if (a[node] < add)
        {
            ans = 0;
        }
    }
    return ans;
}

bool check(ll mid)
{
    return dfs(1, 0, mid - a[1]);
}

void solve()
{
    ll n;
    cin >> n;
    g.clear();
    g.resize(n + 1);
    a.clear();
    a.resize(n + 1);

    rep(i, 1, n + 1)
    {
        cin >> a[i];
    }

    rep(i, 0, n - 1)
    {
        ll p;
        cin >> p;
        g[p].push_back(i + 2);
    }

    ll low = a[1], high = 1e16, ans = a[1];
    while (high >= low)
    {
        ll mid = (high + low) / 2;
        if (check(mid))
        {
            ans = mid;
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    cout << ans << "\n";
}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}