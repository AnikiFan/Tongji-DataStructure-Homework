//无权无向图
#include<iostream>
#include<queue>
#define MAXR 100
#define MAXC 100
#define OK 1
#define OverFlow {cout<<endl<<endl<<"OVERFLOW"<<endl<<endl; return -2;}
using namespace std;
typedef int Status;
typedef int AdjMatrix[MAXR][MAXC] ;
typedef char ElemType;
typedef struct {
	ElemType * Vertices;	
	AdjMatrix Mat;
	int ArcN;
	int VerN;
}Graph;
int FindVertex(Graph G,ElemType Target)
{
	for(int i = 0;i<G.VerN;i++)
	  if(G.Vertices[i]==Target)
		return i;
	return -1;
}
Status InitGraph(Graph &G)
{
	cout<<"please first input VerN, and then ArcN"<<endl;
	cin >> G.VerN;
	if(G.VerN>MAXR||G.VerN>MAXC){
		cout<<"OVERSIZE"<<endl;
		return -1;
	}
	int count = 0;
	G.Vertices = new ElemType [G.VerN];
	if(!G.Vertices)
	  OverFlow;
	for(int i = 0;i<G.VerN;i++)
	  cin>> G.Vertices[i];
	cin>> G.ArcN;
	if(G.ArcN>(G.VerN*(G.VerN-1)/2)||G.ArcN<0){
		cout<<"INVALID SIZE"<<endl;
		return -1;
	}
	for(int i = 0;i<G.ArcN;i++){
		ElemType head,tail;
		cin>>head;
		cin >> tail;
		int head_pos,tail_pos;
		head_pos= FindVertex(G,head);
		tail_pos=FindVertex(G,tail);
		if(head_pos==-1||tail_pos==-1){
			cout<<"Can't find it"<<endl;
			return -1;
		}
		if(G.Mat[head_pos][tail_pos]==1){
			cout<<"repeat!"<<endl;
			G.ArcN--;
		}
		G.Mat[head_pos][tail_pos]=1;
		G.Mat[tail_pos][head_pos]=1;
	}
	return OK;
}
void DFS(Graph G,int now,int *visit)
{
	cout<<G.Vertices[now];
	visit[now]=1;
	for(int i= 0;i<G.VerN;i++)
	  if(G.Mat[now][i]&&!visit[i])
		DFS(G,i,visit);
	return;
}
void DFS_TRAVERSE(Graph G,int first)
{
	if(first<0||first>=G.VerN){
		cout<<"INVALID FIRST"<<endl;
		return ;
	}
	int* visit = new int [G.VerN]{0};
	if(!visit){
		cout<<"OVERFLOW"<<endl;
		return;
	}
	cout<<"DFS TRAVERSE"<<endl;
	DFS(G,first,visit);
	cout<<endl;
	return;
}
void BFS_TRAVERSE(Graph G,int first)
{
	if(first<0||first>=G.VerN){
		cout<<"INVALID FIRST"<<endl;
		return ;
	}
	int* visit = new int [G.VerN]{0};
	if(!visit){
		cout<<"OVERFLOW"<<endl;
		return;
	}
	cout<<"BFS TRAVERSE"<<endl;
	std::queue<int> Q;
	int now=first;
	visit[now]=1;
	Q.push(first);
	while(!Q.empty()){
		now = Q.front();
		cout<<G.Vertices[now];
		Q.pop();
		for(int i = 0;i<G.VerN;i++)
			if(G.Mat[now][i]&&!visit[i]){
				Q.push(i);
				visit[i]=1;
			}
	}
	cout<<endl;
	return;
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
