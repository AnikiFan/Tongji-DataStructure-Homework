#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define MAXN 5000
int first[MAXN]={0},second[MAXN]={0},ans[MAXN]={0};
int n;
int p,e;
int opt;
int maxn=0;
void add(){
		for(int i =0;i<MAXN;i++){
						if(first[i]+second[i])
								printf("%d %d ",first[i]+second[i],i);
				}

		return ;
}
void multi()
{
		for(int i =0;i<=maxn*2;i++){
						for(int j=0;j<=i;j++){
								ans[i]+=first[j]*second[i-j];
						}
				}
				for(int i =0;i<=maxn*2;i++){
						if(ans[i])
								printf("%d %d ",ans[i],i);
				}

				return;
}
int main()
{
		scanf("%d",&n);
		for(int i =0;i<n;i++){
				scanf("%d%d",&p,&e);
				if(e>maxn)
						maxn =e;
				first[e]=p;
		}
		scanf("%d",&n);
		for(int i =0;i<n;i++){
				scanf("%d%d",&p,&e);
				if(e>maxn)
						maxn =e;
				second[e]=p;
		}
		scanf("%d",&opt);
		if(opt==0){
				add();
					}
		else if(opt ==1){
				multi();
						}
		else if(opt ==2){
				add();
				printf("\n");
				multi();
		}
		return 0;
}
