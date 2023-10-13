#include<stdio.h>
#include<malloc.h>

#define OK 1
#define OVERFLOW -2
#define ERROR 0
#define MAX_SIZE 1100

typedef int Status;
typedef struct{
	int i;
	int j;
}ElemType,index;
typedef struct Node{//元素结点
	ElemType data;
	struct Node * next;
}Node,*QueuePtr;
typedef struct {//特殊结点
	QueuePtr front;//队头指针
	QueuePtr rear;//队尾指针
}LinkQueue;

LinkQueue Queue;
int mark[MAX_SIZE][MAX_SIZE]={0};//用于记录是否已被计数
int mat[MAX_SIZE][MAX_SIZE]={0};//用于矩阵
int num=0;
int n,m;

Status InitQueue(LinkQueue &Q)
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(Node));
	if(!Q.front)
	  return OVERFLOW; 
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
	  return OVERFLOW;
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


void Search( index cur,int &valid)
{
	  index next;	
	EnQueue(Queue,cur);
	while(!QueueEmpty(Queue)){
		DeQueue(Queue,cur);
		int i = cur.i;
		int j = cur.j;
		mark[i][j]=1;
		//printf("Mark:{%d %d}\n",i,j);
		if((i!=1&&i!=n)&&(j!=1&&j!=m))
		  valid = 1;
		if(!mark[i+1][j]&&mat[i+1][j]){
			next = {i+1,j};
			EnQueue(Queue,next);
			//printf("Enter:{%d %d}\n",i+1,j);
		}
		if(!mark[i-1][j]&&mat[i-1][j]){
			next = {i-1,j};
			EnQueue(Queue,next);
			//printf("Enter:{%d %d}\n",i-1,j);
		}
		if(!mark[i][j+1]&&mat[i][j+1]){
			next = {i,j+1};
			EnQueue(Queue,next);
			//printf("Enter:{%d %d}\n",i,j+1);
		}

		if(!mark[i][j-1]&&mat[i][j-1]){
			next = {i,j-1};
			EnQueue(Queue,next);
			//printf("Enter:{%d %d}\n",i,j-1);
		}
	}
	return ;
}
//用队列模拟递归，第一个元素进入，相关联的元素再进入，然后第一个元素退出
int main()
{
	scanf("%d%d",&n,&m);
	for(int i =1;i<=n;i++)
	  for(int j = 1;j<=m;j++)
		scanf("%d",&mat[i][j]);
	for(int i = 1;i<=n;i++)
	  for(int j=1;j<=m;j++)
		if(!mark[i][j]&&mat[i][j]){//未被搜索过且为1
			int valid=0;//需要有在中间的元素
			InitQueue(Queue);
			index index{i,j};
			//printf("Search:%d %d\n\n",i,j);
			Search(index,valid);	
			DestroyQueue(Queue);
			//printf("valid:%d\n",valid);
			if(valid)
			  num++;
		}
	printf("%d",num);
	return 0;
}
