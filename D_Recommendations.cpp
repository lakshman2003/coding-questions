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
    vll left(n),right(n);
    fr(i,0,n) cin>>left[i]>>right[i];
    vll maxleft(n,-1),minright(n,1e10);
    v2ll temp;
    fr(i,0,n) {
        ll l = left[i],r = right[i];
        temp.pb({l,LLONG_MAX,i});
        temp.pb({r+1,-l,i});
    }
    sort(all(temp));
    multiset <ll> mt;
    for(auto x:temp){
        if(x[1]==LLONG_MAX){
            mt.insert(x[0]);
        }
        else {
            mt.erase(mt.find(left[x[2]]));
            auto it = mt.upper_bound(left[x[2]]);
            if(it!=mt.begin()){
                it--;
                maxleft[x[2]] = *it;
            }
            
        }
    }
    temp.clear();
    fr(i,0,n) {
        swap(left[i], right[i]);
        left[i]*=-1;
        right[i]*=-1;
    }
    fr(i, 0, n)
    {
        ll l = left[i], r = right[i];
        temp.pb({l, LLONG_MAX, i});
        temp.pb({r + 1, -l, i});
    }

    sort(all(temp));
    mt.clear();
    for (auto x : temp)
    {
        if (x[1] == LLONG_MAX)
        {
            mt.insert(x[0]);
        }
        else
        {
            mt.erase(mt.find(left[x[2]]));
            auto it = mt.upper_bound(left[x[2]]);
            if (it != mt.begin())
            {
                it--;
                minright[x[2]] = -*it;
            }
        }
    }

    fr(i, 0, n)
    {
        swap(left[i], right[i]);
        left[i] *= -1;
        right[i] *= -1;
    }
    vll ans(n);
    fr(i,0,n){
        if(maxleft[i]==-1) maxleft[i] = left[i];
        if(minright[i]==1e10) minright[i] = right[i];
        ans[i] = minright[i]-maxleft[i]-(right[i]-left[i]);
    }
    map <pll,ll> mp;
    fr(i,0,n) {
        pll p = {left[i],right[i]};
        if(mp.find(p)==mp.end()) mp[p] = ans[i];
        else mp[p] = min(mp[p],ans[i]);
    }
    fr(i,0,n){
        pll p = {left[i],right[i]};
        ans[i] = mp[p];
    }
    fr(i,0,n) cout<<ans[i]<<en;
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