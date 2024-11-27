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
#define mod 1000000007
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


struct node
{
    int left, right, zeros, runs,lazy,cnt;
    node()
    {
        left = right = 0;
        zeros = 0;
        runs = 0;
        lazy = 0;
        cnt = 0;
    }
};

class Segtree
{
    public:  
    ll n;
    vector <node> t;
    Segtree(ll x = 0)
    {
        n = x;
        t.resize(4*n+1);
    }


    void push(ll ind,ll l,ll r){
        if(t[ind].lazy){
            if (l != r)
            {
                ll mid = (l + r) >> 1;
                t[ind << 1].lazy+= t[ind].lazy;
                t[ind << 1 | 1].lazy+= t[ind].lazy;
            }
            t[ind].zeros = 0;
            t[ind].cnt+= (r-l+1)*t[ind].lazy;
            t[ind].lazy = 0;
        }
    }

    node merge(node x,node y)
    {
        node ans;
        ans.zeros = x.zeros+y.zeros;
        ans.runs = x.runs + y.runs;
        ans.left = x.left;
        ans.right = y.right;
        ans.cnt = x.cnt+y.cnt;
        if(x.right==y.left and x.right) ans.runs--;
        return ans;
    }

    void build(ll ind, ll l, ll r)
    {
        if (l == r) 
        {
            t[ind].zeros = 1;
            return;
        }
        ll mid = (l + r) >> 1;
        build(ind << 1, l, mid);
        build(ind << 1 | 1, mid + 1, r);
        t[ind] = merge(t[ind << 1], t[ind << 1 | 1]);
    }

    void update(ll ind,ll l,ll r,ll lq ,ll rq,ll op)
    {
        push(ind,l,r);
        if(l>rq or r<lq) return;
        if(l>=lq and r<=rq)
        {
            t[ind].lazy+= 1;
            t[ind].left = t[ind].right = op;
            t[ind].runs = 1;
            push(ind,l,r);
            return;
        }
        ll mid = (l+r)>>1;
        update(ind<<1,l,mid,lq,rq,op);
        update(ind<<1|1,mid+1,r,lq,rq,op);
        t[ind] = merge(t[ind<<1],t[ind<<1|1]);
    }

    node query(ll ind,ll l,ll r,ll lq,ll rq)
    {
        push(ind,l,r);
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
    v2ll g;
    fr(i,0,q){
        ll l,r,c;
        cin>>l>>r>>c;
        g.pb(vll{c,l-1,r-1});
    }
    sort(all(g));
    Segtree sg(n);
    sg.build(1,0,n-1);
    ll ans= 0;
    ll op = 0;
    for(auto v:g){
        ll c= v[0],l = v[1],r = v[2];
        node q = sg.query(1,0,n-1,l,r);
        ans+= (q.zeros+q.runs)*c;
        sg.update(1,0,n-1,l,r,++op);
    }
    bool ok = true;
    for(auto v:g){
        ll c = v[0], l = v[1], r = v[2];
        if(l!=0 and sg.query(1,0,n-1,l,l).cnt==1) ok = false;
        if(r!=n-1 and sg.query(1,0,n-1,r,r).cnt==1) ok = false;
    }
    fr(i,0,n){
        if (sg.query(1, 0, n - 1, i, i).cnt == 0) ok = false;
    }
    if(!ok) ans=-1; 
    cout<<ans<<en;
}

signed main(){
    fast
    solve();
    return 0;
}