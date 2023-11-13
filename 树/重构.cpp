#define _CRT_SECURE_NO_WARNINGS
#include<queue>
#include<stack>
#include<stdio.h>
#define MAXN 10020
#define MAXINFOLENGTH 2000000
char input[MAXINFOLENGTH];
int main()
{
	int n=1;
	while(1){
		//求顺序树的深度
		if(scanf("%s",input)!=1||input[0]=='#')
		  return 0;
		char *p = input;
		int sqdepth=0;
		int sqmaxdepth = 0;
		int bidepth=0;
		int bimaxdepth =0;
		std::stack<int>s;
		s.push(0);
			while(*p){
				if(*p=='d'){
					sqdepth++;
					bidepth++;
					s.push(bidepth);
				}
				else{
					sqdepth--;
					bidepth = s.top();
					s.pop();
				}
				p++;
				if(sqdepth>sqmaxdepth)
				  sqmaxdepth = sqdepth;
				if(bidepth>bimaxdepth)
				  bimaxdepth=bidepth;
			}
		printf("Tree %d: %d => %d\n",n,sqmaxdepth,bimaxdepth);
		n++;
	}
	return 0;
}
