#include <bits/stdc++.h>
using namespace std;

const int maxn = 500 + 10;
struct Grap{
    int head[maxn],tot;
    struct edge{
        int from,to;
        double w;
    }e[maxn << 1];
    inline void add(int u,int v,double w){
        e[++tot].from = u;
        e[tot].to = v;  e[tot].w = w;
    } 
    inline void dbadd(int u,int v,double w){
        add(u,v,w); add(v,u,w);
    }
}grap;


struct Dijkstra{
    struct Node{
        int u;
        double dis;
        friend bool operator < (Node a,Node b){
            return a.dis> b.dis;
        }
    };

    double dis[maxn],vis[maxn];
    void disInit(){
        for(int i = 0; i < sizeof(dis) / sizeof(dis[0]); ++i){
            dis[i] = 1e9;
        }
    }
    void dijkstra(int s){
        disInit();
        dis[s] = 0;
        priority_queue<Node> q;
        q.push((Node){s,0});
        while(!q.empty()){
            int u = q.top().u; q.pop();
            vis[u] = 0;
            for(int v,nxt = grap.head[u]; nxt; nxt = grap.e[nxt].from){
                v = grap.e[nxt].to;
                if(dis[v] > grap.e[nxt].w + dis[u]){
                    dis[v] = g.e[nxt].w + dis[u];
                    if(!vis[v]){
                        vis[v] = 1;
                        q.push((Node){v,dis[v]});
                    }
                }
            }
        }
    }
}getDis;



int main(){
    
    return 0;
}