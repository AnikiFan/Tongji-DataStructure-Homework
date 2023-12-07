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
	G.Vertices = new Vec[G.VecNum];
	if(!G.Vertices){
		cout<<"OVERFLOW"<<endl;
		getchar();
		return -2;
	}
	for(int i = 0;i<G.VecNum;i++)
	  G.Vertices[i].in = 0;
	int n;
	Arc*p;
	for(int i = 0;i<G.VecNum;i++){
		cin>> G.Vertices[i].w;
		G.Vertices[i].firstArc = NULL;
		cin>>n;
		for(int j = 0;j<n;j++){
			p = new Arc;
			cin>> p->pos;
			G.Vertices[p->pos].in ++;
			p->next = G.Vertices[i].firstArc;
			G.Vertices[i].firstArc = p;
		}
	}
	G.top= -1;
	return OK;
}
Status Topo(Graph&G)
{
	int count = G.VecNum;
	int top =-1;
	int* temp= new int[G.VecNum]{0};
	Arc* p;
	while(count){
		for(int i =0;i<G.VecNum;i++)
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
	int t  = top;
	while(t!=-1){
		cout<<t<<endl;
		t = G.Vertices[t].in;
	}
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
	for(int i = 0;i<G.VecNum;i++)
	  G.Vertices[i].e = 0;
	while(!S.empty()){
		now = S.top();
		S.pop();
		p = G.Vertices[now].firstArc;
		while(!p){
			if(G.Vertices[p->pos].e<G.Vertices[p->pos].w+G.Vertices[now].e)
			  G.Vertices[p->pos].e=G.Vertices[p->pos].w+G.Vertices[now].e;
			p = p->next;
		}
	}
	return OK;
}
Status GetVl(Graph&G)
{
	int top =G.top;
	Arc*p ;
	for(int i = 0;i<G.VecNum;i++)
	  G.Vertices[i].l=G.Vertices[top].e;
	while(top!=-1){
		top = G.Vertices[top].in;
		p = G.Vertices[top].firstArc;
		while(!p){
			if(G.Vertices[p->pos].l-G.Vertices[top].w<G.Vertices[top].l)
			  G.Vertices[top].l=G.Vertices[p->pos].l-G.Vertices[top].w;
			p = p->next;
		}
	}
	return OK;
}
int main()
{
	Graph G;
	InitGraph(G);
	cout<<"end"<<endl;
	Topo(G);
	cout<<"end"<<endl;
	GetVe(G);
	cout<<"end"<<endl;
	GetVl(G);
	cout<<"end"<<endl;
	return 0;
}
