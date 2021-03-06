#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(ll i=0;i<n;i++)
#define MEM(i,n) memset(i,n,sizeof i)
const ll MAXN = 1000003;
ll t;
ll n;
ll s[MAXN];
ll pre[MAXN],suf[MAXN];
int main() {
  cin>>t;
  while(t--){
    MEM(pre,0);
    MEM(suf,0);
    cin>>n;
    REP (i,n) {
      cin>>s[i];
      if (i==0) {
	pre[i] = s[i];
	continue;
      }
      pre[i] = max(pre[i-1],s[i]);
    }
    suf[n-1] = s[n-1];
    for (ll i=n-2;i>=0;i--) {
      suf[i] = min(suf[i+1],s[i]);
    }
    ll ans = 0;
    for (ll i=1;i<n-1;i++) {
      if (s[i]>pre[i-1]&&s[i]<suf[i+1]) ans++;
    }
    cout<<ans<<endl;
  }
  return 0;
}
