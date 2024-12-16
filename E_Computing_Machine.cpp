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
    string s,t;
    cin>>s>>t;
    vll poss(n,0);
    fr(i,0,n){
        if(s[i]=='1') poss[i]++;
        else {
            bool left = false,right = false;
            if(i-1>=0 and t[i-1]=='1')  left = true;
            if(i-2>=0 and s[i-2]=='0') left = true;
            if(i+1<n and t[i+1]=='1') right = true;
            if(i+2<n and s[i+2]=='0') right = true;
            if(left and right) poss[i]++;
        }
    }
    fr(i,1,n) poss[i]+=poss[i-1];
    ll q;
    cin>>q;
    while(q--){
        ll l,r;
        cin>>l>>r;
        l--,r--;
        if(l==r){
            if(s[l]=='1') cout<<1<<en;
            else cout<<0<<en;
            continue;
        }
        ll cnt = 0;
        if(l+2<=r-2){
            cnt+= poss[r-2];
            cnt-= poss[l+1];
        }
        if(s[l]=='1') cnt++;
        if(l+1<=r and s[l+1]=='1') cnt++;
        else if(l+1<=r){
            bool left = false,right = false;
            if(t[l]=='1') left = true;
            if(l+2<=r and t[l+2]=='1') right = true;
            if(l+3<=r and s[l+3]=='0') right = true;
            if(left and right) cnt++;
        }
        if(l+1!=r and s[r]=='1') cnt++;
        if(r-1>l+1 and s[r-1]=='1') cnt++;
        else if(r-1>l+1){
            bool left = false,right = false;
            if(r-2>=l and t[r-2]=='1') left = true;
            if(r-3>=l and s[r-3]=='0') left = true;
            if(t[r]=='1') right = true;
            if(left and right) cnt++;
        }
        cout<<cnt<<en;
    }

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