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
    pair<int,int> nearestPoint(int x,int y);

    //这一块为核心算法内部使用变量

    //p_num:粒子数量,iters:迭代次数
    int iters,pNum;
    double v_max,v_min,pos_max,pos_min; //阈值范围
    vector<double> pBest;   //pos:position,spd:speed,pBest
    double gBest;
    vector<pair<int,int>> pos,spd;
    Matrix<pair<int,int>, Dynamic, Dynamic> fTest; 
    Matrix<pair<int,int>, Dynamic, Dynamic> posMat;   

public:
    PSOAlgorithm(int,int);
    double CoreAlgorithm(int,int);
};


#endif