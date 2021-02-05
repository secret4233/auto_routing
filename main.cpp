#include <bits/stdc++.h>
#include "inc/pso.h"
#include "inc/graph.h"
#include "inc/log.h"
#include "inc/astar.h"



using namespace std;    


int main(){
    LogUtils logger;
    
    AStar method1(25,1);
    int star = method1.GetGraphVertexNum(2,0);
    int end = method1.GetGraphVertexNum(2,4);
    double ans = method1.CoreAlgorithm(star,end);

    printf("%lf",ans);

}
