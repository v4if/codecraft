#include "include/kk_graph.h"
#include "include/kk_craft.h"
#include "stdio.h"
#include "stdlib.h"
#include <queue>
#include <algorithm>
#include <stack>
#include <set>

// 路径记录
struct Tracer {
    int preAdjvex;  //前向节点
    int minDistance; //路径权重和
};

// 广度优先搜索
HANDLE_T BFS(EdgeNode* head[], const unsigned int max_node) {
    Tracer route_trace[max_node];
//    起点自身距离
    route_trace[0].preAdjvex = 0;
    route_trace[0].minDistance = 0;
    for (int i = 1; i < max_node; ++i) {
        route_trace[i].preAdjvex = -1;
        route_trace[i].minDistance = INF;
    }

    std::queue<EdgeNode*> q_wait;
    std::set<EdgeNode*> visited;
//    链域边表头
    q_wait.push(head[0]);
    visited.insert(head[0]);
    EdgeNode* linked_list;
    int dp_dis;
    while (!q_wait.empty()) {
        linked_list = q_wait.front();
        q_wait.pop();

        while (linked_list) {
//            前向节点 + 边权重
            dp_dis = route_trace[linked_list->preAdjvex].minDistance + linked_list->weight;
            if (dp_dis < route_trace[linked_list->adjvex].minDistance) {
                route_trace[linked_list->adjvex].minDistance = dp_dis;
                route_trace[linked_list->adjvex].preAdjvex = linked_list->preAdjvex;
            }

//            不搜索重复节点
            if (visited.find(head[linked_list->adjvex]) == visited.end()) {
                q_wait.push(head[linked_list->adjvex]);
                visited.insert(head[linked_list->adjvex]);
            }

            linked_list = linked_list->next;
        }
    }

    for (int i = 0; i < max_node; ++i) {
        printf("[%d, %d] ", route_trace[i].preAdjvex, route_trace[i].minDistance);
    }
    printf("\n");

//  逆序构建路径
    printf("The min cost : %d", route_trace[max_node - 1].minDistance);
    std::stack<int> path;
    int pre_adjvex = route_trace[max_node - 1].preAdjvex;
    path.push(max_node - 1);
    while (pre_adjvex) {
        path.push(pre_adjvex);
        pre_adjvex = route_trace[pre_adjvex].preAdjvex;
    }
    path.push(0);

//    输出最优路径
    while (!path.empty()) {
        printf(" -> %d", path.top());
        path.pop();
    }
    printf("\n");
}

HANDLE_T craft_entry(EdgeNode* head[], const unsigned int max_node, const unsigned int max_edge) {
    BFS(head, max_node);
}
