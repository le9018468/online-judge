#include <bits/stdc++.h>
using namespace std;

int main() {
  int d;
  cin>>d;
  vector<bool> b;
  while (d) {
    b.push_back(d%2);
    d/=2;
  }
  vector<char> ans;
  ans.push_back('+');
  for (int i=int(b.size())-2;i>=0;i--) {
    if (b[i]) {
      if (b[i+1]) ans.push_back('+');
      else ans.push_back('-');
    } else {
      if (b[i+1]) ans.push_back('+');
      else ans.push_back('-');
    }
  }
  cout<<ans.size()<<endl;
  while (ans.size()) {
    cout<<ans.back();
    ans.pop_back();
  }
	
}
