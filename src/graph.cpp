#include "graph.h"

// 该函数用于生成制定点数和边数的图
Graph::Graph(int _vecNum,int _edgeNum):vecNum(_vecNum),edgeNum(_edgeNum){}

// 该函数用于给定图的情况
// 通过先确定点的数量,后续再添加边来处理
Graph::Graph(int _vecNum):vecNum(_vecNum){}

// 添加有向边
void Graph::AddEdge(int u,int v,double w){
    e[++edgeNum].from = head[u];
    e[edgeNum].u = u;   e[edgeNum].v = v;  
    e[edgeNum].w = w;   head[u] = edgeNum;
} 


// 无向图加边
void Graph::DbAddEdge(int u,int v,double w){
    AddEdge(u,v,w); AddEdge(v,u,w);
}


// graphNode: 节点的信息
// 该函数取得某个节点的首条边
Edge *Graph::GetFirstEdgeNode(int graphNode){
    if(graphNode > vecNum){
        LogError("节点超出范围");
        return NULL;
    }
    return &e[head[graphNode]];
}


// edgeNode:边的信息
// 该函数取得某个节点边的后继边
Edge *Graph::GetNxtNode(const Edge &edge){ 
    if(edge.from > edgeNum){
        LogError("边数不在预期范围内");
        return NULL;
    }
    if(edge.from == 0)  return NULL;

    return &e[edge.from];
}