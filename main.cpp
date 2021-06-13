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
void PrintAStarExample();
void PrintPSO();
void PrintPSOExample();

void DealProblem();

int main(){
    LogUtils logger(ALL_LOG_LEVEL);
    srand(time(NULL));
    //PrintNearest();
    //PrintBFSAndAStar();
    //PrintAStar();
    //PrintKruAndPSO();
    //PrintPSO();
    //PrintPSOExample();
    //PrintAStarExample();
    //DealProblem();
    int which;
    printf("选择输出内容：1.BFS和A*比较 2.Kruskal算法和PSO算法比较 3.解决实际问题\n");
    cin >> which;
    switch (which)
    {
    case 1:
        PrintBFSAndAStar();
        break;
    case 2:
        PrintKruAndPSO();
        break;
    case 3:
        DealProblem();
        break;
    default:
        printf("输入有误!!!");
        break;
    }
    return 0;
}

void DealProblem(){

    int problem = 0;
    printf("\n问题类型：1.两点斯坦纳树问题 2.多点斯坦纳树问题\n");
    cin >> problem;
    if(problem == 2){
        int pointNum = 0;
        vector<pair<int,int>> dict;
        printf("给定点数量？\n");
        cin >> pointNum;
        for(int i = 0,x,y; i < pointNum; ++i){
            cin >> x >> y;
            dict.push_back(make_pair(x,y));
        }
        PSOAlgorithm method2(pointNum * 2,max(100,pointNum * pointNum),dict);
        method2.CoreAlgorithm();
        method2.PrintAlgorithmAns();
        printf("\n");
    }else if(problem == 1){
        int startX,startY,endX,endY,obstacleNum,lineNum = 30;
        vector<pair<int,int>> dict;

        // printf("坐标范围?\n");
        // cin >> lineNum; lineNum += 10;
        printf("起点坐标？\n");
        cin >> startX >> startY;
        printf("终点坐标?\n");
        cin >> endX >> endY;
        printf("障碍物数量?\n");
        cin >> obstacleNum;
        for(int i = 0,x,y; i < obstacleNum * 2; ++i){
            cin >> x >> y;
            dict.push_back(make_pair(x,y));
        }

        AStar method1(lineNum * lineNum,dict);
        int start = method1.GetGraphVertexNum(startX,startY);
        int end = method1.GetGraphVertexNum(endX,endY);
        method1.CoreAlgorithm(start,end);
        method1.PrintPath(start,end);
    }else{
        printf("输入错误！！");
    }
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
    int lineNum = 800,calNum = 1;

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
        //printf("\n第%d次:\n",i);
        printf("BFS算法时间:%lfms，A*算法时间:%lfms\n",useTime[0],useTime[1]);
        printf("相对时间减少:%lf%%\n",rate * 100); 
        
    }
}

void PrintKruAndPSO(){
    double averageTime = 0,averageCost = 0;
    int averageKru = 0,averagePSO = 0;
    printf("\n");
    const int calSum = 10;
    for(int i = 1; i <= calSum; ++i){
        double beginTime,useTime,kruAns,PSOAns,rate;
        beginTime = clock();
        int pointNum = 9;
        int iter = max(100,pointNum * pointNum / 2);
        PSOAlgorithm method2(pointNum * 2,iter,pointNum);
        method2.CoreAlgorithm();
        useTime = (clock() - beginTime) / 1000;
        averageTime += useTime;

        kruAns = method2.GetKruskalAns();
        PSOAns = method2.GetPSOAns();   
        rate = (kruAns - PSOAns) / kruAns;
        averageCost += rate;

        averageKru += (int)kruAns,averagePSO += PSOAns;
        printf("第%d次:\n运行时间:%lfms\n",i,useTime);
        printf("kruskal:%d,\tPSO:%d\n",(int)kruAns,(int)PSOAns);
        printf("相较而言消耗减少:%lf%% \n",rate * 100);
    }

    averageCost /= calSum;  averageTime /= calSum;
    averagePSO /= calSum;   averageKru /= calSum;

    printf("\nKruskal:%d  PSO:%d 减少:%d\n",averageKru,averagePSO,averageKru - averagePSO);
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


void PrintPSO(){
    printf("\n");
    PSOAlgorithm method2(20,500,4);
    method2.CoreAlgorithm();

    method2.PrintAlgorithmAns();
    
    printf("\n"); 
}


void PrintPSOExample(){
    printf("\n");
    vector<pair<int,int>> dict;
    dict.push_back(make_pair(39,54));
    dict.push_back(make_pair(21,25));
    dict.push_back(make_pair(89,10));
    dict.push_back(make_pair(84,99));
    PSOAlgorithm method2(20,500,dict);
    method2.CoreAlgorithm();

    method2.PrintAlgorithmAns();
    printf("\n");
}

void PrintAStarExample(){
    int lineNum = 30;
    vector<pair<int,int>> tmp;
    tmp.push_back(make_pair(1,2));
    tmp.push_back(make_pair(2,3));
    tmp.push_back(make_pair(2,0));
    tmp.push_back(make_pair(3,3));

    AStar method1(lineNum * lineNum,tmp);
    int start = method1.GetGraphVertexNum(0,0);
    int end = method1.GetGraphVertexNum(4,4);
    double ans = method1.CoreAlgorithm(start,end);

    method1.PrintPath(start,end);

    // printf("%d -> %d %lf\n",start,end,ans);
    // printf("start: x:%d,y:%d\n",start/lineNum,start%lineNum);
    // printf("end: x:%d,y:%d\n",end/lineNum,end%lineNum); 
}