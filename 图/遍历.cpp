//由题目中的数据范围可知，较为稀疏，且顶点个数较多，所以选择用邻接表的数据结构
//DFS的时间复杂度为n+e，邻接表的空间复杂度为n+e，BFS的时间复杂度为e 
//调试时的错误在于visit数组没有初始化
//易错点在于，由于有重边，BFS时，在添加进队列时，visit就要置1
#include<iostream>
#include<queue>
#define OK 1
using namespace std;
typedef int Status;
struct Box{//边结点
	int pos;//存储结点在Vertices中的下标
	Box*next;//指向下一个邻接结点的指针域
};
typedef struct{
	Box* firstArc;//为了遍历时方便，所以存储了指向第一条边的指针
	Box* lastArc;//因为使用尾插法，所以存储指向末尾的指针
}Vec;//结点
typedef struct{
	int VecN;//结点数
	int ArcN;//边数
	Vec* Vertices;//结点数组
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
		if(!G.Vertices[a].firstArc){//链表为空
			G.Vertices[a].firstArc=p;
			G.Vertices[a].lastArc=p;
			p->next = NULL;
		}
		else{
			p->next = NULL;
			G.Vertices[a].lastArc->next = p;
			G.Vertices[a].lastArc= p;
		}
		p = new Box;
		if(!p){
			cout<<"OVERFLOW"<<endl;
			return -2;
		}
		p->pos = a;
		if(!G.Vertices[b].firstArc){//链表为空
			G.Vertices[b].firstArc=p;
			G.Vertices[b].lastArc=p;
			p->next = NULL;
		}
		else{
			p->next = NULL;
			G.Vertices[b].lastArc->next = p;
			G.Vertices[b].lastArc= p;
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
	int *visit = new int [G.VecN]{0};
	if(!visit){
		cout<<"OVERFLOW"<<endl;
		return ;
	}
	for(int i = 0;i<G.VecN;i++)
	  if(!visit[i]){
		  DFS(G,i,visit,1);
		  cout<<"}";
	  }
	cout<<endl;
	return ;
}
void BFS(Graph G,int first,int*visit)
{
	std::queue<int>Q;
	cout<<"{";
	Q.push(first);
	int now;
	int beg=1;
	Box*p;
	while(!Q.empty()){
		now = Q.front();
		Q.pop();
		if(beg){
			beg=0;
			cout<<now;
		}
		else{
			cout<<" ";
			cout<<now;
		}
		visit[now]=1;
		p = G.Vertices[now].firstArc;
		while(p){
			if(!visit[p->pos]){
				visit[p->pos]=1;
				Q.push(p->pos);
			}
			p = p->next;
		}
	}
	cout<<"}";
	return ;
}
void BFS_TRAVERSE(Graph G)
{
	int *visit = new int [G.VecN]{0};
	if(!visit){
		cout<<"OVERFLOW"<<endl;
		return ;
	}
	for(int i = 0;i<G.VecN;i++)
	  if(!visit[i])
		  BFS(G,i,visit);
	cout<<endl;
	return ;
}
int main()
{
	Graph G;
	InitGraph(G);
	DFS_TRAVERSE(G);
	BFS_TRAVERSE(G);
	return 0;
}
