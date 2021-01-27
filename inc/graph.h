#ifndef _GRAPH_H
#define _GRAPH_H 

#include <bits/stdc++.h>

using namespace std;


const int maxn = 200 + 10;          //点数
const int maxm = 200 * 200 + 10;    //边数

typedef struct GRAP{
    int head[maxn],tot;
    struct edge{
        int from,to;
        double w;
    }e[maxm];
    inline void add(int u,int v,double w){
        e[++tot].from = head[u];
        e[tot].to = v;  e[tot].w = w;
        head[u] = tot;
    } 
    inline void dbadd(int u,int v,double w){
        add(u,v,w); add(v,u,w);
    }
}Grap;



#endif 
