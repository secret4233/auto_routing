#include <bits/stdc++.h>
#include "inc/pso.h"
#include "inc/graph.h"
#include "inc/log.h"
#include "inc/astar.h"



using namespace std;    


void PrintKruAndPSO();
void PrintNearest();
void PrintAStar();

int main(){
    LogUtils logger(ALL_LOG_LEVEL);
    srand(time(NULL));
    //PrintAStar();
    PrintKruAndPSO();
    //PrintNearest();

    return 0;
}

void PrintAStar(){
   int lineNum = 50; 
    AStar method1(lineNum * lineNum,1);
    int start = method1.GetGraphVertexNum(rand()%lineNum,0);
    int end = method1.GetGraphVertexNum(rand()%lineNum,lineNum-1);
    double ans = method1.CoreAlgorithm(start,end);

    printf("%d -> %d %lf\n",start,end,ans);
    printf("start: x:%d,y:%d\n",start/lineNum,start%lineNum);
    printf("end: x:%d,y:%d\n",end/lineNum,end%lineNum); 
}

void PrintKruAndPSO(){
   double averageTime,averageCost;
    printf("\n");
    const int calSum = 5;
    for(int i = 1; i <= calSum; ++i){
        double beginTime,useTime,kruAns,PSOAns,rate;
        beginTime = clock();
        PSOAlgorithm method2(20,500,20);
        method2.CoreAlgorithm();
        useTime = (clock() - beginTime) / 1000;
        averageTime += useTime;

        kruAns = method2.GetKruskalAns();
        PSOAns = method2.GetPSOAns();   
        rate = (kruAns - PSOAns) / kruAns;
        averageCost += rate;

        printf("第%d次:\n运行时间:%lfms\n",i,useTime);
        printf("kruskal:%d,\tPSO:%d\n",(int)kruAns,(int)PSOAns);
        printf("相较而言消耗减少:%lf%% \n",rate * 100);
    }

    averageCost /= calSum;
    averageTime /= calSum;

    printf("\n平均时长:%lfms\n",averageTime);
    printf("平均消耗减少:%lf%%\n",averageCost * 100);
    
    printf("\n"); 
}

void PrintNearest(){
    double averageRate;
    printf("\n");
    const int calSum = 5;
    for(int i = 1; i <= calSum; ++i){
        double beginTime[5],useTime[5],rate;
        PSOAlgorithm method2(20,500,20);


        beginTime[0] = clock();
        method2.CoreAlgorithm();
        useTime[0] = (clock() - beginTime[0]) / 1000;

        method2.SetNearestAlgorithm(1);
        beginTime[1] = clock();
        method2.CoreAlgorithm();
        useTime[1] = (clock() - beginTime[1]) / 1000;

        rate = (useTime[1] - useTime[0]) / useTime[1];
        averageRate += rate;

        printf("\n第%d次:\n",i);
        printf("优化算法时间:%lfms，未优化算法时间:%lfms\n",useTime[0],useTime[1]);
        printf("相对时间减少:%lf%%\n",rate * 100);
    }

    averageRate /= calSum;
    printf("平均下来，时间减少:%lf\n",averageRate);

    
    printf("\n");
}
