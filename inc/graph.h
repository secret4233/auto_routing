#ifndef _GRAPH_H
#define _GRAPH_H 

#include <bits/stdc++.h>
#include "log.h"

using namespace std;


const int MAX_VERTEX = 200 + 10;           //点数
const int MAX_EDGE = 200 * 200 + 10;    //边数

// TODO 使用int还是double需要再次确定
// TODO 内部变量考虑vector?

typedef struct graphEdgeMessage{
    int from,u,v;
    double w;
}Edge;

typedef struct graphVertexMessage{
    int which,xAxis,yAxis;
}Vertex;

class Graph{
private:
    int vecNum,edgeNum; 
    int head[MAX_VERTEX];
    Edge e[MAX_EDGE];
    Vertex vx[MAX_VERTEX];
public:
    Graph(int _vecNum);
    Graph();
    void AddEdge(int u,int v,double w); 
    void DbAddEdge(int u,int v,double w);
    void AddVertex(int which,int x,int y);
    const Edge *GetFirstEdge(int graphVertex);
    const Edge *GetNxtEdge(const Edge *edeg);
    const Vertex *GetVertex(int graphVertex);
    double calDistance(const Vertex&,const Vertex&);
};



#endif 
