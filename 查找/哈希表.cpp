#include<iostream>
typedef int Status;
#define OK 1
using namespace std;
unsigned long long get_max_prime(unsigned long long n)
{
	if(n%2)
	  n --;
	int flag = 1;
	while(n>0){
		flag= 1;
		int i = n -1;
		while(i>1){
			if(n%i){
				flag =0;
				break;
			}
			i--;
		}
		if(flag)
		  break;
		n-=2;
	}
	return n;
}
unsigned long long get_key(string str)
{
	unsigned long long key=0;
	for(int i = 0;i<str.length();i++){
		key+=(str[i]);
		key*=37;
	}
	return key;
}
void detect(bool*vec,unsigned long long key,unsigned long long len)
{
	int  i = 0;
	int d = 1;
	while(i<len){
		if(d%2){
			if(vec[(key+(d/2)*(d/2))%len]){
				vec[(key+(d/2)*(d/2))%len]=1;
				break;
			}
		}
		else{
			if(vec[(key-(d/2)*(d/2))%len]){
				vec[(key-(d/2)*(d/2))%len]=1;
				break;
			}
		}
		d++;
		i++;
	}
	if(i==len)
	  cout<<"-"<<" ";
	else 
	  cout<<i<<" ";
	return ;
}
int main()
{
	bool* vec;
	int n,p;
	cin>>n>>p;
	p = get_max_prime(p);
	string in;
	vec = new bool[p];
	for(int i = 0;i<p;i++)
	  vec[i]=0;
	unsigned long long key;
	for(int i = 0;i<n;i++){
		cin>>in;
		key = get_key(in);
		key%= p;
		if(!vec[key]){
			cout<<key<<" ";
			vec[key]=1;
		}
		else 
		  detect(vec,key,p);
	}
	return 0;
}
