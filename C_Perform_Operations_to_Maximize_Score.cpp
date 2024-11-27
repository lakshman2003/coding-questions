#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;



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

typedef tree<pll, null_type, less<pll>, rb_tree_tag,
             tree_order_statistics_node_update>
    indexed_set;

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
    vll b(n);
    getv(v,n);
    getv(b,n);
    vll zeros,ones;
    fr(i,0,n) {
        if(b[i]==1) ones.pb(v[i]);
        else zeros.pb(v[i]);
    }
    sort(all(zeros));
    sort(all(ones));
    vll suff(ones.size(),0);
    const ll right_max = 1e10;
    fr_rev(i,ones.size()-1,0){
        suff[i] = (right_max-ones[i]);
        if(i!=ones.size()-1) suff[i]+= suff[i+1];
    }

    auto check = [&](ll mid,ll removed){
        auto it = lower_bound(all(zeros),mid);
        ll n1 = zeros.end() - it;
        if(it!=zeros.end() and (*it)<=removed) n1--;
        ll pos = n/2;
        pos--;
        ll g = n-pos-1;
        if(n1>=g) return true;
        ll more = g-n1;
        it = lower_bound(all(ones),mid);
        ll extra = ones.end()-it;
        more-=extra;
        if(more<=0) return true;
        it--;
        ll r = it-ones.begin();
        ll l = r-more+1;
        if(l<0) return false;
        ll req = suff[l] - (((r+1)<ones.size())?suff[r+1]:0) - (more)*(right_max-mid);
        return req<=k;
    };

    iset st;
    fr(i, 0, n) st.insert(MP(v[i],i));
    ll ans = 0;
    fr(i,0,n){
        if(b[i]==1){
            ll val = v[i]+k;
            st.erase(st.find(MP(v[i],i)));
            ll med = st.find_by_order(n/2-1)->ff;
            ans = max(ans,val+med);
            st.insert(MP(v[i],i));
        }
        else
        {
            ll lo = v[i];
            ll hi = right_max;
            ll val = lo;
            while(lo<=hi){
                ll mid =(lo+hi)/2;
                ll med = mid-v[i];
                if(check(med,v[i])){
                    val = mid;
                    lo = mid+1;
                }
                else hi = mid-1;
            }
            ans = max(ans,val);
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