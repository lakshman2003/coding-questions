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
    ll n;
    cin>>n;
    vll q(n),k(n),j(n);
    getv(q,n);
    getv(k,n);
    getv(j,n);
    vector <pair<ll,pair<ll,ll>>> dp(n,MP(0,MP(-1,-1)));
    dp[n-1] = MP(1,MP(-1,-1));
    map <ll,ll> mpq,mpk,mpj;
    mpq[q[n-1]]= n-1;
    mpk[k[n-1]] = n-1;
    mpj[j[n-1]] = n-1;
    fr_rev(i,n-2,0){ 
        auto it = mpq.lower_bound(q[i]);
        if(it!=mpq.begin()){
            it--;
            dp[i] = MP(1,MP(0,it->ss));
        }
        it = mpk.lower_bound(k[i]);
        if (it != mpk.begin())
        {
            it--;
            dp[i] = MP(1, MP(1, it->ss));
        }
        it = mpj.lower_bound(j[i]);
        if (it != mpj.begin())
        {
            it--;
            dp[i] = MP(1, MP(2, it->ss));
        }
        if(dp[i].ff){
            mpq[q[i]]= i;
            mpk[k[i]] = i;
            mpj[j[i]]= i;
        }
    }
    if(dp[0].ff){
        cout<<"YES"<<en;
        ll curr= 0;
        vector <pair<char,ll>> ans;
        while(curr<n-1){
            auto [t,ch] = dp[curr].ss;
            pair <char,ll> p;
            if(t==0) p.ff = 'q';
            else if(t==1) p.ff = 'k';
            else p.ff = 'j';
            p.ss = ch+1;
            ans.pb(p);
            curr = ch;
        }
        cout<<ans.size()<<en;
        for(auto [x,y]:ans) cout<<x<<" "<<y<<en;
    }
    else cout<<"NO"<<en;
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