#ifndef _GRAPH_H
#define _GRAPH_H 

#include <bits/stdc++.h>
#include <log.h>

using namespace std;


const int maxn = 200 + 10;          //点数
const int maxm = 200 * 200 + 10;    //边数

typedef struct graphEdge{
    int from,u,v;
    double w;
}Edge;

class Graph{
private:
    int head[maxn],tot;
    Edge e[maxm];
public:
    void add(int u,int v,double w); 
    void dbadd(int u,int v,double w);
    Edge *getFirstEdgeNode(int graphNode);
    Edge *getNxtNode(const Edge &e);
};



#endif 
