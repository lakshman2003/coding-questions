#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<int>, rb_tree_tag,
tree_order_statistics_node_update> indexed_set;

#define ll int
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


void solve()
{
    ll a,b,n,q;
    cin>>a>>b>>n>>q;
    map <ll,set <ll>> mprow,mpcol;
    fr(i,0,n)
    {
        ll x,y;
        cin>>x>>y;
        mprow[x].insert(y);
        mpcol[y].insert(x);
    }

    ll rowl = 1, rowr = a,coll = 1,colr = b;
    ll ans1 = 0,ans2= 0;
    fr(i,0,q)
    {
        char ch;
        ll x;
        cin>>ch>>x;
        ll ans = 0;
        if(ch=='U')
        {
            while(1)
            {
                auto it = mprow.lower_bound(rowl);
                if(it==mprow.end() or it->ff>=rowl+x) break;
                ll t = it->ff;
                if(mprow.find(t)==mprow.end()) continue;
                ans += mprow[t].size();
                for (auto y : mprow[t])
                {
                    mpcol[y].erase(t);
                    if (mpcol[y].size() == 0)
                        mpcol.erase(y);
                }
                mprow.erase(t);
            }
            rowl+=x;
        }

        else if(ch=='D')
        {
            while (1)
            {
                auto it = mprow.upper_bound(rowr);
                if (it == mprow.begin() or (--it)->ff <= rowr - x)
                    break;
                ll t = it->ff;
                if (mprow.find(t) == mprow.end())
                    continue;
                ans += mprow[t].size();
                for (auto y : mprow[t])
                {
                    mpcol[y].erase(t);
                    if (mpcol[y].size() == 0)
                        mpcol.erase(y);
                }
                mprow.erase(t);
            }
            rowr -= x;
        }

        else if(ch=='L')
        {
            while (1)
            {
                auto it = mpcol.lower_bound(coll);
                if (it == mpcol.end() or it->ff >= coll + x)
                    break;
                ll t = it->ff;
                if (mpcol.find(t) == mpcol.end())
                    continue;
                ans += mpcol[t].size();
                for (auto y : mpcol[t])
                {
                    mprow[y].erase(t);
                    if (mprow[y].size() == 0)
                        mprow.erase(y);
                }
                mpcol.erase(t);
            }
            coll += x;
        }

        else
        {
            while (1)
            {
                auto it = mpcol.upper_bound(colr);
                if (it == mpcol.begin() or (--it)->ff <= colr - x)
                    break;
                ll t = it->ff;
                if (mpcol.find(t) == mpcol.end())
                    continue;
                ans += mpcol[t].size();
                for (auto y : mpcol[t])
                {
                    mprow[y].erase(t);
                    if (mprow[y].size() == 0)
                        mprow.erase(y);
                }
                mpcol.erase(t);
            }
            colr -= x;
        }
        
        if(i&1) ans2+=ans;
        else ans1+=ans;
    }
    cout<<ans1<<" "<<ans2<<en;
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