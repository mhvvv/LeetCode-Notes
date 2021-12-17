/*
 *  单源最短路径 - Dijkstra
 *  Author: mhvvv
 *  Date: 2021/12/17
 *  Location: Suzhou
 *  Description:  邻接表和邻接矩阵两种方式存图, Dijkstra算法的C++实现
*/
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int INF = 0x3f3f3f3f;
const int maxLen = 105;

struct Edge {
    int to;
    int value;
    Edge(int t=-1, int v = INF) : to(t), value(v) {}
    bool operator < (const Edge& e) { return value > e.value; }
};
 
void Dijkstra_adjList() {   //  O(M)
    // 建立邻接表
    int point_num, edge_num;
    scanf("%d %d", &point_num, &edge_num);    // faster
    vector<vector<Edge> > adjList(point_num);
    int u, v, value;
    for(int num = 0; num < edge_num; ++num) {
        scanf("%d %d %d", &u, &v, &value);
        adjList[u].push_back(Edge(v, value));
       // adjList[v].push_back(Edge(u, value));  有向图
    }
    // Dijkstra 
    vector<bool> vis(point_num, false);
    vis[0] = true;
    vector<int> dis(point_num, INF);
    dis[0] = 0;   // 以0号顶点为源点
    int nearest = 0;
    while(--point_num) {
        int nextNearest, minDis = INF;
        for(Edge e : adjList[nearest]) {
            if(vis[e.to]) continue;
            if(dis[nearest] + e.value < dis[e.to]) {
                dis[e.to] = dis[nearest] + e.value;
                if(dis[e.to] < minDis) {
                    minDis = dis[e.to];
                    nextNearest = e.to;
                }
            }
        }
        vis[nextNearest] = true;
        nearest = nextNearest;
    }
    cout << "Dijkstra_adjList: ";
    for(int i : dis)
        printf("%d ", i);
    printf("\n");
}

void Dijkstra_martix() {
    // 建立邻接表
    int point_num, edge_num;
    scanf("%d %d", &point_num, &edge_num);    // faster
    vector<vector<int> > adjMatrix(point_num, vector<int>(point_num, INF));
    int u, v, value;
    for(int num = 0; num < edge_num; ++num) {
        scanf("%d %d %d", &u, &v, &value);
        adjMatrix[u][v] = value;
    }
    // Dijkstra 
    vector<bool> vis(point_num, false);
    vis[0] = true;
    vector<int> dis(point_num, INF);
    dis[0] = 0;   // 以0号顶点为源点
    int nearest = 0;
    while(--point_num) {
        int nextNearest, minDis = INF;
        for(int i=1; i<adjMatrix.size(); ++i) {  // point_num 在变
            if(vis[i]) continue;
            if(adjMatrix[nearest][i] == INF) continue;
            if(dis[nearest] + adjMatrix[nearest][i] < dis[i]) {
                dis[i] = dis[nearest] + adjMatrix[nearest][i];
                if(dis[i] < minDis) {
                    minDis = dis[i];
                    nextNearest = i;
                }
            }
        }
        vis[nextNearest] = true;
        nearest = nextNearest;
    }
    cout << "Dijkstra_matrix: ";
    for(int i : dis)
        printf("%d ", i);
    printf("\n");
}
int main()
{
    // 邻接表 存 图   O(M) ? 
    Dijkstra_adjList();
    
    cout << " =============== \n";
    
    // 邻接矩阵 存 图   O(N^2)
    Dijkstra_martix();
    
    return 0;
}
/*
    测试样例:
    Input:
        6 9
        0 1 1
        0 2 12
        1 2 9
        1 3 3
        2 4 5
        3 2 4
        3 4 13
        3 5 15
        4 5 4
    Output:
        0 1 8 4 13 17

    Question:
        对于邻接表存图，堆优化真的有意义？ 时间复杂度是O((point_num + edge_num) * log(point_num)) ?
*/