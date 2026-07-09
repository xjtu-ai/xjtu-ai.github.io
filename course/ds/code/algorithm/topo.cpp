#include <algorithm>
#include <iostream>
using namespace std;

const int MAXN(1e4 + 5), MAXM(1e6 + 5);

struct edge {
    int nxt, v;
};
edge e[MAXM];
int head[MAXN], cnt, in_degree[MAXN];

void add(int u, int v) {
    e[++cnt].v = v;
    e[cnt].nxt = head[u];
    head[u] = cnt;
    in_degree[v]++;
}

int len[MAXN], ans[MAXN];
int que[MAXN], h, t;

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int id;
        cin >> id;
        cin >> len[id];
        int x;
        while (true) {
            cin >> x;
            if (x == 0) break;
            add(x, id);
        }
    }
    // 强烈推荐在 BFS 的基础上实现拓扑排序
    h = t = 1;
    que[t++] = 1;
    while (h < t) {
        int u = que[h++];
        for (int i = head[u]; i; i = e[i].nxt) {
            in_degree[e[i].v]--;
            // 正常的 BFS 在这里直接把 e[i].v 入队，但是拓扑排序要等到 e[i].v
            // 所有前置都完成才行
            if (in_degree[e[i].v] == 0) {
                que[t++] = e[i].v;
            }
        }
    }
    // que 恰好是拓扑序
    int max_ans = 0;
    for (int i = 1; i <= n; i++) {
        int u = que[i];
        ans[u] += len[u];
        for (int j = head[u]; j; j = e[j].nxt) {
            ans[e[j].v] = max(ans[e[j].v], ans[u]);
        }
        max_ans = max(max_ans, ans[u]);
    }
    cout << max_ans << endl;
}