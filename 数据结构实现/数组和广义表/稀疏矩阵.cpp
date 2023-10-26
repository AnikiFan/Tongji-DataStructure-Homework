#include<stdio.h>
#include<malloc.h>

#define MAXSIZE 12500
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW {printf("\n\nOVERFLOW\n\n"); return -2;}

typedef int ElemType;
typedef int Status;
typedef struct{
	int i,j;
	ElemType e;
}Triple;
typedef struct{
	Triple data[MAXSIZE+1];//data[0]未用
	int mu,nu,tu;//行数，列数，非零元个数
}TSMatrix;

Status InitMatrix(TSMatrix &M,int mu,int nu,int tu)
{
	if(tu <1||tu>MAXSIZE||mu<1||nu<1)	
	  return ERROR;
	M.mu = mu;
	M.nu=nu;
	M.tu = tu;
	for(int i = 1;i<=tu;i++){
		scanf("%d%d%d",&(M.data[i].i),&(M.data[i].j),&(M.data[i].e));
		if(M.data[i].i<0||M.data[i].i>=M.mu||M.data[i].j<0||M.data[i].j>=M.nu)
		  return ERROR;
	}
	return OK;
}
Status TraverseMatrix(TSMatrix M)
{
	printf("\n----BEGIN TRAVERSE----\n");
	for(int i = 1;i<= M.tu;i++)
	  printf("#%d[%d][%d]:%d\n",i,M.data[i].i,M.data[i].j,M.data[i].e);
	printf("----END TRAVERSE----\n");
	return OK;
}
int SortByRow(Triple A,Triple B)
{
	if(A.i<B.i||(A.i==B.i&&A.j<B.j))
	  return TRUE;
	else
	  return FALSE;
}
int SortByCol(Triple A,Triple B)
{
	if(A.j<B.j||(A.j==B.j&&A.i<B.i))
	  return TRUE;
	else
	  return FALSE;

}
Status  SortMatrix(TSMatrix &M,int (*compare)(Triple A,Triple B))
{
	for(int i= 1;i<= M.tu-1;i++){
		int k = i,j;
		for(j = i+1;j<=M.tu;j++)
		  if(compare(M.data[j],M.data[k]))
			k = j;
		if(k != i){
			Triple temp = M.data[k];
			M.data[k]= M.data[i];
			M.data[i]= temp;
		}
	}
	return OK;
}
Status Permutation(TSMatrix &M)
{
	SortMatrix(M,SortByCol);
	int temp;
	for(int i = 1;i<= M.tu;i++){
		temp = M.data[i].i;
		M.data[i].i=M.data[i].j;
		M.data[i].j=temp;
	}
	return OK;
}
Status FastPermutation(TSMatrix M,TSMatrix &T)
{
	int * num = (int *)calloc(sizeof(int),M.nu),* cpot = (int *)calloc(sizeof(int),M.nu),temp;
	T.mu = M.mu;
	T.nu= M.nu;
	T.tu = M.tu;
	if(!num||!cpot)
	  OVERFLOW
	for(int i = 1;i<= M.tu;i++)
		num[M.data[i].j]++;
	cpot[0]=1;
	for(int i = 1;i< M.nu;i++)
	  cpot[i]= cpot[i-1]+num[i-1];
	//for(int i = 1;i<= M.nu;i++)
	 // printf("num[%d]:%d,cpot[%d]:%d\n",i,num[i],i,cpot[i]);
	for(int i =1;i<= M.tu;i++)
		T.data[cpot[M.data[i].j]++]= M.data[i];
	for(int i = 1;i<= M.tu;i++){
		temp = 	T.data[i].i;
		T.data[i].i= T.data[i].j;
		T.data[i].j= temp;
	}
	free(num);
	free(cpot);
	return OK;
}
int main()
{
	printf("----TEST BEGIN----\n");
	TSMatrix M,T;
	InitMatrix(M,10,10,10);
	TraverseMatrix(M);
	SortMatrix(M,SortByRow);
	TraverseMatrix(M);
	Permutation(M);
	TraverseMatrix(M);
	FastPermutation(M,T);
	TraverseMatrix(T);
	printf("----TEST END----\n");
	return 0;
}
