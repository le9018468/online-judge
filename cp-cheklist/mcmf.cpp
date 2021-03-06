#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

const int MAXN = 102;
const ll MOD = 1000000007;
const int iNF = 0x3f3f3f3f;

int n, b[MAXN], S, T, cnt[26];

struct Edge {
    int frm, des, flow, cap, cost, nxt;
}edge[100005];
int head[MAXN], lst[MAXN], ecnt, dis[MAXN];
bool inq[MAXN];

void add_edge (int f, int t, int cap, int cost) {
    edge[ecnt++] = {f, t, 0, cap, cost, head[f]};
    head[f] = ecnt - 1;
    edge[ecnt++] = {t, f, 0, 0, -cost, head[t]};
    head[t] = ecnt - 1;
}

bool spfa () {
    queue<int> que;
    que.emplace(S);
    memset(dis, iNF, sizeof(dis));
    dis[S] = 0;
    lst[S] = -1;
    inq[S] = true;

    while (que.size()) {
        int cur = que.front();
        que.pop();
        inq[cur] = false;

        for (int i=head[cur]; i!=-1; i=edge[i].nxt) {
            int x = edge[i].des;
            if (edge[i].cap > edge[i].flow && dis[x] > dis[cur] + edge[i].cost) {
                dis[x] = dis[cur] + edge[i].cost;
                lst[x] = i;
                if (!inq[x]) {
                    inq[x] = true;
                    que.emplace(x);
                }
            }
        }
    }

    return dis[T] != iNF;
}

pair<int,int> mcmf () { // cost, flow
    pair<int,int> ret;
    while (spfa()) {
        int max_cap = iNF;
        for (int i=lst[T]; i!=-1; i=lst[edge[i].frm]) {
            max_cap = min(max_cap, edge[i].cap-edge[i].flow);
        }
        debug(max_cap);
        for (int i=lst[T]; i!=-1; i=lst[edge[i].frm]) {
            ret.first += edge[i].cost * max_cap;
            edge[i].flow += max_cap;
            edge[i^1].flow -= max_cap;
        }
        ret.second += max_cap;
    }

    return ret;
}

/*********************GoodLuck***********************/
int main () {
    IOS();
    memset(head, -1, sizeof(head));

    string str;
    cin >> n >> str;
    for (auto c : str) {
        cnt[c-'a']++;
    }
    REP (i, n) {
        cin >> b[i];
    }

    // build network s:0, a-z:1~26, str:26+1~26+n/2, t:26+n/2+1
    // v<=77, e<=1376

    S = 0, T = 26+n/2+1;
    REP1 (i, 26) {
        add_edge(S, i, cnt[i-1], 0);
        for (int j=1; j<=n/2; j++) {
            char c = i-1+'a';
            int cost = 0;
            if (c==str[j-1] && c==str[n-j]) {
                cost = max(b[j-1], b[n-j]);
            } else if (c == str[j-1]){
                cost = b[j-1];
            } else if (c == str[n-j]) {
                cost = b[n-j];
            }
            add_edge(i, 26+j, 1, -cost);
        }
    }
    REP1 (i, n/2) {
        add_edge(26+i, T, 2, 0);
    }
    pair<int,int> ans = mcmf();

    debug(ans.first, ans.second);
    assert(ans.second == n);

    cout << -ans.first << endl;

}
