#include <bits/stdc++.h>
#include <vector>
#include <stack>
#include <algorithm>
#include <climits>

using namespace std;

int solution(string &s, int k)
{
    int n = s.length();
    if (k == n)
    {
        return 0;
    }

    vector<int> pre(n, 0);
    vector<pair<int, int>> last(n);
    stack<pair<int, int>> st;

    // Calculate prefix compression information
    for (int i = 0; i < n; i++)
    {
        if (st.empty() or st.top().first != (s[i] - 'a'))
        {
            st.push(make_pair(s[i] - 'a', 1));
            pre[i] = 1 + ((i) ? pre[i - 1] : 0);
        }
        else
        {
            auto p = st.top();
            st.pop();
            st.push(make_pair(p.first, p.second + 1));
            int len = p.second + 1;
            int x = 0;
            while (len)
            {
                x++;
                len /= 10;
            }
            pre[i] = 1 + x;
            if (i - st.top().second >= 0)
                pre[i] += pre[i - st.top().second];
        }
        last[i] = st.top();
    }

    // Calculate suffix compression information
    reverse(s.begin(), s.end());
    vector<int> suff(n, 0);
    vector<pair<int, int>> last_suff(n);
    while (st.size())
        st.pop();
    for (int i = 0; i < n; i++)
    {
        if (st.empty() or st.top().first != (s[i] - 'a'))
        {
            st.push(make_pair(s[i] - 'a', 1));
            suff[i] = 1 + ((i) ? suff[i - 1] : 0);
        }
        else
        {
            auto p = st.top();
            st.pop();
            st.push(make_pair(p.first, p.second + 1));
            int len = p.second + 1;
            int x = 0;
            while (len)
            {
                x++;
                len /= 10;
            }
            suff[i] = 1 + x;
            if (i - st.top().second >= 0)
                suff[i] += suff[i - st.top().second];
        }
        last_suff[i] = st.top();
    }
    reverse(s.begin(), s.end());
    reverse(suff.begin(), suff.end());
    reverse(last_suff.begin(), last_suff.end());

    // Find the minimum compressed length after removing K characters
    int ans = min(pre[n - k - 1], suff[k]);
    cout<<ans<<endl;
    for (int i = 1; i < n; i++)
    {
        if (i + k - 1 >= n - 1)
            break;
        auto x1 = last[i - 1];
        auto x2 = last_suff[i + k];
        if (x1.first != x2.first)
        {
            ans = min(ans, pre[i - 1] + suff[i + k]);
        }
        else
        {
            int sc = 0;
            if (i - 1 - x1.second >= 0)
                sc += pre[i - 1 - x1.second];
            if (i + k + x2.second <= n - 1)
                sc += suff[i + k + x2.second];
            int len = x1.second + x2.second;
            sc++;
            while (len)
            {
                sc++;
                len /= 10;
            }
            ans = min(ans, sc);
        }
        cout<<ans<<endl;
    }

    return ans;
}

int main()
{
    int t;
    cin>>t;
    while(t--){
        string s;
        cin>>s;
        int k;
        cin>>k;
        cout << solution(s, k) << endl;
    }
    return 0;
}
