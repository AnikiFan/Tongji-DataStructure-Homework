//为了确定给定顶点到每个顶点的最短距离，应该使用BFS
//由于是稀疏图，采用邻接表实现的无向边

#include<iostream>
#include<iomanip>
#include<queue>
#define OK 1
using namespace std;
typedef int Status;
struct Arc{
	int pos;
	Arc* next;
};
typedef struct{
	Arc* firstArc;	
}Vec;
typedef struct{
	int VecN;
	int ArcN;
	Vec* Vertices;
}Graph;
Status InitGraph(Graph&G)
{
	cin>> G.VecN>>G.ArcN;	
	G.Vertices = new Vec[G.VecN];
	if(!G.Vertices){
		cout<<"OVERFLOW"<<endl;
		return -2;
	}
	for(int i = 0;i<G.VecN;i++)
	  G.Vertices[i].firstArc=NULL;
	int a ,b;
	Arc* p ;
	for(int i = 0;i<G.ArcN;i++){
		cin>>a>>b;
		a--;
		b--;
		p = new Arc;
		if(!p){
			cout<<"OVERFLOW"<<endl;
			return -2;
		}
		p->next = G.Vertices[a].firstArc;
		p->pos = b;
		G.Vertices[a].firstArc= p;
		p = new Arc;
		if(!p){
			cout<<"OVERFLOW"<<endl;
			return -2;
		}
		p->next = G.Vertices[b].firstArc;
		p->pos = a;
		G.Vertices[b].firstArc= p;
	}
	return OK;
}
void BFS(Graph G,int first)
{
	int *visit = new int [G.VecN]{0};
	if(!visit){
		cout<<"OVERFLOW"<<endl;
		return;
	}
	std::queue<int>Q;
	std::queue<int>temp;
	Q.push(first);
	visit[first]=1;
	int count = 1;
	int now;
	Arc*p;
	while(!Q.empty()){
		while(!Q.empty()){
			now = Q.front();
			Q.pop();
			p = G.Vertices[now].firstArc;
			while(p){
				if(!visit[p->pos]){
					visit[p->pos]=count;
					temp.push(p->pos);
				}
				p = p->next;
			}
		}
		while(!temp.empty()){
			Q.push(temp.front());
			temp.pop();
		}
		count++;
		if(count>=7)
		  break;
	}
	double num=0;
	for(int i = 0;i<G.VecN;i++)
	  if(visit[i])
		num+=1;
	cout<<first+1<<": "<<setiosflags(ios::fixed)<<setprecision(2)<<(num/G.VecN)*100 <<"%"<<endl;
	return ;
}
void BFS_TRAVERSE(Graph G)
{
	for(int i = 0;i<G.VecN;i++)
	  BFS(G,i);
	return;
}
int main()
{
	Graph G;
	InitGraph(G);
	BFS_TRAVERSE(G);
	return 0;
}
