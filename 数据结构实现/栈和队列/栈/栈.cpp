#include<stdio.h>
#include<process.h>

#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
#define OVERFLOW -2

typedef int Status,ElemType
typedef struct{
	ElemType* top;
	ElemType* base;
	int stacksize;
}SqStack;
//Status InitStack(SqStack &S)
//Status GetTop (SqStack S,ElemType &e)
//Status Push(SqStack &S,ElemType e)
//Status Pop(SqStack &S,ElemType &e)

int main()
{
	printf("----TEST BEGIN----\n");
	return 0;
}

