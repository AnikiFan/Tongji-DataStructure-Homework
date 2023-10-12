#include<stdio.h>
#include<process.h>
#include<malloc.h>

#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
#define INIT_STACK_SIZE 100
#define STACK_SIZE_INCREMENT 100

typedef int Status,ElemType;
typedef struct{
	ElemType* top;
	ElemType* base;
	int stacksize;
}SqStack;
Status InitStack(SqStack &S)
{
	S.base = (ElemType*)malloc(sizeof(ElemType)*INIT_STACK_SIZE);
	if(!S.base)
	  exit(OVERFLOW);
	S.stacksize = INIT_STACK_SIZE;
	S.top = S.base;
	return OK;
}
Status GetTop (SqStack S,ElemType &e)
{
	if(S.top == S.base)
	  return ERROR;
	e = *(S.top -1);
	return OK;
}
Status Push(SqStack &S,ElemType e)
{
	if(S.top-S.base >= S.stacksize){
		S.base = (ElemType*)realloc(S.base,sizeof(ElemType)*(S.stacksize+STACK_SIZE_INCREMENT));
		if(!S.base)
		  exit(OVERFLOW);
		S.top = S.base + S.stacksize;
		S.stacksize += STACK_SIZE_INCREMENT;
	}
	*S.top++=e;
	return OK;
}
Status Pop(SqStack &S,ElemType &e)
{
	if(S.base == S.top)
	  return ERROR;
	e = *--S.top;
	return OK;
}

int main()
{
	SqStack S;
	ElemType temp;
	InitStack(S);
	printf("----TEST BEGIN----\n");
	printf("----TEST FOR PUSH,POP AND GETTOP\n");
	Push(S,1);
	GetTop(S,temp);
	printf("%d/n",temp);
	Push(S,2);
	GetTop(S,temp);
	printf("%d/n",temp);
	Push(S,114514);
	Pop(S,temp);
	printf("%d/n",temp);
	GetTop(S,temp);
	printf("%d/n",temp);
	return 0;
}

