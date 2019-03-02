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

ll t,a,n,b,m;

ll gcd(ll A,ll B,ll *x,ll *y) {
    if (A == 0) {
        *x = 0;
        *y = 1;
        return B;
    }
    ll x1,y1;
    ll ret = gcd(B%A,A,&x1,&y1);
    *x = y1 - B/A*x1;
    *y = x1;
    return ret;
}

ll md(ll x,ll M) {
    x %= M;
    if (x < 0) {
        x += M;
    }
    return x;
}
ll mul(ll x,ll y,ll M) {
    return x * y % M;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> t;
    while (t--) {
        cin >> a >> n >> b >> m;
        ll k1,k2;
        ll d = gcd(n,m,&k1,&k2);
        debug(k1,k2);
        k2 = - k2;

        ll lcm = n * m / d;
        ll x = n * k1 * (b-a) / d + a;
        debug(x);

        if ((b-a)*k1 % d != 0) {
            cout << "no solution" << endl;
            continue;
        }
        debug(lcm);
        ll ans1 = mul(k1*(b-a)/d%(m/d),n,lcm) + a;
        ans1 = md(ans1,lcm);

        cout << ans1 << " " << lcm << endl;
    }
    return 0;
}