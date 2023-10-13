#include<stdio.h>
#include<malloc.h>

#define MAX_SIZE 100
#define OK 1
#define OVERFLOW -2
#define ERROR 0

typedef int ElemType,Status;
typedef struct{
ElemType*	base;
int  front;
int  rear;
} SqQueue;

Status InitQueue(SqQueue &Q)
{
	Q.base = (ElemType*)malloc(sizeof(ElemType)*MAX_SIZE);
	if(!Q.base)
	  return OVERFLOW;
	Q.front = Q.rear = 0;
	return OK;
}

int QueueLength(SqQueue Q)
{
	return (-Q.front + Q.rear+MAX_SIZE)%MAX_SIZE;
}

Status EnQueue(SqQueue &Q,ElemType e)
{
	if((Q.rear +1)%MAX_SIZE==Q.front)
	  return ERROR;
	Q.base[Q.rear++]= e;
	Q.rear %= MAX_SIZE;
	return OK;
}

Status DeQueue(SqQueue&Q,ElemType &e)
{
	if(Q.rear == Q.front)
	  return ERROR;
	e = Q.base[Q.front++];
	Q.front %= MAX_SIZE;
	return 0;
}

Status QueueEmpty(SqQueue Q)
{
	return Q.front == Q.rear;
}

Status GetHead(SqQueue Q ,ElemType &e)
{
	if(Q.rear == Q.front)
	  return ERROR;
	e = Q.base[Q.front];
	return OK;
}
int main()
{
	printf("----TEST BEGIN----\n");
	SqQueue Q;
	ElemType temp;
	printf("----TEST FOR GETLENGTH,QUEUEEMPTY,ENQUEUE AND DEQUEUE, GETHEAD----\n");
	InitQueue(Q);
	printf("Empty:%d\n",QueueEmpty(Q));
	printf("Length:%d\n",QueueLength(Q));
	EnQueue(Q,1);
	printf("Length:%d\n",QueueLength(Q));
	EnQueue(Q,114514);
	GetHead(Q,temp);
	printf("Head:%d\n",temp);
	EnQueue(Q,114);
	printf("Length:%d\n",QueueLength(Q));
	DeQueue(Q,temp);
	printf("Length:%d\n",QueueLength(Q));
	GetHead(Q,temp);
	printf("Head:%d\n",temp);
	printf("Empty:%d\n",QueueEmpty(Q));
	printf("----TEST END----\n");
	return 0;
}

