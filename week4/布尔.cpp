//运用栈来求解表达式
#include<stdio.h>

#define MAX_SIZE 1100
#define OK 1
#define ERROR 0

typedef char ElemType;
typedef int Status;
typedef struct {
	ElemType base[MAX_SIZE];
	int top;
}SqStack;
SqStack Operand;//存储VF
SqStack Opt;//存储其他运算符
char expression[MAX_SIZE];//存储表达式
Status InitStack(SqStack &S)
{
	S.top = 0;
	return OK;
}
Status Push(SqStack &S,ElemType e)
{
	if(S.top==MAX_SIZE)
	  return ERROR;
	S.base[S.top++]=e;
	return OK;
}
Status Pop(SqStack &S,ElemType &e)
{
	if(!S.top)
	  return ERROR;
	e = S.base[--S.top];
	return OK;
}
Status  GetTop(SqStack S,ElemType &e)
{
	if(!S.top)
	  return ERROR;
	e = S.base[S.top-1];
	return OK;
}
Status StackEmpty(SqStack S)
{
	return !S.top;
}
char compare(char c1,char c2){
	switch(c1){
		case '|':
			if(c2=='|')
			  return '>';
			else if(c2=='&')
			  return '<';
			else if(c2=='!')
			  return '<';
			else if(c2=='(')
			  return '>';
			else if(c2==')')
			  return '>';
			break;
		case '&':
			if(c2=='|')
			  return '>';
			else if(c2=='&')
			  return '>';
			else if(c2=='!')
			  return '<';
			else if(c2=='(')
			  return '>';
			else if(c2==')')
			  return '>';
			break;
		case '!':
			if(c2=='|')
			  return '>';
			else if(c2=='&')
			  return '>';
			else if(c2=='!')
			  return '>';
			else if(c2=='(')
			  return '>';
			else if(c2==')')
			  return '>';
			break;
		case '(':
			if(c2=='|')
			  return '<';
			else if(c2=='&')
			  return '<';
			else if(c2=='!')
			  return '<';
			else if(c2=='(')
			  return '>';
			else if(c2==')')
			  return '<';
			break;
		case ')':
			if(c2=='|')
			  return '>';
			else if(c2=='&')
			  return '>';
			else if(c2=='!')
			  return '>';
			else if(c2=='(')
			  return '>';
			else if(c2==')')
			  return '<';
			break;
	}
	return '>';
}
void calc(SqStack &Operand,SqStack &Opt)
{
	bool a,b,ans;
	char c1,c2,opt;
	Pop(Operand,c1);
	Pop(Opt,opt);
	if(opt == '!'){
		if(c1=='V')
		  Push(Operand,'F');
		else 
		  Push(Operand,'V');
		return;
	}
	Pop(Operand,c2);
	if(c1=='V')
	  a =1;
	else 
	  a=0;
	if(c2=='V')
	  b =1;
	else 
	  b=0;
	switch(opt){
		case '|':
			ans = a||b;
		case '&':
			ans = a&&b;
	}	
	if(ans)
	  Push(Operand,'V');
	else
	  Push(Operand,'F');
	return;
}
int main()
{
	InitStack(Operand);
	InitStack(Opt);
	int n =0;
	while(scanf("%s",&expression)&&expression[0]){

		printf("%d %d",Operand.top,Opt.top);

		int i =0;
		char temp;
		while(expression[i]){

			char test1, test2;
			GetTop(Operand,test1);
			GetTop(Opt,test2);

			printf("%c %c\n",test1,test2);


			if(expression[i]==' ')//过滤空格
			  continue;
			if(expression[i]=='V'||expression[i]=='F')
			  Push(Operand ,expression[i]);
			else{
				if(!StackEmpty(Opt)){
					GetTop(Opt,temp);
					while(compare(expression[i],temp)=='<'){
					  calc(Operand,Opt);
					  printf("calc\n");
					}
					if(expression[i]==')'){
						Pop(Opt,temp);
						printf("pop )\n");
						i++;
						continue;
					}
				}
				Push(Opt,expression[i]);
				printf("push %c\n",expression[i]);
			}
			i++;
		}
		if(!StackEmpty(Opt));
		calc(Operand,Opt);
		Pop(Operand,temp);
		printf("Expression %d: %c\n",++n,temp);
	}
	return 0;
}
