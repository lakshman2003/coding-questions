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


void solve()
{
    ll n,m,q;
    cin>>n>>m>>q;
    vector <iset> row(n+1),col(m+1);
    auto query1 = [&](ll ind, iset &st)
    {
        ll lo = 1;
        ll hi = ind;
        ll res = 1;
        while (lo <= hi)
        {
            ll mid = (lo + hi) / 2;
            auto it = st.lower_bound(mid);
            ll cnt = st.order_of_key(ind) - st.order_of_key(*it);
            if (cnt+1 == (ind - mid + 1))
            {
                res = mid;
                hi = mid - 1;
            }
            else
                lo = mid + 1;
        }
        return res - 1;
    };

    auto query2 = [&](ll ind, iset &st, ll maxi)
    {
        ll lo = ind;
        ll hi = maxi;
        ll res = maxi;
        while (lo <= hi)
        {
            ll mid = (lo + hi) / 2;
            auto it= st.upper_bound(mid);
            it--;
            ll cnt = st.order_of_key(*it) - st.order_of_key(ind);
            if (cnt+1 == (mid-ind + 1))
            {
                res = mid;
                lo = mid + 1;
            }
            else
                hi = mid - 1;
        }
        return res + 1;
    };

    set <pll> dest;
    ll ans = n*m;
    fr(i,0,q){
        ll x,y;
        cin>>x>>y;
        
        if(dest.find(MP(x,y))==dest.end()){
            ans--;
            dest.insert(MP(x,y));
            row[x].insert(y);
            col[y].insert(x);
        }
        else
        {
            ll c1 = query1(y,row[x]);
            ll c2 = query2(y,row[x],m);
            ll r1 = query1(x, col[y]);
            ll r2 = query2(x, col[y], n);
            if(c1>=1){
                ans--;
                row[x].insert(c1);
                col[c1].insert(x);
                dest.insert(MP(x,c1));
            }
            if(c2<=m){
                ans--;
                row[x].insert(c2);
                col[c2].insert(x);
                dest.insert(MP(x, c2));
            }
            if (r1>=1)
            {
                ans--;
                col[y].insert(r1);
                row[r1].insert(y);
                dest.insert(MP(r1, y));
            }
            if (r2<=n)
            {
                ans--;
                col[y].insert(r2);
                row[r2].insert(y);
                dest.insert(MP(r2, y));
            }
        }
    }
    cout<<ans<<en;
}

signed main(){
    fast
    solve();
    return 0;
}