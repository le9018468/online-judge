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
const ll MAXN=1003;
const ll MAXLG=__lg(MAXN)+2;

ll T,n,m;
ll c[MAXN][MAXN];
ll dis[MAXN][MAXN];
bool vis[MAXN][MAXN];

ll dx[] = {-1,0,1,0};
ll dy[] = {0,-1,0,1};
/********** Good Luck :) **********/
int main()
{
    IOS(); 
    cin >> T;
    while (T--) {
        cin >> n >> m;
        REP (i,n) {
            REP (j,m) {
                cin >> c[i][j];
            }
        }

        MEM(dis,INF);
        MEM(vis,0);
        priority_queue<pair<ll,pii>,vector<pair<ll,pii>>,greater<pair<ll,pii> > > pq;
        dis[0][0] = c[0][0];
        pq.push({c[0][0],{0,0}});

        while (true) {
            ll curX = -1,curY = -1;
            while (pq.size() && vis[curX=pq.top().Y.X][curY=pq.top().Y.Y]) {
                pq.pop();
            }
            if (curX == -1) {
                break;
            }

            vis[curX][curY]  = true;
            if (curX == n-1 && curY == m-1) {
                break;
            }
            REP (i,4) {
                ll nX = curX + dx[i];
                ll nY = curY + dy[i];
                if (nX >= 0 && nX < n && nY >=0 && nY < m) {
                    if (dis[nX][nY] > dis[curX][curY] + c[nX][nY]) {
                        dis[nX][nY] = dis[curX][curY] + c[nX][nY];
                        pq.push({dis[nX][nY],{nX,nY}});
                    }
                }
            }
        }

        cout << dis[n-1][m-1] << endl;
    }
    return 0;
}
/*
2
4
5
0 3 1 2 9
7 3 4 9 9
1 7 5 5 3
2 3 4 2 5
1
6
0 1 2 3 4 5

*/