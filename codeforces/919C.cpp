#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i=0;i<n;i++)

int n,m,k;
vector<bool> seat[2][2000];
int solve(int dir,int idx) {
  seat[dir][idx].push_back(1);
  int sz = int(seat[dir][idx].size());
  int ret = 0;
  int cons = 0;
  REP (i,sz) {
    if (seat[dir][idx][i]) {
      if (cons-k+1>0) ret+=cons-k+1;
      cons = 0;
    } else cons++;
  }
  return ret;  
}
int main() {
  cin>>n>>m>>k;
  char tmp;
  int cnt= 0;
  REP (i,n) {
    REP (j,m) {
      cin>>tmp;
      if (tmp=='*') {
	seat[0][i].push_back(1);
	seat[1][j].push_back(1);
      } else {
	cnt++;
	seat[0][i].push_back(0);
	seat[1][j].push_back(0);
      }
    }
  }
  if (k==1) {
    cout<<cnt<<endl;
    return 0;
  }
  int ans = 0;
  REP (i,n) ans += solve(0,i);
  REP (i,m) ans += solve(1,i);
  cout<<ans<<endl;
}
