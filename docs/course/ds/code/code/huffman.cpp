#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 1e3 + 5;
char s[MAXN];
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        priority_queue<int, vector<int>, greater<int>> q;
        map<int, int> mp;
        scanf("%s", s + 1);
        int len = strlen(s + 1), cnt = 0;
        for (int i = 1; i <= len; ++i) {
            mp[int(s[i])]++;
        }
        for (auto it = mp.begin(); it != mp.end(); ++it) {
            int x = it->second;
            q.push(x);
        }
        while (!q.empty()) {
            if (q.size() == 1) {
                printf("%d\n", cnt);
                break;
            }
            int ans = q.top();
            q.pop();
            ans += q.top();
            q.pop();
            q.push(ans);
            cnt += ans;
        }
    }
    return 0;
}