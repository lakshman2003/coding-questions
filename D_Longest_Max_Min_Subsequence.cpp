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

struct node
{
    ll maxi,mini,pre;
    node(){
        maxi = -1;
        mini = 1e18;
        pre = 0;
    }
};
class Segtree
{
    public:
    ll n;
    vector <node> t;
    vll v;
    Segtree(ll x = 0)
    {
        n = x;
        t.resize(4*n+1);
    }

    node merge(node x,node y)
    {
        node ans;
        ans.maxi = max(x.maxi,y.maxi);
        ans.mini = min(x.mini,y.mini);
        ans.pre = x.pre+y.pre;
        return ans;
    }
    void build(ll ind,ll l,ll r)
    {
        if(l==r)
        {
            t[ind].maxi = t[ind].mini = v[l];
            return;
        }
        ll mid = (l+r)>>1;
        build(ind<<1,l,mid);
        build(ind<<1|1,mid+1,r);
        t[ind] = merge(t[ind<<1],t[ind<<1|1]);
    }

    void update(ll ind,ll l,ll r,ll pos){
        if(l>pos or r<pos) return;
        if (l == r)
        {
            t[ind].maxi = 0;
            t[ind].mini = 1e18;
            return;
        }
        ll mid = (l + r) >> 1;
        update(ind << 1, l, mid,pos);
        update(ind << 1 | 1, mid + 1, r,pos);
        t[ind] = merge(t[ind << 1], t[ind << 1 | 1]);
    }

    void update_pre(ll ind,ll l,ll r,ll pos,ll val){
        if (l > pos or r < pos)
            return;
        if (l == r)
        {
            t[ind].pre+= val;
            return;
        }
        ll mid = (l + r) >> 1;
        update_pre(ind << 1, l, mid, pos,val);
        update_pre(ind << 1 | 1, mid + 1, r, pos,val);
        t[ind] = merge(t[ind << 1], t[ind << 1 | 1]);
    } 

    node query(ll ind, ll l, ll r, ll lq, ll rq)
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
    ll n;
    cin>>n;
    vll v(n);
    getv(v,n);
    vll suff(n,0);
    set <ll> st;
    fr_rev(i,n-1,0){
        st.insert(v[i]);
        suff[i] = st.size();
    }

    map <ll,vll> pos;
    fr(i,0,n) pos[v[i]].pb(i);

    map <ll,vll> suff_pos;
    fr(i,0,n) suff_pos[suff[i]].pb(i);

    Segtree sg(n);
    sg.v = v;
    sg.build(1,0,n-1);
    ll curr = 1;
    ll ind = 0;
    vll res;
    while(curr<=suff[0]){
        ll lo = ind;
        ll hi = n-1;
        ll r = hi;
        while(lo<=hi){
            ll mid = (lo+hi)>>1;
            if(sg.query(1,0,n-1,0,mid).pre+suff[mid]==(suff[0]-curr+1)) {
                r = mid;
                lo = mid+1;
            }
            else hi = mid-1;
        }

        node q = sg.query(1,0,n-1,ind,r);
        ll val = ((curr&1)?q.maxi:q.mini);
        res.pb(val);
        for (auto x : pos[val])
        {
            sg.update(1, 0, n - 1, x);
        }

        ll val_ind = *lower_bound(all(pos[val]), ind);
        sg.update_pre(1,0,n-1,val_ind,-1);
        if(pos[val].back()<n-1){
            sg.update_pre(1, 0, n - 1, pos[val].back()+1, 1);
        }

        ind = val_ind+1;
        curr++;
    }

    cout<<suff[0]<<en;
    print(res);
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