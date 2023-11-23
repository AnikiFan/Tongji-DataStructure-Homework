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
		if(T->rchild)
		  T->RTag=Link;
		else 
		  T->RTag = Thread;
		if(T->lchild)
		  T->LTag=Link;
		else{
		  T->LTag=Thread;
		 T->lchild = pre;
		}
		if(pre&&!pre->rchild)
		  pre->rchild = T;
		pre = T;
		if(T->LTag==Link)
			MakePreThread(T->lchild,pre);
		if(T->RTag==Link)
			MakePreThread(T->rchild,pre);
	}
	return OK;
}
void PrintInfo(Tree T)
{
	if(!T)
	  return;
	cout<<endl;
	cout<<"data:"<<T->data<<endl;
	cout<<"LTag:"<<(T->LTag==Thread?"Thread":"Link")<<endl;
	cout<<"RTag:"<<(T->RTag==Thread?"Thread":"Link")<<endl;
	cout<<"Lchild:"<<(T->lchild?T->lchild->data:'#')<<endl;
	cout<<"Rchild:"<<(T->rchild?T->rchild->data:'#')<<endl;
	cout<<endl;
	return;
}
Status PreOrder(Tree T)
{
	if(!T)
	  return OK;
	PrintInfo(T);
	PreOrder(T->lchild);
	PreOrder(T->rchild);
	return OK;
}

Status CreatePreThreadTree(Tree& T)
{
	Tree pre = NULL;
	cout<<"Initial Tree"<<endl;
	CreatePreTree(T);
	cout<<"Make Pre Thread"<<endl;
	MakePreThread(T,pre);
	return OK;
}
Status PreTraverse(Tree T)
{
	cout<<"Pre Thread Traverse"<<endl;
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
Status PreThreadInverseTraverse(Tree T)
{
	return OK;
}
int main()
{
	Tree T;
	cout<<"=======TEST BEGIN======="<<endl;
	CreatePreThreadTree(T);
	PreTraverse(T);
	cout<<endl;
	cout<<"=======TEST E N D======="<<endl;
	return 0;
}
