#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"#%d: %s = ",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
template<typename It> ostream& _printRng(ostream &os,It bg,It ed)
{
    os<<"{";
    for(It it=bg;it!=ed;it++) {
        os<<(it==bg?"":",")<<*it;
    }
    os<<"}";
    return os;
}
template<typename T> ostream &operator << (ostream &os,vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 100005;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, q, v[MAXN], c[MAXN];

/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> n >> q;
    REP (i, n) {
        cin >> v[i];
    }
    REP (i, n) {
        cin >> c[i];
    }

    while (q--) {
        int a, b;
        cin >> a >> b;
        vector<ll> dp(MAXN, -INF);
        int bst = 0, sec = 1;

        REP (i, n) {
            ll mx = (bst == c[i]) ? dp[sec] : dp[bst];
            dp[c[i]] = max(dp[c[i]], dp[c[i]] + 1LL * v[i] * a);
            dp[c[i]] = max(dp[c[i]], max(0LL, mx) + 1LL * v[i] * b);
            debug(dp[c[i]], v[i], c[i], mx, bst, sec);

            if (dp[c[i]] > dp[bst]) {
                sec = bst;
                bst = c[i];
            } else if (dp[c[i]] > dp[sec] && bst != c[i]){
                sec = c[i];
            }
        }

        cout << max(0LL,*max_element(dp.begin(), dp.end())) << endl;
    }
}
