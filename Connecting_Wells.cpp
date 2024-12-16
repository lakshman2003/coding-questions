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


class Union_Find
{
    public:
    ll n;
    vll par,rank;
    ll comp;
    
    Union_Find(ll x = 0)
    {
        n = x;
        par.resize(n);
        rank.resize(n,1);
        fr(i,0,n) par[i] = i;
        comp = n;
    }

    ll find(ll x)
    {
        if(par[x]==x) return x;
        return par[x] = find(par[x]);
    }

    void unite(ll a,ll b)
    {
        a = find(a);
        b = find(b);
        if(a==b) return;
        if(rank[a]<rank[b]) swap(a,b);
        rank[a]+= rank[b];
        par[b] = a;
        comp--;
    }
};

void solve()
{
    ll n;
    cin>>n;
    vpll pos(n);
    fr(i,0,n)
    {
        cin>>pos[i].ff>>pos[i].ss;
    }
    auto check = [&](ll mid)
    {
        Union_Find dsu(n);
        fr(i, 0, n)
        {
            fr(j, i + 1, n)
            {
                if (pos[i].ss == pos[j].ss)
                {
                    ll l1 = pos[i].ff - mid, r1 = pos[i].ff + mid;
                    ll l2 = pos[j].ff - mid, r2 = pos[j].ff + mid;
                    if (max(l2, l1) <= min(r1, r2))
                    {
                        dsu.unite(i, j);
                    }
                }
                else if (pos[i].ff == pos[j].ff)
                {
                    ll l1 = pos[i].ss - mid, r1 = pos[i].ss + mid;
                    ll l2 = pos[j].ss - mid, r2 = pos[j].ss + mid;
                    if (max(l2, l1) <= min(r1, r2))
                    {
                        dsu.unite(i, j);
                    }
                }
                else
                {
                    ll lx1 = pos[i].ff - mid, rx1 = pos[i].ff + mid;
                    ll lx2 = pos[j].ff - mid, rx2 = pos[j].ff + mid;
                    ll ly1 = pos[i].ss - mid, ry1 = pos[i].ss + mid;
                    ll ly2 = pos[j].ss - mid, ry2 = pos[j].ss + mid;
                    if (pos[j].ff >= lx1 and pos[j].ff <= rx1 and pos[i].ss >= ly2 and pos[i].ss <= ry2)
                    {
                        dsu.unite(i, j);
                    }
                    if (pos[i].ff >= lx2 and pos[i].ff <= rx2 and pos[j].ss >= ly1 and pos[j].ss <= ry1)
                    {
                        dsu.unite(i, j);
                    }
                }
            }
        }
        return dsu.comp==1;
    };
    ll lo = 0, hi = 1e9;
    ll ans = hi;
    while (lo <= hi)
    {
        ll mid = (lo+hi)/2;
        if(check(mid)){
            ans = mid;
            hi = mid-1;
        }
        else lo = mid+1;
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