#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define FOR(i, j, k, in) for (ll i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (ll i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(),_a.end()
#define FOREACH(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define X first
#define Y second
typedef pair<ll, ll> pi;
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

const ll INF = (ll)1e18 + 7;
const ll MOD = 1000000007;
const ll MAXN = 103;
ll n,m,k,px,py,c;
vector<ll> e[MAXN];
bool vis[MAXN];
ll xp[MAXN],yp[MAXN],my[MAXN];
/********** Main()  function **********/
bool DFS(ll x){
  for(auto v:e[x]){
    if(vis[v])continue;
    vis[v]=1;
    if(yp[v]==-1||DFS(yp[v])){
      xp[x]=v;
      yp[v]=x;
      return 1;
    }
  }
  return 0;
}

bool DFS2(ll x,ll sx,ll sy){
  for(auto v:e[x]){
    if(vis[v]||(x==sx&&v==sy))continue;
    vis[v]=1;
    if(my[v]==-1||DFS2(my[v],sx,sy)){
      my[v]=x;
      return 1;
    }
  }
  return 0;
}

int main()
{
  IOS();
  ll t= 0;
  while(cin>>n>>m>>k){
    t++;
    REP(i,n)e[i].clear();
    REP(i,k)cin>>px>>py,e[--px].pb(--py);
    c=0;
    MEM(my,-1);
    MEM(xp,-1);
    MEM(yp,-1);
    REP(i,n){
      MEM(vis,0);
      if(DFS(i))c++;
    }
    pary(xp,xp+c);
    ll ans = 0;
    REP(i,n){
      if(xp[i]==-1)continue;
      MEM(my,-1);
      ll cnt = 0;
      REP(j,n){
        MEM(vis,0);
        if(DFS2(j,i,xp[i]))cnt++;
      }
      debug(i,ans,cnt);
      if(cnt!=c)ans++;
    }
    cout<<"Board "<<t<<" have "<<ans<<" important blanks for "<<c<<" chessmen."<<endl;
  }

	return 0;
}
