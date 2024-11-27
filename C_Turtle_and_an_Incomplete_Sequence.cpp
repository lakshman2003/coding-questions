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

pll common(ll x,ll y)
{
    string s1,s2;
    while(x>0)
    {
        if(x&1) s1 = '1'+ s1;
        else s1 = '0'+s1;
        x/=2;
    }
    while (y > 0)
    {
        if (y & 1)
            s2 = '1' + s2;
        else
            s2 = '0' + s2;
        y /= 2;
    }

    ll i = 0,j = 0, c = 0;
    while(i<s1.length() and j<s2.length() and s1[i]==s2[j])
    {
        i++;
        j++;
        c++;
    }

    return MP(s1.length()-c,s2.length()-c);
}
void solve()
{
    ll n;
    cin>>n;
    vll v(n);
    getv(v,n);
    vpll arr;
    fr(i,0,n) if(v[i]!=-1) arr.pb(MP(i,v[i]));
    if(arr.size()==0)
    {
        ll curr = 1;
        fr(i,0,n)
        {
            cout<<curr<<" ";
            if(curr==1) curr=2;
            else curr=1;
        }
        cout<<en;
        return;
    }
    vll ans = v;
    ll pos = arr[0].ff;
    fr_rev(i,pos-1,0)
    {
        if(ans[i+1]%2==0) ans[i] = ans[i+1]/2;
        else ans[i] = ans[i+1]*2;
    }
    fr(i,0,arr.size()-1)
    {
        auto [p1,x] = arr[i];
        auto [p2,y] = arr[i+1];
        auto [e1,e2] = common(x,y);
        ll extra = (p2-p1-1-e1-e2);
        if(extra<-1 or extra%2==0)
        {
            cout<<-1<<en;
            return;
        }
        fr(j,p1+1,p1+e1+1) ans[j] = ans[j-1]/2;
        fr_rev(j,p2-1,p2-e2) ans[j] = ans[j+1]/2;
        ll ind1 = p1+e1+1;
        ll ind2 = p2-e2-1;
        while(ind1<=ind2)
        {
            if (ans[ind1-1] % 2 == 0)
                ans[ind1] = ans[ind1-1] / 2;
            else
                ans[ind1] = ans[ind1-1] * 2;
            ans[ind2] = ans[ind1];
            ind1++;
            ind2--;
        }
    }
    pos = arr.back().ff;
    fr(i, pos +1, n)
    {
        if (ans[i - 1] % 2 == 0)
            ans[i] = ans[i - 1] / 2;
        else
            ans[i] = ans[i - 1] * 2;
    }
    print(ans);
    cout<<en;
    
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