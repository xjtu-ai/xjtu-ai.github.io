#include "Queue.cpp"
#include <iostream>

using namespace std;

enum { MAX_N = 100, MAX_M = 2000 };

class Graph {
  public:
    int n; // 顶点数
    struct Edge {
        float weight; // 边的权重
        int to, next; // 终点索引 / 下一条边的索引
        Edge(int t = -1, int n = -1, float w = 1.0)
            : to(t), next(n), weight(w) {}
    } edges[MAX_M];  // 存储所有边的数组
    int head[MAX_N]; // 存储每个顶点的第一条边的索引
    int count;       // 当前边的数量

    Graph(int n = 0) : n(n), count(0) {
        for (int i = 0; i < MAX_N; ++i) {
            head[i] = -1; // 初始化每个顶点的邻接表头为-1
        }
    }
    // 添加无向边（from到to和to到from各加一条边，len需小于MAX_M）
    void addEdge(int from, int to, float weight = 1.0) {
        addDirectedEdge(from, to, weight);
        addDirectedEdge(to, from, weight);
    }
    // 添加有向边（from到to加一条边，len需小于MAX_M）
    void addDirectedEdge(int from, int to, float weight = 1.0) {
        edges[count] = Edge(to, head[from], weight);
        head[from] = count;
        count++;
    }
    bool hasEdge(int from, int to) {
        int index = head[from];
        while (index != -1) {
            if (edges[index].to == to) return true;
            index = edges[index].next;
        }
        return false;
    }
    // 深度优先遍历 (DFS)
    void dfs(int node, bool visited[]) {
        visited[node] = true;
        cout << node << " ";

        int index = head[node];
        while (index != -1) {
            int neighbor = edges[index].to;
            if (!visited[neighbor]) {
                dfs(neighbor, visited); // 递归访问
            }
            index = edges[index].next;
        }
    }
    // 广度优先遍历 (BFS)
    void bfs(int node, bool visited[]) {
        Queue q; // 使用前文定义的队列
        q.push(node);
        visited[node] = true;

        while (!q.isEmpty()) {
            int current = q.pop();
            cout << current << " ";

            int index = head[current];
            while (index != -1) {
                int neighbor = edges[index].to;
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor); // 将未访问的邻居入队
                }
                index = edges[index].next;
            }
        }
    }
};