//该实验模拟的是顺序表的静态实现
#define LIST_MAX_LENGTH 100
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

#include<malloc.h>
#include<stdio.h>

typedef int Status;
typedef int Boolean;
typedef int ElemType;
typedef struct{
	ElemType *elem;
	int length;//current length
	int listsize;//current allocated size
}SqList;


Status InitList_SqList(SqList &L){
	L.elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!L.elem) exit(OVERFLOW);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}

Status ListInsert_sq(SqList &L,int i,ElemType e){
	ElemType *q,*p;
	if(i<1||i>L.length+1) 
	  return ERROR;
	if(L.length>=L.listsize){
		ElemType * newbase;
		newbase = (ElemType*)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
		if(!newbase)
		  exit(OVERFLOW);
		L.elem = newbase;
		L.listsize += LISTINCREMENT;
	}
	q = L.elem+i-1;
	for(p=L.elem+L.length-1;p>=q;--p)
	  *(p+1)=*p;
	*q = e;
	++L.length;
	return OK;
}

Status ListDelete_sq(SqList L,int i){
	if(i<1||i>L.length)
	  return ERROR;
	ElemType *p = L.elem+i-1;
	for(;p<L.elem+L.length ;p++)
	  *p=*(p+1);
	L.length --;
	return OK;
}

int GetElem(SqList L,int i,ElemType &e){
	if(i<1||i>L.length)
	  return ERROR;
	e = *(L.elem+i-1);
	return OK;
}


int LocateElem_Sq(SqList L,ElemType e){
	ElemType *p = L.elem,*p_last = L.elem + L.length -1;
	while(p<=p_last&&*p!=e) p++;
	if(*p!=e)
	  return FALSE;
	return p-L.elem+1;
}

void MergeList_Sq(SqList La,SqList Lb,SqList &Lc){
	int len_la = La.length,len_lb= Lb.length,len_lc= len_la+len_lb;
	ElemType* pa= La.elem,*pb= Lb.elem;
	Lc.listsize = len_lc;
	Lc.length = len_lc;
	Lc.elem = (ElemType*)malloc (len_lc*sizeof(ElemType));
	if(!Lc.elem)
	  exit(OVERFLOW);
	ElemType *pa_last = pa+len_la-1,*pb_last = pb+len_lb-1,*pc=Lc.elem;
	while(pa<=pa_last&&pb<=pb_last){
		if(*pa<*pb)
		 *pc++=*pa++;
		else
		 *pc++=*pb++;
	}
	while(pa<=pa_last)
		 *pc++=*pa++;
	while(pb<=pb_last)
		 *pc++=*pb++;
	return ;
}

Status ListTraverse(SqList La,Status(*visit)(ElemType)){
	for(int i = 0;i<La.length;i++)
	  visit(*(La.elem+i));
	return OK;
}

Status visit(ElemType e){
	printf("%d\n",e);
	return OK;
}

Status CreateList_Sq(SqList &L,int n){
	L.elem = (ElemType*)malloc(sizeof(ElemType)*n);
	if(!L.elem)
	  exit(OVERFLOW);
	L.length = n;
	L.listsize = LIST_INIT_SIZE;
	while(n>L.length){
		L.elem = (ElemType*)realloc(L.elem,sizeof(ElemType)*(L.length+LISTINCREMENT));
		if(!L.elem)
		  exit(OVERFLOW);
		L.listsize += LISTINCREMENT;
	}
	for(int i = 0;i<n;i++)
	  scanf("%d",L.elem+i);
	return OK;
}

Status OrderInsert_Sq(SqList &L,ElemType e){
	if(L.length >=L.listsize){
		L.elem =(ElemType*)realloc(L.elem,sizeof(ElemType)*(L.listsize+LISTINCREMENT));
		if(!L.elem)
		  exit(OVERFLOW);
		L.listsize += LISTINCREMENT;
	}
	ElemType* p = L.elem,*p_last = L.elem+L.length-1;
	while(*p<e&&p<=p_last)
	  p++;
	ElemType*q = p_last;
	while(q>=p){
	  *(q+1)=*q;
	  q--;
	}
	*p = e;
	L.length ++;
	return OK;
}

