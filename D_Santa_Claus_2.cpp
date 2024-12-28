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
    ll n,m,sx,sy;
    cin>>n>>m>>sx>>sy;
    map <ll,vll> mpx,mpy;
    fr(i,0,n){
        ll x,y;
        cin>>x>>y;
        mpx[x].pb(y);
        mpy[y].pb(x);
    }
    for(auto &[x,y]:mpx){
        sort(all(y));
    }
    for(auto &[y,x]:mpy){
        sort(all(x));
    }
    ll currx = sx, curry = sy;
    map <ll,vll> prex,prey;
    for(auto &[x,y]:mpx){
        prex[x].resize(sz(y)+1);
    }
    for(auto &[y,x]:mpy){
        prey[y].resize(sz(x)+1);
    }
    fr(i,0,m){
        char d;
        ll c;
        cin>>d>>c;
        if(d=='U'){
            if(mpx.find(currx)!=mpx.end()){
                ll ind1 = lower_bound(all(mpx[currx]),curry)-mpx[currx].begin();
                ll ind2 = upper_bound(all(mpx[currx]),curry+c)-mpx[currx].begin();
                prex[currx][ind1]++;
                prex[currx][ind2]--;
            }
            curry+=c;
        }
        else if(d=='D'){
            if(mpx.find(currx)!=mpx.end()){
                ll ind1 = lower_bound(all(mpx[currx]),curry-c)-mpx[currx].begin();
                ll ind2 = upper_bound(all(mpx[currx]),curry)-mpx[currx].begin();
                prex[currx][ind1]++;
                prex[currx][ind2]--;
            }
            curry-=c;
        }
        else if(d=='L'){
            if(mpy.find(curry)!=mpy.end()){
                ll ind1 = lower_bound(all(mpy[curry]),currx-c)-mpy[curry].begin();
                ll ind2 = upper_bound(all(mpy[curry]),currx)-mpy[curry].begin();
                prey[curry][ind1]++;
                prey[curry][ind2]--;
            }
            currx-=c;
        }
        else{
            if(mpy.find(curry)!=mpy.end()){
                ll ind1 = lower_bound(all(mpy[curry]),currx)-mpy[curry].begin();
                ll ind2 = upper_bound(all(mpy[curry]),currx+c)-mpy[curry].begin();
                prey[curry][ind1]++;
                prey[curry][ind2]--;
            }
            currx+=c;
        }
    }
    set <pll> st;
    for(auto &[x,y]:mpx){
        fr(i,1,sz(y)){
            prex[x][i]+=prex[x][i-1];
        }
        fr(i,0,sz(y)){
            if(prex[x][i]>0)
                st.insert({x,mpx[x][i]});
        }
    }
    for(auto &[y,x]:mpy){
        fr(i,1,sz(x)){
            prey[y][i]+=prey[y][i-1];
        }
        fr(i,0,sz(x)){
            if(prey[y][i]>0)
                st.insert({mpy[y][i],y});
        }
    }   
    cout<<currx<<" "<<curry<<" "<<sz(st)<<en;

}

signed main(){
    fast
    solve();
    return 0;
}