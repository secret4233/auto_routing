#include <bits/stdc++.h>
#include "inc/pso.h"
#include "inc/graph.h"
#include "inc/log.h"
#include "inc/astar.h"



using namespace std;    


int main(){
    LogUtils logger(ALL_LOG_LEVEL);
    
    int lineNum = 50; 
    AStar method1(lineNum * lineNum,1);
    int start = method1.GetGraphVertexNum(30,0);
    int end = method1.GetGraphVertexNum(47,lineNum-1);
    double ans = method1.CoreAlgorithm(start,end);

    printf("%d -> %d %lf\n",start,end,ans);
    return 0;
}
