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

vll a,b;
v2ll rec(ll l,ll r){
    v2ll ans;
    if(l==r) {
        ans.pb({ b[l], a[l], 1});
        return ans;
    };
    ll mid = (l+r)>>1;
    v2ll left = rec(l,mid);
    v2ll right = rec(mid+1,r);

    vll p1(mid-l+1),p2(mid-l+1),s1(r-mid),s2(r-mid);
    p1[0] = a[l];
    p2[0] = b[l];
    fr(i,l+1,mid+1) {
        p1[i-l] = __gcd(p1[i-l-1],a[i]);
        p2[i-l] = __gcd(p2[i-l-1],b[i]);
    }

    s1[r-mid-1] = a[r];
    s2[r-mid-1] = b[r];
    fr_rev(i,r-1,mid+1){
        s1[i-mid-1] = __gcd(s1[i-mid],a[i]);
        s2[i-mid-1] = __gcd(s2[i-mid],b[i]); 
    }

    map <pll,ll> leftg,rightg;
    leftg[MP(p2[mid-l],p1[mid-l])]++;
    rightg[MP(s2[0],s1[0])]++;
    ll currg1 = a[mid],currg2 = b[mid];
    ll curr = mid;
    while(curr>=l+1){
        currg1 = __gcd(currg1,a[curr]);
        currg2 = __gcd(currg2,b[curr]);
        ll g1 = __gcd(p1[curr-l-1],currg2);
        ll g2 = __gcd(p2[curr-l-1],currg1);
        leftg[MP(g1,g2)]++;
        curr--;
    }

    curr = mid+1;
    currg1 = a[mid+1],currg2 = b[mid+1];
    while(curr<r){
        currg1 = __gcd(currg1,a[curr]);
        currg2 = __gcd(currg2,b[curr]);
        ll g1 = __gcd(s1[curr-mid], currg2);
        ll g2 = __gcd(s2[curr-mid], currg1);
        rightg[MP(g1,g2)]++;
        curr++;
    }

    map <pll,ll> freq;
    for(auto x:left) freq[MP(__gcd(x[0],s1[0]),__gcd(x[1],s2[0]))]+= x[2];
    for(auto x:right) freq[MP(__gcd(x[0], p1[mid-l]), __gcd(x[1], p2[mid-l]))] += x[2];
    for(auto [x,c1]:leftg){
        for(auto [p,c2]:rightg){
            ll g1 = __gcd(x.ff,p.ff), g2 = __gcd(x.ss,p.ss);
            freq[MP(g1, g2)]+= c1*c2;
        }
    }

    for(auto [x,y]:freq) ans.pb({x.ff,x.ss,y});
    return ans;
}

void solve()
{
    ll n;
    cin>>n;
    a.resize(n);
    b.resize(n);
    getv(a,n);
    getv(b,n);
    v2ll ans = rec(0,n-1);
    ll maxi = 0,cnt = 0;
    for(auto x:ans){
        if(x[0]+x[1]>maxi){
            maxi = x[0]+x[1];
            cnt = x[2];
        }
        else if(x[0]+x[1]==maxi) cnt+= x[2];
    }
    cout<<maxi<<" "<<cnt<<en;
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