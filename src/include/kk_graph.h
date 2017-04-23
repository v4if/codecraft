//
// Created by root on 4/21/17.
//

#ifndef CODECRAFT_KK_GRAPH_H
#define CODECRAFT_KK_GRAPH_H

#include "pre_types.h"

//邻接表相关数据结构

//边表节点
struct EdgeNode {
    int preAdjvex; //前向节点
    int adjvex; //邻接点域，存储顶点对应下标
    int weight; //边表权重
    struct EdgeNode* next;   //链域，指向下一邻接点
};

#endif //CODECRAFT_KK_GRAPH_H
