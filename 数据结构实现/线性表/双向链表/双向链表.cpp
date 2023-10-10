//本实验模拟的是双向循环链表
#define OK 1
#define FALSE 0
#define ERROR 0
#define OVERFLOW -2

#include<stdio.h>
#include<malloc.h>
#include<process.h>

typedef int ElemType,Status;
typedef struct DulNode{
	DulNode* prior;
	DulNode* next;
	ElemType data;
}DulNode,*DulLinkList;

//创建链表
Status CreateDulList(DulLinkList & L,int n){
	DulNode* p ;
	L = (DulNode *)malloc(sizeof(DulNode));
	L->prior =L;
	L->next = L;
	p=L;
	for(int i =0;i<n;i++){
		p->next= (DulNode*)malloc(sizeof(DulNode));
		p->next ->prior = p;
		p=p->next ; 
		scanf("%d",&p->data);
	}	
	p->next = L;
	L->prior = p;
	return OK;
}
//显示输出
Status TraverseList(DulLinkList L,Status visit(ElemType)){
	DulNode*p= L->next;
	while(p!=L){
		visit(p->data);
		p=p->next;
	}
	printf("\n");
	return OK;
}
Status visit(ElemType e){
	printf("%d ",e);
	return OK;
}
//插入
Status InsertList(DulLinkList L,int i,ElemType e){
	int j = 0;
	DulNode*p=L,*q;
	while(p->next!=L&&j<i-1){
		p = p->next;
		j++;
	}
	if(p->next==L||j>i-1)
	  return ERROR;
	q=p->next ;
	p->next = (DulNode*)malloc(sizeof(DulNode));
	p->next->data = e;
	p->next->prior = p;
	q->prior = p->next;
	p->next ->next = q;
	return OK;
}
//删除
Status DeleteList(DulLinkList L,int i){
	int j =0;
	DulNode*p =L,*q;
	while(p->next!=L&&j<i-1){
		p=p->next;
		j++;
	}
	if(p->next==L||j>i-1)
	  return ERROR;
	q= p->next;
	p->next = q->next;
	q->next->prior=p;
	free(q);
	return OK;
}
int main()
{
	DulLinkList L;
	printf("----TEST BEGIN-----\n\n");
	printf("----TEST FOR CREATEDULLIST AND TRAVERSELIST----\n\n");
	printf("please input 10 integers\n");
	CreateDulList(L,10);
	TraverseList(L,visit);
	printf("----TEST FOR INSERT AND DELETE----\n\n");
	InsertList(L,3,114514);
	InsertList(L,7,1919810);
	TraverseList(L,visit);
	DeleteList(L,3);
	DeleteList(L,6);
	TraverseList(L,visit);
	return 0;
}
