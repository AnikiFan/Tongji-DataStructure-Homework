#define _CRT_SECURE_NO_WARNINGS
#define INFO_MAX_LENGTH 110
#define OPT_MAX_LENGTH 10
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define LIST_INIT_SIZE 20000
#define LISTINCREMENT 10

#include<malloc.h>
#include<stdio.h>
#include<string.h>

typedef int Status;
typedef struct{
	char no[INFO_MAX_LENGTH];
	char name[INFO_MAX_LENGTH];
} ElemType;
typedef struct{
	ElemType *elem;
	int length;//current length
	int listsize;//current allocated size
}SqList;
SqList L;
char opt[OPT_MAX_LENGTH];

void ListInsert_sq(SqList &L,int i,ElemType e){
	ElemType *q,*p;
	if(i<1||i>L.length+1) {
		printf("-1\n");
		return;
	}
	//printf("%d %s %s\n",i,e.no,e.name);
	if(L.length>=L.listsize){
		ElemType * newbase;
		newbase = (ElemType*)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
		if(!newbase)
		  return ;
		L.elem = newbase;
		L.listsize += LISTINCREMENT;
	}
	q = L.elem+i-1;
	for(p=L.elem+L.length-1;p>=q;--p)
	  *(p+1)=*p;
	*q = e;
	++L.length;
	printf("0\n");
	return;
}

void ListDelete_sq(SqList & L,int i){
	if(i<1||i>L.length){
		printf("-1\n");
		return;
	}
	ElemType *p = L.elem+i-1;
	//printf("%d %s %s\n",i,p->no,p->name);
	for(;p<L.elem+L.length ;p++)
	  *p=*(p+1);
	L.length --;
	printf("0\n");
	return;
}
void LocateElem_By_No(SqList L,char No[]){
	ElemType *p = L.elem,*p_last = L.elem + L.length -1;
	while(p<=p_last&&strcmp(No,p->no)) p++;
	if(strcmp(No,p->no)){
	  printf("-1\n");
	  return;
	}
	printf("%lld %s %s\n",p-L.elem+1,p->no,p->name);
	return;
}
void LocateElem_By_Name(SqList L,char Name[]){
	ElemType *p = L.elem,*p_last = L.elem + L.length -1;
	while(p<=p_last&&strcmp(Name,p->name)) p++;
	if(strcmp(Name,p->name)){
		printf("-1\n");
		return;
	}
	printf("%lld %s %s\n",p-L.elem+1,p->no,p->name);
	return;
}
Status CreateList_Sq(SqList &L,int n){
	L.elem = (ElemType*)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
	if(!L.elem)
	  return OVERFLOW;
	L.listsize = LIST_INIT_SIZE;
	while(n>LIST_INIT_SIZE){
		L.elem = (ElemType*)realloc(L.elem,sizeof(ElemType)*(L.length+LISTINCREMENT));
		if(!L.elem)
		  return  OVERFLOW;
		L.listsize += LISTINCREMENT;
	}
	L.length = n;
	for(int i =0;i<n;i++){
		ElemType in;
		scanf("%s%s",in.no,in.name);
		L.elem[i]=in;
		//printf("get %s %s\n",in.no,in.name);
	}
	return OK;
}
int main()
{
	int n ;
	scanf("%d",&n);
	CreateList_Sq(L,n);
	while(scanf("%s",opt)==1&&strcmp(opt,"end")){
		if(!strcmp(opt,"insert")){
			int pos;
			ElemType info;
			scanf("%d%s%s",&pos,info.no,info.name);
			ListInsert_sq(L,pos,info);
		}
		else if(!strcmp(opt,"remove")){
			int pos;
			scanf("%d",&pos);
			ListDelete_sq(L,pos);
		}
		else if(!strcmp(opt,"check")){
			scanf("%s",opt);
			if(!strcmp(opt,"name")){
				scanf("%s",opt);
				LocateElem_By_Name(L,opt);
			}
			else if(!strcmp(opt,"no")){
				scanf("%s",opt);
				LocateElem_By_No(L,opt);
			}
		}
	}
	printf("%d",L.length);
	return 0;
}
