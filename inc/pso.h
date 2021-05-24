#ifndef _PSO_H
#define _PSO_H 

#include <bits/stdc++.h>
#include <Eigen/Core> 
#include "log.h"
#include "graph.h"

using namespace std;
using namespace Eigen;

const int INF = 0x3f3f3f3f;
const double pi = acos(-1.0);

struct particleMessage{
    int UsefulNum; // 有效点的数量
    vector<Vertex> BasicMessage;
    vector<Vertex> GetUsefulMessage(){
        vector<Vertex> result;
        result.assign(BasicMessage.begin(),BasicMessage.begin() + UsefulNum);
        return result;
    }
    Vertex &operator [] (int x){
        if(x >= BasicMessage.size()){
            LogError("particleMessage out of bound! BasicMessage.size:%d,need to find:%d",(int)BasicMessage.size(),x);
        }
        return BasicMessage[x];
    }
};

class PSOAlgorithm{
private:
    double kruskalAns,algorithmAns;
    vector<Vertex> basicPoints; 
    vector<Vertex> hananPoints; // hanan点集合
    //int pointsBelong[200][200]; // 距离某点最近的hanan点
    bool useNewNearest;
    double kruskalAlgorithm(const vector<Vertex>&);
    Vertex dealOutOfBounds(Vertex,bool);
    void randGraph(int);
    void getBounds(vector<pair<int,int>>);
    void readGraph(vector<pair<int,int>>);
    void getHananPoints();
    //void getPointsBelong();
    void init();
    // double calCost(const vector<Vertex>&);
    Vertex nearestPoint(int x,int y);
    Vertex nearestPointNew(int x,int y);

    //这一块为核心算法内部使用变量

    //pNum:粒子数量,iters:迭代次数,maxHananNum:最大的hanan点数量
    int iters,pNum,maxHananNum;
    int spdMax,spdMin,posMax,posMin;    // 阈值范围,左开右开
    vector<particleMessage> pBest;      // 各粒子求得的最优{x1,x2...}
    particleMessage gBest;              // 全局最优长度{x1,x2...}
    vector<particleMessage> pos,spd;    // 各粒子的位置或速度信息

    // 第一维:迭代次数,第二维:粒子数
    Matrix<double, Dynamic, Dynamic> fTest;             // 每次迭代,各个粒子求得的{y}
    Matrix<particleMessage, Dynamic, Dynamic> posMat;   // 每次迭代,各个粒子的最优解{x1,x2...}

    vector<Edge> pointConnection;
public:
    PSOAlgorithm(int,int,int);
    PSOAlgorithm(int,int,vector<pair<int,int>>);
    void CoreAlgorithm();
    void PrintAlgorithmAns();
    void SetNearestAlgorithm(bool);
    double GetKruskalAns();
    double GetPSOAns();
    
};


#endif