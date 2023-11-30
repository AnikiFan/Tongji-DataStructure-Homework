//有向有权正邻接表
#include<iostream>
#include<iomanip>
#include<queue>
using namespace std;
#define OK 1
#define OverFlow {cout<<endl<<endl<<"OVERFLOW"<<endl<<endl;return -2;}
typedef int Status;
typedef char ElemType;
struct Arc{
	int weight;
	int pos;
	Arc *next;
};
typedef struct{
	ElemType data;
	Arc* firstArc;
} Vertex;
typedef struct{
	int VecN;
	int ArcN;
	Vertex* Vertices;
}Graph;
int Search(Graph G,ElemType Target)
{
	for(int i = 0;i<G.VecN;i++)
	  if(G.Vertices[i].data==Target)
		return i;
	return -1;
}
Status InitGraph(Graph&G)
{
	cout<<"please input VecN and ArcN"<<endl;	
	cin>>G.VecN;
	if(G.VecN<0){
		cout<<"INVALID SIZE"<<endl;
		return -1;
	}
	G.Vertices = new Vertex[G.VecN];
	if(!G.Vertices)
	  OverFlow;
	for(int i = 0;i<G.VecN;i++){
		cin>>G.Vertices[i].data;
		G.Vertices[i].firstArc = NULL;
	}
	cin>>G.ArcN;
	if(G.ArcN<0){
		cout<<"INVALID SIZE"<<endl;
		return -1;
	}
	ElemType from ,to;
	int from_pos,to_pos;
	int w;
	for(int i = 0;i<G.ArcN;i++){
		cin>>from>>to>>w;
		from_pos=Search(G,from);
		to_pos=Search(G,to);
		if(from_pos==-1||to_pos==-1){
			cout<<"INVALID ARC"<<endl;
			G.ArcN--;
			continue;
		}
		Arc*temp =new Arc;
		if(!temp)
		  OverFlow;
		temp->weight = w;
		temp->next= G.Vertices[from_pos].firstArc;
		temp->pos = to_pos;
		G.Vertices[from_pos].firstArc = temp;
	}
	return OK;
}
void DFS(Graph G,int now,int *visit)
{
	cout<<G.Vertices[now].data;
	visit[now]=1;
	Arc*p = G.Vertices[now].firstArc;
	while(p){
		if(!visit[p->pos]){
			cout<<"--"<<p->weight<<"-->";
			DFS(G,p->pos,visit);
		}
		p = p->next;
	}
	return ;
}
void DFS_TRAVERSE(Graph G,int first)
{
	cout<<"BEGIN DFS TRAVERSE"<<endl;
	int *visit= new int [G.VecN]{0};
	if(!visit){
		cout<<"OVERFLOW"<<endl;
		return;
	}
	DFS(G,first,visit);
	cout<<endl;
	return ;
}
void BFS_TRAVERSE(Graph G,int first)
{
	cout<<"BEGIN BFS TRAVERSE"<<endl;
	int *visit= new int [G.VecN]{0};
	if(!visit){
		cout<<"OVERFLOW"<<endl;
		return;
	}
	std::queue<int>Q;
	std::queue<int>W;
	Q.push(first);
	W.push(0);
	int now;
	int w;
	Arc*p;
	while(!Q.empty()){
		now = Q.front();
		w=W.front();
		Q.pop();
		W.pop();
		visit[now]=1;
		if(w)
		  cout<<"--"<<w<<"-->";
		cout<<G.Vertices[now].data;
		p = G.Vertices[now].firstArc;
		while(p){
			if(!visit[p->pos]){
				Q.push(p->pos);
				W.push(p->weight);
			}
			p=p->next;
		}
	}
	cout<<endl;
	return ;
}
int main()
{
	cout<<"=======TEST BEGIN======="<<endl;
	Graph G;
	InitGraph(G);
	DFS_TRAVERSE(G,0);
	BFS_TRAVERSE(G,0);
	cout<<"=======TEST E N D======="<<endl;
	return 0;
}
