//
//  Graph.cpp
//  db_core
//
//  Created by jason on 15/3/4.
//  Copyright (c) 2015年 jason. All rights reserved.
//

#include <iostream>
#include<set>
#include <queue>
#include <stack>

using namespace std;

//定义图中的最大边数
#define MAX_EDGES 40
//定义图中最大节点数
#define MAX_NODE 30

#define Max 100000


//构建图类
class Graph
{
private:
    int nodecount;  //顶点数
    
    int edgecount;  //边数
    
    int a[MAX_NODE];    //表示定点的数组

    int b[MAX_NODE][MAX_NODE];  //存储图的矩阵


public:
    Graph(int s = MAX_NODE);    //构造函数
    
    int getNodeCount(); //当前的节点数
    
    int getEdgeCount(); //当前的边数
    
    void insertNode(int);   //插入一个节点
    
    void insertEdge(int ,int ,int);  //插入一条边
    
    
    void deleteEdge(int,int);   //删除一条边
    
    void prim(int); //生成最小树
    
    int DFS(int);   //深度优先搜索
    
    void DFS(int node,int v[],int& n);
    
    void BFS(int);  //广度优先搜索
    
    bool isliantong();  //判断是否连通
    
    void liantongfenliang();    //连通分量的数目
    
    int getWeight(int,int); //获得某条边的权值
    
    int getFirstNeighbor(int);  //获得所给顶点的第一个相邻节点
    
    int getNextNeighbor(int,int);   //获得某一邻接节点的下一个邻接节点
    
    
    
};


//构造函数
Graph::Graph(int s)
{//参数s表示图的最大节点
    //将图初始化，图为空
    for(int i=0;i<=s-1;i++)
        for(int j=0;j<=s-1;j++)
            b[i][j]=0;
    nodecount=0;
    for(int k=0;k<=s-1;k++)
        a[k]=-1;    //-1表示无顶点
    
}



//获取当前的顶点数
int Graph::getNodeCount()
{
    return nodecount;   //返回节点数
}


//获取当前的边数
int Graph::getEdgeCount()
{
    return edgecount;   //返回边数
}


//插入一个顶点
void Graph::insertNode(int v)
{
    a[v]=v; //为顶点赋值
    nodecount++;    //顶点数+1
}


//插入一条边
void Graph::insertEdge(int x,int y,int w)
{
    b[x][y]=w;
    b[y][x]=w;
    cout<<"该边插入成功! "<<endl;
    edgecount++;
}


//删除一条边
void Graph::deleteEdge(int x ,int y)
{
    b[x][y]=0;
    b[y][x]=0;
    cout<<"边("<<x<<","<<y<<")已经成功删除!";
    edgecount--;    //边数-1
}


//prim求生成最小树
void Graph::prim(int x)
{
    int* d=new int[getNodeCount()];
    for(int id=0;id<=getNodeCount()-1;id++)
        d[id]=0;
    int e[10][10];
    for(int im=0;im<=9;im++)
        for(int rm=0;rm<=9;rm++)
            e[im][rm]=0;
    int min;
    int node;
    int l,r;
    
    d[x]=1;
    for(int i=1;i<=nodecount-1;i++)
    {
        min=Max;
        for(int j=0;j<=nodecount-1;j++)
            if(d[j]==1&&a[j]==j)
            {
                for(int k=0;k<=nodecount-1;k++)
                    if(a[k]==k&&d[k]==0&&b[j][k]>0&&b[j][k]<min)
                    {
                        node=k;
                        l=j;
                        r=k;
                        min=b[l][r];
                    }
            }
        d[node]=1;
        e[l][r]=b[l][r];
    }
    
    for(int ln=0;ln<=9;ln++)
        for(int rn=0;rn<=9;rn++)
            if(e[ln][rn]>0)
                cout<<"("<<ln<<","<<rn<<",权值为"<<e[ln][rn]<<") ,";
    
    
}


//广度优先搜索
void Graph::BFS(int x)
{
    int* v=new int[getNodeCount()];
    for(int i=0;i<=getNodeCount()-1;i++)
        v[i]=0;
    cout<<x<<" ";
    v[x]=1;
    queue<int> q;
    q.push(x);
    int next;
    while(!q.empty())
    {
        x=q.front();
        q.pop();
        
        next=getFirstNeighbor(x);
        
        while(next!=-1)
        {  if(!v[next]&&a[next]==next)
        {
            cout<<next<<" ";
            v[next]=1;
            q.push(next);
        }
            next=getNextNeighbor(x,next);
        }
    }
    delete[] v;
}


//深度优先搜索
void Graph::DFS(int node,int v[],int& n)
{
    cout<<node<<" ";
    n++;
    v[node]=1;
    int next=getFirstNeighbor(node);
    while(next!=-1)
    {
        
        if(a[next]==next&&!v[next])
            DFS(next,v,n);
        next=getNextNeighbor(node,next);
    }
}


//递归实现的深度优先搜索
int Graph::DFS(int node)
{
    int n=0;
    int* v=new int[nodecount];
    for(int i=0;i<=nodecount-1;i++)
        v[i]=0;
    DFS(node,v,n);
    delete[] v;
    
    return n;
}


