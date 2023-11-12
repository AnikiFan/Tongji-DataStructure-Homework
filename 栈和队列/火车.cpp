#include<stdio.h>
#include<malloc.h>

#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
#define INIT_STACK_SIZE 100
#define STACK_SIZE_INCREMENT 100
#define LIST_INIT_SIZE 100
#define OVERFLOW -2
char in [LIST_INIT_SIZE];
char out[LIST_INIT_SIZE];
typedef char ElemType;
typedef int Status;
typedef struct{
	ElemType* top;
	ElemType* base;
	int stacksize;
}SqStack;
SqStack station;//用于模拟进栈

Status InitStack(SqStack &S)
{
	S.base = (ElemType*)malloc(sizeof(ElemType)*INIT_STACK_SIZE);
	if(!S.base)
	  return OVERFLOW;
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
		  return OVERFLOW;
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
Status StackEmpty(SqStack S)
{
	return S.top ==S.base;
}
Status EmptyStack(SqStack &S)
{
	S.top = S.base;
	S.stacksize =0;
	return OK;
}
//思路，按照进站队列模拟进栈，每进一个，消除掉最长的一个出站子序列
//出栈序列无需存储，只需顺序读取
//进栈队列需要存储，存储时顺序读取，用顺序表存储
//成功的标志是当进栈队列读取完毕后，模拟栈为空
//遇到的问题是循环时忘记重置了，根据结果推断出来的
int main()
{
	InitStack(station);
	scanf("%s",&in);
	
//	printf("%s\n",in);

	while(scanf("%s",&out)==1&&out[0]){
	int i =0,j=0;
	char temp;
	EmptyStack(station);
		//printf("%s\n",out);
		while(in[i]!='\0'){
			Push(station,in[i]);
			temp = in[i];
			while(out[j] == temp){
				Pop(station,temp);
			 GetTop(station,temp);
				j++;
			}
			i++;
		}
		if(StackEmpty(station))
		  printf("yes\n");
		else
		  printf("no\n");
	}
	return 0;
}
