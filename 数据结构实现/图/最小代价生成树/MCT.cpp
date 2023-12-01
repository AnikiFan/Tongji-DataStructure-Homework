//邻接矩阵实现有权无向图
#include<iostream>
#define OK 1
#define INFINITY 10000
#define MAXN 100
using namespace std;
typedef struct{
	int Mat[MAXN][MAXN];
	int VecN;
	int ArcN;
}Graph;
typedef int Status;
typedef struct{
	int pos;
	int weight;
}NearVec;
Status Init_Graph(Graph&G)
{
	cout<<"please type VecN and ArcN"<<endl;
	cin>> G.VecN>>G.ArcN;
	for(int i = 0;i<G.VecN*G.VecN;i++)
	  G.Mat[i]= INFINITY;
	int a,b;
	for(int i = 0;i<G.ArcN;i++){
		cin>>a>>b;
		G.Mat[a][b]=1;
		G.Mat[b][a]=1;
	}
	return OK;
}
void print_tree(NearVec* NearVertices,int n )
{
	for(int i= 0;i<n;i++)
	  if(NearVertices[i].pos!=-1)
		cout<<"("<<i<<","<< NearVertices[i].pos<<"):"<<NearVertices.weight<<endl;
	return;
}
void Prim(Graph G,int first)
{
	NearVec* NearVertices = new NearVec[G.VecN];
	if(!NearVertices){
		cout<<"OVERFLOW"<<endl;
		return ;
	}
	int temp_w=INFINITY;
	int to_add = first;
	for(int i = 0;i<G.VecN;i++)
	  NearVertices[i].pos = -1;
	while(1){
		NearVertices[to_add].weight = INFINITY;
		for(int i =0;i<G.VecN;i++)
		  if((G.Mat[to_add][i]!=INFINITY)&&(NearVertices[i].weight!=INFINITY)&&(G.Mat[to_add][i]<NearVertices[i].weight)
					  ||(NearVertices[i].weight==INFINITY&&G.Mat[to_add][i]!=INFINITY)){
			  NearVertices[i].pos = to_add;
			  NearVertices[i].weight= G.Mat[to_add][i];
		  }
		for(int i = 0;i<G.VecN;i++)
		  if(NearVertices[i].weight<temp_w){
			temp_w=NearVertices[i].weight;
			to_add= i;
		  }
		if(temp_w==INFINITY)
		  break;
	}
	return;
}
int main()
{
	cout<<"=======TEST BEGIN======="<<endl;
	Graph G;
	Init_Graph(G);
	cout<<"=======TEST E N D======="<<endl;
	return 0;
}