//判断是否连通
bool Graph::isliantong()
{
    int n=0;
    n=DFS(0);
    cout<<"该图的总节点数为:"<<nodecount<<endl;
    cout<<"其中一个连通分量连通的节点数为:"<<n<<endl;
    if(n==nodecount)
        return true;
    else return false;
}


//连通分量的数目
void Graph::liantongfenliang()
{
    int n=0;
    int* v=new int[nodecount];
    for(int i=0;i<=nodecount-1;i++)
        v[i]=0;
    for(int j=0;j<=nodecount-1;j++)
        if(a[j]==j&&!v[j]){
            cout<<"(";
            DFS(j,v,n);
            cout<<") ";
        }
    delete[] v;
}


//获得某条边的权值
int Graph::getWeight(int x,int y)
{
    return b[x][y];
}


//获得所给顶点的第一个相邻节点
int Graph::getFirstNeighbor(int x)
{
    int n=-1;
    if(nodecount==0)
        return -1;
    for(int i=0;i<=nodecount-1;i++)
        if(b[x][i]!=0)
        {  n=a[i];
            break;
        }
    return n;
}


//获得某一邻接节点的下一个邻接节点
int Graph::getNextNeighbor(int x,int y)
{
    if(y==nodecount-1)
        return -1;
    int n=-1;
    for(int i=y+1;i<=nodecount-1;i++)
        if(b[x][i]!=0)
        {
            n=i;
            
            break;
        }
    return n;
}



//测试主函数
int main(){
//    int num;
//    cout<<"请输入该图最多的节点数："<<endl;
//    cin >> num;
    Graph G(30);
    
    cout<<"请输入向图添加几个节点?"<<endl;
    int n;
    cin>>n;
    
    cout<<"请输入你要插入的"<<n<<"个节点!"<<endl;
    int node;
    for(int i=0;i<=n-1;i++)
    {
        cin>>node;
        G.insertNode(node);
    }
    cout<<"你已经向图中成功添加节点!"<<endl;
    
    cout<<"请输入向图中添加几条边"<<endl;
    int e;
    cin>>e;
    
    cout<<"请输入你要添加的"<<e<<"条边以及边上对应的权值!"<<endl;
    cout<<"例如：1 2 10 表示添加顶点1和2之间的边并且权值为10"<<endl;
    int x,y,w;
    for(int j=0;j<=e-1;j++)
    {cin>>x>>y>>w;
        G.insertEdge(x,y,w);
    }
    
    cout<<"你的图已经建立成功!"<<endl;

    
    
    cout<<"***********************"<<endl;
    cout<<"*请选择你要进行的操作:"<<endl;
    cout<<"*1--表示插入新节点!   "<<endl;
    cout<<"*2--表示删除边!       "<<endl;
    cout<<"*3--表示深度优先搜索! "<<endl;
    cout<<"*4--表示广度优先搜索! "<<endl;
    cout<<"*5--表示求最小生成树! "<<endl;
    cout<<"*6--判断图是否连通!   "<<endl;
    cout<<"*7--求图的连通分量!   "<<endl;
    cout<<"*8--插入新的边!       "<<endl;
    cout<<"*0--表示结束操作!     "<<endl;
    cout<<"***********************"<<endl;
    int choice;
    while(true)
    {
        cout<<endl;
        
        cout<<"请你做出选择!"<<endl;
        cin>>choice;
        switch(choice)
        {
                
            case 1:
                cout<<"请输入你要插入的新节点!"<<endl;
                cin>>node;
                //G.deleteNode(node);
                G.insertNode(node);
                cout<<endl;
                break;
                
            case 2:
                cout<<"请输入你要删除的边!"<<endl;
                cin>>x>>y;
                G.deleteEdge(x,y);
                cout<<endl;
                break;
                
            case 3:
                cout<<"请输入你选择的起始节点!"<<endl;
                cin>>node;
                cout<<"深度优先搜索结果为:"<<endl;
                G.DFS(node);
                
                cout<<endl;
                break;
                
            case 4:
                cout<<"请输入你选择的起始节点!"<<endl;
                cin>>node;
                cout<<"广度优先搜索结果为:"<<endl;
                G.BFS(node);
                cout<<endl;
                break;
                
            case 5:
                cout<<"请输入你选择的起始节点!"<<endl;
                cin>>node;
                cout<<"最小生成树为:"<<endl;
                G.prim(node);
                cout<<endl;
                break;
                
            case 6:
                if(G.isliantong())
                    cout<<"该图是连通的!"<<endl;
                else cout<<"该图不是连通的!"<<endl;
                break;
                
            case 7:
                cout<<"图的连通分量为:"<<endl;
                G.liantongfenliang();
                cout<<endl;
                break;
                
            case 8:
                cout<<"请输入你要添加的"<<e<<"条边以及边上对应的权值"<<endl;
                cin>>x>>y>>w;
                G.insertEdge(x,y,w);
                break;
                
            case 0:
                cout<<"已退出"<<endl;
                return 0;
                
        }
    }
    
}
