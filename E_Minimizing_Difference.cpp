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


void solve()
{
    ll n,k;
    cin>>n>>k;
    vll v(n);
    getv(v,n);
    sort(all(v));
    ll lo = 0;
    ll hi = 1e15;
    ll ans = lo;
    auto check = [&](ll mid){
        multiset <ll> mt1,mt2;
        fr(i,0,n){
            mt2.insert(v[i]);
            mt1.insert(v[i]);
        }
        ll s= accumulate(all(v),0LL);
        ll tot = 1e18;
        ll pre = 0;
        fr(i,0,n){
            while(!mt2.empty() and *mt2.begin()<=v[i]+mid){
                s-= *mt2.begin();
                mt2.erase(mt2.begin());
            }
            ll res = s-(mt2.size()*(v[i]+mid));
            res+= i*v[i]-pre;
            tot = min(tot,res);
            pre+= v[i];
        }

        s = 0;
        fr(i,0,n) s+= v[n-1]-v[0];
        ll suff = 0;
        fr_rev(i,n-1,0){
            while (!mt1.empty() and *mt1.rbegin() >= v[i] - mid)
            {
                s -= v[n-1]-*mt1.rbegin();
                mt1.erase(--mt1.end());
            }
            ll res = s - (mt1.size() * (v[n-1]-(v[i] - mid)));
            res += (n-1-i)* (v[n-1]-v[i]) - suff;
            tot = min(tot, res);
            suff+= (v[n-1]-v[i]);
        }
        return tot<=k;
    };
    while(lo<=hi){
        ll mid = (lo+hi)>>1;
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
    ll t =1;
    while(t--)
    {
        solve();
    }
    return 0;
}