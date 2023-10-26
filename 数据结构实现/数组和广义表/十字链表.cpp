#define _CRT_SECURE_NO_WARNINGS
//头结点用数组，行列元素用单链表来记录
#include<stdio.h>
#include<malloc.h>

#define OVERFLOW {printf("\n\nOVERFLOW\n\n");return -1;}
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int ElemType;
typedef int Status;
typedef struct Node{//元素结点
	int i ,j;
	ElemType e;
	struct Node* right,*down;
} Node,*Link,*Head;
typedef struct{
	Head *rhead,*chead;//行和列链表表头指针数组
	int mu,nu,tu;//行数，列数，和非零元个数
}CrossList;

Status InitList(CrossList& L,int mu,int nu,int tu);
Status TraverseList(CrossList L);

int main()
{
	printf("----TEST BEGIN----\n");
	CrossList L;
	InitList(L,10,10,12);
	TraverseList(L);
	printf("----TEST END----\n");
	return 0;
}

Status TraverseList(CrossList L)
{
	for(int i = 0;i<L.mu;i++){
		Link p;
		if((L.rhead[i]))
		  p= L.rhead[i]->right;
			while(p){
				printf("[%d][%d]:%d\n",p->i,p->j,p->e);
				p=p->right;
		}
	}
	return OK;
}

Status InitList(CrossList& L,int mu,int nu,int tu)
{
	L.rhead = (Head*)calloc(sizeof(Head),mu);
	if(!L.rhead)
	  OVERFLOW
	L.chead = (Head*)calloc(sizeof(Head),nu);
	if(!L.chead)
	  OVERFLOW
	L.mu = mu;
	L.nu = nu;
	int r,c,e;
	for(int i = 1;i<= tu;i++){
		scanf("%d%d%d",&r,&c,&e);
		if(r<0||r>=mu||c<0||c>=nu)
		  return ERROR;
		Link p = (Link)malloc(sizeof(Node));
		if(!p)
		  OVERFLOW
		p->i = r;
		p->j=c;
		p->e=e;
		if(!L.rhead[r]){
			 L.rhead[r]= (Head)calloc(sizeof(Node),1);
			  if(!L.rhead[r])
				OVERFLOW
			L.rhead[r]->right = p;
			p->right= NULL;
		}
		  else{
			  Link q = L.rhead[r];
			  while(q->right&&q->right->j<c)
				q=q->right;
			  p->right = q->right;
			  q->right = p;
	  }
		if(!L.chead[c]){
			  L.chead[c]= (Head)calloc(sizeof(Node),1);
			  if(!L.chead[c])
				OVERFLOW
			L.chead[c]->down = p;
			p->down = NULL;
		}
		  else{
			  Link q = L.chead[c];
			  while(q->down&&q->down->i<i)
				q=q->down;
			  p->down = q->down;
			  q->down = p;
	  }
	}
	L.tu = tu;
	return OK;
}
