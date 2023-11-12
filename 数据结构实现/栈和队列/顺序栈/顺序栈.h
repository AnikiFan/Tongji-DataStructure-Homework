#include<stdio.h>
#include<process.h>
#include<malloc.h>

#define INIT_STACK_SIZE 100
#define STACK_SIZE_INCREMENT 100

typedef int Status,ElemType;
typedef struct{
	ElemType* top;
	ElemType* base;
	int stacksize;
}SqStack;

Status InitStack(SqStack &S);
Status GetTop(SqStack S,ElemType &e);
Status Push(SqStack &S,ElemType e);
Status Pop(SqStack &S,ElemType &e);

