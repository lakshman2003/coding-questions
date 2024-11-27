#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set(T) tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>
#define ordered_set_greater(T) tree<T, null_type, greater<T>, rb_tree_tag, tree_order_statistics_node_update>
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
#define F first
#define S second
#define PB push_back
#define EB emplace_back
#define MP make_pair
#define REP(i, a, b) for (ll i = a; i < b; i++)
#define MOD 1000000007
#define digits(n) ((int)log10l(abs(n)) + 1)
// #define MULTICASE
#define MAXN 1000000 // 1e6

template <int m>
struct ModInt
{
    unsigned x;
    ModInt() : x(0) {}
    ModInt(signed sig) : x(sig % m) {}
    ModInt(signed long long sig) : x(sig % m) {}
    int get() const { return (int)x; }
    ModInt pow(ll p)
    {
        if (!x)
            return p % m == 0;
        ModInt res = 1, a = *this;
        while (p)
        {
            if (p & 1)
                res *= a;
            a *= a;
            p >>= 1;
        }
        return res;
    }

    ModInt &operator+=(ModInt that)
    {
        if ((x += that.x) >= m)
            x -= m;
        return *this;
    }
    ModInt &operator-=(ModInt that)
    {
        if ((x += m - that.x) >= m)
            x -= m;
        return *this;
    }
    ModInt &operator*=(ModInt that)
    {
        x = (unsigned long long)x * that.x % m;
        return *this;
    }
    ModInt &operator/=(ModInt that) { return (*this) *= that.pow(m - 2); }

    ModInt operator+(ModInt that) const { return ModInt(*this) += that; }
    ModInt operator-(ModInt that) const { return ModInt(*this) -= that; }
    ModInt operator*(ModInt that) const { return ModInt(*this) *= that; }
    ModInt operator/(ModInt that) const { return ModInt(*this) /= that; }
    bool operator<(ModInt that) const { return x < that.x; }
    friend ostream &operator<<(ostream &os, ModInt a)
    {
        os << a.x;
        return os;
    }
};
typedef ModInt<MOD> mint;

void solve()
{
    //*code here
    int n;
    cin >> n;
    vl c(n);
    REP(i, 0, n)
        cin >> c[i];
    vector<vl> a(n);
    REP(i, 0, n)
    {
        a[i].resize(c[i]);
        REP(j, 0, c[i])
            cin >> a[i][j];
    }
    int ans = INT_MAX;
    for (int i = 0; i < n - 1; i++)
    {
        multiset<int> x(a[i].begin(), a[i].end());
        vi y(a[i + 1].begin(), a[i + 1].end());
        if (i > 0)
        {
            for (auto &j : a[i - 1])
            {
                x.insert(j);
            }
        }
        if (i < n - 2)
        {
            for (auto &j : a[i + 2])
            {
                y.PB(j);
            }
            sort(y.begin(), y.end());
        }
        int k = 0;
        for (auto &j : y)
            k += x.count(j);
        ans = min(ans, k);
    }
    cout << ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
#ifdef MULTICASE
    int t;
    cin >> t;
    while (t--)
#endif
        solve();
    return 0;
}