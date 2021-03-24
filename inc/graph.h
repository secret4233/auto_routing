#ifndef _GRAPH_H
#define _GRAPH_H 

#include <bits/stdc++.h>
#include "log.h"

using namespace std;

const int MAX_LINE = 50;
const int MAX_VERTEX = MAX_LINE * MAX_LINE + 10;           //点数
const int MAX_EDGE = MAX_VERTEX * 8 + 10;    //边数

// TODO 使用int还是double需要再次确定
// TODO 内部变量考虑vector?

typedef struct graphEdgeMessage{
    int from,u,v;
    double w;
    bool operator < (const graphEdgeMessage &target) const{
        return w < target.w;
    }
}Edge;

typedef struct graphVertexMessage{
    int which;
    double xAxis,yAxis;
    graphVertexMessage operator + (const graphVertexMessage &target) const{
        return (graphVertexMessage){which,xAxis + target.xAxis,yAxis + target.yAxis};
    }
    graphVertexMessage operator - (const graphVertexMessage &target) const{
        return (graphVertexMessage){which,xAxis - target.xAxis,yAxis - target.yAxis};
    }
    graphVertexMessage operator * (const double target) const{
        graphVertexMessage tmp;
        tmp.which = which;
        tmp.xAxis = target * xAxis;
        tmp.yAxis = target * yAxis;
        return tmp;
    }
}Vertex;

// 计算两点间距离
double CalDistance(const Vertex&,const Vertex&);

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
};


// 并查集
class UNS{
private:
    int fatherPoint[MAX_VERTEX];
public:
    UNS();
    int FindFather(int);
    void UnionPoint(int,int);
    bool IsSameFather(int,int);
};





#endif 
