#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long

const int N = 1000000;
vector<int> lp(N + 1);
vector<int> pr;

void minpfac()
{
    for (int i = 2; i <= N; ++i)
    {
        if (lp[i] == 0)
        {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; i * pr[j] <= N; ++j)
        {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i])
            {
                break;
            }
        }
    }
}

const int mod = 998'244'353;

int modpow(int x, int n, int m)
{
    if (n == 0)
        return 1 % m;
    long long u = modpow(x, n / 2, m);
    u = (u * u) % m;
    if (n % 2 == 1)
        u = (u * x) % m;
    return u;
}

int mod_inv(int x, int p)
{
    return modpow(x, p - 2, p);
}

int add(int x, int y)
{
    long long res = 1LL * x + 1LL * y;
    while (res < 0)
        res += mod;
    if (res >= mod)
        res -= mod;
    return res;
}

int mul(int x, int y)
{
    long long res = 1LL * x * y;
    if (res >= mod)
        res %= mod;
    return res;
}

int _div(int x, int y)
{
    long long res = 1LL * x * mod_inv(y, mod);
    if (res >= mod)
        res %= mod;
    return res;
}

void solve()
{
    int n;
    cin >> n;
    vector<int> ansf(N + 1, 0);
    vector<int> a(n);

    auto calc = [&](vector<int> &p)
    {
        int sz = p.size();
        int res = 0;
        for (int i = 1; i < (1 << sz); ++i)
        {
            int curr = 1;
            for (int j = 0; j < sz; ++j)
            {
                if ((i >> j) & 1)
                    curr *= p[j];
            }

            if (__builtin_popcount(i) % 2)
            {
                res = add(res, ansf[curr]);
            }
            else
            {
                res = add(res, -ansf[curr]);
            }
        }
        return res;
    };

    for (int i = 0; i < n; ++i)
    {
        int x;
        cin >> x;
        int initial = x;
        vector<int> ps;
        while (x != 1)
        {
            int pos = find(ps.begin(), ps.end(), lp[x]) - ps.begin();
            if (pos == ps.size())
            {
                ps.push_back(lp[x]);
            }
            x /= lp[x];
        }
        a[i] = calc(ps);
        if (i == 0)
            a[i] = 1;
    
        int sz = ps.size();
        for (int j = 1; j < (1 << sz); ++j)
        {
            int curr = 1;
            for (int k = 0; k < sz; ++k)
            {
                if ((j >> k) & 1)
                    curr *= ps[k];
            }

            ansf[curr] = add(ansf[curr], a[i]);
        }
    }

    cout << a[n - 1];
}

int32_t main()
{
    minpfac();
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    solve();
}
