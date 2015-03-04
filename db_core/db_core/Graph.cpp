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
    //set<int> a;
    int b[MAX_NODE][MAX_NODE];
public:
    Graph(int s = MAX_NODE);//构造函数
    
    int getNodeCount();//当前的节点数
    
    int getEdgeCount();//当前的边数
    
    void insertNode(int);//插入一个节点
    
    void isertEdge(int ,int ,int);//插入一条边
    
    
    void deleteEdge(int,int);//删除一条边
    
    void prim(int);//生成最小树
    
    int DFS(int);//深度优先搜索
    
    void DFS(int node,int v[],int& n);
    
    void BFS(int);//广度优先搜索
    
    bool isliantong();//判断是否连通
    
    void liantongfenliang();//连通分量的数目
    
    int getWeight(int,int);//获得某条边的权值
    
    int getFirstNeighbor(int);//获得所给顶点的第一个相邻节点
    
    int getNextNeighbor(int,int);//获得某一邻接节点的下一个邻接节点
    
    
    
};


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Graph::Graph(int s)//构造函数
{
    for(int i=0;i<=s-1;i++)
        for(int j=0;j<=s-1;j++)
            b[i][j]=0;
    nodecount=0;
    for(int k=0;k<=s-1;k++)
        a[k]=-1;
    
}


int Graph::getNodeCount()//当前的节点数
{
    return nodecount;
}


int Graph::getEdgeCount()//当前的边数
{
    return edgecount;
}

void Graph::insertNode(int it)//插入一个节点
{
    //a[nodecount++]=it;
    //a.insert(it);
    a[it]=it;
    nodecount++;
}

void Graph::isertEdge(int x,int y,int w)//插入一条边
{
    b[x][y]=w;
    b[y][x]=w;
    cout<<"该边插入成功! "<<endl;
    edgecount++;
}


void Graph::deleteEdge(int x ,int y)//删除一条边
{
    b[x][y]=0;
    b[y][x]=0;
    cout<<"边("<<x<<","<<y<<")已经成功删除!";
    edgecount--;
}

void Graph::prim(int x)//生成最小树
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
                        //e[a[j]][a[k]]=1;
                        min=b[l][r];
                        //d[a[k]]
                    }
            }
        d[node]=1;
        e[l][r]=b[l][r];
    }
    //}
    
    for(int ln=0;ln<=9;ln++)
        for(int rn=0;rn<=9;rn++)
            if(e[ln][rn]>0)
                cout<<"("<<ln<<","<<rn<<",权值为"<<e[ln][rn]<<") ,";
    
    
    
    
}

void Graph::BFS(int x)//广度优先搜索
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
    {//cout<<"!!!"<<endl;
        //x=
        x=q.front();
        q.pop();
        
        next=getFirstNeighbor(x);
        //if(a[next]==-1)
        //    continue;
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



bool Graph::isliantong()//判断是否连通
{
    int n=0;
    n=DFS(0);
    cout<<"该图的总节点数为:"<<nodecount<<"!"<<endl;
    cout<<"其中一个连通分量连通的节点数为:"<<n<<"!"<<endl;
    if(n==nodecount)
        return true;
    else return false;
}

void Graph::liantongfenliang()//连通分量的数目
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
            //newliantong();
        }
    delete[] v;
}

int Graph::getWeight(int x,int y)//获得某条边的权值
{
    return b[x][y];
}

int Graph::getFirstNeighbor(int x)//获得所给顶点的第一个相邻节点
{
    int n=-1;
    if(nodecount==0)
        return -1;
    for(int i=0;i<=nodecount-1;i++)
        if(b[x][i]!=0)
        {  n=a[i];
            //cout<<n<<"!!"<<endl;
            break;
        }
    return n;
}

int Graph::getNextNeighbor(int x,int y)//获得某一邻接节点的下一个邻接节点
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


int main(){
    int num;
    cout<<"请输入该图最多的节点数："<<endl;
    cin >> num;
    Graph G(num);
    
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
        G.isertEdge(x,y,w);
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
                cout<<"请输入你要添加的"<<e<<"条边以及边上对应的权值!"<<endl;
                cin>>x>>y>>w;
                G.isertEdge(x,y,w);
                break;
                
            case 0:
                cout<<"谢谢,测试完成!"<<endl;
                return 0;
                
        }
    }
    
}
