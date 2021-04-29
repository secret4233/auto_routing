#ifndef _ASTAR_H
#define _ASTAR_H


#include <bits/stdc++.h>
#include "graph.h"
#include "log.h"

/*
u :起点
dis：实际已走距离
h：预估剩余距离
*/
struct Node{
    int u;  
    double dis,h; //    f = dis + h = g + h
    friend bool operator < (Node a,Node b){
        return a.dis + a.h > b.dis + b.h;
    }
}; 


// AStar算法默认代价预估函数:为两点间的曼哈顿距离

class AStar{
private:
    // algorithmAns: 算法结束后得出的结果,若为-1.0则为无解或未求解
    double algorithmAns,BFSAns;
    // k:表名算法求的为k短路,默认为1,即为最短路
    Graph g;
    bool vis[MAX_VERTEX];
    // 创建有障碍的随机图
    void randGraph();

    void addEdge(int,int); 
    double calCost(int,int);
public:
    AStar(int);
    double CoreAlgorithm(int star,int end);
    double BFSAlgorithn(int star,int end);
    int GetGraphVertexNum(int,int);
   
};


#endif