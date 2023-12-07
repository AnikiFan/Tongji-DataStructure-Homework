#include<iostream>
#include<stack>
#define OK 1
using namespace std;
typedef int Status;
typedef struct Arc{
	int e;
	int l;
	int pos;
	Arc*next;
}Arc;
typedef struct{
	Arc*firstArc;
	int e;
	int l;
	int w;
	int in;
}Vec;
typedef struct{
	Vec*Vertices;
	int VecNum;
	int ArcNum;
	int top;
}Graph;
Status InitGraph(Graph&G)
{
	cin >> G.VecNum;
	G.ArcNum = 0;
	G.Vertices = new Vec[G.VecNum+1];
	if(!G.Vertices){
		cout<<"OVERFLOW"<<endl;
		getchar();
		return -2;
	}
	for(int i = 0;i<G.VecNum+1;i++)
	  G.Vertices[i].in = 0;
	int n;
	Arc*p;
	for(int i = 1;i<G.VecNum+1;i++){
		cin>> G.Vertices[i].w;
		G.Vertices[i].firstArc = NULL;
		cin>>G.Vertices[i].in;
		int from;
		for(int j = 0;j<G.Vertices[i].in;j++){
			p = new Arc;
			p->pos = i;
			cin>>from;
			p->next = G.Vertices[from].firstArc;
			G.Vertices[from].firstArc = p;
		}
	}
	G.top= -1;
	return OK;
}
Status Topo(Graph&G)
{
	int count = G.VecNum;
	int top =-1;
	int* temp= new int[G.VecNum+1]{0};
	Arc* p;
	while(count){
		for(int i =1;i<G.VecNum+1;i++)
			if(!G.Vertices[i].in&&!temp[i]){
			  G.Vertices[i].in = top;
			  temp[i]=1;
			  top = i;
			  p = G.Vertices[i].firstArc;
			  while(p){
				  G.Vertices[p->pos].in--;
				  p = p->next;
			  }
			  break;
			}
		count--;
	}
	G.top = top;
	return OK;
}
Status GetVe(Graph&G)
{
	int top = G.top;
	int now;
	Arc*p;
	stack<int> S;
	while(top!=-1){
		S.push(top);
		top = G.Vertices[top].in;
	}
	for(int i = 1;i<=G.VecNum;i++)
	  G.Vertices[i].e = G.Vertices[S.top()].w;
	while(!S.empty()){
		now = S.top();
		S.pop();
		p = G.Vertices[now].firstArc;
		while(p){
			if(G.Vertices[p->pos].e<G.Vertices[now].w+G.Vertices[now].e)
			  G.Vertices[p->pos].e=G.Vertices[now].w+G.Vertices[now].e;
			p = p->next;
		}
	}
	for(int i = 1;i<=G.VecNum;i++)
	  cout<<G.Vertices[i].e<<endl;
	cout<<"**"<<endl;
	return OK;
}
Status GetVl(Graph&G)
{
	int top =G.top;
	Arc*p ;
	for(int i = 1;i<=G.VecNum;i++)
	  G.Vertices[i].l=G.Vertices[top].e;
	while(top!=-1){
		p = G.Vertices[top].firstArc;
		while(p){
			if(G.Vertices[p->pos].l-G.Vertices[top].w<G.Vertices[top].l)
			  G.Vertices[top].l=G.Vertices[p->pos].l-G.Vertices[top].w;
			p = p->next;
		}
		top = G.Vertices[top].in;
	}
	return OK;
}
int main()
{
	Graph G;
	InitGraph(G);
	Topo(G);
	GetVe(G);
	GetVl(G);
	cout<<"end"<<endl;
	return 0;
}
