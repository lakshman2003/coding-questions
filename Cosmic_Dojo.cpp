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
    vll v,freq;
    vpll t;
    Segtree(ll x = 0)
    {
        n = x;
        t.resize(4*n+1);
    }

    pll merge(pll x,pll y)
    {
        pll ans;
        ans.ff = x.ff+y.ff;
        ans.ss = x.ss+y.ss;
        return ans;
    }
    void build(ll ind,ll l,ll r)
    {
        if(l==r)
        {
            t[ind] = MP(v[l]*freq[l],freq[l]);
            return;
        }
        ll mid = (l+r)>>1;
        build(ind<<1,l,mid);
        build(ind<<1|1,mid+1,r);
        t[ind] = merge(t[ind<<1],t[ind<<1|1]);
    }


    void update(ll ind,ll l,ll r,ll pos,ll up)
    {
        if(l>pos or r<pos) return;
        if(l==r)
        {
            freq[l]+= up;
            t[ind] = MP(v[l] * freq[l],freq[l]);
            return;
        }
        ll mid = (l+r)>>1;
        update(ind<<1,l,mid,pos,up);
        update(ind<<1|1,mid+1,r,pos,up);
        t[ind] = merge(t[ind<<1],t[ind<<1|1]);
    }

    pll query(ll ind,ll l,ll r,ll lq,ll rq)
    {
        if(l>rq or r<lq) return MP(0,0);
        if(l>=lq and r<=rq) return t[ind];
        ll mid = (l+r)>>1;
        return merge(query(ind<<1,l,mid,lq,rq),query(ind<<1|1,mid+1,r,lq,rq));
    }
};

void solve()
{
    ll n,m,d;
    cin>>n>>m>>d;
    vll a(n),b(m);
    v2ll queries;
    set <ll> st;
    st.insert(0);
    fr(i,0,d){
        ll x,y,z;
        cin>>x>>y>>z;
        y--;
        queries.pb({x,y,z});
        st.insert(z);
    }

    map <ll,ll> comp,rev_comp;
    vll arr;
    ll sz = 0;
    for(auto x:st){
        comp[x] = sz;
        rev_comp[sz] = x;
        sz++;
        arr.pb(x);
    }

    Segtree sg1(sz),sg2(sz);
    sg1.v = arr;
    sg2.v = arr;
    a.assign(n,0);
    b.assign(m,0);
    vll freq1(sz,0),freq2(sz,0);
    freq1[0] = n,freq2[0] = m;
    sg1.freq = freq1;
    sg2.freq = freq2;
    sg1.build(1,0,sz-1);
    sg2.build(1,0,sz-1);

    ll ans = 0;
    for(auto q:queries){
        ll x = q[0],y = q[1],z = q[2];
        if(x==1){
            ll prev_ind = rev_comp[a[y]];
            ll curr_ind = comp[z];
            pll s1 = sg2.query(1,0,sz-1,0,prev_ind);
            pll s2 = sg2.query(1,0,sz-1,prev_ind+1,sz-1);
            ans-= s1.ff;
            ans-= a[y]*s2.ss;
            s1 = sg2.query(1, 0, sz - 1, 0, curr_ind);
            s2 = sg2.query(1, 0, sz - 1, curr_ind + 1, sz - 1);
            ans+= s1.ff;
            ans+= z*s2.ss;
            sg1.update(1,0,sz-1,prev_ind,-1);
            sg1.update(1,0,sz-1,curr_ind,1);
            a[y] = z;
        }
        else
        {
            ll prev_ind = rev_comp[b[y]];
            ll curr_ind = comp[z];
            pll s1 = sg1.query(1, 0, sz - 1, 0, prev_ind);
            pll s2 = sg1.query(1, 0, sz - 1, prev_ind + 1, sz - 1);
            ans -= s1.ff;
            ans -= b[y] * s2.ss;
            s1 = sg1.query(1, 0, sz - 1, 0, curr_ind);
            s2 = sg1.query(1, 0, sz - 1, curr_ind + 1, sz - 1);
            ans += s1.ff;
            ans += z * s2.ss;
            sg2.update(1, 0, sz - 1, prev_ind, -1);
            sg2.update(1, 0, sz - 1, curr_ind, 1);
            b[y] = z;
        }
        cout<<ans<<en;
    }
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