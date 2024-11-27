#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<int>, rb_tree_tag,
tree_order_statistics_node_update> indexed_set;

#define ll long long
#define vll vector<ll>
#define pb push_back
#define ldd long double
#define en '\n'
#define MP make_pair
#define pii pair<int, int>
#define pll pair<ll, ll>
#define ff first
#define ss second
#define vi vector<int>
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


// class Segtree
// {
//     public:
//     ll n;
//     vll v;
//     v2ll t;
//     Segtree(ll x = 0)
//     {
//         n = x;
//         t.resize(4*n+10);
//     }

//     vll merge(vll a,vll b)
//     {
//         vll ans;
//         ll i = 0,j = 0;
//         while(i<a.size() and j<b.size()){
//             if(a[i]<=b[j]){
//                 ans.pb(a[i++]);
//             }
//             else {
//                 ans.pb(b[j++]);
//             }
//         }
//         while(i<a.size()) ans.pb(a[i++]);
//         while(j<b.size()) ans.pb(b[j++]);
//         return ans;
//     }

//     void build(ll ind,ll l,ll r)
//     {
//         if(l==r)
//         {
//             t[ind] = {v[l]};
//             return;
//         }
//         ll mid = (l+r)>>1;
//         build(ind<<1,l,mid);
//         build(ind<<1|1,mid+1,r);
//         t[ind] = merge(t[ind<<1],t[ind<<1|1]);
//     }

//     ll query(ll ind,ll l,ll r,ll lq,ll rq,ll x)
//     {
//         if(l>rq or r<lq) return 0;
//         if(l>=lq and r<=rq) return upper_bound(t[ind].begin(),t[ind].end(),x)-t[ind].begin();
//         ll mid = (l+r)>>1;
//         return query(ind<<1,l,mid,lq,rq,x)+query(ind<<1|1,mid+1,r,lq,rq,x);
//     }
// };

// vll getnumpoints(vector <ll> layers, vector <ll> energy,ll k){
//     ll n = layers.size();
//     vector <ll> pre(n+1,0);
//     for(ll i = 1;i<=n;i++) pre[i] = pre[i-1]+layers[i-1];
//     vll arr(n+1);
//     arr[0] = INF;
//     fr(i,1,n+1) arr[i] = energy[i-1]+pre[i];
//     Segtree sg;
//     sg.v= arr;
//     sg.build(1,1,n);
//     vector <ll> ans(n);
//     fr(i,1,n+1){
//         ll l = i,r = upper_bound(all(pre),pre[l-1]+k)-pre.begin();
//         ll q = sg.query(1,1,n,l,r,k+pre[i-1]);
//         ans[i-1] = q;
//     }
//     return ans;
// }


struct FenwickTree
{
    int size;
    vector<int> tree;
    FenwickTree(int n)
    {
        size = n;
        tree.assign(n + 1, 0);
    }
    void update(int idx)
    {
        while (idx <= size)
        {
            tree[idx] += 1;
            idx += idx & -idx;
        }
    }
    int query(int idx)
    {
        int res = 0;
        while (idx > 0)
        {
            res += tree[idx];
            idx -= idx & -idx;
        }
        return res;
    }
};

vector<int> getNumPoints(vector<int> layers, vector<int> energy, long k)
{
    int n = layers.size();
    vector<long> prefix(n + 1, 0);
    for (int i = 0; i < n; i++)
        prefix[i + 1] = prefix[i] + (long)energy[i];
    vector<long> S(n, 0);
    for (int j = 0; j < n; j++)
        S[j] = prefix[j + 1] + layers[j];
    vector<long> sorted_S = S;
    sort(sorted_S.begin(), sorted_S.end());
    sorted_S.erase(unique(sorted_S.begin(), sorted_S.end()), sorted_S.end());
    FenwickTree ft(sorted_S.size());
    vector<int> ans(n, 0);
    for (int j = 0; j < n; j++)
    {
        ft.update(lower_bound(sorted_S.begin(), sorted_S.end(), S[j]) - sorted_S.begin() + 1);
    }
    for (int i = 0; i < n; i++)
    {
        // Find j_max where prefix[j+1] - prefix[i] <=k
        long target = k + prefix[i];
        int j_max = upper_bound(prefix.begin() + i + 1, prefix.end(), target) - prefix.begin() - 1;
        if (j_max < i)
        {
            ans[i] = 0;
            continue;
        }
        // Find number of j in [i..j_max] where S[j] <=k +prefix[i]
        long C = k + prefix[i];
        int cnt = upper_bound(sorted_S.begin(), sorted_S.end(), C) - sorted_S.begin();
        cnt = ft.query(cnt);
        // Adjust count for j_max
        ans[i] = cnt;
    }
    return ans;
}
void solve()
{
    ll n,k;
    cin>>n>>k;
    vi l(n),e(n);
    getv(l,n);
    getv(e,n);
    auto ans = getNumPoints(l, e, k);
    print(ans);
    cout<<en; 
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