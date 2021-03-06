#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

const int MAXN = 100006;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1000000007;

int q, n;
string s, t;

bool check() {
    string fs = s, ft = t;
    sort(fs.begin(), fs.end());
    sort(ft.begin(), ft.end());

    return fs == ft;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> q;

    while (q--) {
        cin >> n >> s >> t;
        if (!check()) {
            cout << -1 << endl;
            continue;
        }

        int ans = n;
        REP (l, n) {
            int ptr = 0;
            for (int r=l; r<n; r++) {
                while (ptr < n && s[ptr] != t[r]) {
                    ptr++;
                }

                if (ptr == n) {
                    break;
                }
                ptr++;
                ans = min(ans, n - (r - l + 1));
            }
        }

        cout << ans << endl;
    }
    return 0;
}
