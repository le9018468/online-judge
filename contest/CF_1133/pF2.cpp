#include <bits/stdc++.h>
using namespace std;
typedef int ll;
typedef pair<ll, ll> pii;
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
const ll MAXN = 200003;

ll n,m,d;
vector<ll> edge[MAXN];

ll djs[MAXN],sz[MAXN];
void init() {
    REP (i,MAXN) {
        djs[i] = i;
        sz[i] = 1;
    }
}

ll fnd(ll x) {
    return x == djs[x] ? x : (djs[x] = fnd(djs[x]));
}

bool uni(ll x,ll y) {
    if (sz[x=fnd(x)] > sz[y=fnd(y)]) {
        swap(x,y);
    }
    if (x == y) {
        return false;
    }
    djs[x] = y;
    sz[y] += sz[x];
    return true;
}

bool vis[MAXN];
void dfs(ll nd,ll par) {
    vis[nd] = true;
    for (auto v : edge[nd]) {
        if (v != par && !vis[v]) {
            dfs(v,nd);
        }
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m >> d;
    REP (i,m) {
        ll u,v;
        cin >> u >> v;
        edge[u].emplace_back(v);
        edge[v].emplace_back(u);
    }

    vector<pii> im,ni;
    vis[1] = true;
    for (auto e : edge[1]) {
        if (!vis[e]) {
            debug(e);
            dfs(e,1);
            im.emplace_back(e,1);
        } else {
            ni.emplace_back(e,1);
        }
    }   
    init();
    vector<pii> ans;
    debug(im);
    if (d < SZ(im) || d > SZ(edge[1])) {
        cout << "NO" << endl;
    } else {
        for (auto p : im) {
            if (--d >= 0) {
                uni(p.X,p.Y);
                ans.emplace_back(p.X,p.Y);
            }
        }

        for (auto p : ni) {
            if (d >= 1 && uni(p.X,p.Y)) {
                d--;
                ans.emplace_back(p.X,p.Y);
            }
        }

        for (ll i=2;i<=n;i++) {
            for (auto v : edge[i]) {
                if (v != 1 && uni(v,i)) {
                    ans.emplace_back(i,v);
                }
            }
        }

        debug(ans);
        if (ans.size() == n-1) {
            cout << "YES" << endl;
            for (auto e : ans) {
                cout << e.X << " " << e.Y << endl;
            }
        } else {
            cout <<"NO" << endl;
        }
    }


    


    return 0;
}
