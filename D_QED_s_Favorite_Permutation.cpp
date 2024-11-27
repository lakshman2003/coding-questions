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
    ll n,q;
    cin>>n>>q;
    vll v(n);
    getv(v,n);
    vll pre(n,0);
    fr(i,0,n){
        ll l = i,r= v[i]-1;
        if(l>r) swap(l,r);
        pre[l]++;
        pre[r]--;
    }
    vll notok(n,0);
    fr(i,0,n) {
        if(i) pre[i]+= pre[i-1];
        if(pre[i]) notok[i] = 1; 
    }
    string s;
    cin>>s;
    ll cnt = 0;
    fr(i,0,n-1) if(notok[i] and s[i]=='L' and s[i+1]=='R') cnt++;
    while(q--){
        ll pos;
        cin>>pos;
        pos--;
        if(notok[pos] and s[pos]=='L' and s[pos+1]=='R') {
            cnt--;
        }
        if(pos-1>=0 and notok[pos-1] and s[pos-1]=='L' and s[pos]=='R'){
            cnt--;
        }
        if(s[pos]=='R') s[pos] = 'L';
        else s[pos] = 'R';
        if (notok[pos] and s[pos] == 'L' and s[pos + 1] == 'R')
        {
            cnt++;
        }
        if (pos - 1 >= 0 and notok[pos - 1] and s[pos - 1] == 'L' and s[pos] == 'R')
        {
            cnt++;
        }
        if(cnt) no;
        else yes;
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