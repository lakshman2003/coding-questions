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

int R, C;
ll K;
vector<vector<int>> G;
map<tuple<int, int, int>, ll> dp; 

ll rec(int mid, int s_row, int s_col, ll sum_row, ll sum_col)
{
    if (mid < 0)
        return INF;

    tuple<int, int, int> state = {mid, s_row, s_col};
    if (dp.find(state) != dp.end())
        return dp[state];

    ll total_pairs_S = sum_row * sum_col - (ll)R * C;
    ll same_owner_pairs_S = 0;
    vector<vector<pair<int, int>>> bunny_cells(R * C + 1);

    fr(i, 0, R)
    {
        fr(j, 0, C)
        {
            bunny_cells[G[i][j]].emplace_back(i, j);
        }
    }

    for (int b = 1; b <= R * C; b++)
    {
        int cb = bunny_cells[b].size();
        if (cb <= 1)
            continue;

        vector<pair<int, int>> &cells = bunny_cells[b];
        sort(cells.begin(), cells.end());

        fr(r, 0, cb)
        {
            int i_r = cells[r].first;
            int j_r = cells[r].second;

            int l = lower_bound(cells.begin(), cells.end(), MP(i_r - mid, -1)) - cells.begin();
            int u = upper_bound(cells.begin(), cells.end(), MP(i_r + mid, C)) - cells.begin();

            int low = j_r - mid;
            int high = j_r + mid;

            int lower_idx = lower_bound(cells.begin() + l, cells.begin() + u, MP(0, low),
                                        [&](auto &a, auto &b)
                                        {
                                            return a.ss < b.ss;
                                        }) -
                            cells.begin();
            int upper_idx = upper_bound(cells.begin() + l, cells.begin() + u, MP(0, high),
                                        [&](auto &a, auto &b)
                                        {
                                            return a.ss < b.ss;
                                        }) -
                            cells.begin();

            same_owner_pairs_S += (ll)(upper_idx - lower_idx);
        }
        same_owner_pairs_S -= (ll)cb;
    }

    ll valid_pairs_S = total_pairs_S - same_owner_pairs_S;
    dp[state] = valid_pairs_S >= K ? mid : INF;

    return dp[state];
}

void solve(ll tc)
{
    cin >> R >> C >> K;
    G = vector<vector<int>>(R, vector<int>(C));

    fr(i, 0, R)
    {
        fr(j, 0, C)
        {
            cin >> G[i][j];
        }
    }

    int left = 0, right = max(R, C);
    ll answer = right;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        int s_row = min(mid, R - 1);
        int s_col = min(mid, C - 1);
        ll sum_row = (ll)R * (2LL * s_row + 1) - 1LL * s_row * (s_row + 1);
        ll sum_col = (ll)C * (2LL * s_col + 1) - 1LL * s_col * (s_col + 1);

        ll valid_pairs_S = rec(mid, s_row, s_col, sum_row, sum_col);

        if (valid_pairs_S != INF)
        {
            answer = mid;
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    cout << "Case #" << tc << ": " << answer << en;
}

signed main()
{
    fast;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    ll t;
    cin >> t;
    fr(i, 1, t + 1)
    {
        dp.clear(); 
        solve(i);
    }

    return 0;
}
