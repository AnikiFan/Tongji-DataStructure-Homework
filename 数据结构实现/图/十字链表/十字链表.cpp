#include<iostream>
#define OK 1
using namespace std;
typedef char VertexType;
typedef int Status;
typedef struct ArcBox{
	int headvex,tailvex;
	struct ArcBox *hlink,*tlink;
	int info;
}ArcBox;
typedef struct VexNode{
	VertexType data;
	ArcBox *firstin,*firstout;
}VexNode;
typedef struct{
	VexNode * xlist;
	int vexnum,arcnum;
}OLGraph;
Status InitGraph(OLGraph &G)
{
	cin>>G.vexnum>>G.arcnum;
	G.xlist = new VexNode[G.vexnum];
	if(!G.xlist){
		cout<<"OVERFLOW"<<endl;
		getchar();
		return -2;
	}
	for(int i = 0;i<G.vexnum;i++){
		G.xlist[i].firstin =NULL;
		G.xlist[i].firstout =NULL;
		cin >> G.xlist[i].data;
	}
	int from,to;
	ArcBox*p = NULL;
	for(int i = 0;i<G.arcnum;i++){
		cin>>from>>to;
		if(!G.xlist[from].firstout){
			G.xlist[from].firstout=new ArcBox;
			if(!G.xlist[from].firstout){
				cout<<"OVERFLOW"<<endl;
				getchar();
				return -2;
			}
			G.xlist[from].firstout->tailvex = from;
			G.xlist[from].firstout->tlink = NULL;
			p = G.xlist[from].firstout;
		}
		else{
			p = G.xlist[from].firstout;
			while(p->tlink)
			  p = p->tlink;
			p->tlink= new ArcBox;
			if(!p->tlink){
				cout<<"OVERFLOW"<<endl;
				getchar();
				return -2;
			}
			p = p->tlink;
			p->tailvex = from;
			p->tlink = NULL;
		}
		p ->headvex = to;
		if(!G.xlist[to].firstin){
			G.xlist[to].firstin = p;
			p->hlink = NULL;
		}
		else{
			ArcBox*temp = G.xlist[to].firstin;
			while(temp->hlink)
			  temp = temp->hlink;
			temp ->hlink = p;
			p->hlink =NULL;
		}
	}
	return OK;
}
int main()
{
	cout<<"=======TEST BEGIN======="<<endl;
	OLGraph G;
	InitGraph (G);
	cout<<"=======TEST E N D======="<<endl;
	return 0;
}
