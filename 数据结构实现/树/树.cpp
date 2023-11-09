#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<stdio.h>

#define OK 1
#define ERROR 0
#define OVERFLOW {printf("\n\nOVERFLOW\n\n");return -2;}

typedef int ElemType;
typedef int Status;
typedef struct Node{
	ElemType data;
	struct Node *lchild,*rchild;
}Node,*Tree;
Status CreateTree(Tree &T);
Status visit(Tree T);
//递归实现
Status PreOrderTraverse(Tree T,Status(*visit)(Tree));
Status InOrderTraverse(Tree T,Status(*visit)(Tree));
Status PosOrderTraverse(Tree T,Status(*visit)(Tree));
//非递归，栈实现
Status PreOrder(Tree T,Status(*visit)(Tree));
//Status PreOrder(Tree T,Status(*visit)(Tree));
//Status PreOrder(Tree T,Status(*visit)(Tree));
//Status Display(Tree T);
//int Depth(Tree T);
//int Size(Tree T);

int main()
{
	printf("=======TEST BEGIN=======\n");
	Tree T;
	CreateTree(T);
	printf("----PreOrderTraverse----\n");
	PreOrderTraverse(T,visit);
	printf("------------------------\n");
	printf("----IneOrderTraverse----\n");
	InOrderTraverse(T,visit);
	printf("-----------------------\n");
	printf("----PosOrderTraverse----\n");
	PosOrderTraverse(T,visit);
	printf("------------------------\n");
	printf("=======TEST END=======\n");
	return 0;
}

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
	  PreOrderTraverse(T->lchild,visit);
	visit(T);
	if(T->rchild)
	  PreOrderTraverse(T->rchild,visit);
	return OK;
}

Status PosOrderTraverse(Tree T,Status(*visit)(Tree))
{
	if(T->lchild)
	  PreOrderTraverse(T->lchild,visit);
	if(T->rchild)
	  PreOrderTraverse(T->rchild,visit);
	visit(T);
	return OK;
}
