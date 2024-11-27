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
#define pb push_back
#define pii pair<int, int>
#define pll pair<ll, ll>
#define MP make_pair
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
#define mod 998244353
#define print(v) fr(i,0,v.size()) cout<<v[i]<<" "
#define INF LLONG_MAX
#define yes cout<<"Yes\n"
#define no cout<<"No\n"
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
        t.resize(4*n+1);
    }

    ll merge(ll x,ll y)
    {
        return x+y;
    }
    void build(ll ind,ll l,ll r)
    {
        if(l==r)
        {
            t[ind] = v[l];
            return;
        }
        ll mid = (l+r)>>1;
        build(ind<<1,l,mid);
        build(ind<<1|1,mid+1,r);
        t[ind] = merge(t[ind<<1],t[ind<<1|1]);
    }


    void update(ll ind,ll l,ll r,ll pos,ll val)
    {
        if(l>pos or r<pos) return;
        if(l==r)
        {
            (t[ind]+= val)%=mod;
            return;
        }
        ll mid = (l+r)>>1;
        update(ind<<1,l,mid,pos,val);
        update(ind<<1|1,mid+1,r,pos,val);
        t[ind] = merge(t[ind<<1],t[ind<<1|1]);
    }

    ll query(ll ind,ll l,ll r,ll lq,ll rq)
    {
        if(l>rq or r<lq) return 0;
        if(l>=lq and r<=rq) return t[ind];
        ll mid = (l+r)>>1;
        return merge(query(ind<<1,l,mid,lq,rq),query(ind<<1|1,mid+1,r,lq,rq));
    }
};

void solve()
{
    ll n,k;
    cin>>n>>k;
    vll v(n+1);
    fr(i,1,n+1) cin>>v[i];
    vll pre(n+1,0);
    fr(i,1,n+1) pre[i] = pre[i-1]+v[i];
    map<ll, ll> comp;
    fr(i,0,n+1) comp[pre[i]];
    ll sz = comp.size();
    ll i = 0;
    for(auto &[x,y]:comp) y = i++;

    Segtree sg(sz);

    vll dp(n+1,0);
    dp[0] = 1;
    fr(i,1,n+1){
        ll val = pre[i]-k;
        ll s = 0;
        auto it = comp.lower_bound(val);
        if(it!=comp.begin()) {
            it--;
            ll q = sg.query(1,0,sz-1,0,it->ss);
            (s+= q)%=mod;
        }
        it = comp.upper_bound(val);
        if(it!=comp.end()){
            ll q = sg.query(1, 0, sz - 1, it->ss, sz-1);
            (s += q)%=mod;
        }
        dp[i] = s;
        if(pre[i]!=k) (dp[i]+=1)%=mod;
        sg.update(1,0,sz-1,comp[pre[i]],dp[i]);
    }
    cout<<dp[n]<<en;
}

signed main(){
    fast
    solve();
    return 0;
}