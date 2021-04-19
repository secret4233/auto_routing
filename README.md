# 自动布线算法

## 用于毕业设计

## 主要模块及其关系
1. 随机图生成 
2. 日志模块(内嵌入各个模块)
3. A*和PSO算法模块 

```mermaid
graph TD
    graphClass[图类] --> randGraph[随机图生成]
    randGraph --> aStar[A*算法]
    randGraph --> pso[PSO算法]
    aStar -- 依赖于 --> Dijkstra
    pso -- 依赖于 --> Kruskal 


```


### log 模块
    <!-- 部分参考 -->
    https://www.cnblogs.com/oftenlin/p/9477947.html

### pso算法
    此处代码实现参考
    https://blog.csdn.net/daaikuaichuan/article/details/81382794
