#include <bits/stdc++.h>
#include "inc/pso.h"
#include "inc/graph.h"
#include "inc/log.h"
#include "inc/astar.h"



using namespace std;    


void PrintKruAndPSO();
void PrintNearest();
void PrintAStar();
void PrintBFSAndAStar();
void TestAStarRead();

int main(){
    LogUtils logger(ALL_LOG_LEVEL);
    srand(time(NULL));
    //PrintBFSAndAStar();
    //TestAStarRead();
    PrintAStar();
    //PrintKruAndPSO();
    //PrintNearest();

    return 0;
}


void TestAStarRead(){
    int lineNum = 30;
    vector<pair<int,int>> tmp;
    tmp.push_back(make_pair(2,2));
    tmp.push_back(make_pair(4,4));
    tmp.push_back(make_pair(5,5));
    tmp.push_back(make_pair(6,6));

    AStar method1(lineNum * lineNum,tmp);
    int start = method1.GetGraphVertexNum(rand()%lineNum,0);
    int end = method1.GetGraphVertexNum(rand()%lineNum,lineNum-1);
    double ans = method1.CoreAlgorithm(start,end);

    printf("%d -> %d %lf\n",start,end,ans);
    printf("start: x:%d,y:%d\n",start/lineNum,start%lineNum);
    printf("end: x:%d,y:%d\n",end/lineNum,end%lineNum); 
}

void PrintAStar(){
    int lineNum = 50; 
    AStar method1(lineNum * lineNum);
    int start = method1.GetGraphVertexNum(rand()%lineNum,0);
    int end = method1.GetGraphVertexNum(rand()%lineNum,lineNum-1);
    double ans = method1.CoreAlgorithm(start,end);

    printf("%d -> %d %lf\n",start,end,ans);
    printf("start: x:%d,y:%d\n",start/lineNum,start%lineNum);
    printf("end: x:%d,y:%d\n",end/lineNum,end%lineNum); 
    method1.PrintPath(start,end);
}

void PrintBFSAndAStar(){
    int lineNum = 1000,calNum = 5;

    double averageRate = 0;
    for(int i = 1; i <= calNum; ++i){
        AStar method1(lineNum * lineNum);
        int start = method1.GetGraphVertexNum(rand()%lineNum,0);
        int end = method1.GetGraphVertexNum(rand()%lineNum,lineNum-1);

        double beginTime[5],useTime[5],rate;

        beginTime[0] = clock();
        int BFSAns = method1.BFSAlgorithn(start,end);
        useTime[0] = (clock() - beginTime[0]) / 1000;

        beginTime[1] = clock();
        int AStarAns = method1.CoreAlgorithm(start,end);
        useTime[1] = (clock() - beginTime[1]) / 1000;

        rate = (useTime[0] - useTime[1]) / useTime[0];
        averageRate += rate;

        //printf("start:%d,end:%d\n",start,end);
        if(BFSAns != AStarAns){
            printf("Error:BFSAns:%d,AStarAns:%d\n",BFSAns,AStarAns);
        }
        printf("\n第%d次:\n",i);
        printf("BFS算法时间:%lfms，A*算法时间:%lfms\n",useTime[0],useTime[1]);
        printf("相对时间减少:%lf%%\n",rate * 100); 
        
    }
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
