#include "graph.h"

void Graph::add(int u,int v,double w){
    e[++tot].from = head[u];
    e[tot].u = u;   e[tot].v = v;  
    e[tot].w = w;   head[u] = tot;
} 

void Graph::dbadd(int u,int v,double w){
    add(u,v,w); add(v,u,w);
}


// graphNode: 节点的信息
Edge *Graph::getFirstEdgeNode(int graphNode){
    if(graphNode >= maxn){
        logError("节点超出范围");
        return NULL;
    }
    return &e[head[graphNode]];
}


// edgeNode:边的信息
Edge *Graph::getNxtNode(const Edge &edge){ 
    if(edge.from >= maxm){
        logError("边数不在预期范围内");
        return NULL;
    }
    if(edge.from == 0)  return NULL;

    return &e[edge.from];
}