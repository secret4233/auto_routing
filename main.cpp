#include <bits/stdc++.h>
#include "inc/pso.h"
#include "inc/graph.h"
#include "inc/log.h"
#include "inc/astar.h"



using namespace std;    


int main(){
    LogUtils logger(INFO_LOG_LEVEL);
    
    AStar method1(100,1);
    int start = method1.GetGraphVertexNum(2,0);
    int end = method1.GetGraphVertexNum(2,4);
    double ans = method1.CoreAlgorithm(start,end);

    printf("%d -> %d %lf\n",start,end,ans);
    return 0;
}
