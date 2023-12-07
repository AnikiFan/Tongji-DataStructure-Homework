#include<iostream>
#include<map>
#define OK 1
#define Infinity 10000
using namespace std;
typedef int Status;
typedef struct{
	int weight;
	int lchild,rchild,parent;
	char info;
}root;
typedef struct{
	root* Nodes;
	int leafnum,nodenum;
	string * code;
}Tree;
int Search(root* Nodes,int* visit,int n)
{
	int min = Infinity;
	int minn = -1;
	for(int i = 0;i<n;i++)
		if((!visit[i])&&(Nodes[i].weight<min)&&Nodes[i].weight){
			minn = i;
			min = Nodes[i].weight;
		}
	visit[minn]=1;
	return minn;
}
Status InitTree(Tree&T)
{
	string text;
	map<char,int> bin;
	cin>>text;
	int i =0;
	while(i<text.length()){
		if(bin.count(text[i])==0)
		  bin[text[i]]=1;
		else
		  bin[text[i]]++;
		i++;
	}
	T.leafnum = bin.size();
	T.nodenum = T.leafnum*2-1;
	T.Nodes = new root[T.nodenum];
	if(!T.Nodes){
		cout<<"OVERFLOW"<<endl;
		getchar();
		return -2;
	}
	for(int i =0;i<T.nodenum;i++)
	  T.Nodes[i].weight = 0;
	map<char,int>::iterator IT = bin.begin();
	for(int i = 0;i<T.leafnum;i++){
		T.Nodes[i].weight = (int)(100*(*IT).second/text.length());
		T.Nodes[i].info = (*IT).first;
		T.Nodes[i].lchild =-1;
		T.Nodes[i].rchild =-1;
		cout<<"["<<i<<"]:"<<T.Nodes[i].info<<endl;
		IT++;
	}
	i =T.leafnum;
	int *visit = new int[T.nodenum]{0};
	int a,b;
	while(i<T.nodenum){
		a = Search(T.Nodes,visit,T.nodenum);
		b = Search(T.Nodes,visit,T.nodenum);
		T.Nodes[i].lchild = a;
		T.Nodes[i].rchild = b;
		T.Nodes[i].weight = T.Nodes[a].weight + T.Nodes[b].weight;
		T.Nodes[a].parent = i;
		T.Nodes[b].parent = i;
		cout<<"a="<<a<<" b="<<b<<" parent="<<i<<endl;
		i++;
	}
	T.Nodes[T.nodenum-1].parent = -1;
	return OK;
}
void GetCode(Tree &T)
{
	int  now,pre;
	T.code = new string[T.leafnum];
	for(int i = 0;i<T.leafnum;i++){
		now = i;
		while(T.Nodes[now].parent!=-1){
			pre = now;	
			now = T.Nodes[now].parent;
			if(T.Nodes[now].lchild==pre)
			  T.code[i].push_back('0');
			else
			  T.code[i].push_back('1');
		}
	}
	for(int i = 0;i<T.leafnum;i++)
	  reverse(T.code[i].begin(),T.code[i].end());
	return ;
}
void Traverse(Tree T,int now)
{
	if(now ==-1)
	  return ;
	cout<<"pos: "<<now<<" weight: "<<T.Nodes[now].weight<<" parent: "<<T.Nodes[now].parent;
	if(T.Nodes[now].lchild ==-1&&T.Nodes[now].rchild ==-1)
	  cout<<" info:"<<T.Nodes[now].info<<endl;
	else
	  cout<<endl;
	Traverse(T,T.Nodes[now].rchild);
	Traverse(T,T.Nodes[now].lchild);
	return;
}
void ShowCode(Tree T)
{
	for(int i = 0;i<T.leafnum;i++)
		cout<<"info:"<< T.Nodes[i].info<<" Code:"<<T.code[i]<<endl;
	int sum = 0;
	for(int i = 0;i<T.leafnum;i++)
	  sum+=T.code[i].length();
	cout<<"ratio:"<<(double)sum/(T.leafnum*8)<<endl;

	return ;
}
int main()
{
	cout<<"=======TEST BEGIN======="<<endl;
	Tree T;
	InitTree(T);
	cout<<"Traverse"<<endl;
	Traverse(T,T.nodenum-1);
	GetCode(T);
	ShowCode(T);
	cout<<"=======TEST E N D======="<<endl;
	return 0;
}
