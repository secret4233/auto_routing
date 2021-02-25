#include "pso.h"


//const int INF = 0x3f3f3f3f;
//const double pi = acos(-1.0);
//struct PSO{
    ////dim:维数,p_num:粒子数量,iters:迭代次数
    //int dim,pNum,iters;
    //double v_max,v_min,pos_max,pos_min; //阈值范围
    //vector<double> pos,spd,pBest;   //pos:position,spd:speed
    //double gBest;
    //Matrix<Matrix<double,2,2>, Dynamic, Dynamic> fTest; //TODO 考虑自定义内部矩阵,然后重载比较函数?
    //Matrix<Matrix<double,2,2>, Dynamic, Dynamic> posMat;   

 ////   double calCost(double x){,
        //double res = x * x + 1;
        //return res;
    //}


    ////初始化粒子
    //double init(int _dim,int _pNum,int _iters = 100000){
        //posMat.resize(_iters,pNum); posMat.fill(INF);
        //fTest.resize(_iters,pNum);  fTest.fill(INF);            
        //static mt19937 rng;
        //uniform_real_distribution<double> rand1(-1,2);
        //uniform_real_distribution<double> rand2(-2,4);
        //for(int i = 1; i < pNum; ++i){
            //pos.push_back(rand1(rng));
            //spd.push_back(rand2(rng));
        //}
        //vector<double> vec;
        //for(int i = 0; i < pNum; ++i){  //初始化各个粒子的历史最优位置
            //double tmp = calCost(pos[i]);
            //fTest(0,i) = tmp;
            //posMat(0,i) = pos[i];
            //pBest.push_back(pos[i]);
        //}
        //Index  minRow,minCol;
        //fTest.row(0).minCoeff(&minRow,&minCol);
        //gBest = posMat(minRow,minCol);// 初始化全局最优解
    //}

    ////pso算法
    //void psoAlgorithm(){
        //static mt19937 rng;
        //uniform_real_distribution<double> randNum(0,1);
        //for(int step = 1; step <= iters; ++step){
            //double w = 0.9 - (double)step / iters * 0.5; 
            //for(int i = 0; i < pNum; ++i){
                //spd[i] = w * spd[i] + 2 * randNum(rng) * (pBest[i] - pos[i])
                                    //+ 2 * randNum(rng) * (gBest - pos[i]);
                //pos[i] = pos[i] + spd[i];
                ////越界处理
                //if (spd[i] < -2 || spd[i] > 4)
                    //spd[i] = 4;
                //if (pos[i] < -1 || pos[i] > 2)
                    //pos[i] = -1;
                //posMat(step,i) = pos[i];
            //}
            ////更新函数值矩阵
            //for (int i = 0; i < pNum; ++i){
                //auto tmp = calCost(pos[i]);
                //fTest(step, i) = tmp;
            //} 
            //for(int i = 0; i < pNum; ++i){
                //MatrixXd tmpBest;
                //tmpBest = fTest.col(i);
                //Index minRow,minCol;
                //tmpBest.minCoeff(&minRow,&minCol);
                //pBest[i] = posMat(minRow,i);
            //}
            //gBest = *min_element(pBest.begin(),pBest.end());
        //}
    //}


//};

// 生成随机数量(5-10),位置不定(0-9999)的点
// FIXME 注意去重
void PSOAlgorithm::randGraph(){
    int randPointNum = rand() % 6 + 5;
    Vertex tmp;
    for(int i = 0; i < randPointNum; ++i){
        tmp.which = i;
        tmp.xAxis = rand() % 10000,tmp.yAxis = rand() % 10000;
        basicPoints.push_back(tmp);
        LogInfo("PSOAlgothm basic point: which:%d\t,xAxis:%d\t,yAxis:%d\t",
                i,tmp.xAxis,tmp.yAxis);
    }
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
    return;
}


//kruskal算法:充当代价函数
//返回-1:运行有误
double PSOAlgorithm::kruskalAlgorithm(const vector<Vertex>* randPoints){
    if(basicPoints.size() <= 0){
        LogError("randGraph not running");
        return -1;
    }

    
}