Status Union(SqList la,SqList lb,SqList &lc){
	int len_la = la.length,len_lb = lb.length;
	lc.elem= (ElemType*)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
	if(!lc.elem)
	  exit(OVERFLOW);
	ElemType* pa = la.elem ,* pb = lb.elem ,*pc = lc.elem,* pa_last = la.elem +len_la -1, *pb_last = lb.elem + len_lb-1;
	lc.length = len_la;
	while(pa<= pa_last)
	  *pc++=*pa++;
	while(pb<= pb_last){
		if(!LocateElem_Sq(la,*pb)){
		  *pc++=*pb ;
			lc.length ++; 
		}
		pb ++;
	}
	return OK;
}
int main()
{
    SqList L,La,Lb,Lc,Ld,Le,SetA,SetB,SetC;
	ElemType temp;
	printf("TEST START\n");
	InitList_SqList(L);
	ListInsert_sq(L,1,1);
	ListInsert_sq(L,2,2);
	ListDelete_sq(L,2);
	ListInsert_sq(L,2,114514);

	GetElem(L,2,temp);
	printf("elem:%d\n",temp);

	GetElem(L,1,temp);
	printf("elem:%d\n",temp);

	ListInsert_sq(L,3,1919810);
	temp = LocateElem_Sq(L,1919810);
	printf("location:%d\n",temp);

	InitList_SqList(La);
	InitList_SqList(Lb);
	ListInsert_sq(La,1,1);
	ListInsert_sq(Lb,1,2);

	ListInsert_sq(La,2,3);
	ListInsert_sq(Lb,2,4);

	ListInsert_sq(La,3,5);
	ListInsert_sq(Lb,3,6);

	ListInsert_sq(La,4,99);
	ListInsert_sq(Lb,4,99);

	MergeList_Sq(La,Lb,Lc);
	printf("merge and traverse:\n");
	printf("first merged list\n");
	ListTraverse(La,visit);
	printf("second merged list\n");
	ListTraverse(Lb,visit);
	printf("merged list\n");
	ListTraverse(Lc,visit);
	
	printf("input 10 numbers\n");
	CreateList_Sq(Ld,10);
	ListTraverse(Ld,visit);	
	
	InitList_SqList(Le);
	ListInsert_sq(Le,1,10);
	ListInsert_sq(Le,2,20);
	ListInsert_sq(Le,3,30);
	ListInsert_sq(Le,4,40);
	ListInsert_sq(Le,5,50);
	ListInsert_sq(Le,6,60);
	ListInsert_sq(Le,7,70);
	printf("order list to be inserted\n");
	ListTraverse(Le,visit);
	OrderInsert_Sq(Le,55);
	printf("order list after inserted\n");
	ListTraverse(Le,visit);

	printf("first set to be unioned\n");
	InitList_SqList(SetA);
	ListInsert_sq(SetA,1,4);
	ListInsert_sq(SetA,2,345);
	ListInsert_sq(SetA,3,4543);
	ListInsert_sq(SetA,4,45);
	ListInsert_sq(SetA,5,23);
	ListTraverse(SetA,visit);
	
	printf("second set to be unioned\n");
	InitList_SqList(SetB);
	ListInsert_sq(SetB,1,4);
	ListInsert_sq(SetB,2,34);
	ListInsert_sq(SetB,3,453);
	ListInsert_sq(SetB,4,345);
	ListInsert_sq(SetB,5,23);
	ListTraverse(SetB,visit);
	
	printf("unioned set\n");
	Union(SetA,SetB,SetC);
	ListTraverse(SetC,visit);
	return 0;
}

