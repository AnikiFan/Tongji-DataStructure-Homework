#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string>
#define MAXN 100
#define ERROR 0
#define OK 1
#define OverFlow {printf("\n\nOVERFLOW\n\n");return -2;}
using namespace std;
typedef struct Node{
	char data;
	Node* lchild;
	Node* rchild;
}*Tree,Node;
int Pos(string pre,string in,Tree &T)
{
	T=new Node;
	//printf("%s %s\n",pre.data(),in.data());
	if(pre.length()!=in.length())
	  return ERROR;
	else if(pre.empty()&&in.empty()){
		T= NULL;
	  return OK;
	}
	else{
		int lchild_empty = 0;
		int rchild_empty = 0;
		int root = in.find_first_of(pre[0]);
		T->data = pre[0];
		if(root<0)
		  return ERROR;
		int status=1;
		return Pos(pre.substr(1,root),in.substr(0,root),T->lchild)*Pos(pre.substr(root+1),in.substr(root+1),T->rchild);
	}
}
int PosOrder(Tree T)
{
	if(T){
		PosOrder(T->lchild);
		PosOrder(T->rchild);
		printf("%c",T->data);
	}
	return OK;
}
int main()
{
	string pre,in;
	char temppre[MAXN],tempin[MAXN];
	while(scanf("%s %s",temppre,tempin)==2){
		pre=temppre;
		in=tempin;
		Tree T;
		if(!T)
		  OverFlow
		int status = Pos(pre,in,T);
		if(!status)
		  printf("Error\n");
		else{
			PosOrder(T);
			putchar('\n');
		}
	}
	return 0;
}
