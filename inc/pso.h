#ifndef _PSO_H
#define _PSO_H 

#include <bits/stdc++.h>
#include <Eigen/Core> 
#include "log.h"
#include "graph.h"

using namespace std;
using namespace Eigen;

class PSOAlgorithm{
private:
    double kruskalAns,algorithmAns;
    vector<Vertex> basicPoints; //TODO 是否使用自定义模板有待考虑,暂定使用自身的模板
    vector<Vertex> hananPoints; // hanan点集合
    double kruskalAlgorithm(const vector<Vertex>*);
    void randGraph();
    void getHananPoints();

    //这一块为算法内部使用变量

    //dim:维数,p_num:粒子数量,iters:迭代次数
    int dim,iters,pNum;
    double v_max,v_min,pos_max,pos_min; //阈值范围
    vector<double> pos,spd,pBest;   //pos:position,spd:speed,pBest
    double gBest;
    Matrix<pair<int,int>, Dynamic, Dynamic> fTest; 
    Matrix<pair<int,int>, Dynamic, Dynamic> posMat;   

public:
    PSOAlgorithm(int);
    double CoreAlgorithm(int,int);
};


#endif