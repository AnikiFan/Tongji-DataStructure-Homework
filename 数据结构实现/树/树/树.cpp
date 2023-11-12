#include "树.h"
#include "../../栈和队列/顺序栈/顺序栈.h"
#include"../../header.h"
#include<stack>
#include<queue>
Status CreateTree(Tree &T)
{
	ElemType input;
	scanf("%d",&input);
	if(!input){
		T = NULL;
		printf("create empty node\n");
		return OK;
	}
	T = (Tree)malloc(sizeof(Node));
	if(!T)
	  OVERFLOW;
	T->data = input;
	printf("create node with %d\n",input);
	CreateTree(T->lchild);
	CreateTree(T->rchild);
	return OK;
}

Status visit(Tree T)
{
	printf("%d\n",T->data);
	return OK;
}

Status PreOrderTraverse(Tree T,Status(*visit)(Tree))
{
	visit(T);
	if(T->lchild)
	  PreOrderTraverse(T->lchild,visit);
	if(T->rchild)
	  PreOrderTraverse(T->rchild,visit);
	return OK;
}

Status InOrderTraverse(Tree T,Status(*visit)(Tree))
{
	if(T->lchild)
	  InOrderTraverse(T->lchild,visit);
	visit(T);
	if(T->rchild)
	  InOrderTraverse(T->rchild,visit);
	return OK;
}

Status PosOrderTraverse(Tree T,Status(*visit)(Tree))
{
	if(T->lchild)
	  PosOrderTraverse(T->lchild,visit);
	if(T->rchild)
	  PosOrderTraverse(T->rchild,visit);
	visit(T);
	return OK;
}

Status PreOrder1(Tree T,Status (*visit)(Tree))
{
	std::stack <Tree> s;
	Tree p=T;
	while(!s.empty()||p){
		while(p){
			s.push(p);
			visit(p);	
			p= p->lchild;
		}
		p=s.top();
		p=p->rchild;
		s.pop();
	}
	return OK;
}
Status PreOrder2(Tree T,Status (*visit)(Tree))
{
	std::stack<Tree> s;
	Tree p = T;
	while(!s.empty()||p){
		while(p){
			visit(p);
			s.push(p->rchild);
			p= p->lchild;
		}
		p= s.top();
		s.pop();
	}
	return OK;
}

Status InOrder(Tree T,Status(*visit)(Tree))
{
	std::stack<Tree> s;
	Tree p = T;
	while(p||!s.empty()){
		while(p){
			s.push(p);
			p = p->lchild;
		}
		p = s.top();
		visit(p);
		s.pop();
		p = p->rchild;
	}
	return OK;
}
Status PosOrder1(Tree T,Status(*visit)(Tree))
{
	std::stack<Tree> s;
	Tree p = T,temp = NULL;
	while(p){
		while(p&&p!= temp){
		//	printf("left,%d\n",p->data);
			s.push(p);
			p = p->lchild;
		}
		p = s.top();
		//printf("at,%d\n",p->data);
		if(p->rchild&&p->rchild!= temp){
			p=p->rchild;
			//printf("right,%d\n",p->data);
		}
		else{
			visit(p);
			temp = p;
			//printf("temp:%d\n",temp->data);
			s.pop();
		}
		if(s.empty())
		  return OK;
	}
	return OK;
}
int Depth(Tree T)
{
	if(!T)
		return 0;
	else
		return Depth(T->rchild)>Depth(T->lchild)?Depth(T->rchild)+1:Depth(T->lchild)+1;
}
int size(Tree T)
{
	if(!T)
	  return 0;
	else
		return 1+size(T->rchild)+size(T->lchild);
}
Status Switch(Tree &T)
{
	if(!T)
	  return OK;
	else{
		Switch(T->rchild);
		Switch(T->lchild);
		Tree temp = T->rchild;
		T->rchild= T->lchild;
		T->lchild = temp;
	}
	return OK;
}
Status Copy(Tree &dst,Tree src)
{
	if(!src){
		dst =NULL;
		return OK;
	}
	else{
		dst = (Tree)malloc(sizeof(Node));
		if(!dst)
		  OVERFLOW
		dst->data = src->data;
		Copy(dst->rchild,src->rchild);
		Copy(dst->lchild,src->lchild);
	}
	return OK;
}
Status LevelTraverse(Tree T,Status(*visit)(Tree))
{
	std::queue<Tree> q;
	Tree p =T;
	q.push(p);
	while(!q.empty()){
		p = q.front();
		q.pop();
		visit(p);
		if(p->lchild)
		  q.push(p->lchild);
		if(p->rchild)
		  q.push(p->rchild);
	}
	return OK;
}
