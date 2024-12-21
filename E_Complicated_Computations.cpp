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

struct node{
    ll maxi,left,right;
    node(){
        maxi = left = right = -1;
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

    node merge(node x,node y){
        node ans;
        ans.left = x.left;
        if(x.left==x.right and x.left!=-1) ans.left+= y.left;
        ans.right = y.right;
        if(y.left==y.right and y.right!=-1) ans.right+= x.right;
        ans.maxi = max({x.maxi,y.maxi,x.right+y.left});
        return ans;
    }

    void update(ll ind,ll l,ll r,ll pos,ll val)
    {
        if(l>pos or r<pos) return;
        if(l==r)
        {
            t[ind].left=  t[ind].right = t[ind].maxi = val;
            return;
        }
        ll mid = (l+r)>>1;
        update(ind<<1,l,mid,pos,val);
        update(ind<<1|1,mid+1,r,pos,val);
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
    ll n;
    cin>>n;
    vll v(n);
    getv(v,n);
    v2ll pos(n+1);
    fr(i,0,n){
        pos[v[i]].pb(i);
    }
    bool f= false;
    fr(i,2,n+1){
        if(sz(pos[i])){
            f= true;
            break;
        }
    }
    if(!f){
        cout<<1<<en;
        return;
    }
    Segtree st(n);
    for(auto x:pos[1]){
        st.update(1,0,n-1,x,1);
    }
    fr(i,2,n+1){
        for(auto x:pos[i]){
            st.update(1,0,n-1,x,-1);
        }
        ll q= st.query(1,0,n-1,0,n-1).maxi;
        cout<<q<<" ";
        if(q<i-1){
            cout<<i<<en;
            return;
        } 
        for(auto x:pos[i]){
            st.update(1,0,n-1,x,1);
        }
    }
    cout<<n+1<<en;
}

signed main(){
    fast
    solve();
    return 0;
}