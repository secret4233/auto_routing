#include "astar.h"

double AStar::calCost(int nowVertex,int endVertex){
    const Vertex *now = g.GetVertex(nowVertex);
    const Vertex *end = g.GetVertex(endVertex);

    return abs(now->xAxis - end->xAxis) + abs(now->yAxis - end->yAxis);
}

// 变量的使用有点优化

const int maxObstacleNum = 5;
int obstacleNum;
int sqrtVertexNum;
// 表明随机图生成的障碍,第一个点代表左下,第二点为右上
pair<int,int> obstacleMessage[maxObstacleNum][2];

void randObstacle(){
    obstacleNum = rand() % 3 + 1;
    for(int i = 0; i < obstacleNum; ++i){
        obstacleMessage[i][0].first = (rand() % (sqrtVertexNum - 2)) + 1;
        obstacleMessage[i][0].second = (rand() % (sqrtVertexNum - 2)) + 1;
        obstacleMessage[i][1].first = (rand() % (sqrtVertexNum - 2)) + 1;
        obstacleMessage[i][1].second = (rand() % (sqrtVertexNum - 2)) + 1;

        if(obstacleMessage[i][0].first > obstacleMessage[i][1].first){
            swap(obstacleMessage[i][0].first,obstacleMessage[i][1].first);
        }
        if(obstacleMessage[i][0].second > obstacleMessage[i][1].second){
            swap(obstacleMessage[i][0].second,obstacleMessage[i][1].second);
        }
        LogDebug("A* rand graph: left %02d %02d",obstacleMessage[i][0].first,obstacleMessage[i][0].second);
        LogDebug("A* rand graph: right %02d %02d",obstacleMessage[i][1].first,obstacleMessage[i][1].second);
    }
}

bool isInObstacle(int xAxis,int yAxis){
    for(int i = 0; i < obstacleNum; ++i){
        if(xAxis >= obstacleMessage[i][0].first && xAxis <= obstacleMessage[i][1].first
            && yAxis >= obstacleMessage[i][0].second && yAxis <= obstacleMessage[i][1].second){
                LogDebug("xAxis:%d yAxis:%d  whichObstacle:%d",xAxis,yAxis,i);
                return true;
            }
    }
    return false;
}

bool isInGraph(int xAxis,int yAxis){
    if(xAxis < 0 || xAxis >= sqrtVertexNum || yAxis < 0 || yAxis >= sqrtVertexNum){
        return false;
    }
    return true;
}

int AStar::GetGraphVertexNum(int xAxis,int yAxis){
    return xAxis * sqrtVertexNum + yAxis;
}

void AStar::addEdge(int xAxis,int yAxis){
    int xAxisChange[5] = {0,0,1,-1};
    int yAxisChange[5] = {1,-1,0,0};
    int nowNum = GetGraphVertexNum(xAxis,yAxis);
    for(int i = 0; i < 4; ++i){
        int nxtXAxis = xAxis + xAxisChange[i];
        int nxtYAxis = yAxis + yAxisChange[i];
        if(!isInObstacle(nxtXAxis,nxtYAxis) && isInGraph(nxtXAxis,nxtYAxis)){
            int nxtNum = GetGraphVertexNum(nxtXAxis,nxtYAxis);
            g.AddEdge(nowNum,nxtNum,1);
            LogDebug("a new edge: %d -> %d",nowNum,nxtNum);
        }
    }
    return;
}

void AStar::randGraph(){
    randObstacle();
    for(int i = 0 ; i < sqrtVertexNum; ++i){
        for(int j = 0; j < sqrtVertexNum; ++j){
            if(isInObstacle(i,j))   continue;
            addEdge(i,j);
        }
    }
}

//要求_vertexNum为平方数
AStar::AStar(int _vertexNum,int _k):g(_vertexNum){
    k = _k; algorithmAns = -1;
    sqrtVertexNum = (int)sqrt(_vertexNum);
    randGraph();
    LogInfo("AStar init complete");
};



double AStar::CoreAlgorithm(int start,int end){
    priority_queue<Node> q;
    q.push((Node){start,0,calCost(start,end)});
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
            newX.h = calCost(v,end); 
            newX.dis = nxt->w + oldX.dis;
            q.push(newX);
        }
    }
    LogInfo("该图不存在从起始点到终止点的路径");
    return algorithmAns;
}