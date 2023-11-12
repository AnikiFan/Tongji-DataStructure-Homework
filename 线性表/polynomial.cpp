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
Poly poly1,poly2,ans;
//建立链表
Status CreateList_L(LinkList&L,int n){//运用尾插法
	LNode* node;
	ElemType temp;
//	printf("Create size:%d\n");
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
		node->next = NULL;
//		printf("add {%d %d}\n",in.co,in.deg);
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
//尾插法
Status ListInsert(LinkList& L,ElemType e){
	LNode *node =(LNode*)malloc(sizeof(LNode));
	if(!node)
	  return OVERFLOW;
	node->data = e;
	node->next = NULL;
	L.rear->next = node;
	L.rear = L.rear->next;
	return OK;
}
//遍历链表
Status TraversePoly(LinkList L,Status(*visit)(ElemType)){
	if(L.front==L.rear)
	  return ERROR;
//	printf("Begin Traverse\n");
	LNode * p= L.front->next;
	while(p!=L.rear){
		visit(p->data);
		p= p->next;
	}
	visit(p->data);
	printf("\n");
	return OK;
}
Status visit(ElemType e){
	printf("%d %d ",e.co,e.deg);
	return OK;
}
//销毁
Status DestroyList_L(LinkList L){
	LNode*p = L.front,*q =L.front;
	while(p->next ){
		p = p->next;
		free(q);
		q = p;
	}
	free(p);
	return OK;
}
//有序链表的合并
//这里的合并后链表独立的，而PPT上的链表与第一个合并的链表共用一个头节点。
//PPT上的做法应该是为了最大化利用链表的特性，存储起来十分方便，例如在尾部时可以直接将其中一个链表中的next拿过来。
Status AddPoly(LinkList La,LinkList Lb,LinkList &Lc){
	LNode * pa = La.front->next,*pb = Lb.front->next;
	InitList(Lc);
	while(pa&&pb){
//		printf("compare:La{%d %d},Lb{%d %d}\n",pa->data.co,pa->data.deg,pb->data.co,pb->data.deg);
		if(pa->data.deg>pb->data.deg){
			ListInsert(Lc,pb->data);
//			printf("add Lb{%d %d}\n",pb->data.co,pb->data.deg);
			pb = pb->next;
		}
		else if(pa->data.deg<pb->data.deg){
			ListInsert(Lc,pa->data);
//			printf("add La{%d %d}\n",pa->data.co,pa->data.deg);
			pa = pa->next;
		}
		else {
			term in={pa->data.co+pb->data.co,pa->data.deg};
			if(in.co){
				ListInsert(Lc,in);
//				printf("add La+Lb{%d %d}\n",in.co,in.deg);
			}
				pa = pa->next;
				pb = pb->next;
		}
	}
	while(pa){
		ListInsert(Lc,pa->data);
//		printf("add La{%d %d}\n",pa->data.co,pa->data.deg);
		pa=pa->next;
	}
	while(pb){
		ListInsert(Lc,pb->data);
//		printf("add Lb{%d %d}\n",pb->data.co,pb->data.deg);
		pb=pb->next;
	}
	TraversePoly(Lc,visit);
	return OK;
}
Status AddToPoly(LinkList La,LinkList &Lb,LinkList &Lc){
	LNode * pa = La.front->next,*pb = Lb.front->next;
	InitList(Lc);
	while(pa&&pb){
//		printf("compare:La{%d %d},Lb{%d %d}\n",pa->data.co,pa->data.deg,pb->data.co,pb->data.deg);
		if(pa->data.deg>pb->data.deg){
			ListInsert(Lc,pb->data);
//			printf("add Lb{%d %d}\n",pb->data.co,pb->data.deg);
			pb = pb->next;
		}
		else if(pa->data.deg<pb->data.deg){
			ListInsert(Lc,pa->data);
//			printf("add La{%d %d}\n",pa->data.co,pa->data.deg);
			pa = pa->next;
		}
		else {
			term in={pa->data.co+pb->data.co,pa->data.deg};
			if(in.co){
				ListInsert(Lc,in);
//				printf("add La+Lb{%d %d}\n",in.co,in.deg);
			}
				pa = pa->next;
				pb = pb->next;
		}
	}
	while(pa){
		ListInsert(Lc,pa->data);
//		printf("add La{%d %d}\n",pa->data.co,pa->data.deg);
		pa=pa->next;
	}
	while(pb){
		ListInsert(Lc,pb->data);
//		printf("add Lb{%d %d}\n",pb->data.co,pb->data.deg);
		pb=pb->next;
	}
	DestroyList_L(La);
	DestroyList_L(Lb);
	Lb = Lc;
	return OK;
}


Status TimePoly(Poly L,Poly&  ans,term operand)
{
	if(L.front ==L.rear )
	  return ERROR;
	InitList(ans);
	LNode*p = L.front->next;
	while(p){
		term in{p->data.co*operand.co,p->data.deg+operand.deg};
		ListInsert(ans,in);	
		p=p->next;
	}
	return OK;
}
Status MultiPoly(LinkList La,LinkList Lb)
{
	Poly ans,temp,temp1;
	InitList(ans);
	LNode*p=La.front->next;
	while(p){
		InitList(temp);
		InitList(temp1);
		TimePoly(Lb,temp,p->data);
//		printf("to add:");
//	TraversePoly(temp,visit);
//	printf("been added:");
		AddToPoly(temp,ans,temp1);
	//TraversePoly(ans,visit);
		p=p->next;
	}
	TraversePoly(ans,visit);
	return OK;
}
int main()
{
	int n;
	scanf("%d",&n);
	CreateList_L(poly1,n);
	scanf("%d",&n);
	CreateList_L(poly2,n);
	scanf("%d",&n);
	if(n==0){
		Poly ans;
		AddPoly(poly1,poly2,ans);
	}
	else if(n==1){
		MultiPoly(poly1,poly2);
	}
	else{
		Poly ans;
		AddPoly(poly1,poly2,ans);
		MultiPoly(poly1,poly2);
	}
	return 0;
}
