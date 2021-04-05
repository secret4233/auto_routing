#include "pso.h"

// 生成随机数量(10-20),位置不定(0-99)的点
// FIXME 注意去重
void PSOAlgorithm::randGraph(){
    int randPointNum = rand() % 11 + 10;

    // 此处规定hanan点数量,为总随机点数-2
    maxHananNum = randPointNum - 2;
    Vertex tmp;
    for(int i = 1; i <= randPointNum; ++i){
        tmp.which = i;
        tmp.xAxis = rand() % posMax,tmp.yAxis = rand() % posMax;
        basicPoints.push_back(tmp);
        LogInfo("PSOAlgothm basic point: which:%d\t,xAxis:%d\t,yAxis:%d\t",
                i,(int)tmp.xAxis,(int)tmp.yAxis);
    }
    LogInfo("PSOAlgorithm randGraph complete");
    return;
}


void PSOAlgorithm::getHananPoints(){                                                                                                                                                                                                                                                                                               
    // Axes:Axis的复数形式
    vector<int> xAxes,yAxes;
    set<pair<int,int>> dict; //用于检验元素是否重复,简易树套树(doge)
    pair<int,int> tmp;
    for(auto it = basicPoints.begin(); it != basicPoints.end(); it++){
        xAxes.push_back(it->xAxis);
        yAxes.push_back(it->yAxis);
        dict.insert(make_pair(it->xAxis,it->yAxis));
    }
    sort(xAxes.begin(),xAxes.end());    unique(xAxes.begin(),xAxes.end());
    sort(yAxes.begin(),yAxes.end());    unique(yAxes.begin(),yAxes.end());

    Vertex tmpVertex;
    for(auto i = xAxes.begin(); i != xAxes.end(); i++){
        for(auto j = yAxes.begin(); j != yAxes.end(); j++){
            int xAxis = *i,yAxis = *j;
            if(dict.count(make_pair(xAxis,yAxis)))  continue;
            tmpVertex.xAxis = xAxis,tmpVertex.yAxis = yAxis;
            hananPoints.push_back(tmpVertex);
        }
    }
    LogInfo("PSOAlgorithm getHananPoints complete");
    return;
}

void PSOAlgorithm::getPointsBelong(){
    memset(pointsBelong,-1,sizeof(pointsBelong));
    int directionXAxis[10] = {1,-1,0,0};
    int directionYAxis[10] = {0,0,1,-1};
    queue<Vertex> q;
    Vertex nowVertex,needToAdd;
    for(int i = 0; i < hananPoints.size(); ++i){
        nowVertex = hananPoints[i];
        nowVertex.which = i;
        q.push(nowVertex);
        pointsBelong[(int)nowVertex.xAxis][(int)nowVertex.yAxis] = i;
    } 
    while(!q.empty()){
        nowVertex = q.front();    q.pop();
        for(int i = 0; i < 4; ++i){
            int nowXAxis = nowVertex.xAxis + directionXAxis[i];
            int nowYAxis = nowVertex.yAxis + directionYAxis[i];

            if(nowXAxis < 0 || nowXAxis >= 100 || nowYAxis < 0 || nowYAxis >= 100)  continue;
            if(pointsBelong[nowXAxis][nowYAxis] != -1)  continue;

            pointsBelong[nowXAxis][nowYAxis] = nowVertex.which;

            needToAdd.which = nowVertex.which;
            needToAdd.xAxis = (double)nowXAxis,needToAdd.yAxis = (double)nowYAxis;
            q.push(needToAdd);
        }
    }
    LogInfo("PSOAlgorithm getPointsBelong complete");
    return;
}

Vertex PSOAlgorithm::nearestPoint(int x,int y){
    int which = pointsBelong[x][y];
    if(which == -1 || which >= hananPoints.size()){
        LogError("nearestPoint error, xAxis:%d,yAxis:%d",x,y);
    }
    return hananPoints[which];
}


/*
kruskal算法:充当代价函数
返回-1:运行有误
TODO 目前采用最简单的做法,即暴力枚举每条边后生成最小生成树,后续可以考虑优化
*/
double PSOAlgorithm::kruskalAlgorithm(const vector<Vertex>& randPoints){
    if(basicPoints.size() <= 0){
        LogError("randGraph not running");
        return -1;
    }
    vector<Vertex> nowPoints = basicPoints;
    nowPoints.insert(nowPoints.end(),randPoints.begin(),randPoints.end());

    // LogDebug("krskalAlgorithm nowPoints size:%d",(int)nowPoints.size());

    // 给随机点生成编号
    for(int i = 0; i < nowPoints.size(); ++i){
        nowPoints[i].which = i;
    }

    vector<Edge> allEdge;
    Edge tmp;
    for(int i = 0; i < nowPoints.size(); ++i){
        for(int j = 0; j < nowPoints.size(); ++j){
            if(i == j)  continue;
            tmp.u = nowPoints[i].which,tmp.v = nowPoints[j].which;
            tmp.w = CalDistance(nowPoints[i],nowPoints[j]);
            allEdge.push_back(tmp);
        }
    }
    sort(allEdge.begin(),allEdge.end());


    class UNS dict;
    double nowAns = 0.0;
    for(auto it = allEdge.begin(); it !=  allEdge.end(); it++){
        if(!dict.IsSameFather(it->u,it->v)){
            dict.UnionPoint(it->u,it->v);
            nowAns += it->w;
        }
    }
    return nowAns;
}


