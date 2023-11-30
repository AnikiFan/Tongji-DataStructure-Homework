//由题目中的数据范围可知，较为稀疏，且顶点个数较多，所以选择用邻接表的数据结构
//DFS的时间复杂度为n+e，邻接表的空间复杂度为n+e，BFS的时间复杂度为e 

#include<iostream>
#define OK 1
using namespace std;
typedef int Status;
struct Box{
	int pos;//存储结点在Vertices中的下标
	Box*next;//指向下一个邻接结点的指针域
};
typedef struct{
	Box* firstArc;//为了遍历时方便，所以存储了指向第一条边的指针
	Box* lastArc;//因为使用尾插法，所以存储的是指向结尾
}Vec;
typedef struct{
	int VecN;
	int ArcN;
	Vec* Vertices;
}Graph;
Status InitGraph(Graph&G)
{
	cin>> G.VecN>>G.ArcN;
	G.Vertices = new Vec [G.VecN];
	if(!G.Vertices){
		cout<<"OVERFLOW"<<endl;
		return -2;
	}
	for(int i = 0;i<G.VecN;i++){
		G.Vertices[i].firstArc=NULL;
		G.Vertices[i].lastArc=NULL;
	}
	int a,b;
	Box*p;
	for(int i =0;i<G.ArcN;i++){
		cin>> a>>b;
		p = new Box;
		if(!p){
			cout<<"OVERFLOW"<<endl;
			return -2;
		}
		p->pos = b;
		if(!G.Vertices[i].firstArc){//链表为空
			G.Vertices[i].firstArc=p;
			G.Vertices[i].lastArc=p;
			p->next = NULL;
		}
		else{
			p->next = NULL;
			G.Vertices[i].lastArc->next = p;
			G.Vertices[i].lastArc= p;
		}
	}
	return OK;
}
void DFS(Graph G,int now,int*visit,int first)
{
	if(!first)
	  cout<<" ";
	else
	  cout<<"{";
	cout<<now;
	visit[now]=1;
	Box*p = G.Vertices[now].firstArc;
	while(p){
		if(!visit[p->pos])
		  DFS(G,p->pos,visit,0);
		p=p->next;
	}
	return;
}
void DFS_TRAVERSE(Graph G)
{
	int *visit = new int [G.VecN];
	if(!visit){
		cout<<"OVERFLOW"<<endl;
		return ;
	}
	for(int i = 0;i<G.VecN;i++)
	  if(!visit[i]){
		  DFS(G,i,visit,1);
		  cout<<"}";
	  }
	return ;
}
int main()
{
	Graph G;
	return 0;
}
