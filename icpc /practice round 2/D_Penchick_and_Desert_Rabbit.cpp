#include <bits/stdc++.h>
using namespace std;
void solve()
{
    int n;
    cin >> n;
    vector<int> a(n), dp(n);
    for(int &ai: a)
        cin >> ai;
    dp[n - 1] = a[n - 1];
    for(int i = n - 2; i >= 0; --i)
        dp[i] = max(a[i], dp[i + 1] + a[i]);
    for(int i = n - 2; i >= 0; --i)
        dp[i] = max(dp[i], dp[i + 1]);
    int mnsum = a[0], psum = a[0];
    int ans = dp[1] - mnsum;
    for(int i = 1; i < n - 1; ++i)
    {
        psum = min(psum + a[i], a[i]);
        mnsum = min(mnsum, psum);
        ans = max(ans, dp[i + 1] - mnsum);
    }
    cout << ans;
}