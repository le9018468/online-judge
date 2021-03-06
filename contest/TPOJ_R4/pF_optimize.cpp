#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<double,double> pdd;
#define SQ(i) ((i)*(i))
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) int(i.size())
#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(),_a.end()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define X first
#define Y second
#ifdef tmd
#define TIME(i) Timer i(#i)
#define debug(...) do{\
    fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template<typename T>void _do(T &&_x){cerr<<_x<<endl;}
template<typename T,typename ...S> void _do(T &&_x,S &&..._t){cerr<<_x<<" ,";_do(_t...);}
template<typename _a,typename _b> ostream& operator << (ostream &_s,const pair<_a,_b> &_p){return _s<<"("<<_p.X<<","<<_p.Y<<")";}
template<typename It> ostream& _OUTC(ostream &_s,It _ita,It _itb)
{
    _s<<"{";
    for(It _it=_ita;_it!=_itb;_it++)
    {
        _s<<(_it==_ita?"":",")<<*_it;
    }
    _s<<"}";
    return _s;
}
template<typename _a> ostream &operator << (ostream &_s,vector<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,set<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,deque<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define TIME(i)
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif
class Timer {
private:
    string scope_name;
    chrono::high_resolution_clock::time_point start_time;
public:
    Timer (string name) : scope_name(name) {
        start_time = chrono::high_resolution_clock::now();
    }
    ~Timer () {
        auto stop_time = chrono::high_resolution_clock::now();
        auto length = chrono::duration_cast<chrono::microseconds>(stop_time - start_time).count();
        double mlength = double(length) * 0.001;
        debug(scope_name, mlength);
    }
};

const ll MOD = 998244353;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 4096;

int n;
ll a[MAXN];
ll pre[MAXN], tr[MAXN][MAXN], dp[2][MAXN];

bool lt (ll a1, ll a2, ll b1, ll b2, ll k) {
    ll sumA = k * (a1 + SQ(a2));
    ll sumB = k * (b1 + SQ(b2));
    return sumA < sumB;
}

ll mpow(ll base,ll ep) {
    ll ret = 1;
    while (ep > 0) {
        if (ep & 1) {
            ret = ret * base % MOD;
        }
        base = base * base % MOD;
        ep >>= 1;
    }
    return ret;
}

void solve (int j, int nL, int nR, int tL, int tR) {
    if (nL <= nR) {
        int mid = (nL + nR) >> 1;
        ll sum = pre[mid];
        ll tr = 0;
        for (int k = max(0, tL); k <= min(mid-1, tR); k++) {
            ll cur = pre[mid] - pre[k];
            if (lt(dp[(j&1)^1][k], cur, dp[(j&1)^1][tr], sum, mid)) {
                tr = k;
                sum = cur;
            }
        }
        dp[j&1][mid] = dp[(j&1)^1][tr] + SQ(sum);

        solve(j, nL, mid-1, tL, tr);
        solve(j, mid + 1, nR, tr, tR);
    }
}
/********** Good Luck :) **********/
int main()
{
    TIME(main);
    IOS();
    cin >> n;
    REP1 (i, n) {
        cin >> a[i];
        pre[i] = pre[i-1] + a[i];
    }

    
    REP1 (i, n) {
        dp[0][i] = 100000000000000;
    }
    REP1 (i, n) {
        solve(i, i, n, 1, n);
        ll invn = mpow(i, MOD - 2);
        ll sqm = SQ((pre[n] * invn) % MOD) % MOD;
        cout << (((dp[i&1][n]%MOD * invn % MOD) - sqm) % MOD + MOD) % MOD << endl;
    }

    return 0;
}