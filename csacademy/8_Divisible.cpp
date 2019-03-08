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

string num;
ll cnt[26];

/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> num;
    ll n =SZ(num);
    REP (i,n) {
        cnt[num[i]-'0']++;
    }

    if (n <= 4) {
        vector<ll> permu;
        REP (i,10) {
            REP (j,cnt[i]) {
                permu.emplace_back(i);
            }
        }

        do {
            if (permu[0] != 0) {
                ll cur = 0;
                for (auto v : permu) {
                    cur *= 10;
                    cur += v;
                }
                if (cur % 8 == 0) {
                    cout << cur << endl;
                    return 0;
                }
            }
        } while (next_permutation(ALL(permu)));
        cout << -1 << endl;
    } else {
        vector<string> ans;
        REP (i,10) {
            REP (j,10) {
                REP (k,10) {
                    if ((i*100 + j*10 + k) % 8 == 0) {
                        cnt[i]--;
                        cnt[j]--;
                        cnt[k]--;
                        if (cnt[i]>=0 && cnt[j]>=0 && cnt[k]>=0) {

                            ll left = -1;
                            REP1 (l,9) {
                                if (cnt[l]) {
                                    left = l;
                                    break;
                                }
                            }

                            string ns;
                            if (left != -1) {
                                ns += char(left+'0');
                                REP (l,10) {
                                    REP (m,cnt[l]-(left==l)) {
                                        ns += char(l+'0');
                                    }
                                }
                            }

                            ns += char(i+'0');
                            ns += char(j+'0');
                            ns += char(k+'0');
                            ans.emplace_back(ns);

                        }
                        cnt[i]++;
                        cnt[j]++;
                        cnt[k]++;
                    }
                }
            }
        }
        if (SZ(ans)) {
            sort(ALL(ans));
            cout << ans[0] << endl;
        } else {
            cout << -1 << endl;

        }
    }
    return 0;
}
