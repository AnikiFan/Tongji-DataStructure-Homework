#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<stdio.h>

typedef int ElemType;
typedef int Status;
typedef struct Node{
	ElemType data;
	struct Node *lchild,*rchild;
}Node,*Tree;
//先序创建
Status CreateTree(Tree &T);
Status visit(Tree T);
//递归实现
Status PreOrderTraverse(Tree T,Status(*visit)(Tree));
Status InOrderTraverse(Tree T,Status(*visit)(Tree));
Status PosOrderTraverse(Tree T,Status(*visit)(Tree));
//非递归，栈实现
//保存根结点
Status PreOrder1(Tree T,Status(*visit)(Tree));
//保存兄弟结点
Status PreOrder2(Tree T,Status(*visit)(Tree));
Status InOrder(Tree T,Status(*visit)(Tree));
//通过位置来判断
Status PosOrder1(Tree T,Status(*visit)(Tree));
//Status Display(Tree T);
int Depth(Tree T);
int size(Tree T);
Status Switch(Tree &T);
Status Copy(Tree &dst,Tree src);
Status LevelTraverse(Tree T,Status(*visit)(Tree));

