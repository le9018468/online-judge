#include <bits/stdc++.h>
using namespace std;

vector<int> ans;
int fat[200003];

int main(){
  ios_base::sync_with_stdio(0);cin.tie(0);
  int n;
  cin >> n;
  for (int i = 2; i <= n; i++) {
    cin >> fat[i];
  }

  int cur = n;
  while (cur != 1) {
    ans.emplace_back(cur);
    cur = fat[cur];
  }

  cout << 1;
  for (auto it = ans.rbegin(); it != ans.rend(); it++) {
    cout << " " << (*it);
  }
  cout<<" \n";

}
