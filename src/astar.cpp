#include "astar.h"

double AStar::calCost(int nowVertex,int endVertex){
    const Vertex *now = g.GetVertex(nowVertex);
    const Vertex *end = g.GetVertex(endVertex);

    return abs(now->xAxis - end->xAxis) + abs(now->yAxis - end->yAxis);
}

// 全局变量的使用考虑优化

const int maxObstacleNum = 5;
int obstacleNum;
int sqrtVertexNum;
// 表明随机图生成的障碍,第一个点代表左下,第二点为右上
pair<int,int> obstacleMessage[maxObstacleNum][2];

void randObstacle(){
    obstacleNum = rand() % 3 + 1; //随机生成三个障碍物
    for(int i = 0; i < obstacleNum; ++i){
        obstacleMessage[i][0].first = (rand() % (sqrtVertexNum - 2)) + 1;
        obstacleMessage[i][0].second = (rand() % (sqrtVertexNum - 2)) + 1;
        obstacleMessage[i][1].first = (rand() % (sqrtVertexNum - 2)) + 1;
        obstacleMessage[i][1].second = (rand() % (sqrtVertexNum - 2)) + 1;
        // obstacleMessage[i][1].first = min(obstacleMessage[i][0].first + rand() % 10,sqrtVertexNum - 1);
        // obstacleMessage[i][1].second = min(obstacleMessage[i][1].second + rand() % 10,sqrtVertexNum - 1);

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
            //LogDebug("a new edge: %d -> %d",nowNum,nxtNum);
        }
    }
    return;
}

void AStar::randGraph(){
    randObstacle();
    for(int i = 0 ; i < sqrtVertexNum; ++i){
        for(int j = 0; j < sqrtVertexNum; ++j){
            if(isInObstacle(i,j))   continue;
            g.AddVertex(GetGraphVertexNum(i,j),i,j);
            addEdge(i,j);
        }
    }
    LogInfo("AStar rand graph complete");
}

void AStar::readGraph(vector<pair<int,int>> dict){
    // 处理障碍，记录到数组中
    obstacleNum = dict.size() / 2;
    for(int i = 0; i < dict.size(); i += 2){
        obstacleMessage[i / 2][0] = dict[i];
        obstacleMessage[i / 2][1] = dict[i + 1];
        LogDebug("A* rand graph: left %02d %02d",obstacleMessage[i/2][0].first,obstacleMessage[i/2][0].second);
        LogDebug("A* rand graph: right %02d %02d",obstacleMessage[i/2][1].first,obstacleMessage[i/2][1].second);
    }
    for(int i = 0 ; i < sqrtVertexNum; ++i){
        for(int j = 0; j < sqrtVertexNum; ++j){
            if(isInObstacle(i,j))   continue;
            g.AddVertex(GetGraphVertexNum(i,j),i,j);
            addEdge(i,j);
        }
    }
    LogInfo("AStar read graph complete");
}

//要求_vertexNum为平方数
AStar::AStar(int _vertexNum):g(_vertexNum),vertexNum(_vertexNum){
    vis = new int[_vertexNum + 10];
    algorithmAns = -1;
    sqrtVertexNum = (int)sqrt(_vertexNum);
    randGraph();
    LogInfo("AStar init complete");
};

AStar::AStar(int _vertexNum,vector<pair<int,int>> _obstacle):g(_vertexNum),vertexNum(_vertexNum){
    vis = new int[_vertexNum + 10];
    algorithmAns = -1;
    sqrtVertexNum = (int)sqrt(_vertexNum);
    if(_obstacle.size() % 2){
        LogError("传入数据格式有误");
        return;
    }
    readGraph(_obstacle);
    LogInfo("AStar init complete");
}

AStar::~AStar(){
    delete vis;
    LogDebug("AStar 类内存释放");
}

double AStar::CoreAlgorithm(int start,int end){
    memset(vis,-1,sizeof(int) * (vertexNum + 10));
    priority_queue<Node> q;
    q.push((Node){start,0,calCost(start,end)});
    LogInfo("A*算法开始");
    while(!q.empty()){
        Node oldX = q.top(); q.pop();
        int u = oldX.u;
        if(u == end){
            algorithmAns = oldX.dis;
            LogInfo("A*算法求出了一个解");
            return algorithmAns;     
        }
        for(const Edge *nxt = g.GetFirstEdge(u); nxt != NULL; nxt = g.GetNxtEdge(nxt)){
            int v = nxt->v;
            
            if(vis[v] != -1)    continue; //该搜索路径下,已经访问过该节点,则无需入队
            Node newX = oldX;  //继承访问过的节点,也可视为搜索路径
            newX.u = v; 
            vis[v] = u;
            newX.h = calCost(v,end); 
            newX.dis = nxt->w + oldX.dis;
            q.push(newX);
        }
    }
    LogInfo("该图不存在从起始点到终止点的路径");
    return algorithmAns;
}

double AStar::BFSAlgorithn(int start,int end){
    memset(vis,-1,sizeof(int) * (vertexNum + 10));
    priority_queue<Node> q;
    q.push((Node){start,0,0});
    LogInfo("BFS算法开始");
    while(!q.empty()){
        Node oldX = q.top(); q.pop();
        int u = oldX.u;
        if(u == end){
            BFSAns = oldX.dis;
            LogInfo("BFS算法求出了一个解");
            return BFSAns;     
        }
        for(const Edge *nxt = g.GetFirstEdge(u); nxt != NULL; nxt = g.GetNxtEdge(nxt)){
            int v = nxt->v;
            
            if(vis[v] != -1)    continue; //该搜索路径下,已经访问过该节点,则无需入队
            Node newX = oldX;  //继承访问过的节点,也可视为搜索路径
            newX.u = v; 
            vis[v] = u;
            newX.dis = nxt->w + oldX.dis;
            q.push(newX);
        }
    }
    LogInfo("该图不存在从起始点到终止点的路径");
    return BFSAns; 
}

void AStar::PrintPath(int start,int end){
    printf("\n");
    for(int i = 0; i < obstacleNum; ++i){
        printf("障碍物%02d: 左下角坐标:(%d,%d),右上角坐标:(%d,%d)\n",
            i,  obstacleMessage[i][0].first,obstacleMessage[i][0].second,
                obstacleMessage[i][1].first,obstacleMessage[i][1].second);
    }

    vector<pair<int,int>> path;
    int now = end;
    while(1){
        path.push_back(make_pair(now / sqrtVertexNum,now % sqrtVertexNum));
        if(vis[now] == start){
            now = vis[now];
            path.push_back(make_pair(now / sqrtVertexNum,now % sqrtVertexNum));
            break;
        }
        now = vis[now];
    }
    printf("\n路径为:\n");
    //打印开头
    printf("(%d %d) ->\n",path[path.size()-1].first,path[path.size()-1].second);
    for(int i = path.size() - 2; i >= 1; --i){
        pair<int,int> now,nxt,from;
        now = path[i],nxt = path[i - 1],from = path[i + 1];
        // 相邻点坐标，x轴和y轴都存在不同值
        if((now.first != nxt.first || now.first != from.first) && (now.second != nxt.second || now.second != from.second)){
            printf("(%d %d)",path[i].first,path[i].second);
            printf(" ->\n");
        }
    }
    printf("(%d %d)\n",path[0].first,path[0].second);
}