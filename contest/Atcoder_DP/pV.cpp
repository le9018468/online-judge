#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
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
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

template<class T> inline bool cmax(T &a, const T &b) { return b > a ? a = b, true : false; }
template<class T> inline bool cmin(T &a, const T &b) { return b < a ? a = b, true : false; }
template<class T> using MaxHeap = priority_queue<T>;
template<class T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

const ll MOD=1000000007;
const ll INF=0x3f3f3f3f3f3f3f3f;
const ll MAXN=1e5+5;
const ll MAXLG=__lg(MAXN)+2;

ll n,m;
vector<ll> edge[MAXN];

ll dp1[MAXN],dp2[MAXN];

void DFS1(ll nd,ll par) {
    dp1[nd] = 1;
    for (auto v:edge[nd]) if (v != par) {
        DFS1(v,nd);
        dp1[nd] = dp1[nd] * dp1[v] % m;
    }
    dp1[nd]++;
    dp1[nd] %= m;
}

void DFS2(ll nd,ll par,ll f) {
    debug(nd,par,f);
    vector<ll> pre,suf;
    for (auto v:edge[nd]) if (v != par) {
        pre.eb(dp1[v]);
        suf.eb(dp1[v]);
    }

    ll len = SZ(pre); 
    REP1 (i,len-1) {
        pre[i] = pre[i] * pre[i-1] % m;
        suf[len-1-i] = suf[len-1-i] * suf[len-i] % m;
    }
    
    debug(pre,suf);
    dp2[nd] = (len?pre[len-1]:1) * f % m;

    ll i = 0;
    for (auto v:edge[nd]) {
        if (v != par) {
            ll cf = (i?pre[i-1]:1) * (i!=len-1?suf[i+1]:1) % m * f % m;
            DFS2(v,nd,(cf+1)%m);
            i++;
        }
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m;
    REP (i,n-1) {
        ll u,v;
        cin >> u >> v;
        edge[u].eb(v);
        edge[v].eb(u);
    }

    DFS1(1,1);
    DFS2(1,1,1);

    pary(dp1+1,dp1+1+n);
    REP1 (i,n) {
        cout << dp2[i] << endl;
    }
    return 0;
}
