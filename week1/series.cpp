#include<stdio.h>
#define maxn 20000
int ans[maxn]={0};
int temp[maxn]={0};
int n,a;
void add(int x,int to[])
{
		*maxn += x;
		for(int i =0;i<maxn;i++){
				to[i+1]+=to[i]/10;
				to[i]%=10;
		}
		return;
}
void multi(int x,int to[])
{
		int temp;
		for(int i = 0;i<maxn;i++){
				
		}
		return ;
}
int main()
{
		scanf("%d%d",&n,&a);
		while(scanf("%d%d",&n,&a)==2){
				for(int i =1;i<=n;i++){
						
				}
		}
		return 0;
}
