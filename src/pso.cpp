#include <Eigen/Core> //todo 避免重复引用头文件 
#include "pso.h"

using namespace std;

const int INF = 0x3f3f3f3f;
const double pi = acos(-1.0);
struct PSO{
    //dim:维数,p_num:粒子数量,iters:迭代次数
    int dim,p_num,iters;
    double v_max,v_min,pos_max,pos_min;
    vector<double> pos,spd,p_best;
    double g_best;

};