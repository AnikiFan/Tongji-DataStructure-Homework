#define _CRT_SECURE_NO_WARNINGS
#define MAXN 11000
#define OK 1
#define ERROR 0
#define MAXINFOLENGTH 30
#include<stdio.h>
#include<cstdlib>
typedef int Status;
typedef struct{
	char data;
	int lchild;
	int rchild;
}ElemType;
typedef struct{
	ElemType elem[MAXN];
	int root;
} Tree;
Status CreateTree(Tree &T)
{
	int n;
	char temp[MAXINFOLENGTH]; 
	int mark[MAXN]={0};
	scanf("%d",&n);
	getchar();
	for(int i =0;i<n;i++){
		scanf("%s",temp);
		T.elem[i].data = temp[0];
		scanf("%s",temp);
		if(temp[0]=='-')
		  T.elem[i].lchild = -1;
		else {
		  T.elem[i].lchild = atoi(temp);
			mark[T.elem[i].lchild]=1;
		}
		scanf("%s",temp);
		if(temp[0]=='-')
		  T.elem[i].rchild = -1;
		else {
		  T.elem[i].rchild = atoi(temp);
		mark[T.elem[i].rchild]=1;
		}
	}
	for(int i = 0;i<n;i++)
	  if(!mark[i]){
		  T.root = i;
		  return OK;
	  }
	return ERROR;
}
int Depth(Tree T,int root)
{
	if(root==-1)
	  return 0;
	else 
	  return Depth(T,T.elem[root].lchild)>Depth(T,T.elem[root].rchild)?Depth(T,T.elem[root].lchild)+1:Depth(T,T.elem[root].rchild)+1;
}
Status valid(Tree T1,int root1,Tree T2,int root2)
{
	if(root1 == -1 && root2 == -1)
	  return OK;
	else if(root1 == -1&& root2!=-1||root1 !=-1&&root2==-1)
	  return ERROR;
	else if(T1.elem[root1].data!= T2.elem[root2].data)
	  return ERROR;
	else if(T1.elem[root1].lchild ==-1&&T2.elem[root2].lchild==-1)
	  return valid(T1,T1.elem[root1].rchild,T2,T2.elem[root2].rchild);
	if (T1.elem[T1.elem[root1].lchild].data==T2.elem[T2.elem[root2].lchild].data)
		 return valid(T1,T1.elem[root1].rchild,T2,T2.elem[root2].rchild);
	else 
		return valid(T1,T1.elem[root1].lchild,T2,T2.elem[root2].rchild)&&valid(T1,T1.elem[root1].rchild,T2,T2.elem[root2].lchild);
}

int main()
{
	Tree T1,T2;
	CreateTree(T1);
	CreateTree(T2);
	if(valid(T1,T1.root,T2,T2.root))
	  printf("Yes\n");
	else 
	  printf("No\n");
	printf("%d\n",Depth(T1,T1.root));
	printf("%d\n",Depth(T2,T2.root));
	return 0;
}
