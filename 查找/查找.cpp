#include<iostream>
using namespace std;
#define MAXN 200
string real[MAXN*MAXN+10],ans[MAXN*MAXN+10];
int flag[MAXN*MAXN+10]={0};
int find(string target,int n, int m)
{
	int l= 0,h = n*m;
	for(int i = l;i<h;i++)
	  if(real[i]==target)
		return i;
	return -1;
}
int main()
{
	int now = 0,sum =0,n,m;
	cin >>n>>m;
	for(int i =0;i<m*n;i++)
		cin>> real[i];
	for(int i =0;i<m*n;i++)
		cin>> ans[i];
	string src;
	for(int i = 0;i<n*m;i++){
		if(flag[i])
		  continue;
		if(real[i]==ans[i]){
		  flag[i]=1;
		  continue;
		}
		flag[i]=1;
		src = real[i];
		now = i;
		while(ans[now]!=src){
		    now = find(ans[now],n ,m);
			flag[now]=1;
			sum++;
			//cout<<now;
		}
	}
	cout<<sum;
	return 0;
}
