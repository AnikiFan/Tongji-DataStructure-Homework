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
Status InitTree(Tree &T,int n);//n为深度
Status visit(Tree T);
//递归实现
Status PreOrderTraverse(Tree T,Status(*visit)(Tree));
Status InOrderTraverse(Tree T,Status(*visit)(Tree));
Status PosOrderTraverse(Tree T,Status(*visit)(Tree));
//非递归，栈实现
Status PreOrder(Tree T,Status(*visit)(Tree));

int main()
{
	printf("=======TEST BEGIN=======\n");
	Tree T;
	InitTree(T,3);
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

Status InitTree(Tree &T,int n)
{
	if(!n)
	  return OK;
	T = (Tree)calloc(sizeof(Node),1);//将指针初始化为NULL，如果用malloc，则需要另外置NULL
	if(!T)
	  OVERFLOW;
	T->data = n;
	printf("create node with %d\n",n);
	InitTree(T->lchild, n-1);
	InitTree(T->rchild, n-1);
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
