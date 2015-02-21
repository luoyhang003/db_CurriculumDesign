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
    //返回顶点度数
    int ReturnDegree(int v);
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


//析构函数
template <class VertexType, class EdgeType>
Graph<VertexType, EdgeType>::~Graph(void)
{
    for (int i = 0; i < NumVertices; i++) {
        Edge<EdgeType> *p = VertexList[i].out;
        while (p!=NULL) {
            VertexList[i].out = p->next;
            delete p;
            p = VertexList[i].out;
        }
    }
    delete [] VertexList;
}


//成员函数ReturnVertexPos()
template <class VertexType, class EdgeType>
int Graph<VertexType, EdgeType>::ReturnVertexPos(const VertexType &vertex)
{
    for(int i = 0; i < NumVertices; i++)
    {
        if (VertexList[i].data == vertex) {
            return i;
        }
    }
    return -1;
}


//成员函数ReturnFirstNeighbor()
template <class VertexType, class EdgeType>
int Graph<VertexType, EdgeType>::ReturnFirstNeighbor(int v)
{
    Edge<EdgeType> *p;
    if (v != -1) {
        p = VertexList[v].out;
        if (p != NULL) {
            return p->jj;
        }
        return -1;
    }
}


//成员函数ReturnNextNeighbor()
template <class VertexType, class EdgeType>
int Graph<VertexType, EdgeType>::ReturnNextNeighbor(int vi, int vj)
{
    if (vi != -1) {
        Edge<EdgeType> *p = VertexList[vi].out;
        while (p != NULL) {
            if (p->jj == vj && p->next != NULL) {
                return p->next->jj;
            }
            else
                p = p->next;
        }
    }
    return -1;
}


//成员函数ReturnEdgeInfo()
template <class VertexType, class EdgeType>
EdgeType Graph<VertexType, EdgeType>::ReturnEdgeInfo(int vi, int vj)
{
    vi = ReturnVertexPos(vi);
    vj = ReturnVertexPos(vj);
    if (vi != -1 && vj != -1) {
        Edge<EdgeType> *p = VertexList[vi].out;
        while (p != NULL) {
            if (p->jj == vj) {
                return p->edgeInfo;
            }
            else
                p = p->next;
        }
    }
    return 0;
}


//成员函数InsertVertex()
template <class VertexType, class EdgeType>
void Graph<VertexType,EdgeType>::InsertVertex(const VertexType &vertex)
{
    int i = ReturnVertexPos(vertex);
    if (i > 0 && i < NumVertices) {
        cerr << "表中已有该节点" << endl;
        return;
    }
    VertexList[NumVertices].data = vertex;
    VertexList[NumVertices].out = NULL;
    NumVertices++;
}


//成员函数DeleteVertex()
//假设与该顶点关联的边都已经删除
template <class VertexType, class EdgeType>
void Graph<VertexType, EdgeType>::DeleteVertex(int v)
{
    if (v < 0 || v > NumVertices - 1) {
        cerr<<"非法删除"<<endl;
        return;
    }
    for (int i = v; i < NumVertices - 1; i++) {
        VertexList[i] = VertexList[i+1];
    }
    NumVertices--;
}


//成员函数InsertEdge()
template <class VertexType, class EdgeType>
void Graph<VertexType, EdgeType>::InsertEdge(int vi, int vj, EdgeType edgeInfo)
{
    Edge<EdgeType> *p = VertexList[vi].out;
    Edge<EdgeType> *NewEdge = NULL;
    NewEdge = new Edge<EdgeType>(vj, edgeInfo);
    if (p == NULL) {
        VertexList[vi].out = NewEdge;
        NumEdges++;
        return;
    }
    while (p->jj != vj && p->next != NULL) {
        p = p->next;
    }
    if (p->jj == vj) {
        cerr<<"非法插入"<<endl;
        return;
    }
    if (p->next == NULL) {
        p->next = NewEdge;
        NumEdges++;
    }
}


//成员函数DeleteEdge
template <class VertexType, class EdgeType>
void Graph<VertexType, EdgeType>::DeleteEdge(int vi, int vj)
{
    Edge<EdgeType> *r;
    Edge<EdgeType> *p = VertexList[vi].out;
    if (p == NULL) {
        cerr<<"非法删除"<<endl;
        return;
    }
    if (p->jj == vj) {
        VertexList[vi].out = p->next;
        NumEdges--;
        return;
    }
    r = p;
    p = p->next;
    if (p == NULL) {
        cerr<<"非法删除"<<endl;
        return;
    }
    while (p->jj != vj && p->next != NULL) {
        r = p;
        p = p->next;
    }
    if (p->jj == vj) {
        r->next = p->next;
        delete p;
        NumEdges--;
        return;
    }
    cerr<<"非法删除"<<endl;
}


//成员函数ReturnDegree
template <class VertexType, class EdgeType>
int Graph<VertexType, EdgeType>::ReturnDegree(int v)
{
    int vi = ReturnVertexPos(v);
    int count = 0;
    if (vi != -1) {
        Edge<EdgeType> *p = VertexList[vi].out;
        cout<<"YES";

        while (p != NULL) {
            count++;
            cout<<"YES";
            p = p->next;
        }
    }
    return count;
}

template <class VertexType, class EdgeType>
class Digraph:Graph<VertexType, EdgeType>
{

};



template <class VertexType, class EdgeType>
class WeightedGraph:Graph<VertexType, EdgeType>
{

};



template <class VertexType, class EdgeType>
class WeightedDigraph:Graph<VertexType, EdgeType>
{
    
};


//














int main() {
    // insert code here...
    cout << "Hello, World!\n";
    Graph<char, int> g;
//    g.InsertVertex('a');
//    g.InsertVertex('b');
//    g.InsertVertex('c');
//    g.InsertVertex('d');
//    g.InsertVertex('e');

    cout<<g.IsEmpty()<<endl;
    cout<<g.ReturnDegree('a')<<endl;
    return 0;
}


//5
//a b c d e
//5
//a b 1
//a d 1
//a e 1
//c d 1
//c e 1
