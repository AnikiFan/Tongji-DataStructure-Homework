#include<stdio.h>

#define MAX_SIZE 100
#define OK 1
#define ERROR 0

typedef int Status,ElemType;
typedef struct {
	ElemType base[MAX_SIZE];
	int top;
}SqStack;
Status InitStack(SqStack &S)
{
	S.top = 0;
	return OK;
}
Status Push(SqStack &S,ElemType e)
{
	if(S.top==MAX_SIZE)
	  return ERROR;
	S.base[S.top++]=e;
	return OK;
}
Status Pop(SqStack &S,ElemType &e)
{
	if(!S.top)
	  return ERROR;
	e = S.base[--S.top];
	return OK;
}
Status  GetTop(SqStack S,ElemType &e)
{
	if(!S.top)
	  return ERROR;
	e = S.base[S.top-1];
	return OK;
}
int main()
{
	SqStack S;
	ElemType temp;
	InitStack(S);
	printf("----TEST BEGIN----\n");
	printf("TEST FOR PUSH , POP AND GETTOP\n");
	Push(S,1);
	Push(S,114514);
	Pop(S,temp);
	printf("%d\n",temp);
	GetTop(S,temp);
	printf("%d\n",temp);
	return 0;
}
