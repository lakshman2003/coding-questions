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
    ll x, y;
    cin >> x >> y;
    x--; y--;
    ll n = 8;
    v2ll board(n, vll(n, 0));
    board[y][x] = 1;
    ll dx[] = {2, 1, -1, -2, -2, -1, 1, 2};
    ll dy[] = {1, 2, 2, 1, -1, -2, -2, -1};
    
    auto is_valid = [&](ll x, ll y) {
        return x >= 0 && x < n && y >= 0 && y < n && board[x][y] == 0;
    };
    
    function<bool(ll, ll, ll)> dfs = [&](ll x, ll y, ll cnt) {
        if (cnt == n * n) return true;
        vector<pair<ll, ll>> moves;
        for (ll i = 0; i < 8; i++) {
            ll nx = x + dx[i];
            ll ny = y + dy[i];
            if (is_valid(nx, ny)) {
                ll degree = 0;
                for (ll j = 0; j < 8; j++) {
                    ll nnx = nx + dx[j];
                    ll nny = ny + dy[j];
                    if (is_valid(nnx, nny)) degree++;
                }
                moves.push_back({degree, i});
            }
        }
        sort(moves.begin(), moves.end());
        for (auto move : moves) {
            ll i = move.second;
            ll nx = x + dx[i];
            ll ny = y + dy[i];
            board[nx][ny] = cnt + 1;
            if (dfs(nx, ny, cnt + 1)) return true;
            board[nx][ny] = 0;
        }
        return false;
    };
    
    if (dfs(y, x, 1)) {
        for (ll i = 0; i < n; i++) {
            for (ll j = 0; j < n; j++) {
                cout << board[i][j] << " ";
            }
            cout << en;
        }
    } else {
        cout << "No solution exists" << en;
    }
}

signed main(){
    fast
    solve();
    return 0;
}