#include<stdio.h>
#define MAXN 100010
int ans[MAXN];
int main()
{
		int n,k;
		scanf("%d%d",&n,&k);
		for(int i = 0;i<n;i++)
				scanf("%d",&ans[(i+k)%n]);
		for(int i =0;i<n;i++)
				printf("%d ",ans[i]);
		printf("\n");
		return 0;
}
