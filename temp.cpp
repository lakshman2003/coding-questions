#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<int>, rb_tree_tag,
tree_order_statistics_node_update> indexed_set;

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
#define v2ll vector< vector<ll>>
#define vpi vector<pii>
#define vpll vector<pll>
#define iset indexed_set
#define minpqll priority_queue<ll,vector<ll>,greater<ll>>
#define getv(v, n) for(ll i = 0; i < n; i++) cin >> v[i];
#define get_pair(v,n) for (ll i=0;i<n;i++) cin>>v[i].ff>>v[i].ss;
#define fr(i,a,b) for(ll i=a;i<(b);i++)
#define fr_e(i,a,b) for(ll i=a;i<=b;i++)
#define fr_rev(i,a,b) for(ll  i=(a);i>=b;i--)
#define all(v) v.begin(),v.end()
#define mod 1000000007
#define print(v) fr(i,0,v.size()) cout<<v[i]<<" "
#define INF LLONG_MAX
#define yes cout<<"YES\n"
#define no cout<<"NO\n"
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define stp(n) cout<<fixed<<setprecision(n)
#define sz(v) 1LL*v.size()
 
inline ll add(ll a,ll b)
{
    a+=b;
    if(a>=mod) a%=mod;
    return a;
}

inline ll mul(ll a,ll b)
{
    return ((a%mod)*(b%mod))%mod;
}

inline ll bin_pow(ll a,ll b)
{
    ll ans=1;
    while(b)
    {
        if(b%2) ans=ans*a%mod;
        a=mul(a,a);
        b/=2;
    }
    return ans;
}

inline ll inv(ll a)
{
    return bin_pow(a,mod-2)%mod;
}


void solve(int k, string a, string b)
{
    int n = a.length(), m = b.length();
    vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(m+1, vector<int>(k+1, -1)));
    auto rec = [&](auto &self, int lvl, int match, int tot) -> int {
        if (tot > k) return 1e6;
        if (lvl == n) return (tot == k) ? 0 : 1e6;
        if (dp[lvl][match][tot] != -1) return dp[lvl][match][tot];
        int ans = self(self, lvl + 1, match, tot) + 1;
        string t = b.substr(0, match) + a[lvl];
        int new_match = 0;
        string combined = b + "#" + t;
        vector<int> z(combined.size(), 0);
        for (int i = 1, l = 0, r = 0; i < combined.size(); i++) {
            if (i <= r) z[i] = min(r - i + 1, z[i - l]);
            while (i + z[i] < combined.size() && combined[z[i]] == combined[i + z[i]]) z[i]++;
            if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
            if (i > b.size() && z[i] == b.size()) { new_match = b.size(); break; }
            if (i > b.size()) new_match = max(new_match, z[i]);
        }
        ans = min(ans, self(self, lvl + 1, new_match, tot + (new_match == m)));
        return dp[lvl][match][tot] = ans;
    };
    int ans = rec(rec, 0, 0, 0);
    cout << (ans >= 1e6 ? -1 : ans) << en;
};

signed main(){
    fast
    ll t = 1;
    while(t--)
    {
        int k;
        string a,b;
        cin>>k>>a>>b;
        solve(k,a,b);
    }
    return 0;
}