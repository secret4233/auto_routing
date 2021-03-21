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
};

class PSOAlgorithm{
private:
    double kruskalAns,algorithmAns;
    vector<Vertex> basicPoints; // TODO 是否使用自定义模板有待考虑
    vector<Vertex> hananPoints; // hanan点集合
    double kruskalAlgorithm(const vector<Vertex>&);
    void randGraph();
    void getHananPoints();
    void init();
    double calCost(const vector<Vertex>&);
    Vertex nearestPoint(int x,int y);

    //这一块为核心算法内部使用变量

    //pNum:粒子数量,iters:迭代次数
    int iters,pNum,maxHananNum;
    double vMax,vMin,posMax,posMin; //阈值范围
    vector<particleMessage> pBest;   // 各粒子求得的最优长度
    particleMessage gBest;           // 全局最优长度
    vector<particleMessage> pos,spd; // 各粒子的位置及速度信息

    // 第一维:迭代次数,第二维:粒子数
    Matrix<double, Dynamic, Dynamic> fTest;             // 每个粒子求得的长度
    Matrix<particleMessage, Dynamic, Dynamic> posMat;   // 最优解(包含的点)

public:
    PSOAlgorithm(int,int);
    double CoreAlgorithm();
    double GetKruskalAns();
};


#endif