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
const ll MAXN=10000003;
const ll MAXLG=__lg(MAXN)+2;

int n;
int z[MAXN*2];
int org[MAXN];
int nw[MAXN*2];
void z_build() {
  int bst = 0;
  z[0] = 0;
  for(int i=1;i<n;i++){
    if(bst+z[bst]<i)z[i]=0;
    else if(z[bst*2-i]+i>=bst+z[bst]) z[i] = z[bst]+bst-i;
    else z[i] = z[bst*2-i];
    while(i+z[i]+1<n&&i-z[i]-1>=0&&nw[i+z[i]+1]==nw[i-z[i]-1])z[i]++;
    if(i+z[i]>bst+z[bst])bst = i;
  }
}
int longest_palindromic_substring() {
  memset(nw,-1,(2*n+1)*(sizeof (int)));
  REP(i,n)nw[i*2+1] = org[i];
  n = n*2+1;
  pary(nw,nw+n);
  z_build();
  int ans = -1;
  REP(i,n){
    cmax(ans,z[i]);
  }
  return ans;
}
/********** Main()  function **********/
int main()
{
  IOS();
  cin>>n;
  REP(i,n)cin>>org[i];
  cout<<longest_palindromic_substring()-1<<endl;
	return 0;
}
