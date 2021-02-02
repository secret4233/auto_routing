#ifndef _GRAPH_H
#define _GRAPH_H 

#include <bits/stdc++.h>
#include "log.h"

using namespace std;


const int MAX_VEC = 200 + 10;           //点数
const int MAX_EDGE = 200 * 200 + 10;    //边数

typedef struct graphEdge{
    int from,u,v;
    double w;
    int xAxis,yAxis;
}Edge;

class Graph{
private:
    int vecNum,edgeNum; 
    int head[MAX_VEC];
    Edge e[MAX_EDGE];
public:
    Graph(int _vecNum,int _edgeNum);
    Graph(int _vecNum);
    void AddEdge(int u,int v,double w); 
    void DbAddEdge(int u,int v,double w);
    Edge *GetFirstEdgeNode(int graphNode);
    Edge *GetNxtNode(Edge *edeg);
};



#endif 