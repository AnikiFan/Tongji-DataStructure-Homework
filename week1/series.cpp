#include<stdio.h>
#define maxn 20000
int ans[maxn]={0};
int temp[maxn]={0};
int n,a;
void add(int x,int to[])
{
		*to += x;
		for(int i =0;i<maxn-1;i++){
				to[i+1]+=to[i]/10;
				to[i]%=10;
		}
		return;
}
void list_add(int src[],int dst[])
{
		for(int i =0;i<maxn-1 ;i++){
				dst[i]+= src[i];
				if(dst[i]/10){
						dst[i]%=10;
						dst[i+1]++;
				}
		}
}
void multi(int x,int to[])
{
		int up=0;
		for(int i = 0;i<maxn-1;i++){
				to[i]= to[i]*x+up;
				up = to[i]/10;
				to[i]%=10;
		}
		return ;
}
int main()
{
		while(scanf("%d%d",&n,&a)==2){
				if(a == 0||n==0){
						printf("0\n");
						continue;
				}
				for(int i = 0;i<maxn;i++)
						ans[i]=0;
				for(int i =1;i<=n;i++){
						for(int j = 0;j<maxn;j++)
								temp[j]=0;
						add(i,temp);
						for(int j = 1;j<=i;j++){
								multi(a,temp);
						}
						list_add(temp,ans);
				}
				int first=1;
				for(int i = maxn-1;i>=0;i--){//边界问题要注意
						if(ans[i]&&first){
								first=0;
								printf("%d",ans[i]);
						}
						else if(!first)
								printf("%d",ans[i]);
				}
				printf("\n");
		}
		return 0;
}
