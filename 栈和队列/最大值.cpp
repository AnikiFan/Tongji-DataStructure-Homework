#include<stdio.h>
#include<malloc.h>
#include<string.h>

#define OK 1
#define OVERFLOW -2
#define ERROR 0

typedef long long Status,ElemType;
typedef struct Node{//元素结点
	ElemType data;
	struct Node * next;
}Node,*QueuePtr;
typedef struct {//特殊结点
	ElemType maxdata;
	long long max_size;
	QueuePtr front;//队头指针
	QueuePtr rear;//队尾指针
	long long Length;
}LinkQueue;
LinkQueue Q;
Status InitQueue(LinkQueue &Q,long long max_size)
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(Node));
	if(!Q.front)
		return OVERFLOW; 
	Q.front ->next = NULL;
	Q.max_size = max_size;
	Q.Length = 0;
	return OK;
}
Status EnQueue(LinkQueue&Q,ElemType e)
{
	if(Q.Length>=Q.max_size){
		printf("Queue is Full\n");
	  return ERROR;
	}
	if(Q.front == Q.rear)
	  Q.maxdata = e;
	Q.rear->next =  (Node*) malloc(sizeof(Node));
	if(!Q.rear->next)
		return OVERFLOW;
	Q.Length ++;
	Q.rear = Q.rear->next;
	Q.rear->next = NULL;
	Q.rear->data = e;
	if(e>Q.maxdata)
	  Q.maxdata = e;
	return OK;
}
Status FindMax(LinkQueue&Q)
{
	if(Q.front == Q.rear)
	  return ERROR;
	Node* p = Q.front->next;
	ElemType max = p->data;
	while(p!=Q.rear){
		if(p->data>max)
		  max = p->data;
		p= p->next;
	}
	if(p->data>max)
	  max = p->data;
	Q.maxdata =max;
	return OK;
}
Status DeQueue(LinkQueue&Q,ElemType &e)
{
	if(Q.front == Q.rear){
		printf("Queue is Empty\n");
	  return ERROR;
	}
	Node * temp = Q.front->next;
	Q.front ->next = temp->next;
	if(!temp->next)
	  Q.rear = Q.front;
	e = temp->data;
	printf("%lld\n",e);
	Q.Length--;
	if(e==Q.maxdata)
	  FindMax(Q);
	free(temp);
	return OK;
}
Status TraverseQueue(LinkQueue Q)
{
	if(Q.front == Q.rear)
	  return ERROR;
	Node* p= Q.front->next;	
	while(p!= Q.rear){
	  printf("%lld ",p->data);
		p= p->next;
	}
	printf("%lld\n",p->data);
	return OK;
}
Status Max(LinkQueue Q)
{
	if(Q.front == Q.rear){
		printf("Queue is Empty\n");
	  return ERROR;
	}
	printf("%lld\n",Q.maxdata);
	return OK;
}
int main()
{
	long long n;
	long long temp;
	char opt[20]  ;
	scanf("%lld",&n);
	InitQueue(Q,n);
	while(scanf("%s",opt)==1&&strcmp(opt,"quit")){
		if(!strcmp(opt,"dequeue"))
		  DeQueue(Q,temp);
		else if(!strcmp(opt,"enqueue")){
			scanf("%lld",&temp);
			EnQueue(Q,temp);
		}
		else if(!strcmp(opt,"max"))
		  Max(Q);
	}
	TraverseQueue(Q);	
	return 0;
}
