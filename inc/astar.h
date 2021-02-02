#ifndef _ASTAR_H
#define _ASTAR_H


#include <bits/stdc++.h>
#include "graph.h"


struct Node{
    int u;  
    double dis,h; //    f = dis + h = g + h
    int vis[MAX_VEC]; //此处的vis亦作记录,但记录的是搜索路径上是否访问过
    friend bool operator < (Node a,Node b){
        return a.dis + a.h > b.dis + b.h;
    }
}; 


// AStar算法默认代价预估函数:为两点间的曼哈顿距离
double CalCost(int nowAxis,int endAxis);

class AStar:public Graph{
private:
    // algorithmAns: 算法结束后得出的结果,若为-1.0则为无解或未求解
    double algorithmAns;
    // k:表名算法求的为k短路,默认为1,即为最短路
    int k;
public:
    AStar(int _vecNum = 30,int _k = 1):Graph(_vecNum),k(_k),algorithmAns(-1.0){};
    double CoreAlgorithm(int star,int end,double (*cal)(int,int) = &CalCost);
};


#endif