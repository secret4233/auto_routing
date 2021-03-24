#include "pso.h"

// 生成随机数量(5-10),位置不定(0-9999)的点
// FIXME 注意去重
void PSOAlgorithm::randGraph(){
    int randPointNum = rand() % 6 + 5;

    // 此处规定hanan点数量,为总随机点数-2
    maxHananNum = randPointNum - 2;
    Vertex tmp;
    for(int i = 1; i <= randPointNum; ++i){
        tmp.which = i;
        tmp.xAxis = rand() % 10000,tmp.yAxis = rand() % 10000;
        basicPoints.push_back(tmp);
        LogInfo("PSOAlgothm basic point: which:%d\t,xAxis:%d\t,yAxis:%d\t",
                i,tmp.xAxis,tmp.yAxis);
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

    // 给随机点生成编号
    for(int i = 0; i < nowPoints.size(); ++i){
        if(nowPoints[i].which == 0){
            if(i == 0){
                LogError("firstPoint is zero");
                return -1;
            }
            nowPoints[i].which = nowPoints[i - 1].which + 1;
        }
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
    fTest.resize(iters,pNum);
    static mt19937 rng;
    uniform_real_distribution<int> rand1(0,10000);
    uniform_real_distribution<int> rand2(-20000,20000);
    for(int i = 0; i < pNum; ++i){ // 枚举所有粒子
        particleMessage posNeedToAdd,spdNeedToAdd;
        posNeedToAdd.UsefulNum = rand() % (maxHananNum + 1);
        spdNeedToAdd.UsefulNum = posNeedToAdd.UsefulNum;
        for(int j = 0; j < maxHananNum; ++j){ // 枚举每个粒子的最大Hanan点的数量
            // TODO:此处选用的hanan点为随机生成某点后取最近的点,也许可优化
            Vertex tmpMessage = nearestPoint(rand1(rng),rand1(rng));
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
    gBest = posMat(minCol,minCol);
}


//pNum:粒子数量,iters:迭代次数
PSOAlgorithm::PSOAlgorithm(int _pNum,int _iters):pNum(_pNum),iters(_iters){
    randGraph();
    getHananPoints();
    vector<Vertex> tmp;
    kruskalAns = kruskalAlgorithm(tmp);
}


double PSOAlgorithm::CoreAlgorithm(){
   static mt19937 rng;
    uniform_real_distribution<double> randNum(0,1);
    for(int step = 1; step <= iters; ++step){
        double omiga = 0.9 - (double)step / iters * 0.5;

        for(int i = 0; i < pNum; ++i){            
            // 更新各个粒子有效点的信息
            int nowHananPointsNum = max(max(gBest.UsefulNum,pBest[i].UsefulNum),pos[i].UsefulNum);
            for(int nowPoint = 0; nowPoint < nowHananPointsNum; ++nowPoint){
                spd[i][nowPoint] = spd[i][nowPoint] * omiga
                                    + (pBest[i][nowPoint] - pos[i][nowPoint]) * 2 * randNum(rng)
                                    + (gBest[nowPoint] - pos[i][nowPoint]) * 2 * randNum(rng);
                pos[i][nowPoint] = pos[i][nowPoint] + spd[i][nowPoint];
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
        gBest = *min_element(pBest.begin(),pBest.end()); 
    }
}