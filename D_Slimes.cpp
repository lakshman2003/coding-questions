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
    vll v;
    vpll t;
    Segtree(ll x = 0)
    {
        n = x;
        t.resize(4*n+1);
    }

    pll merge(pll x,pll y)
    {
        pll ans;
        ans.ff = max(x.ff,y.ff);
        ans.ss = min(x.ss,y.ss);
        return ans;
    }
    void build(ll ind,ll l,ll r)
    {
        if(l==r)
        {
            t[ind] = MP(v[l],v[l]);
            return;
        }
        ll mid = (l+r)>>1;
        build(ind<<1,l,mid);
        build(ind<<1|1,mid+1,r);
        t[ind] = merge(t[ind<<1],t[ind<<1|1]);
    }

    pll query(ll ind,ll l,ll r,ll lq,ll rq)
    {
        if(l>rq or r<lq) return MP(0,1e12);
        if(l>=lq and r<=rq) return t[ind];
        ll mid = (l+r)>>1;
        return merge(query(ind<<1,l,mid,lq,rq),query(ind<<1|1,mid+1,r,lq,rq));
    }
};

void solve()
{
    ll n;
    cin>>n;
    vll v(n);
    getv(v,n);
    vll pre(n,0);
    fr(i,0,n) {
        pre[i] = v[i];
        if(i) pre[i]+= pre[i-1];
    }
    Segtree sg(n);
    sg.v = v;
    vll ans(n,1e9);
    sg.build(1,0,n-1);
    fr(i,0,n){
        if(i<n-1 and v[i+1]>v[i]) ans[i] = 1;
        else if(i and v[i-1]>v[i]) ans[i] = 1;
        else 
        {
            if (i + 2 <= n - 1)
            {
                ll lo = i + 2, hi = n - 1;
                while (lo <= hi)
                {
                    ll mid = (lo + hi) >> 1;
                    pll q = sg.query(1, 0, n - 1, i + 1, mid);
                    ll s = pre[mid] - pre[i];
                    if (q.ff != q.ss and s > v[i])
                    {
                        ans[i] = mid - i;
                        hi = mid - 1;
                    }
                    else
                        lo = mid + 1;
                }
            }
            if (i - 2 >= 0)
            {
                ll lo = 0, hi = i - 2;
                while (lo <= hi)
                {
                    ll mid = (lo + hi) >> 1;
                    pll q = sg.query(1, 0, n - 1, mid, i - 1);
                    ll s = pre[i - 1] - ((mid) ? pre[mid - 1] : 0);
                    if (q.ff != q.ss and s > v[i])
                    {
                        ans[i] = min(ans[i], i - mid);
                        lo = mid + 1;
                    }
                    else
                        hi = mid - 1;
                }
            }
        }
    }
    fr(i,0,n) if(ans[i]==1e9) ans[i] = -1;
    print(ans);
    cout<<en;
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