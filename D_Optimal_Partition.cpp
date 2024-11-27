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

class Segtree
{
    public:
    ll n;
    vll v,t;
    Segtree(ll x = 0)
    {
        n = x;
        t.resize(4*n+1,-1e9);
    }

    ll merge(ll x,ll y)
    {
        return max(x,y);
    }
    
    void update(ll ind,ll l,ll r,ll pos,ll val)
    {
        if(l>pos or r<pos) return;
        if(l==r)
        {
            t[ind] = max(t[ind],val);
            return;
        }
        ll mid = (l+r)>>1;
        update(ind<<1,l,mid,pos,val);
        update(ind<<1|1,mid+1,r,pos,val);
        t[ind] = merge(t[ind<<1],t[ind<<1|1]);
    }

    ll query(ll ind,ll l,ll r,ll lq,ll rq)
    {
        if(l>rq or r<lq) return -1e9;
        if(l>=lq and r<=rq) return t[ind];
        ll mid = (l+r)>>1;
        return merge(query(ind<<1,l,mid,lq,rq),query(ind<<1|1,mid+1,r,lq,rq));
    }
};

void solve()
{
    ll n;
    cin>>n;
    vll v(n+1);
    fr(i,1,n+1) cin>>v[i];
    vll pre(n+1,0);
    map <ll,ll> comp;
    comp[0];
    fr(i,1,n+1) {
        pre[i] = pre[i - 1] + v[i];
        comp[pre[i]];
    }
    map <ll,ll> rev_comp;
    ll sz = 0;
    for(auto &[x,y]:comp) {
        y= sz;
        rev_comp[sz]= x;
        sz++;
    }

    Segtree sgpos(sz),sgneg(sz);
    map <ll,ll> mp0;
    fr(i,0,n+1) mp0[pre[i]] = -1e9;
    vll dp(n+10,-1e9);
    dp[n+1] = 0;
    mp0[pre[n]] = dp[n+1];
    fr_rev(i,n,1){
        // single element
        if(v[i]>0) dp[i] = dp[i+1]+1;
        else if(v[i]<0) dp[i] = dp[i+1]-1;
        else dp[i] = dp[i+1];

        // equal case
        dp[i] = max(dp[i],mp0[pre[i-1]]);

        // greater case
        ll ind = comp[pre[i-1]]+1;
        ll q = sgpos.query(1,0,sz-1,ind,sz-1);
        dp[i] = max(dp[i],q-i);

        // lesser case
        ind = comp[pre[i - 1]] - 1;
        q = sgneg.query(1, 0, sz - 1, 0, ind);
        dp[i] = max(dp[i], q + i);

        // updates
        mp0[pre[i]] = max(mp0[pre[i]],dp[i+1]);
        sgpos.update(1,0,sz-1,comp[pre[i]],dp[i+1]+(i+1));  
        sgneg.update(1,0,sz-1,comp[pre[i]],dp[i+1]-(i+1));

    }
    cout<<dp[1]<<en;
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