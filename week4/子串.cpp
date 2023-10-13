#include<stdio.h>

#define MAX_SIZE 100000
#define OK 1
#define ERROR 0

typedef int ElemType;
typedef int Status;
typedef struct {
	ElemType base[MAX_SIZE];
	int top;
}SqStack;
SqStack index;
int maxlen=0,maxpos=0;
int len[MAX_SIZE]={0};
Status InitStack(SqStack &S)
{
	S.top = 0;
	return OK;
}
Status Pop(SqStack &S,ElemType &e)
{
	if(!S.top)
	  return ERROR;
	e = S.base[--S.top];
	return OK;
}
Status Push(SqStack &S,ElemType e)
{
	if(S.top==MAX_SIZE)
	  return ERROR;
	S.base[S.top++]=e;
	return OK;
}
Status StackEmpty(SqStack S)
{
	return S.top ==0;
}
//思路：
//顺序读取字符串，把如果是（把位序的值压入栈，如果是），弹出一个栈中的值，计算差值，最后取最大值
//如果读取）时，则无视发生
int main()
{
	int n =0;
	int tempindex;
	char temp = getchar();
	InitStack(index);
	while(temp !='\r'&&temp !='\n'&&temp !=EOF){
		if(temp == '(')
		  Push(index,n);
		if(temp ==')'&&!StackEmpty(index)){
			Pop(index,tempindex);
			len[n]= n-tempindex+1+len[tempindex-1];
			if(len[n]>maxlen){
				maxlen = len[n];
				maxpos =n-len[n]+1;
			}
		}
		temp = getchar();
		n++;
	}
	printf("%d %d",maxlen,maxpos);
	return 0;
}
