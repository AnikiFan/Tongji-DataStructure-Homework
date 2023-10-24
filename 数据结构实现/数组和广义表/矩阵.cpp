#include<stdio.h>
#include<stdarg.h>
#include<malloc.h>
#define MAX_ARRAY_DIM 8
#define OK 1
#define ERROR 0
#define OVERFLOW {printf("\n\nOVERFLOW\n\n");  return -2; }

typedef int ElemType;
typedef int Status;
typedef struct{
	ElemType *base;
	int dim;
	int *bounds;
	int *constants;
}Array;

Status InitArray(Array& A,int dim,int bound,...)
{
	if(dim <0||dim>MAX_ARRAY_DIM)
	  return ERROR;
	printf("Init Array with dim %d\n",dim);
	A.bounds = (int *)malloc(sizeof(int)*(dim));
	if(!A.bounds)
	  OVERFLOW;
	va_list valist;
	va_start(valist,bound);
	int size=bound,temp;
	if(bound<=0)
	  return ERROR;
	A.bounds[0]=bound;
	printf("bound0:%d\n",bound);
	for(int i =2;i<=dim;i++){
		temp =va_arg(valist,int);
		printf("bound%d:%d\n",i-1,temp);
		if(temp <= 0)
		  return ERROR;
		A.bounds[i-1]= temp;
		size *= temp;
	}
	va_end(valist);
	A.base = (ElemType *)calloc(sizeof(ElemType),size);
	printf("alloc size:%d\n",size);
	if(!A.base)
	  OVERFLOW;
	A.constants = NULL;
	A.dim = dim;
	return OK;
}
Status DestroyArray(Array &A)
{
	if(A.base)
	free(A.base);
	if(A.constants)
	free(A.bounds);
	if(A.constants)
	  free(A.constants);
	 A.dim = 0;
	return OK;
}
Status Value(Array A,ElemType &e,int index,...)
{
	int size = A.bounds[0],dim=0,incre;
	ElemType *p=A.base;
	va_list index_list;
	va_start(index_list,index);
	if(index <0||index>A.bounds[0]-1)
	  return ERROR;
	p+= index;
	for(int i = 2;i<= A.dim;i++){
		incre = 1;
		for(int j = 0;j<=i-2;j++)
		  incre *= A.bounds[j];
		incre *= *index_list;
		va_arg(index_list,int);
		p += incre;
	}
	printf("Value loc:%d,Value num:%d\n",p-A.base,*p);
	e= *p;
	return OK;
}
Status Assign(Array A,ElemType e,int index,...)
{
	int size = A.bounds[0],dim=0,incre;
	ElemType *p=A.base;
	va_list index_list;
	va_start(index_list,index);
	if(index <0||index>A.bounds[0]-1)
	  return ERROR;
	p+= index;
	for(int i = 2;i<= A.dim;i++){
		incre = 1;
		for(int j = 0;j<=i-2;j++)
		  incre *= A.bounds[j];
		incre *= *index_list;
		va_arg(index_list,int);
		p += incre;
	}
	printf("Assign loc:%d,Assign num:%d\n",p-A.base,e);
	*p= e;
	return OK;
}
Status TraverseArray(Array A)
{
	int size = 1;
	int *temp = (int*)malloc(sizeof(int)*A.dim);
	if(!size)
	  OVERFLOW
	temp[0]=A.bounds[0];
	printf("size[0]:%d\n",temp[0]);
	for(int i = 2;i<= A.dim;i++){
		temp[i-1]=temp[i-2]*A.bounds[i-1];
		printf("temp[%d]:%d\n",i-1,temp[i-1]);
	}
	for(int i =0;i<A.dim;i++)
	  size *= A.bounds[i];
	for(int i = 0;i<size;i++){
	  printf("%d ",A.base[i]);
	  for(int j = 0;j<A.dim;j++)
		if(!((i+1)%temp[j]))
		  putchar('\n');
	}
	printf("\n");
	free(temp);
	return OK;
}
int main()
{
	printf("----TEST BEGIN----\n");
	Array A;
	InitArray(A,4,4,2,3,2);
	Assign(A,1,0,0,0,0);
	Assign(A,1,3,0,0,0);
	Assign(A,1,3,0,1,0);
	Assign(A,1,0,0,1,0);
	TraverseArray(A);
	DestroyArray(A);
	printf("----TEST END----\n");
	return 0;
}
