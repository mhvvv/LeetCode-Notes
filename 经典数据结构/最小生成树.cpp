/*
 *  最小生成树 - Prim & Kruskal
 *  Author: mhvvv
 *  Date: 2021/12/17
 *  Description:  
 *    Prim - 邻接矩阵
 *    Kruskal - 边集(堆存储), 并查集判断集合 
 */

// Prim 适用于稠密图，时间复杂度O(n^2)
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 0x3f3f3f3f;

void Prim() {
/*
    G = (V, E)是连通带权无向图, V = {0, 1, ... n-1} 是顶点集, E是边集.
    求最小生成树 T = (S, e),  其中 S = V
*/
    int n;  // 点数
    scanf("%d", &n);
    vector<vector<int> > G(n, vector<int>(n, INF));
    int u, v, value;
    while(~scanf("%d %d %d", &u, &v, &value)) {
        G[u][v] = value;
        G[v][u] = value;
    }
    int cost = 0;
    vector<int> lowcost = G[0];   // S -> S-V的“距离”
    vector<bool> vis(n, false);
    vis[0] = true;
    int size_S = 1;
    while(size_S < n) {   // O(n)
        int lowc = INF, k;
        for(int i=0; i<n; ++i) {      // O(n)
            if(!vis[i] && lowcost[i] < lowc) {
                lowc = lowcost[i];
                k = i;
            }
        }
        vis[k] = true;
        cost += lowcost[k];
        ++size_S;
        for(int i=0; i<n; ++i) {        // O(n)
            if(!vis[i] && G[k][i] < lowcost[i])
                lowcost[i] = G[k][i];
        }
    }
    cout << "Prim: " << cost << endl;
}

// =========================================
struct Edge {
    int u;
    int v;
    int value;
    Edge(int u = -1, int v = -1, int value = -1) : u(u), v(v), value(value) {}
    friend bool operator < (const Edge&e1, const Edge& e2) { return e1.value > e2.value; }
};
int getf(vector<int>& f, int x) {
    if(f[x] == x) return x;
    else f[x] = getf(f, f[x]);
    return f[x];
}
bool merge(vector<int>& f, int x, int y) {
    int fx = getf(f, x);
    int fy = getf(f, y);
    if(fx == fy) return false;
    f[fy] = fx;
    return true;
}
void Kruskal() {
    int n;
    scanf("%d", &n);
    
    priority_queue<Edge> pq; //堆存边
    int u, v, value;
    while(~scanf("%d %d %d", &u, &v, &value)) 
        pq.push(Edge(u, v, value));

    // 并查集初始化
    vector<int> f(n);  
    for(int i=0; i<n; ++i) f[i] = i; 

    int tot = 0, cost = 0;
    while(!pq.empty() && tot < n-1) {
        // 不断选最短的判断, 选n-1条
        Edge e = pq.top();
        pq.pop();
        if(merge(f, e.u, e.v)) {
            ++tot;
            cost += e.value;
        }
    }
    cout << "Kruskal: " << cost << endl;

}

int main()
{
    Prim();   // O(n^2)  与边数无关, 对稠密图友好
    
    cout << " =============== \n";
    
    Kruskal();      // O(MlogM),  对定点多但边少的稀疏图友好
}
/*
    Input:
        6
        0 1 6
        0 2 1
        0 3 5
        1 2 5
        1 4 3
        2 3 5
        2 5 4
        3 5 2
        4 5 6

    Output:
        15
*/