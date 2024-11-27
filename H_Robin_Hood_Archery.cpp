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
struct node{
    map <ll,ll,greater<ll>> mp; 
    ll m1,m2;
    node(){
        m1 = m2 = 0;
    }
};
class Segtree
{
    public:
    ll n;
    vll v;
    vector <node> t;
    Segtree(ll x = 0)
    {
        n = x;
        t.resize(4*n+1);
    }

    node merge(node x,node y)
    {
        node ans;
        if(x.mp.size()>y.mp.size()) {
            ans.mp = x.mp;
            for(auto [val,f]:y.mp){
                ans.mp[val]+=f;
            }
        }
        else {
            ans.mp = y.mp;
            for (auto [val, f] : x.mp)
            {
                ans.mp[val] += f;
            }
        }
        ll m1 = 0,m2 = 0;
        ll ch = 0;
        for(auto [x,y]:ans.mp){
            m1+= x*(y/2);
            m2+= x*(y/2);
            if(ch==0) m1+= x*(y%2);
            else m2+= x*(y%2);
            if(y&1) ch^=1;
        }
        ans.m1 = m1;
        ans.m2 = m2;
        return ans;
    }
    void build(ll ind,ll l,ll r)
    {
        if(l==r)
        {
            t[ind].mp[v[l]]++;
            t[ind].m1= v[l];
            return;
        }
        ll mid = (l+r)>>1;
        build(ind<<1,l,mid);
        build(ind<<1|1,mid+1,r);
        t[ind] = merge(t[ind<<1],t[ind<<1|1]);
    }

    node query(ll ind,ll l,ll r,ll lq,ll rq)
    {
        node temp;
        if(l>rq or r<lq) return temp;
        if(l>=lq and r<=rq) return t[ind];
        ll mid = (l+r)>>1;
        return merge(query(ind<<1,l,mid,lq,rq),query(ind<<1|1,mid+1,r,lq,rq));
    }
};
void solve()
{
    ll n,q;
    cin>>n>>q;
    vll v(n);
    getv(v,n);
    Segtree sg(n);
    sg.v = v;
    sg.build(1,0,n-1);
    map <pll,ll> dp;
    while(q--){
        ll l,r;
        cin>>l>>r;
        l--;r--;
        if(dp.find(MP(l,r))!=dp.end()) {
            if(dp[MP(l,r)]) yes;
            else no;
            continue;
        }
        node q = sg.query(1,0,n-1,l,r);
        dp[MP(l,r)] = (q.m2>=q.m1);
        if(q.m2>=q.m1) yes;
        else no;
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