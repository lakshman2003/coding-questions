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
    ll n,q;
    cin>>n>>q;
    vector <pair<ll,ll>> arr;
    vll pos(n + 1, 1);
    fr(i,0,q){
        ll a;
        char ch;
        cin>>a>>ch;
        if(ch=='-') arr.pb({a,-1});
        else arr.pb({a,1});
        if(ch=='+') pos[a]++;
    }
    v2ll mp(n+1,vll(n+1,0));
    fr(i,1,n+1){
        fr(j,1,n+1){
            if(i==j) continue;
            ll l1 = 1,r1 = 1,l2 = 2,r2 = 2,d = 1;
            for(auto [x,y]:arr){
                if(x==i){
                    if(y==1) r1++;
                    else l1++;
                }
                else if(x==j){
                    if(y==1) r2++;
                    else l2++;
                }
                if(r1>=l2){
                    d++;
                    l2++,r2++;
                }
            }
            mp[i][j] = d;
        }
    }
    v2ll dp((1<<n)+1,vll(n+1,-1));
    auto rec = [&](auto &self,ll mask,ll last)->ll{
        if(mask==0) return pos[last];
        if(dp[mask][last]!=-1) return dp[mask][last];
        ll ans = 1e18;
        fr(i,1,n+1){
            if(mask&(1<<(i-1))){
                ans = min(ans,self(self,mask^(1<<(i-1)),i)+mp[last][i]);
            }
        }
        return dp[mask][last] = ans;
    };
    ll ans = 1e18;
    fr(i,1,n+1){
        ans = min(ans,rec(rec,(1<<n)-1^(1<<(i-1)),i));
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