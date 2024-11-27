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

pll dp[101][1LL<<17];
ll n;
ll v[101];
vll fac[61];
ll comp[61],spf[61];
ll arr[61];
pll rec(ll lvl,ll mask){
    if(lvl==n) return {0,0};
    if(dp[lvl][mask].ff!=-1) return dp[lvl][mask];
    if(mask==0 or v[lvl]==1) {
        return {v[lvl] - 1 + rec(lvl + 1, mask).ff,1};
    }
    pll ans = {v[lvl] - 1 + rec(lvl + 1, mask).ff,1};
    fr_e(i,2,59){
        bool ok = true;
        ll currmask = 0;
        for(auto x:fac[i]) {
            if (!(mask & (1LL << comp[x]))){
                ok = false;
                break;
            }
            currmask^= (1LL<<comp[x]);
        }
        if(ok){
            pll choice = rec(lvl + 1, mask ^ currmask);
            ans = min(ans,{abs(i-v[lvl])+choice.ff,i});
        };
    }
    return dp[lvl][mask] = ans;
}

void solve()
{
    cin>>n;
    fr(i,0,n) cin>>v[i];
    fr(i,1,61) spf[i] = i;
    fr(i,2,61) {
        spf[i] = 2;
        i++;
    }
    for(ll i = 3;i*i<61;i++){
        if(spf[i]==i){
            for(ll j = i*i;j<61;j+=i){
                if(spf[j]==j) spf[j]= i;
            }
        }
    }

    fr(i,2,61){
        set <ll> f;
        ll t= i;
        while(t>1){
            f.insert(spf[t]);
            t/=spf[t];
        }
        for(auto x:f) fac[i].pb(x);
    }

    ll sz= 0;
    fr(i,2,61) if(spf[i]==i) comp[i] = sz++;

    memset(dp,-1,sizeof(dp));
    pll curr = rec(0,(1LL<<17)-1);
    cout<<curr.ss<<" ";
    ll mask = (1LL<<17)-1;
    fr(i,1,n){
        ll newmask = mask;
        if(curr.ss!=1) for(auto x:fac[curr.ss]) newmask^=(1LL<<comp[x]);
        curr = rec(i,newmask);
        cout<<curr.ss<<" ";
        mask = newmask;
    }
}

signed main(){
    fast
    ll t= 1;
    while(t--)
    {
        solve();
    }
    return 0;
}