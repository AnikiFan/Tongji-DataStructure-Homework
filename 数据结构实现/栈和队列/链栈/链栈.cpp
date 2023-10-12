#include<stdio.h>
#include<malloc.h>
#include<process.h>
#define ERROR 0
#define OK 1

typedef int Status,ElemType;
typedef struct Node{
	struct Node * next;
	ElemType data;
}Node,*LinkStack;
//因为没有头结点，头指针会改变，需要用引用传参。
Status Pop(LinkStack &S,ElemType &e)
{
	if(!S)
	  return ERROR;
	e = S->data;
	Node* temp = S;
	S = S->next;
	free(temp);
	return OK;
}
Status Push(LinkStack &S,ElemType e)
{
	Node * temp  = S;
	S = (Node*)malloc(sizeof(Node));
	if(!S)
	  exit(OVERFLOW);
	S->data = e;
	S->next = temp;
	return OK;
}
int main()
{
	LinkStack S;
	ElemType temp;
	printf("----TEST BEGIN----\n");
	printf("----TEST FOR POP AND PUSH----\n");
	Push(S,114514);
	Push(S,2);
	Pop(S,temp);
	printf("%d\n",temp);
	Pop(S,temp);
	printf("%d\n",temp);
	return 0;
}
