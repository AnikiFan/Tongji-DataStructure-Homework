#include "顺序栈.h"
int main()
{
	SqStack S;
	ElemType temp;
	InitStack(S);
	printf("----TEST BEGIN----\n");
	printf("----TEST FOR PUSH,POP AND GETTOP\n");
	Push(S,1);
	GetTop(S,temp);
	printf("%d\n",temp);
	Push(S,2);
	GetTop(S,temp);
	printf("%d\n",temp);
	Push(S,114514);
	Pop(S,temp);
	printf("%d\n",temp);
	GetTop(S,temp);
	printf("%d\n",temp);
	printf("\n----TEST END----\n");
	return 0;
}
