#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<double,double> pdd;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) ll(i.size())
#define FOR(i, j, k, in) for (ll i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (ll i=j ; i>=k ; i-=in)
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
const ll MAXN = 100005;

ll n,q,dp[MAXN][305];
vector<int> edge[MAXN];

namespace SEG {
    ll dt[MAXN*4],N;
    void add(ll pos,ll val) {
        for (dt[pos+=N]+=val;pos>1;pos>>=1) {
            dt[pos>>1] = dt[pos] + dt[pos^1];
        }
    }

    ll query(ll l,ll r) {
        ll ret = 0;
        for (l+=N,r+=N;l<r;l>>=1,r>>=1) {
            if (l&1) {
                ret += dt[l++];
            }
            if (r&1) {
                ret += dt[--r];
            }
        }
        return ret;
    }
}

const ll MAXLG = __lg(MAXN) + 2;
int in[MAXN],out[MAXN],time_stamp;
int anc[MAXLG][MAXN],dep[MAXN];

void dfs(ll nd,ll par) {
    in[nd] = time_stamp++;
    anc[0][nd] = par;
    dep[nd] = dep[par]+1;
    for (auto v : edge[nd]) {
        if (v != par) {
            dfs(v,nd);
        }
    }
    out[nd] = time_stamp++;
}

void build_lca() {
    REP1 (i,MAXLG-1) {
        REP1 (nd,n) {
            anc[i][nd] = anc[i-1][anc[i-1][nd]];
        }
    }
}

ll lca(ll u,ll v) {
    debug(u,v);
    if (dep[u] > dep[v]) {
        swap(u,v);
    }
    for (ll i=MAXLG-1;i>=0;i--) {
        if (dep[anc[i][v]] >= dep[u]) {
            v = anc[i][v];
        }
    }
    debug(u,v);
    if (u == v) {
        return u;
    }
    for (ll i=MAXLG-1;i>=0;i--) {
        if (anc[i][u] != anc[i][v]) {
            u = anc[i][u];
            v = anc[i][v];
        }
    }
    return anc[0][u];
}

inline ll anc_cnt(ll i) {
    return SEG::query(in[1],out[i]);
}

pii a[MAXN];
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> q;
    REP (i,n-1) {
        ll u,v;
        cin >> u >> v;
        edge[u].emplace_back(v);
        edge[v].emplace_back(u);
    }

    dfs(1,1);
    build_lca();
    SEG::N = n * 2;
    pary(in+1,in+1+n);
    pary(out+1,out+1+n);

    while (q--) {
        ll k,m,r;
        cin >> k >> m >> r;
        
        REP (i,k) {
            ll ai;
            cin >> ai;
            a[i].X = ai;
            SEG::add(in[ai],1);
            SEG::add(out[ai],-1);
        }

        REP (i,k) {
            ll nd = lca(a[i].X,r);
            debug(a[i].X,r,nd);
            a[i].Y = anc_cnt(a[i].X) + anc_cnt(r) - 2*anc_cnt(nd);
            if (SEG::query(in[nd],in[nd]+1)) {
                a[i].Y++;
            }
            a[i].Y--;
        }

        sort(a,a+k,[&](const pii &p1,const pii &p2){return p1.Y < p2.Y;});

        dp[0][1] = 1;
        REP1 (i,k-1) {
            REP1 (j,m) {
                if (j <= a[i].Y) {
                    dp[i][j] = 0;
                } else {
                    dp[i][j] = dp[i-1][j]*(j-a[i].Y) + dp[i-1][j-1];
                    dp[i][j] %= MOD;
                }
            }
        }
        REP (i,k) {
            pary(dp[i]+1,dp[i]+1+m);
        }
        ll ans = 0;
        REP1 (i,m) {
            ans += dp[k-1][i];
            ans %= MOD;
        }
        cout << ans << endl;

        REP (i,k) {
            SEG::add(in[a[i].X],-1);
            SEG::add(out[a[i].X],1);
        }
    }
    return 0;
}
