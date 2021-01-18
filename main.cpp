#include <bits/stdc++.h>
#include "pso.h"


using namespace std;    

const int maxn = 200 + 10;          //点数
const int maxm = 200 * 200 + 10;    //边数

struct Grap{
    int head[maxn],tot;
    struct edge{
        int from,to;
        double w;
    }e[maxm];
    inline void add(int u,int v,double w){
        e[++tot].from = head[u];
        e[tot].to = v;  e[tot].w = w;
        head[u] = tot;
    } 
    inline void dbadd(int u,int v,double w){
        add(u,v,w); add(v,u,w);
    }
}grap;

struct Node{
    double x,y;
}dict[maxn];


struct Dijkstra{
    struct Node{
        int u;
        double dis;
        friend bool operator < (Node a,Node b){
            return a.dis > b.dis;
        }
    };
    double dis[maxn];
    int vis[maxn];

    //初始化
    void disInit(){
        for(int i = 0; i < sizeof(dis) / sizeof(dis[0]); ++i){
            dis[i] = 1e9;
        }
    }

    //dijkstra算法
    void dijkstra(int s){
        disInit();
        dis[s] = 0;
        priority_queue<Node> q;
        q.push((Node){s,0});
        while(!q.empty()){
            int u = q.top().u; q.pop();
            if(vis[u])  continue;
            vis[u] = 1;
            for(int v,nxt = grap.head[u]; nxt; nxt = grap.e[nxt].from){
                v = grap.e[nxt].to;
                if(dis[v] > grap.e[nxt].w + dis[u]){
                    dis[v] = grap.e[nxt].w + dis[u];
                    if(!vis[v]){
                        q.push((Node){v,dis[v]});
                    }
                }
            }
        }
    }
}getHx;


struct AStar{
   struct Node{
        int u;  
        double dis,h; //    f = dis + h = g + h
        int vis[maxn]; //此处的vis亦作记录,但记录的是搜索路径上是否访问过
        friend bool operator < (Node a,Node b){
            return a.dis + a.h > b.dis + b.h;
        }
    }; 
    int k = 2;  //k即为k短路
    double ans = -1; 


    //A*算法
    void aStar(int s,int end,double *hx){
        priority_queue<Node> q;
        q.push((Node){s,0,hx[s]});
        while(!q.empty()){
            Node oldX = q.top(); q.pop();
            int u = oldX.u;
            if(u == end){
                if(--k == 0){
                    ans = oldX.dis;
                    return;     
                }
            }
            for(int v,nxt = grap.head[u]; nxt; nxt = grap.e[nxt].from){
                v = grap.e[nxt].to;
                if(oldX.vis[v])    continue; //该搜索路径下,已经访问过该节点,则无需入队
                Node newX = oldX;  //继承访问过的节点,也可视为搜索路径
                newX.u = v; 
                newX.vis[v] = 1;
                newX.h = hx[v]; 
                newX.dis = grap.e[nxt].w + oldX.dis;
                q.push(newX);
            }
        }
        return;
    }
}getAns;

//取得两点间的欧几里得距离
inline double getErDistance(Node a,Node b){
    return  sqrt(pow(a.x - b.x,2) + pow(a.y - b.y,2));
}


int main(){
    int n,m;
    cin >> n >> m;
    for(int i = 1; i <= n; ++i){
        cin >> dict[i].x >> dict[i].y;
    }
    for(int i = 1; i <= m; ++i){
        int u,v;
        cin >> u >> v;
        grap.dbadd(u,v,getErDistance(dict[u],dict[v]));
    }
    getHx.dijkstra(n);
    
    
    // for(int i = 1; i <= n; ++i){
    //     printf("n-> %d distance: %f\n",i,getHx.dis[i]);
    // 


    getAns.aStar(1,n,getHx.dis);
    if(getAns.ans != -1)    printf("%.2f\n",getAns.ans);
    else                    printf("-1\n");

    return 0;
}