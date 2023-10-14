#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#define TRUE 1
#define OK 1
#define ERROR 0
#define FALSE 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef struct {
	int co;
	int deg;
}ElemType,term;
typedef int Status;
//因为这里结构体内部包含自身，LNode无法省去
typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode;
typedef struct {
	LNode* front;
	LNode* rear;
}LinkList,Poly;
Poly poly1,poly2;
//建立链表
Status CreateList_L(LinkList&L,int n){//运用尾插法
	LNode* node;
	ElemType temp;
	L.front = (LNode*)malloc(sizeof(LNode));
	if(!L.front)
	  return OVERFLOW;
	L.front->next = NULL;
	L.rear = L.front;

	for(int i =0;i<n;i++){
		term in ;
		scanf("%d%d",&in.co,&in.deg);
		node = (LNode*)malloc(sizeof(LNode));
		if(!node)
		  return OVERFLOW;
		L.rear->next = node;
		L.rear = node;
		node->data = in;
	}
	return OK;
}
//初始化链表
Status InitList(LinkList &L){
	L.front = (LNode*)malloc(sizeof(LNode));
	if(!L.front)
	  return OVERFLOW;
	L.front->next = NULL;
	L.rear = L.front;
	return OK;
}
//插入元素
Status ListInsert(LinkList L,int i,ElemType e){
	int j = 0;//从零开始是因为插入操作涉及到插入项的前一项,并且顺序的比较也涉及到i-1
	LNode*p = L.front;
	while(p&&j<i-1){
		p=p->next;
		j++;
	}
	if(!p||j>i-1)
	  return ERROR;
	LNode*q = (LNode*)malloc(sizeof(LNode));
	if(!q)
	  return OVERFLOW;
	q->next = p->next;
	q->data= e;
	p->next = q;
	return OK;
}
//遍历链表
Status TraversePoly(LinkList L,Status(*visit)(ElemType)){
	LNode * p= L->front.next;
	while(p!=rear){
		visit(p->data);
		p= p->next;
	}
	visit(p->data);
	printf("\n");
	return OK;
}
Status visit(ElemType e){
	printf("%d %d",e.co,e.deg);
	return OK;
}
//有序链表的合并
//这里的合并后链表独立的，而PPT上的链表与第一个合并的链表共用一个头节点。
//PPT上的做法应该是为了最大化利用链表的特性，存储起来十分方便，例如在尾部时可以直接将其中一个链表中的next拿过来。
Status AddPoly(LinkList La,LinkList Lb,LinkList &Lc){
	LNode * pa = La->next,*pb = Lb->next;
	InitList(Lc);
	int i =1;
	while(pa&&pb){
		if(pa->data.co>pb->data.co){
		  ListInsert(Lc,i,pb->data);
		pb = pb->next;
		}
		else if(pa->data.co<pb->data.co){
		  ListInsert(Lc,i,pa->data);
		  pa = pa->next;
		}
		else {
			term in={pa->data.co+pb->data.co,pa->data.deg};
			ListInsert(Lc,i,in);
			pa = pa->next;
			pb = pb->next;
		}
		i++;
	}
	while(pa){
		ListInsert(Lc,i,pa->data);
		pa=pa->next;
		i++; 
	}
	while(pb){
		ListInsert(Lc,i,pb->data);
		pb=pb->next;
		i++;
	}
	TraversePoly(ans,visit);
	return OK;
}
//销毁
Status DestroyList_L(LinkList L){
	LNode*p = L,*q =L;
	while(p->next ){
		p = p->next;
		free(q);
		q = p;
	}
	free(p);
	return OK;
}
int main()
{
	int n;
	scanf("%d",&n);
	CreateList_L(Poly1,n);
	scanf("%d",&n);
	CreateList_L(Poly2,n);
	scanf("%d",&n);
	if(n==0){
		Poly ans;
		AddPoly(Poly1,Poly2,ans);
	}
	else {

	}
	return 0;
}
