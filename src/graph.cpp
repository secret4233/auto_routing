#include "graph.h"


// 默认构造函数生成100个点
Graph::Graph():vecNum(100){}


// 该函数用于给定图的情况
// 通过先确定点的数量,后续再添加边来处理
Graph::Graph(int _vecNum):vecNum(_vecNum){}

// 添加有向边
void Graph::AddEdge(int u,int v,double w){
    e[++edgeNum].from = head[u];
    e[edgeNum].u = u;   e[edgeNum].v = v;  
    e[edgeNum].w = w;   head[u] = edgeNum;
} 


// 添加无向(双向)边
void Graph::DbAddEdge(int u,int v,double w){
    AddEdge(u,v,w); AddEdge(v,u,w);
}

// 图类加点
void Graph::AddVertex(int which,int xAxis,int yAxis){
    vx[which].which = which;
    vx[which].xAxis = xAxis;
    vx[which].yAxis = yAxis;
}


// graphNode: 节点的信息
// 该函数取得某个节点的首条边
const Edge *Graph::GetFirstEdge(int graphVertex){
    if(graphVertex > vecNum){
        LogError("节点超出范围");
        return NULL;
    }
    return &e[head[graphVertex]];
}


// edgeNode:边的信息
// 该函数取得某个节点边的后继边
const Edge *Graph::GetNxtEdge(const Edge *edge){ 
    if(edge->from > edgeNum){
        LogError("边数不在预期范围内");
        return NULL;
    }
    if(edge->from == 0)  return NULL;

    return &e[edge->from];
}

const Vertex *Graph::GetVertex(int graphVertex){
    if(graphVertex > vecNum){
        LogError("节点超出范围");
        return NULL;
    }
    return &vx[graphVertex];
}

double CalDistance(const Vertex& x,const Vertex& y){
    return abs(x.xAxis - y.xAxis) + abs(x.xAxis - y.yAxis); 
}

int UNS::findFather(int x){
    if(fatherPoint[x] == x)  return x;
    return fatherPoint[x] = findFather(fatherPoint[x]);
}

void UNS::unionPoint(int x,int y){
    int a = findFather(x),b = findFather(y);
    if(a != b)  fatherPoint[a] = b;
}