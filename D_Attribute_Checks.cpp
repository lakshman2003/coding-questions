#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less_equal<int>, rb_tree_tag, 
tree_order_statistics_node_update> ordered_set;

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
    ll m, n;
    cin>>n>>m;
    vll op(n);
    getv(op,n);
    multiset <ll> st1,st2;
    v2ll dp(m+10,vll(m+10,0));
    ll rem = m;
    fr_rev(i,n-1,0){
        if(op[i]!=0){
            if(op[i]<0) {
                st1.insert(-op[i]);
            }
            else {
                st2.insert(op[i]);
            }
        }
        else
        {   
            vll v11,v12,v21,v22;
            for(auto x:st1){
                v11.pb(x);
                v12.pb(x);
            }
            for(auto x:st2){
                v21.pb(x);
                v22.pb(x);
            }
            ll j1 = -1,j2 = -1;
            fr_rev(st,rem-1,0){
                // ch strength
                ll currst = st+1;
                ll currin = rem-currst;
                while(!v11.empty() and v11.back()>currst) v11.pop_back();
                while(j1+1<v21.size() and v21[j1+1]<=currin) j1++;
                ll x1 = v11.size(),x2 = j1+1;
                dp[rem][st] = dp[rem+1][currst]+x1+x2;

                // ch in
                currst = st;
                currin = rem - currst;
                while (!v12.empty() and v12.back() > currst)
                    v12.pop_back();
                while (j2 + 1 < v22.size() and v22[j2 + 1] <= currin)
                    j2++;
                x1 = v12.size(), x2 = j2 + 1;
                dp[rem][st] = max(dp[rem][st],dp[rem + 1][currst] + x1 + x2);
            }
            st1.clear();
            st2.clear();
            rem--;
        }
    }
    cout<<dp[1][0]<<en;
}

signed main(){
    fast
    ll t = 1;
    while(t--)
    {
        solve();
    }
    return 0;
}