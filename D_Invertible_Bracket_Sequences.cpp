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
        t.resize(4*n+1);
    }

    ll merge(ll x,ll y)
    {
        return min(x,y);
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
            t[ind] = val;
            v[l]= val;
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
    string s;
    cin>>s;
    ll n = s.length();
    vll pre1(n+2,0);
    ll cnt = 0;
    bool ok= false;
    fr(i,1,n+1)
    {
        if(s[i-1]=='(') cnt++;
        else cnt--;
        if(cnt<0 or ok) 
        {
            pre1[i] = -1e16;
            ok = true;
        }
        else pre1[i] = cnt;
    }
    vll pre2(n+2,0);
    fr(i,1,n+1) 
    {
        if(s[i-1]=='(') pre2[i] = -1;
        else pre2[i] = 1;
        pre2[i]+=  pre2[i-1];
    }
    vll suff(n+2);
    suff[n] = 1;
    if(s[n-1]=='(') suff[n] = 1e16;
    fr_rev(i,n-1,1)
    {
        if(s[i-1]==')') suff[i] = suff[i+1]+1;
        else suff[i] = suff[i+1]-1;
    }
    map <ll,vll> mp;
    fr(i,1,n+1) mp[suff[i+1]-pre2[i]].pb(i);
    ll ans = 0;
    Segtree sg(n+2);
    sg.v = pre2;
    sg.build(1,0,n+1);
    fr(l,1,n+1)
    {
        ll lo = l;
        ll hi = n;
        ll maxi_r = 0;
        while(lo<=hi)
        {
            ll mid = (lo+hi)/2;
            ll q = sg.query(1,0,n+1,l,mid)-pre2[l-1];
            if(q+pre1[l-1]>=0)
            {
                maxi_r = mid;
                lo = mid+1;
            }
            else hi = mid-1;
        }
        if(maxi_r)
        {
            ll x = pre1[l-1]-pre2[l-1];
            if(!mp[x].size()) continue;
            auto it1 = lower_bound(all(mp[x]),l);
            auto it2 = upper_bound(all(mp[x]), maxi_r);
            ans+= (it2-it1);
        }
    }
    cout<<ans<<en;
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