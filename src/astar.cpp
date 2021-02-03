#include "astar.h"

double CalCost(Graph *g,int nowVertex,int endVertex){
    const Vertex *now = g->GetVertex(nowVertex);
    const Vertex *end = g->GetVertex(endVertex);

    return abs(now->xAxis - end->xAxis) + abs(now->yAxis - end->yAxis);
}

void AStar::randGraph(int sqrtVecNum){
    int obstacleNum = rand() % 3 + 1;
    pair<int,int> obsracleMessage;

    for(int i = 0 ; i < sqrtVecNum; ++i){
        for(int j = 0; j < sqrtVecNum; ++j){

        }
    }
}

AStar::AStar(int _vecNum,int _k):g(100){
    k = _k; algorithmAns = -1;
    randGraph(10);
};



double AStar::CoreAlgorithm(int star,int end,double (*cal)(int,int)){
    priority_queue<Node> q;
    q.push((Node){star,0,cal(star,end)});
    LogDebug("A*算法开始");
    while(!q.empty()){
        Node oldX = q.top(); q.pop();
        int u = oldX.u;
        if(u == end){
            if(--k == 0){
                algorithmAns = oldX.dis;
                LogInfo("A*算法求出了一个解");
                return algorithmAns;     
            }
        }
        for(const Edge *nxt = g.GetFirstEdge(u); nxt != NULL; nxt = g.GetNxtEdge(nxt)){
            int v = nxt->v;
            
            if(oldX.vis[v])    continue; //该搜索路径下,已经访问过该节点,则无需入队
            Node newX = oldX;  //继承访问过的节点,也可视为搜索路径
            newX.u = v; 
            newX.vis[v] = 1;
            newX.h = cal(v,end); 
            newX.dis = nxt->w + oldX.dis;
            q.push(newX);
        }
    }
    LogInfo("该图不存在从起始点到终止点的路径");
    return algorithmAns;
}