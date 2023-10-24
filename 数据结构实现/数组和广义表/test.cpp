#include<stdio.h>
#include<stdarg.h>
void f(int n,...)
{
	int i ;
	va_list valist;
	va_start (valist,n);
	printf("%d\n",n);
	printf("%d\n",*valist);
	va_arg(valist,int);
	printf("%d\n",*valist);
	va_end(valist);
	return ;
}
int main()
{
	f(1,2,3);
	return 0;
}

