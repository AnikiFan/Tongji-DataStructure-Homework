//本实验是模拟带头节点的单链表
//既然LinkList是一个指针，那么课件中有些对于它的引用应该是多余的，应该只有在要用malloc的地方引用才是必要的。
//问题：链表什么时候要创建一个节点，而不是复用之前的节点。
#include<stdio.h>
#include<malloc.h>
#include<process.h>
#define TRUE 1
#define OK 1
#define ERROR 0
#define FALSE 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int ElemType,Status;
typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;

//取元素(按序号查找)
Status GetElem_L(LinkList L,int i,ElemType &e){
	int j = 1;//从1开始是因为查询操作只涉及待查询项，不会涉及到头节点。
	LNode* p = L->next;
	while(p&&j<i){
		p = p->next;
		j++;
	}
	if(!p||j>i)
	  return ERROR;
	e = p->data;
	return OK;
}
//插入元素
Status ListInsert(LinkList L,int i,ElemType e){
	int j = 0;//从零开始是因为插入操作涉及到插入项的前一项,并且顺序的比较也涉及到i-1
	LNode*p = L;
	while(p&&j<i-1){
		p=p->next;
		j++;
	}
	if(!p||j>i-1)
	  return ERROR;
	LNode*q = (LNode*)malloc(sizeof(LNode));
	if(!q)
	  exit(OVERFLOW);
	q->next = p->next;
	q->data= e;
	p->next = q;
	return OK;
}
//删除元素
Status DeleteElem(LinkList L,int i){
	int j =0;
	LNode *p = L;
	while(p&&j<i-1){
		p= p->next;
		j++;
	}
	if(!p||j>i-1||!p->next)
	  return ERROR;
	LNode *q = p->next;
	p ->next = q ->next;
	free(q);
	return OK;
}
//建立链表
Status CreateList_L(LinkList&L,int n){
	LNode* node;
	ElemType temp;
	L = (LinkList)malloc(sizeof(LNode));
	if(!L)
	  exit(OVERFLOW);
	L->next = NULL;
	for(int i =0;i<n;i++){
		scanf("%d",&temp);
		node = (LNode*)malloc(sizeof(LNode));
		if(!node)
		  exit(OVERFLOW);
		node ->next = L->next;
		L->next = node;
		node->data = temp;
	}
	return OK;
}
//初始化链表
Status InitList(LinkList &L){
	L = (LNode*)malloc(sizeof(LNode));
	if(!L)
	  exit(OVERFLOW);
	L->next = NULL;
	return OK;
}
//有序链表的合并
//这里的合并后链表独立的，而PPT上的链表与第一个合并的链表共用一个头节点。
//PPT上的做法应该是为了最大化利用链表的特性，存储起来十分方便，例如在尾部时可以直接将其中一个链表中的next拿过来。
Status MergeList_L(LinkList La,LinkList Lb,LinkList &Lc){
	LNode * pa = La->next,*pb = Lb->next;
	InitList(Lc);
	int i =1;
	while(pa&&pb){
		if(pa->data>pb->data){
		  ListInsert(Lc,i,pb->data);
		pb = pb->next;
		}
		else {
		  ListInsert(Lc,i,pa->data);
		  pa = pa->next;
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
	return OK;
}
//查找（按值查找）
int LocateElem_L(LinkList L,ElemType e,Status(*compare)(ElemType,ElemType)){
	int i = 1;
	LNode* p = L->next;
	while(p&&!compare(p->data,e)){
		p= p->next;
	  i++;
	}
	if(!p)
	  return FALSE;
	return i;
}
Status compare(ElemType a,ElemType b){
	if(a ==b)
	  return OK;
	else
	  return FALSE;
}
//遍历链表
Status TraverseList(LinkList L,Status(*visit)(ElemType)){
	LNode * p= L->next;
	while(p){
		visit(p->data);
		p= p->next;
	}
	printf("\n");
	return OK;
}
Status visit(ElemType e){
	printf("%d ",e);
	return OK;
}
//求长度
int ListLength_L (LinkList L){
	int i =0;
	LNode* p = L->next;
	while(p){
		i++;
		p = p->next;
	}
	return i;
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
Status ClearList(LinkList L){
	LNode*p = L->next,*q = L->next;
	L->next = NULL;
	while(p){
		q= p->next;
		free(p);
		p = q;
	}
	return OK;
}
Status ListEmpty_L(LinkList L){
	if(L->next)
	  return FALSE;
	else 
	  return TRUE;
}
Status PriorElem_L(LinkList L,ElemType cur_e,ElemType &pre_e){
	LNode* p =L;
	while(p->next&&p->next->data!= cur_e)
		p=p->next;
	if(p->next){
	  pre_e = p->data;
	 return OK;	
	}
	return INFEASIBLE;
}
Status NextElem_L(LinkList L,ElemType cur_e,ElemType &nex_e){
	LNode*p = L->next;
	while(p&&p->data != cur_e)
	  p=p->next;
	if(!p||!p->next)
	  return INFEASIBLE;
	nex_e = p->next->data;
	return OK;
}
//PPT中的算法里，不会重复查询新加入 La的元素，因为它们本来就来自 Lb，不会再与 Lb中的元素重合
void UnionList_L(LinkList La,LinkList Lb){
	LNode * pb = Lb->next,*q;
	free(Lb);
	while(pb){
		if(!LocateElem_L(La,pb->data,compare))
			ListInsert(La, 1, pb->data);
		q = pb;
		pb = pb ->next;
		free(q);
	}
	return ;
}
int main()
{
	LinkList L,La,Lb,Lc,Ld;
	ElemType temp;
	printf("TEST BEGIN\n");
	printf("TEST FOR CREATELIST AND TRAVERSE\n");
	printf("please input 5 integers\n");
	CreateList_L(L,5);	
	TraverseList(L,visit);
	printf("TEST FOR INITLIST, INSERT AND DELETE\n");
	ListInsert(L,1,1);
	ListInsert(L,2,114514);
	TraverseList(L,visit);
	InitList(La);
	ListInsert(La,1,1);
	ListInsert(La,2,45);
	ListInsert(La,3,343);
	TraverseList(La,visit);
	DeleteElem(La,2);
	TraverseList(La,visit);
	printf("TEST FOR MERGING LIST\n");
	InitList(Lb);
	ListInsert(Lb,1,10);
	ListInsert(Lb,2,20);
	ListInsert(Lb,3,30);
	ListInsert(Lb,4,40);
	InitList(Lc);
	ListInsert(Lc,1,14);
	ListInsert(Lc,2,20);
	ListInsert(Lc,3,35);
	ListInsert(Lc,4,36);
	TraverseList(Lb,visit);
	TraverseList(Lc,visit);
	MergeList_L(Lb,Lc,Ld);
	TraverseList(Ld,visit);
	printf("TEST FOR LOCATEELEMENT\n");
	printf("search for 36\n");
	printf("%d\n",LocateElem_L(Ld,36,compare));
	printf("TEST FOR GETLENGTH\n");
	printf("%d\n",ListLength_L(Ld));
	printf("TEST FOR DESTROYLIST, CLEARLIST AND EMPTYLIST\n");
	printf("list to be cleared\n");
	TraverseList(Ld,visit);
	ClearList(Ld);
	printf("length after being cleared:%d\n",ListLength_L(Ld));
	DestroyList_L(L);
	printf("whether it is empty:%d\n",ListEmpty_L(Ld));
	printf("TEST FOR PRIORELEM AND NEXTELEM\n");
	printf("searched list\n");
	TraverseList(Lc,visit);
	printf("search for 36's prior element\n");	
	PriorElem_L(Lc,36,temp);
	printf("%d\n",temp);
	temp =0;
	printf("search for 6's prior element\n");	
	PriorElem_L(Lc,6,temp);
	printf("%d\n",temp);
	printf("search for 35's next element\n");
	NextElem_L(Lc,35,temp);
	printf("%d\n",temp);
	temp =0;
	printf("search for 36's next element\n");
	NextElem_L(Lc,36,temp);
	printf("%d\n",temp);
	printf("TEST FOR LIST UNION\n");
	printf("first list to be unioned\n");
	TraverseList(La,visit);
	printf("second list to be unioned\n");
	TraverseList(Lb,visit);
	UnionList_L(La,Lb);
	printf("UNIONED LIST\n");
	TraverseList(La,visit);
	return 0;
}
