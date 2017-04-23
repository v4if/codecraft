#include <time.h>
#include <sys/timeb.h>
#include "src/include/kk_graph.h"
#include "src/include/kk_craft.h"
#include "stdio.h"
#include "stdlib.h"

#define _DEBUG

void print_time(const char *head)
{
#ifdef _DEBUG
    struct timeb rawtime;
    struct tm * timeinfo;
    ftime(&rawtime);
    timeinfo = localtime(&rawtime.time);

    static int ms = rawtime.millitm;
    static unsigned long s = rawtime.time;
    int out_ms = rawtime.millitm - ms;
    unsigned long out_s = rawtime.time - s;
    ms = rawtime.millitm;
    s = rawtime.time;

    if (out_ms < 0)
    {
        out_ms += 1000;
        out_s -= 1;
    }
    printf("%s date/time is: %s \tused time is %lu s %d ms.\n", head, asctime(timeinfo), out_s, out_ms);
#endif
}

void print_graph(EdgeNode* head[], unsigned int max_node) {
    EdgeNode* linked_list;
    for (int i = 0; i < max_node; ++i) {
        linked_list = head[i];
        printf("%d ", i);
        while (linked_list) {
//            邻接点域，权重
            printf("-> %d, %d, %d ", linked_list->preAdjvex, linked_list->adjvex, linked_list->weight);
            linked_list = linked_list->next;
        }
        printf("\n");
    }
}

int main() {
    print_time("Begin");

    const char* read_file = "/root/CLionProjects/codecraft/case_tests/case0.txt";

    FILE *fp = fopen(read_file, "r");
    if (fp == NULL)
    {
        printf("Fail to open file %s\n", read_file);
        return -1;
    }

    unsigned int max_node, max_edge;
    fscanf(fp, "%d%d", &max_node, &max_edge);

    if (max_node > MAX_NODE) {
        printf("MAX_NODE -> %d", MAX_NODE);
        exit(1);
    }
//    表头顶点节点，指针数组
    EdgeNode* head[max_node];

//    初始化为NULL
    for (int i = 0; i < max_node; ++i) {
        head[i] = NULL;
    }

//    读取边表节点
    unsigned int cnt = 0;
    unsigned int from, to, weight;
    EdgeNode* p_edge;
    EdgeNode* linked_to;
    while ((cnt < max_node) && (cnt < MAX_NODE) && !feof(fp)) {
        fscanf(fp, "%d%d%d", &from, &to, &weight);
        p_edge = (EdgeNode*)malloc(sizeof(EdgeNode));
        p_edge->preAdjvex = from;
        p_edge->adjvex = to;
        p_edge->weight = weight;
        p_edge->next = NULL;

        linked_to = head[from];
        if (linked_to == NULL) {
            head[from] = p_edge;
        } else {
            while (linked_to->next) {
                linked_to = linked_to->next;
            }

            linked_to->next = p_edge;
        }

//        无向图，双向连接
        p_edge = (EdgeNode*)malloc(sizeof(EdgeNode));
        p_edge->preAdjvex = to;
        p_edge->adjvex = from;
        p_edge->weight = weight;
        p_edge->next = NULL;

        linked_to = head[to];
        if (linked_to == NULL) {
            head[to] = p_edge;
        } else {
            while (linked_to->next) {
                linked_to = linked_to->next;
            }

            linked_to->next = p_edge;
        }
    }

    print_graph(head, max_node);

    craft_entry(head, max_node, max_edge);

    print_time("End");

//    释放内存
    EdgeNode* free_edge;
    for (int i = 0; i < max_node; ++i) {
        while (head[i]) {
            free_edge = head[i];
            head[i] = head[i]->next;
            free(free_edge);
        }
    }
    return 0;
}