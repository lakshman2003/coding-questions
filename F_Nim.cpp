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
    vll v(n);
    getv(v,n);
    v2ll queries(q);
    fr(i,0,q){
        ll l,r;
        cin>>l>>r;
        l--,r--;
        queries[i].pb(l);
        queries[i].pb(r);
        queries[i].pb(i);
    }
    ll block = sqrt(n);
    sort(all(queries),[&](vll &a,vll &b){
        if(a[0]/block!=b[0]/block) return a[0]/block<b[0]/block;
        return a[1]<b[1];
    });
    v2ll dp(105,vll(105,0)),dp1(105,vll(105,0));
    vpll ans(q,{0,0});
    auto add = [&](ll x){
        dp[x][1]++;
        fr(i,0,52){
            fr(j,1,52){
                ll val = x^i;
                if(val>52) cout<<val<<en;
                dp1[val][j+1]+=dp[i][j];
            }
        }
    };

    auto remove = [&](ll x){
        fr(i,0,52){
            fr_rev(j,52,1){
                ll val = x^i;
                (dp[val][j+1] = (dp[val][j+1]-dp[i][j]+mod))%=mod;
            }
        }
    };
    ll l = 0,r = -1;
    fr(i,0,q){
        ll l1 = queries[i][0],r1 = queries[i][1];
        while(r<r1){
            r++;
            add(v[r]);
        }
        while(l>l1){
            l--;
            add(v[l]);
        }
        while(r>r1){
            remove(v[r]);
            r--;
        }
        while(l<l1){
            remove(v[l]);
            l++;
        }
        fr(j,0,51){
            if(dp[0][j]){
                ans[queries[i][2]] = {r1-l1+1,dp[0][j]};
                break;
            }   
        }
    }
    fr(i,0,q) {
        if(ans[i].ff==0) cout<<-1<<en;
        else cout<<ans[i].ff<<" "<<ans[i].ss<<en;
    }

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