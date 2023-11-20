#include<iostream>
using namespace std;
#define OverFlow {cout<<"OVERFLOW"<<endl;return -2;}
#define OK 1
typedef int Status;
typedef char ElemType;
typedef enum{Link,Thread} Tag;
typedef struct Node{
	Node* parent;
	Node* lchild;
	Node* rchild;
	ElemType data;	
	Tag LTag,RTag;
}Node,*Tree;
Status CreatePreTree(Tree& T)
{
	char input;
	cin>>input;
	if(input=='#'){
		T=NULL;
		return OK;
	}
	T= new Node;
	if(!T)
	  OverFlow
	T->data = input;
	CreatePreTree(T->lchild);
	CreatePreTree(T->rchild);
	return OK;
}
Status MakePreThread(Tree& T,Tree &pre)
{
	if(T){
		MakePreThread(T->lchild,pre);
		if(pre&&!pre->rchild){
			pre->rchild = T;
			pre->RTag= Thread;
		}
		if(!T->lchild){
			T->lchild = pre;
			T->LTag=Thread;
		}
		pre = T;
		MakePreThread(T->rchild,pre);
	}
	return OK;
}
Status CreatePreThreadTree(Tree& T)
{
	Tree pre = NULL;
	CreatePreTree(T);
	MakePreThread(T,pre);
	return OK;
}
Status PreTraverse(Tree T)
{
	while(T){
		while(T->LTag==Link){
			cout<<T->data;
			T=T->lchild;
		}
		cout<<T->data;
		T=T->rchild;
	}
	return OK;
}
int main()
{
	Tree T;
	CreatePreTree(T);
	PreTraverse(T);
	return 0;
}
