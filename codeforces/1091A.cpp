#include <bits/stdc++.h>
using namespace std;

int y,b,r;
int main () {
    cin >> y >> b >> r;
    cout << min(b,min(y+1,r-1)) * 3 << endl;
}