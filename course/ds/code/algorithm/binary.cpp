#include <bits/stdc++.h>
using namespace std;

const int MAXN(1e6 + 5);

/*
假设 a 是长度为 n 的从小到大排序的数组，查找 v 的首次出现位置

如果不存在，返回 -1
*/
int binary_search(int *a, int n, int v) {
    int l = 1, r = n, mid; // [l, r] 是当前可能的下标区间
    int ans = n + 1;
    while (l <= r) {
        mid = (l + r) / 2;                    // 这次猜测中位数
        if (v == a[mid]) ans = min(ans, mid); // 最小的那个出现位置
        if (v > a[mid]) l = mid + 1;
        else r = mid - 1;
    }
    if (ans == n + 1) ans = -1;
    return ans;
}

int n, m;
int a[MAXN];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
    }
    while (m--) {
        int x;
        scanf("%d", &x);
        printf("%d ", binary_search(a, n, x));
    }
    return 0;
}