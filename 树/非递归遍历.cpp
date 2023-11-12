#define _CRT_SECURE_NO_WARNINGS
#define OVERFLOW {printf("\n\nOVERFLOW\n\n");return -2;}
#include<malloc.h>
#include<stdio.h>
#include<stack>
typedef char ElemType;
typedef struct Node{
	ElemType data;
	struct Node *lchild,*rchild;
}Node,*Tree;

#include<string.h>
#define MAXOPTSIZE 10
typedef char ElemType ;
typedef int Status ;
#define OK 1

Status visit(Tree T)
{
	printf("%c",T->data);
	return OK;
}
Status PosOrderTraverse(Tree T,Status(*visit)(Tree))
{
	if(!T)
	  return OK;
	PosOrderTraverse(T->lchild,visit);
	PosOrderTraverse(T->rchild,visit);
	visit(T);
	return OK;
}


int main()
{
	int n,flag=0;
	char opt[MAXOPTSIZE];
	ElemType val ;
	scanf("%d",&n);
	std::stack<Tree> s;
	Tree p=(Tree)malloc(sizeof(Node)),T = p,temp;//工作指针初始化
	if(!T)
	  OVERFLOW;
	while(n){
		while(flag||((scanf("%s",opt)==1&&!strcmp(opt,"push")))){
			flag =0;
			p ->lchild =(Tree)malloc(sizeof(Node));
			p ->rchild =(Tree)malloc(sizeof(Node));
			scanf(" %c",&val);
			p->data = val;
			//printf("create node with %c,left\n",p->data);
			s.push(p);
			p = p->lchild;
		}
		//此时读入了一个pop,应该回收左节点，同时修改栈顶结点的左节点为NULL
		free(p);
		p = s.top();
		//printf("back to node with %c\n",p->data);
		s.pop();
		p->lchild = NULL;
		n--;
		while(n&&(scanf("%s",opt)==1&&!strcmp(opt,"pop"))){
			//每循环一次说明有一个右孩子结点为NULL
			free(p->rchild);
			p->rchild = NULL;
			p = s.top();
			s.pop();
			//printf("back to node with %c\n",p->data);
			n--;
		//	printf("n:%d",n);
		}
		//此时读入了一个push
		if(!n){
			free(p->rchild);
			p->rchild = NULL;
		}
		p = p->rchild;
		//printf("right\n");
		flag = 1;
		//printf("n:%d",n);
	}
	PosOrderTraverse(T,visit);
	return 0;
}
