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

ll n,q;
vector <vpll> g;
vll odd,even,cum_xor,dist;
struct node
{
    ll val;
    node* child[2];
    node()
    {
        child[0] = child[1] = NULL;
        val = 0;
    }
};

struct Trie
{
    node *root;
    Trie()
    {
        root= new node;
    }

    void insert(ll val)
    {
        node *curr= root;
        for(int i = 31;i>=0;i--)
        {
            curr->val++;
            ll x=  (val>>i)&1;
            if(curr->child[x]==NULL) curr->child[x] = new node;
            curr = curr->child[x];
        }
        curr->val++;
    }


    void remove(ll val)
    {
        node *curr = root;
        for(int i = 31;i>=0;i--)
        {
            if(curr==NULL) break;
            curr->val--;
            ll x = (val>>i)&1;
            curr = curr->child[x];
        }
        if(curr!=NULL) curr->val--;
    }

    ll find_best(ll val)
    {
        ll ans = 0;
        node *curr = root;
        for(int i = 31;i>=0;i--)
        {
            ll x = (val >> i) & 1;
            if(curr->child[x^1]!=NULL and curr->child[x^1]->val)
            {
                ans+= 1LL<<i;
                curr = curr->child[x^1];
            }
            else if(curr->child[x]!=NULL and curr->child[x]->val) curr = curr->child[x];
            else break;
        }
        return ans;
    }

};


void dfs(ll node,ll p,ll curr_xor,ll d)
{
    if(d&1) odd.pb(curr_xor);
    else even.pb(curr_xor);
    cum_xor[node] = curr_xor;
    dist[node] = d;
    for(auto edge:g[node])
    {
        auto [x,wei]= edge;
        if(x==p) continue;
        dfs(x,node,curr_xor^wei,d+1);
    }
}

void solve()
{
    cin>>n>>q;
    g.clear();
    g.resize(n);
    cum_xor.resize(n,0);
    odd.clear();
    even.clear();
    dist.resize(n,0);
    fr(i,0,n-1)
    {
        ll a,b,w;
        cin>>a>>b>>w;
        a--;b--;
        g[a].pb(MP(b,w));
        g[b].pb(MP(a,w));
    }   
    dfs(0,-1,0,0);
    Trie t_odd,t_even;
    for(auto x:odd) t_odd.insert(x);
    for(auto x:even) t_even.insert(x);

    ll curr_xor = 0;
    while(q--)
    {
        char ch;
        cin>>ch;
        if(ch=='^') 
        {
            ll x;
            cin>>x;
            curr_xor^=x;
        }
        else
        {
            ll x,w;
            cin>>x>>w;
            x--;
            w^=cum_xor[x];
            ll ans = 0;
            if(dist[x]&1)
            {
                t_odd.remove(cum_xor[x]);
                ans = t_odd.find_best(w);
                t_odd.insert(cum_xor[x]);
                ans = max(ans,t_even.find_best(w^curr_xor));
            }
            else
            {
                t_even.remove(cum_xor[x]);
                ans = t_even.find_best(w);
                t_even.insert(cum_xor[x]);
                ans = max(ans, t_odd.find_best(w ^ curr_xor));
            }
            cout<<ans<<" ";
        }
    }
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