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
    string s;
    cin>>s;
    if(n%2==0){
        vll freq(26,0);
        fr(i,0,n){
            if(i%2==0) freq[s[i]-'a']++;
        }
        ll ans = (n/2)-*max_element(all(freq));
        freq.assign(26,0);
        fr(i, 0, n)
        {
            if (i % 2)
                freq[s[i] - 'a']++;
        }
        ans += (n / 2) - *max_element(all(freq));
        cout<<ans<<en;
    }
    else
    {
        v2ll pre_odd(n,vll(26,0)),pre_even(n,vll(26,0));
        v2ll suff_odd(n, vll(26, 0)), suff_even(n, vll(26, 0));
        fr(i,0,n){
            if(i){
                fr(j, 0, 26)
                {
                    pre_odd[i][j] = pre_odd[i - 1][j];
                    pre_even[i][j] = pre_even[i - 1][j];
                }
            }
            if(i%2==0) pre_even[i][s[i]-'a']++;
            else pre_odd[i][s[i]-'a']++;
        }

        fr_rev(i, n-1, 0)
        {
            if (i<n-1)
            {
                fr(j, 0, 26)
                {
                    suff_odd[i][j] = suff_odd[i + 1][j];
                    suff_even[i][j] = suff_even[i + 1][j];
                }
            }
            if (i % 2 == 0)
                suff_even[i][s[i] - 'a']++;
            else
                suff_odd[i][s[i] - 'a']++;
        }   

        auto find_max = [&](vll &pe,vll &po,vll &se,vll &so){
            vll freq(26,0);
            fr(i,0,26) freq[i]+= pe[i]+se[i];
            ll ans = (n-1)/2- *max_element(all(freq));

            freq.assign(26,0);
            fr(i, 0, 26) freq[i] += po[i] + so[i];
            ans+= (n - 1) / 2 - *max_element(all(freq));
            return ans;
        };
        
        ll ans = 1e18;
        fr(i,0,n){
            vll t1(26),t2(26),t3(26),t4(26);
            if(i){
                t1 = pre_even[i-1];
                t2 = pre_odd[i-1];
            }
            if(i<n-1) {
                t3 = suff_odd[i+1];
                t4 = suff_even[i+1];
            }
            ans = min(ans,1+find_max(t1,t2,t3,t4));
        }
        cout<<ans<<en;
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