#include "astar.h"


double AStar::CoreAlgorithm(int star,int end,double (*cal)(int,int)){
    
    priority_queue<Node> q;
    q.push((Node){star,0,cal(star,end)});
    while(!q.empty()){
        Node oldX = q.top(); q.pop();
        int u = oldX.u;
        if(u == end){
            if(--k == 0){
                algorithmAns = oldX.dis;
                return algorithmAns;     
            }
        }
        for(Edge *nxt = GetFirstEdgeNode(u); nxt != NULL; nxt = GetNxtNode(nxt)){
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
    return algorithmAns;
}