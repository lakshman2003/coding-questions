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
    vll t;
    Segtree(ll x = 0)
    {
        n = x;
        t.resize(4*n+1,-1);
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
        if(l>rq or r<lq) return -1;
        if(l>=lq and r<=rq) return t[ind];
        ll mid = (l+r)>>1;
        return merge(query(ind<<1,l,mid,lq,rq),query(ind<<1|1,mid+1,r,lq,rq));
    }
};

class Solution
{
public:
    vector<int> maximumSumQueries(vector<int> &nums1, vector<int> &nums2, vector<vector<int>> &queries)
    {
        int n = nums1.size();
        vector <pair <int,int>> arr;
        for(int i=0;i<n;i++)
        {
            arr.push_back({nums1[i],nums2[i]});
        }
        sort(arr.begin(),arr.end(),[&](auto &a,auto &b)
        {
            if(a.first!=b.first) return a.first>b.first;
            return a.second>b.second;
        });
        vector <int> idx;
        int m = queries.size();
        for(int i= 0;i<m;i++) idx.push_back(i);
        sort(idx.begin(),idx.end(),[&](auto &a,auto &b)
        {
            return queries[a][0]>queries[b][0];
        });
        vector <int> ans(m);
        map <ll,ll> comp;
        for(auto &x:nums2) comp[x];
        for(auto &x:queries) comp[x[1]];
        ll compsz = 0;
        for(auto &[x,y]:comp) y = compsz++;
        Segtree st(compsz);
        ll ind = -1;
        for(int i = 0;i<m;i++){
            while(ind+1<n and arr[ind+1].first>=queries[idx[i]][0])
            {
                ind++;
                st.update(1,0,compsz-1,comp[arr[ind].second],arr[ind].first+arr[ind].second);
            }
            ans[idx[i]] = st.query(1,0,compsz-1,comp[queries[idx[i]][1]],compsz-1);
        }
        return ans;

    }
};