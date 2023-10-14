#define _CRT_SECURE_NO_WARNINGS
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define LIST_INIT_SIZE 100010
#define LISTINCREMENT 10

#include<malloc.h>
#include<stdio.h>

typedef int Status;
typedef int ElemType;
typedef struct{
	ElemType *elem;
	int length;//current length
	int listsize;//current allocated size
}SqList;
SqList ans;

Status InitList_SqList(SqList &L,int n){//初始化一个特定长度的零顺序表
	L.elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!L.elem) 
	 return OVERFLOW;
	L.length = n;
	for(int i =0;i<n;i++)
	  L.elem[i]=0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}
Status ListWrite_sq(SqList &L,int i,ElemType e){
	ElemType *q,*p;
	if(i<1||i>L.length+1) 
	  return ERROR;
	if(L.length>=L.listsize&&i==L.length+1){
		ElemType * newbase;
		newbase = (ElemType*)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
		if(!newbase)
		  return OVERFLOW;
		L.elem = newbase;
		L.listsize += LISTINCREMENT;
	}
	q = L.elem+i-1;
	*q = e;
	if(i==L.length+1)
	  L.length++;
	return OK;
}
int GetElem(SqList L,int i,ElemType &e){
	if(i<1||i>L.length)
	  return ERROR;
	e = *(L.elem+i-1);
	return OK;
}
int main()
{
		int n,k,temp;
		scanf("%d%d",&n,&k);
		InitList_SqList(ans,n);
		for(int i = 0;i<n;i++){
			scanf("%d",&temp);
		  ListWrite_sq(ans,(i+k)%n+1,temp);
		}
		for(int i =0;i<n;i++){
			GetElem(ans,i+1,temp);
			printf("%d ",temp);
		}
		return 0;
}
