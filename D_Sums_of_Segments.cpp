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
    ll n;
    cin>>n;
    vll v(n+1);
    fr(i,1,n+1) cin>>v[i];
    vll pre(n+1,0);
    fr(i,1,n+1) pre[i] = pre[i-1]+v[i];
    vll suff(n+2,0);
    fr_rev(i,n,1) suff[i] = suff[i+1]+pre[i];
    vll val(n+1,0);
    fr(i,1,n+1) val[i]= suff[i]- (n-i+1)*pre[i-1];
    vll pre2(n+1,0);
    fr(i,1,n+1) pre2[i] = pre2[i-1]+val[i];
    ll q;
    cin>>q;
    while(q--){
        ll l,r;
        cin>>l>>r;
        auto get = [&](ll x)->pll{
            ll lo= 1,hi = n,ans = n;
            while(lo<=hi){
                ll mid = (lo+hi)>>1;
                ll pos = n-mid+1;
                ll cnt = (n*(n+1))/2- ((pos-1)*pos)/2;
                if(cnt>=x){
                    ans = mid;
                    hi = mid-1;
                }
                else lo = mid+1;
            }
            ll t = n-ans+1;
            ll rem = x-((n*(n+1))/2-((t+1)*(t))/2);
            ll p = ans + (rem-1);
            return MP(ans,p);
        };
        auto s1 = get(l),s2 = get(r);
        ll ans = 0;
        ll x1 = s1.ff+1,x2 = s2.ff-1;
        if(x2>=x1){
            ans+= pre2[x2]-pre2[x1-1];
        }
        if(s1.ff==s2.ff){
            ll x= s1.ss,y = s2.ss;
            ans+= suff[x]-suff[y+1] - (y-x+1)*pre[s1.ff-1];
        }
        else
        {
            ans+= suff[s1.ss]- (n-s1.ss+1)*pre[s1.ff-1];
            ans+= suff[s2.ff]-suff[s2.ss+1]-(s2.ss-s2.ff+1)*pre[s2.ff-1];
        }
        cout<<ans<<en;
        
    }
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