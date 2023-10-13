#include<stdio.h>
#include<malloc.h>
#include<process.h>

#define OK 1
#define OVERFLOW -2
#define ERROR 0

typedef int Status,ElemType;
typedef struct Node{//元素结点
	ElemType data;
	struct Node * next;
}Node,*QueuePtr;
typedef struct {//特殊结点
	QueuePtr front;//队头指针
	QueuePtr rear;//队尾指针
}LinkQueue;
Status InitQueue(LinkQueue &Q)
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(Node));
	if(!Q.front)
		exit(OVERFLOW); 
	Q.front ->next = NULL;
	return OK;
}
Status DestroyQueue(LinkQueue &Q)
{
	while(Q.front)
	{
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front=Q.rear;
	}
	return OK;
}
Status EnQueue(LinkQueue&Q,ElemType e)
{
	Q.rear->next =  (Node*) malloc(sizeof(Node));
	if(!Q.rear->next)
	  exit(OVERFLOW);
	Q.rear = Q.rear->next;
	Q.rear->next = NULL;
	Q.rear->data = e;
	return OK;
}
Status DeQueue(LinkQueue&Q,ElemType &e)
{
	if(Q.front == Q.rear)
	  return ERROR;
	Node * temp = Q.front->next;
	Q.front ->next = temp->next;
	if(!temp->next)
	  Q.rear = Q.front;
	e = temp->data;
	free(temp);
	return OK;
}
Status QueueEmpty(LinkQueue Q)
{
	return Q.front == Q.rear;
}
Status GetHead(LinkQueue Q,ElemType &e)
{
	if(Q.front == Q.rear)
	  return ERROR;
	e = Q.front->next->data;
	return OK;
}

int main()
{
	LinkQueue Q;
	ElemType temp;
	printf("====TEST BEGIN====\n");
	printf("====TEST FOR ENQUEUE, DEQUEUE AND GETHEAD\n");
	InitQueue(Q);
	EnQueue(Q,1);
	EnQueue(Q,114514);
	GetHead(Q,temp);
	printf("%d\n",temp);
	DeQueue(Q,temp);
	printf("%d\n",temp);
	GetHead(Q,temp);
	printf("%d\n",temp);
	return 0;
}
