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
const ll k = 1024;
const ll g = MAXN/k + 3;
ll n,m;
struct SEG{
    ll seg[MAXN*2];
    void add(ll pos,ll val) {
        for (seg[pos+=n]+=val;pos>1;pos>>=1) {
            seg[pos>>1] = seg[pos] + seg[pos^1];
        }
    }

    ll query(ll l,ll r) {
        ll ret = 0;
        for (l+=n,r+=n;l<r;l>>=1,r>>=1) {
            if (l&1) {
                ret += seg[l++];
            }
            if (r&1) {
                ret += seg[--r];
            }
        }
        return ret;
    }
}blk[g];

ll a[MAXN],b[MAXN];

ll id[MAXN];
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m;
    REP (i,n) {
        cin >> a[i];
        id[a[i]] = i;
    }

    REP (i,n) {
        cin >> b[i];
        b[i] = id[b[i]];
        blk[i/k].add(b[i],1);
    }

    REP (__w__,m) {
        ll cmd;
        cin >> cmd;
        if (cmd == 1) {
            ll l1,r1,l2,r2;
            cin >> l1 >> r1 >> l2 >> r2;
            l1--,r1--,l2--,r2--;
            ll ret = 0;
            if (r2-l2 <= k*2) {
                for (ll i=l2;i<=r2;i++) {
                    ret += (b[i] >= l1 && b[i] <= r1);
                }
            } else {
                for (ll i=l2;i<((l2-1)/k+1)*k;i++) {
                    debug(i);
                    ret += (b[i] >= l1 && b[i] <= r1);
                }
                for (ll i=r2;i>(r2-k+1)/k*k+k-1;i--) {
                    debug(i);
                    ret += (b[i] >= l1 && b[i] <= r1);
                }
                for (ll i=(l2-1)/k+1;i<=(r2-k+1)/k;i++) {
                    debug(i);
                    ret += blk[i].query(l1,r1+1);
                }
            }
            cout << ret << endl;
        } else {
            ll l,r;
            cin >> l >> r;
            l--,r--;
            blk[l/k].add(b[l],-1);
            blk[r/k].add(b[r],-1);
            swap(b[l],b[r]);
            blk[l/k].add(b[l],1);
            blk[r/k].add(b[r],1);

        }
    }

   
    return 0;
}
