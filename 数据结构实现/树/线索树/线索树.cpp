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
Status CreateTree(Tree& T,Tree parent)
{
	char input;
	cin>>input;
	if(input=='#'){
		T=NULL;
		return OK;
	}
	T= new Node;
	T->parent= parent;
	if(!T)
	  OverFlow
		  T->data = input;
	CreateTree(T->lchild,T);
	CreateTree(T->rchild,T);
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
	cout<<"Init Tree"<<endl;
	CreateTree(T,NULL);
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
	cout<<endl;
	return OK;
}
Status PreThreadInverseTraverse(Tree T)
{
	cout<<"Pre Thread Inverse Traverse"<<endl;
	Tree p = T;
	while(p->rchild){
		while(p->rchild&&p->RTag==Link)
		  p = p->rchild;
		if(p->lchild &&p->LTag==Link)
		  p = p->lchild;
	}
	//此时p到达先序遍历的最后一个结点
	while(p->lchild){
		cout<<p->data;
		if(p->lchild&&p->LTag==Thread)
		  p = p->lchild;	
		else if(!p->parent){
			cout<<endl;
			return OK;
		}
		else if(p->parent->lchild == p||p->parent->LTag==Thread)
		  p = p->parent;
		else {
			p=p->parent->lchild;
			while(p->RTag==Link||p->LTag==Link){
				while(p->rchild&&p->RTag==Link)
				  p = p->rchild;
				if(p->lchild &&p->LTag==Link)
				  p = p->lchild;
			}
		}
	}
	cout<<p->data;
	cout<<endl;
	return OK;
}
Status MakeInThread(Tree &T,Tree &pre)
{
	if(!T)
	  return OK;
	MakeInThread(T->lchild,pre);
	if(pre&&pre->RTag==Thread)
	  pre->rchild = T;
	if(T->lchild)
	  T->LTag =  Link;
	else {
		T->LTag = Thread;
		T->lchild = pre;
	}
	if(T->rchild)
	  T->RTag = Link;
	else 
	  T->RTag = Thread;
	pre = T;
	MakeInThread(T->rchild,pre);
	return OK;
}
Status CreateInThreadTree(Tree &T)
{
	Tree pre = NULL; 
	cout<<"Init Tree"<<endl;
	CreateTree(T,NULL);
	cout<<"Make In Thread"<<endl;
	MakeInThread(T,pre);
	return OK;
}
Status InTraverse(Tree T)
{
	cout<<"In Thread Traverse"<<endl;
	if(!T)
	  return OK;
	Tree p = T;
	while(p->LTag==Link)
	  p = p->lchild;
	//到达中序遍历的第一个结点
	while(p->rchild){
		cout<<p->data;
		if(p->RTag==Thread)
		  p = p->rchild;
		else{
			p=p->rchild;
			while(p->LTag==Link)
			  p=p->lchild;
		}
	}
	cout<<p->data;
	cout<<endl;
	return OK;
}
Status InThreadInverseTraverse(Tree T)
{
	cout<<"In Thread Inverse Traverse"<<endl;
	Tree p = T;
	while(p->RTag==Link)
	  p = p->rchild;
	//达到中序遍历的最后一个结点
	while(p){
		cout<<p->data;
		if(p->LTag==Thread)
		  p = p->lchild;
		else {
			p = p->lchild;
			while(p->RTag == Link)
			  p = p->rchild;
		}
	}
	cout<<endl;
	return OK;
}
Status MakePosThread(Tree &T,Tree &pre)
{
	if(!T)
	  return OK;
	MakePosThread(T->lchild,pre);
	MakePosThread(T->rchild,pre);
	if(pre&&pre->RTag == Thread)
	  pre->rchild= T; 
	if(T->lchild)
	  T->LTag = Link;
	else {
		T->LTag=Thread;
		T->lchild = pre;
	}
	if(T->rchild)
	  T->RTag = Link;
	else 
	  T->RTag = Thread;
	pre = T;
	return OK;
}
Status CreatePosThreadTree(Tree &T)
{
	Tree pre =NULL;
	cout<<"Init Tree"<<endl;
	CreateTree(T,NULL);
	cout<<"Make Pos Thread"<<endl;
	MakePosThread(T,pre);
	return OK;
}
Status PosTraverse(Tree T)
{
	cout<<"Pos Thread Traverse"<<endl;
	if(!T)
	  return OK; 
	Tree p = T;
	while(p->RTag==Link||p->LTag==Link){
		while(p->LTag==Link)
		  p=p->lchild;
		if(p->RTag==Link)
		  p = p->rchild;
	}
	//此时到达后序遍历的第一个结点
	while(p->rchild){
		cout<<p->data;
		if(p->RTag==Thread)
		  p=p->rchild;
		else if(!p->parent){
			cout<<endl;
		  return OK;
		}
		else if(p->parent ->RTag==Thread||p->parent->rchild == p)
		  p=p->parent;
		else {
			p=p->parent;
			if(p->RTag==Link){
				p=p->rchild;
				while(p->RTag==Link||p->LTag==Link){
					while(p->LTag==Link)
					  p=p->lchild;
					if(p->RTag==Link)
					  p = p->rchild;
				}
			}
		}
	}
	return OK;
}
Status PosInverseTraverse(Tree T)
{
	cout<<"Pos Inversae Traverse"<<endl;
	if(!T)
	  return OK;
	Tree p = T;
	while(p->lchild){
		cout<<p->data;
		if(p->LTag==Thread||p->RTag==Thread)
		  p = p->lchild;
		else 
		  p = p->rchild;
	}
	cout<<p->data;
	cout<<endl;
	return OK;
}
int main()
{
	Tree T1,T2,T3;
	cout<<"=======TEST BEGIN======="<<endl;
	CreatePreThreadTree(T1);
	PreTraverse(T1);
	PreThreadInverseTraverse(T1);
	CreateInThreadTree(T2);
	InTraverse(T2);
	InThreadInverseTraverse(T2);
	CreatePosThreadTree(T3);
	PosTraverse(T3);
	PosInverseTraverse(T3);
	cout<<"=======TEST E N D======="<<endl;
	return 0;
}
