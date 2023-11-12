#include "顺序栈.h"
#include"../../header.h"
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

