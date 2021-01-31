#include <bits/stdc++.h>
#include "inc/pso.h"
#include "inc/graph.h"
#include "inc/log.h"



using namespace std;    


int main(){
    LogUtils logger;
    LogInfo("QAQ%d",233);

    Graph graph(20,40);

    for(int i = 1; i <= 20; ++i){
        graph.DbAddEdge(1,i,2.0);
    }

    // for(int i = 1; i <= 20; ++i){
    //     Edge *now = graph.getFirstEdgeNode(i);
    //     for(;now != NULL;now = graph.getNxtNode(*now)){
    //         printf("%02d --> %02d %f\n",now->u,now->v,now->w);
    //     }
    // }

}
