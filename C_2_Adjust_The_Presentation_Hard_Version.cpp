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
    ll n,m,q;
    cin>>n>>m>>q;
    vll a(n),b(m);
    getv(a,n);
    fr(i,0,n) a[i]--;
    getv(b,m);
    fr(i,0,m) b[i]--;
    vll pos(n);
    fr(i,0,n) pos[a[i]] = i;
    vector <set<ll>> st(n); 
    fr(i,0,m) st[pos[b[i]]].insert(i);
    fr(i,0,n) st[i].insert(m);
    vll val(n);
    fr(i,0,n) val[i] = *st[i].begin();
    ll bad = 0;
    fr(i,0,n-1) if(val[i]>val[i+1]) bad++;
    
    auto out = [&bad]{
        if(bad) cout<<"TIDAK"<<en;
        else cout<<"YA"<<en;
    };
    out();

    while(q--){
        ll s,t;
        cin>>s>>t;
        s--;t--;
        ll prev = pos[b[s]];
        ll now = pos[t];
        st[prev].erase(s);
        st[now].insert(s);
        b[s] = t;
        set <pll> changes;
        if(prev<n-1) changes.insert(MP(prev,prev+1));
        if(prev-1>=0) changes.insert(MP(prev-1,prev));
        if (now < n - 1)
            changes.insert(MP(now, now + 1));
        if (now - 1 >= 0)
            changes.insert(MP(now - 1, now));
        for(auto [x,y]:changes){
            if(val[x]>val[y]) bad--;
        }
        val[prev] = *st[prev].begin();
        val[now] = *st[now].begin();
        for (auto [x, y] : changes)
        {
            if (val[x] > val[y])
                bad++;
        }
        out();
    }

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