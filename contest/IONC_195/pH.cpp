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
#define REP(i, j) for (int i=0; i<(j); i++)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(),_a.end()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define X first
#define Y second
#ifdef tmd
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
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 5003;
const ll K = 10;

int n, k, dp[MAXN][1<<K], dp2[MAXN][1<<K];
int p[MAXN];
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> k;
    int c, d;
    REP1 (i, n) {
        cin >> c;
        REP (j, c) {
            cin >> d;
            p[i] += 1<<(d-1);
        }
    }

    MEM(dp, iNF);
    dp[0][0] = 0;
    dp2[0][0] = 1;

    REP1 (i, n) {
        REP (mask, 1<<k) {
            dp[i][mask] = dp[i-1][mask];
            dp2[i][mask] = dp2[i-1][mask];

            int del = mask ^ p[i];
            if ((mask & p[i]) == p[i]) {
                for(int sub = p[i]; sub >= 0; sub = (sub-1) & p[i]){
                    int cur = sub + del;
                    if (dp[i-1][cur] + 1 < dp[i][mask]) {
                        dp[i][mask] = dp[i-1][cur] + 1;
                        dp2[i][mask] = dp2[i-1][cur];
                    } else if (dp[i-1][cur] + 1 == dp[i][mask]) {
                        dp2[i][mask] = ll(dp2[i][mask] + dp2[i-1][cur]) % MOD;
                    }
                    if (sub == 0) {
                        break;
                    }
                }
            }
        }
    }

    if (dp[n][(1<<k)-1] == iNF) {
        cout << -1 << endl;
    } else {
        cout << dp[n][(1<<k)-1] << " " << dp2[n][(1<<k)-1] << endl;
    }
    return 0;
}
