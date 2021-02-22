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
    vector<Vertex> basicPoint;
    // Graph g;
    double kruskalAlgorithm(const vector<Vertex>*);
    void randGraph();
    void addEdge(int,int);

    //这一块为算法内部使用变量

public:
    PSOAlgorithm(int);
    double CoreAlgorithm(int,int);
};


#endif