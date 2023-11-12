#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<queue>
#define MAXN 100010
typedef struct{
	int val;//1代表还未被感染
	int lchild;
	int rchild;
	int parent;
}Node;
typedef Node Tree[MAXN];
Tree T;
int main()
{
	int n,start,count =0,temp;
	scanf("%d%d",&n,&start);
	for(int i =0;i<n;i++){
		T[i].val = 1;
		scanf("%d%d",&T[i].lchild,&T[i].rchild);
		T[T[i].lchild].parent= i;
		T[T[i].rchild].parent= i;
	}
	T[start].val = 0;
	T[0].parent = -1;
	std::queue<int>q,p;
	q.push(start);
	while(1){
		//printf("count:%d\n",count);
		while(!q.empty()){
		temp = q.front();	
		q.pop();
		if(T[temp].parent!=-1&&T[T[temp].parent].val){
			p.push(T[temp].parent);
			T[T[temp].parent].val= 0;
			//printf("get %d\n",T[temp].parent);
		}
		if(T[temp].lchild!=-1&&T[T[temp].lchild].val){
			p.push(T[temp].lchild);
			T[T[temp].lchild].val= 0;
			//printf("get %d\n",T[temp].lchild);
		}
		if(T[temp].rchild!=-1&&T[T[temp].rchild].val){
			p.push(T[temp].rchild);
			T[T[temp].rchild].val= 0;
			//printf("get %d\n",T[temp].rchild);
		}
		}
			//printf("ready to get:");
		while(!p.empty()){
			q.push(p.front());
			p.pop();
			//printf("%d",q.back());	
		}
		//printf("\n");
		if(q.empty())
		  break;
		count++;
	}
	printf("%d",count);
	return 0;
}