// pso算法的初始化
void PSOAlgorithm::init(){
    posMat.resize(iters,pNum); 
    fTest.resize(iters,pNum);       fTest.fill(INF);
    static mt19937 rng;
    uniform_real_distribution<double> rand1(0,99);
    // uniform_real_distribution<double> rand2(-99,99);
    for(int i = 0; i < pNum; ++i){ // 枚举所有粒子
        particleMessage posNeedToAdd,spdNeedToAdd;
        posNeedToAdd.UsefulNum = rand() % (maxHananNum + 1);
        spdNeedToAdd.UsefulNum = posNeedToAdd.UsefulNum;
        for(int j = 0; j < maxHananNum; ++j){ // 枚举每个粒子的最大Hanan点的数量
            // TODO:此处选用的hanan点为随机生成某点后取最近的点,也许可优化
            Vertex tmpMessage = nearestPoint((int)rand1(rng),(int)rand1(rng));
            posNeedToAdd.BasicMessage.push_back(tmpMessage);
            spdNeedToAdd.BasicMessage.push_back(Vertex{0,0,0});
        }
        pos.push_back(posNeedToAdd);
        spd.push_back(spdNeedToAdd);
    }

    for(int i = 0; i < pNum; ++i){
        double tmp = kruskalAlgorithm(pos[i].GetUsefulMessage());
        fTest(0,i) = tmp;
        posMat(0,i) = pos[i];
        pBest.push_back(pos[i]);
    }
    Index minRow,minCol;
    fTest.row(0).minCoeff((&minRow,&minCol));
    gBest = posMat(0,minCol);

    LogInfo("PSOAlgorithm init complete");
}


//pNum:粒子数量,iters:迭代次数
PSOAlgorithm::PSOAlgorithm(int _pNum,int _iters):pNum(_pNum),iters(_iters){
    spdMax = 100,spdMin = -100;
    posMax = 100,posMin = -1;
    randGraph();
    getHananPoints();
    getPointsBelong();
    init();
    vector<Vertex> tmp;
    kruskalAns = kruskalAlgorithm(tmp);
    LogInfo("PSOAlgorithm::PSOAlgorithm complete");
}

//该函数负责处理越界的情况
Vertex PSOAlgorithm::dealOutOfBounds(Vertex which,bool isSpeed){
    Vertex now;
    int minBound = posMin,          maxBouns = posMax;
    if(isSpeed) minBound = spdMin,  maxBouns = spdMax;

    if(which.xAxis <= minBound)    now.xAxis = minBound + 1;
    if(which.xAxis >= maxBouns)    now.xAxis = maxBouns - 1;  

    if(which.yAxis <= minBound)    now.yAxis = minBound + 1;
    if(which.yAxis >= maxBouns)    now.yAxis = maxBouns - 1;
    return now;
}

void PSOAlgorithm::CoreAlgorithm(){
    static mt19937 rng;
    uniform_real_distribution<double> randNum(0,1);

    double nowGobalBestAns = INF;
    for(int step = 1; step < iters; ++step){
        double omiga = 0.9 - (double)step / iters * 0.5;

        for(int i = 0; i < pNum; ++i){            
            // 更新各个粒子有效点的信息
            int nowHananPointsNum = max(max(gBest.UsefulNum,pBest[i].UsefulNum),pos[i].UsefulNum);
            for(int nowPoint = 0; nowPoint < nowHananPointsNum; ++nowPoint){
                spd[i][nowPoint] = spd[i][nowPoint] * omiga
                                    + (pBest[i][nowPoint] - pos[i][nowPoint]) * 2 * randNum(rng)
                                    + (gBest[nowPoint] - pos[i][nowPoint]) * 2 * randNum(rng);
                pos[i][nowPoint] = pos[i][nowPoint] + spd[i][nowPoint];

                // 越界处理
                spd[i][nowPoint] = dealOutOfBounds(spd[i][nowPoint],1);
                pos[i][nowPoint] = dealOutOfBounds(pos[i][nowPoint],0);

                pos[i][nowPoint] = nearestPoint(pos[i][nowPoint].xAxis,pos[i][nowPoint].yAxis);
            }

            // 取得更新后粒子的有效信息
            posMat(step,i) = pos[i];
        }

        //更新函数值矩阵
        for (int i = 0; i < pNum; ++i){
            auto tmp = kruskalAlgorithm(pos[i].GetUsefulMessage());
            fTest(step, i) = tmp;
        } 
        for(int i = 0; i < pNum; ++i){
            MatrixXd tmpBest;
            tmpBest = fTest.col(i); 
            Index minRow,minCol;
            tmpBest.minCoeff(&minRow,&minCol);
            pBest[i] = posMat(minRow,i);
        }
        Index minRow,minCol;
        fTest.row(step).minCoeff((&minRow,&minCol));
        if(fTest(step,minCol) < nowGobalBestAns){
            nowGobalBestAns = fTest(step,minCol);
            gBest = posMat(step,minCol);
        }
        // LogDebug("PSOAlgorithm CoreAlgorithm step%d complete",step);
    }
    return;
}

void PSOAlgorithm::PrintAlgorithmAns(){
    printf("生成的随机点:\n");
    for(int i = 0; i < basicPoints.size(); ++i){
        printf("随机点%02d: x轴坐标:%02d,y轴坐标:%02d\n",i,(int)basicPoints[i].xAxis,(int)basicPoints[i].yAxis);
    }

    printf("PSO算法最优结果使用的hanan点:\n");
    for(int i = 0; i < gBest.UsefulNum; ++i){
        printf("hanan点%02d: x轴坐标:%02d,y轴坐标:%02d\n",i,(int)gBest[i].xAxis,(int)gBest[i].yAxis);
    }

    double PSOAns = kruskalAlgorithm(gBest.GetUsefulMessage());
    printf("\nPSO算法求得得最小斯坦纳树的值:%lf\n",PSOAns);

    printf("最小生成树求得的值:%lf\n",kruskalAns);
    
    return;
}