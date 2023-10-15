#include<stdio.h>
#include<malloc.h>

#define LIST_SIZE 1000
#define OVERFLOW -2
#define OK 1
#define ERROR 0
#define LISTINCREMENT 10

typedef int ElemType,Status;
typedef struct{
	ElemType elem[LIST_SIZE];
	int listsize;
	int length;
}num;
num sum,temp;

Status CreateNum(num &L,int num){
	L.length = 0;
	L.listsize = LIST_SIZE;
	if(num<10)
	L.elem[L.length++]=num;
	if(num>=10){
		L.length =2;
		L.elem[0]=num-10;
		L.elem[1]=1;
	}
	return OK;
}
Status PrintNum(num La,Status(*visit)(ElemType)){
	for(int i =La.length-1;i>=0;i--)
	  visit(La.elem[i]);
	printf("\n");
	return OK;
}
Status visit(ElemType e){
	printf("%d",e);
	return OK;
}
Status Add(num src,num &dst){
	int i = 0;
	int remainder=0;
	//printf("%d %d\n",src.length,dst.length);
//printf("ADD:");
//PrintNum(src,visit);
//PrintNum(dst,visit);

	while(i<dst.length){
		dst.elem[i]+=remainder;
		if(i<src.length)
		  dst.elem[i]+=src.elem[i];
		remainder= dst.elem[i]/10;
		dst.elem[i]%=10;
		//printf("remainder:%d dst.elem[i]:%d\n",remainder,dst.elem[i]);
		i++;
	}
	while(i<src.length||remainder){
		dst.elem[dst.length++]=remainder;
		if(i<src.length)
		  dst.elem[i]+=src.elem[i];
		remainder=dst.elem[i]/10;
		dst.elem[i]%=10;
		//printf("###remainder:%d,dst.elem[i]:%d\n",remainder,dst.elem[i]);
		i++;
	}
	return OK;
}
Status Multi(int c,num &operand){
	if(c>=10){
		//printf("multi%d",c);
		num temp;
		CreateNum(temp,0);
		Add(operand,temp);
		for(int i =operand.length-1;i>=0;i--)
			operand.elem[i+1]=operand.elem[i];
		operand.length++;
		operand.elem[0]=0;
		Multi(c-10,temp);
		Add(temp,operand);
	}
	else{
		//printf("multi%d",c);
		int remainder=0;
		for(int i =0;i<operand.length;i++){
			operand.elem[i]*=c;
			operand.elem[i]+=remainder;
			remainder= operand.elem[i]/10;
			operand.elem[i]%=10;
		}
		if(remainder)
		  operand.elem[operand.length++]=remainder;
	}
	return OK;
}


int main()
{
	int N,A;
	while(scanf("%d%d",&N,&A)==2){
		if(A==0){
		  printf("0\n");
			continue;
		}
		CreateNum(sum,0);
		for(int i =1;i<=N;i++){
			CreateNum(temp,i);	
			for(int j =1;j<=i;j++)
			  Multi(A,temp);
		//	printf("%d Add:",i);
		//	PrintNum(temp,visit);
			Add(temp,sum);
	//		printf("%d Sum:",i);
	//		PrintNum(sum,visit);
		}
		PrintNum(sum,visit);
	}
	return 0;
}
