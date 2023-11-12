#define _CRT_SECURE_NO_WARNINGS
#include<stack>
#include<stdio.h>
#define MAXN 1010
typedef int Tree[MAXN];
int main()
{
	int n;
	int parent,child;
	int x,y;
	scanf("%d",&n);
	while(n--){
		int N,M;
		int ans;
		Tree T={0};
		scanf("%d%d",&N,&M);
		for(int i =0;i<N-1;i++){
			scanf("%d%d",&parent,&child);
			T[child]= parent;
		}
		for(int i = 0;i<M;i++){
			std::stack<int>s1,s2;	
			scanf("%d%d",&x,&y);
			s1.push(x);
			s2.push(y);
			//printf("push s1:%d\n",x);
			//printf("push s2:%d\n",y);
			while(T[x]){
				x = T[x];
				s1.push(x);
			//printf("push s1:%d\n",x);
			}
			while(T[y]){
				y = T[y];
				s2.push(y);
			//printf("push s2:%d\n",y);
			}
			while((!s1.empty())&&(!s2.empty())&&(s1.top()==s2.top())){
				ans = s1.top();
				//printf("ans: %d\n",ans);
				s1.pop();
				s2.pop();
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
