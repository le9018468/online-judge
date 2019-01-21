#include <bits/stdc++.h>
using namespace std;

int n;
char s[1000003];
int pre[1000003],suf[1000003];
int main () {
    cin >> n;
    for (int i=1;i<=n;i++) {
        cin >> s[i];
    }


    memset(pre,-1,sizeof pre);
    memset(suf,-1,sizeof suf);

    int cnt = 0;
    for (int i=1;i<=n;i++) {
        if (s[i] == ')') {
            if (cnt) {
                cnt--;
            } else {
                break;
            }
        } else {
            cnt++;
        }
        pre[i] = cnt;
    }

    cnt = 0;
    for (int i=n;i>0;i--) {
        if (s[i] == '(') {
            if (cnt) {
                cnt--;
            } else {
                break;
            }
        } else {
            cnt++;
        }
        suf[i] = cnt;
    }
    pre[0] = 0;
    suf[n+1] = 0;
#ifdef tmd
    for (int i=1;i<=n;i++) {
        cout << pre[i] << " \n"[i==n];
    }

    for (int i=1;i<=n;i++) {
        cout << suf[i] << " \n"[i==n];
    }
#endif
    int ans = 0;
    for (int i=1;i<=n;i++) {
        if (s[i] == '(') {
            if ((pre[i-1] != -1 && suf[i+1] != -1) && pre[i-1] == 1 + suf[i+1]) {
                ans++;
            }
        } else {
            if ((pre[i-1] != -1 && suf[i+1] != -1) && pre[i-1] + 1 == suf[i+1]) {
                ans++;
            }
        }
    }

    cout << ans << endl;
}