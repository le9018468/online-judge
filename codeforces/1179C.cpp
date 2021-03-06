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
const ll MAXN = 300005;

ll n,m,q;
ll a[MAXN], b[MAXN];

namespace B {
    ll bit[1000006];
    void add(ll x, ll val) {
        for (;x < 1000006; x+=-x&x) {
            bit[x] += val;
        }
    }

    ll query(ll x) {
        ll ret = 0;
        for (;x > 0; x-=-x&x) {
            ret += bit[x];
        }
        return ret;
    }
}

struct Node {
    Node *l, *r;
    ll key, val, pri, mx, tag, sz;
    Node (ll k, ll v): l(0), r(0), key(k), val(v), pri(rand()), mx(v), tag(0), sz(1){};

    ll get() {
        return mx + tag;
    }

    void push () {
        if (l) {
            l->tag += tag;
        }
        if (r) {
            r->tag += tag;
        }
        val += tag;
        mx += tag;
        tag = 0;
    }

    void pull() {
        mx = val;
        sz = 1;
        if (l) {
            sz += l->sz;
            mx = max(mx,l->get());
        }
        if (r) {
            sz += r->sz;
            mx = max(mx,r->get());
        }
    }
};
Node *root;

void split(Node *o, Node *&A, Node *&B, ll k) { // <= k, > k
    if (!o) {
        A = B = 0;
        return;
    }
    o->push();
    if (o->key > k) {
        B = o;
        split(o->l, A, B->l, k);
    } else {
        A = o;
        split(o->r, A->r, B, k);
    }
    o->pull();
    return;
}

Node *mrg(Node *A, Node *B) {
    if (!A || !B) {
        return A ? A : B;
    }
    if (A->pri > B->pri) {
        A->push();
        A->r = mrg(A->r, B);
        A->pull();
        return A;
    } else {
        B->push();
        B->l = mrg(A, B->l);
        B->pull();
        return B;
    }
}

// can be optimize
ll search(Node *nd) {
    Node *l = nd->l, *r = nd->r;
    nd->push();
    if (r && r->mx + r->tag > 0) {
        return search(r);
    }
    if (nd->val + nd->tag > 0) {
        return nd->key;
    }
    if (l && l->mx + l->tag > 0) {
        return search(l);
    }
    return -1;
}

ll SIZ(Node *nd) {
    return nd ? nd->sz : 0;
}

void add(Node *nd) {
    if (nd) {
        nd->tag++;
    }
}

void sub(Node *nd) {
    if (nd) {
        nd->tag--;
    }
}

void chgA(ll f,ll t) {
    debug(f,t);
    Node *lf, *ef, *gf;
    split(root, lf, ef, f - 1);
    split(ef, ef, gf, f);

    assert(ef);
    lf = mrg(lf,ef->l);
    gf = mrg(ef->r,gf);
    delete ef;

    sub(lf);
    root = mrg(lf,gf);

    Node *l, *r;
    split(root, l, r, t);
    add(l);

    debug(SIZ(r) + 1 - (m - B::query(t - 1)));
    debug(B::query(t-1), t);
    l = mrg(l, new Node(t, SIZ(r) + 1 - (m - B::query(t - 1))));
    root = mrg(l,r);
}

void chgB(ll f,ll t) {
    Node *l, *r;
    split(root, l, r, f);
    add(l);
    root = mrg(l,r);

    split(root, l, r, t);
    sub(l);
    root = mrg(l,r);

    B::add(f, -1);
    B::add(t, +1);
}

void build() {
    vector<ll> srt_a;
    REP (i,n) {
        srt_a.eb(a[i]);
    }
    sort(ALL(srt_a));

    root = new Node(srt_a[0], n);
    REP1 (i,n - 1) {
        root = mrg(root, new Node(srt_a[i], n-i));
    }

    REP (i, m) {
        Node *l, *r;
        split(root, l, r, b[i]);
        sub(l);
        root = mrg(l,r);
        B::add(b[i], 1);
    }

}

void dfs(Node *nd) {
    nd->push();
    if (nd->l) {
        dfs(nd->l);
    }
    debug(nd->key, nd->val, nd->mx, nd->tag, nd->sz);
    if (nd->r) {
        dfs(nd->r);
    }
}

/********** Good Luck :) **********/
int main()
{
    IOS();
    srand(880301);
    cin >> n >> m;
    REP (i,n) {
        cin >> a[i];
    }
    REP (i,m) {
        cin >> b[i];
    }
    build();
    // dfs(root);
    cin >> q;
    while (q--) {
        ll cmd, i, x;
        cin >> cmd >> i >> x;
        if (cmd == 1) {
            chgA(a[i-1], x);
            a[i-1] = x;
        } else {
            chgB(b[i-1], x);
            b[i-1] = x;
        }
        // dfs(root);
        cout << search(root) << endl;
    }
    return 0;
}