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


void solve()
{
    ll n,k;
    cin>>n>>k;
    string s;
    cin>>s;
    vll pre(n+1);
    pre[1] = (s[0]=='1');
    fr(i,2,n+1) pre[i] = pre[i-1]+ (s[i]=='1');
    vll dp(n+1,0);
    if(s[n-k]=='0') dp[n-k+1] = (pre[n]==pre[n-k]);
    else dp[n-k+1] = (pre[n]==pre[n-k]+k);
    for(int i = n-2*k+1;i>=1;i-=k)
    {
        if(s[i-1]=='1') dp[i] = dp[i+k] & (pre[i+k-1]==k+pre[i-1]);
        else dp[i] = dp[i+k]&(pre[i+k-1]==pre[i-1]);
    }

    if(dp[1])
    {
        cout<<n<<en;
        return;
    }
    
    deque <pll> dq;
    map <ll,ll> mp;
    ll i = 0;
    while(i<n)
    {
        ll c = 1;
        while(i+1<n and s[i+1]==s[i])
        {
            i++;
            c++;
        }
        mp[c]++;
        dq.pb(MP(c,s[i]-'0'));
        i++;
    }
    ll last = -1;
    ll curr = 0;
    fr(i,1,n)
    {
        cout<<last<<" "<<curr<<en;
        ll x = s[i-1]-'0';
        if(last==-1) last = x;
        if(last==x) curr++;
        if(curr>k) 
        {
            cout<<-1<<en;
            return;
        }
        if(last!=x)
        {
            if(curr<k) 
            {
                cout<<-1<<en;
                return;
            }
            last = x;
            curr = 1;
        }
        auto p1 = dq.front();
        auto p2 = dq.back();
        cout<<"Printing"<<en;
        cout << last << " " << curr << en;
        cout<<p1.ff<<" "<<p2.ff<<" "<<en;
        dq.pop_front();
        mp[p1.ff]--;
        if(mp[p1.ff]==0) mp.erase(p1.ff);
        if(p1.ff>1) 
        {
            dq.push_front(MP(p1.ff - 1, p1.ss));
            mp[p1.ff-1]++;
        }
        ll end = p2.ff + curr;
        if(p2.ss!=last) end = p2.ff;
        mp[end]++;
        if(p2.ss==last) 
        {
            mp[p2.ff]--;
            if(mp[p2.ff]==0) mp.erase(p2.ff);
        }
        mp[end]++;
        cout<<"Printing map"<<en;
        for(auto [x,y]:mp)
        {
            cout<<x<<" "<<y<<en;
        }
        if(mp.size()==1 and mp.begin()->ff==k and end==k)
        {
            cout<<i<<en;
            return;
        }
        if(p2.ss==last) mp[p2.ff]++;
        mp[end]--;
        if(mp[end]==0) mp.erase(end);
    }
    cout<<-1<<en;
}

signed main(){
    fast
    ll t;
    cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}