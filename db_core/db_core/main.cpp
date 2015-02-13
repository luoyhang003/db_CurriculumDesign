//
//  main.cpp
//  db_core
//
//  Created by jason on 15/2/12.
//  Copyright (c) 2015年 jason. All rights reserved.
//

#include <iostream>
using namespace std;

const int DEFAULT_VERTEX_NUMBER = 20;//图的默认定点数

//声明边表类
template<class EdgeType>
class Edge
{
public:
    int jj; //边的另一顶点
    EdgeType edgeInfo;  //边表节点对象
    Edge<EdgeType> *next;   //指向下一条边的指针
    Edge(void){}    //空的构造函数
    Edge(int i, EdgeType A):jj(i), edgeInfo(A), next(NULL){}    //带参数的构造函数
    int operator != (const Edge &B) const{return jj!=B.jj;} //操作符重载
};


//声明顶点表类
template <class VertexType, class EdgeType>
class Vertex {
public:
    VertexType data;    //顶点序号
    Edge<EdgeType> *out;    //顶点连接的边
    Vertex(){out = NULL;}   //构造函数
    void operator = (Vertex &a){data = a.data; out = a.out;}    //运算符重载
};


//声明邻接链表表示的图类
template <class VertexType, class EdgeType>
class Graph
{
private:
    //顶点表
    Vertex<VertexType,EdgeType> *VertexList;
    //顶点个数
    int NumVertices;
    //最大顶点个数
    int MaxNumVertices;
    //边的个数
    int NumEdges;
    //获取顶点在表中的位置
    int ReturnVertexPos(const VertexType &vertex);
public:
    //构造函数
    Graph(int size=DEFAULT_VERTEX_NUMBER);
    //析构函数
    ~Graph(void);
    //判断图是否为空
    bool IsEmpty(void) const{return NumVertices==0;}
    //判断图的存储是否溢出
    bool isFull(void) const{return NumVertices==MaxNumVertices;}
    //返回顶点个数
    int NumOfVertices(void){return NumVertices;}
    //返回边的个数
    int NumOfEdges(void){return NumEdges;}
    //返回顶点的值
    VertexType ReturnValue(int i)
    {
        return (i>=0&&i<NumVertices)?VertexList[i]:NULL;
    }
    //添加顶点
    void InsertVertex(const VertexType& vertex);
    //删除顶点
    void DeleteVertex(int v);
    //添加边
    void InsertEdge(int vi, int vj, EdgeType edgeInfo);
    //删除边
    void DeleteEdge(int vi, int vj);
    //返回图中的边
    EdgeType ReturnEdgeInfo(int vi, int vj);
    //返回与某顶点相关联的第一条边的另一个顶点序号
    int ReturnFirstNeighbor(int v);
    //返回与某边相关联的下一条边的另一个顶点序号
    int ReturnNextNeighbor(int vi, int vj);
};


//构造函数Graph()
template <class VertexType, class EdgeType>
Graph<VertexType, EdgeType>::Graph(int size):
NumVertices(0),MaxNumVertices(size),NumEdges(0)
{
    int n,e,k,j;    //n表示定点数，e表示边数
    VertexType newVertex,first,second;
    EdgeType Edgeinfo;
    //为顶点表申请空间
    VertexList = new Vertex<VertexType,EdgeType>[MaxNumVertices];
    cout << "请输入顶点数：" << endl;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> newVertex;
        InsertVertex(newVertex);
    }
    cout << "请输入边数：" << endl;
    cin >> e;
    for (int i=0; i < e; i++) {
        cin >> first >> second >> Edgeinfo;
        k = ReturnVertexPos(first);
        j = ReturnVertexPos(second);
        InsertEdge(k, j, Edgeinfo);
    }
}












int main(int argc, const char * argv[]) {
    // insert code here...
    cout << "Hello, World!\n";
    
    return 0;
}





