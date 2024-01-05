#include<iostream>
typedef int Status;
#define OK 1
using namespace std;
bool is_prime(unsigned long long n)
{
	if(n<2)
	  return 0;
	for(int i = n-1;i>=2;i--)
	  if(!(n%i))
		return 0;
	return 1;
}
unsigned long long get_key(string str)
{
	unsigned long long key=0;
	for(int i = 0;i<str.length();i++){
		key*=37;
		key+=(str[i]);
	}
	return key;
}
void detect(bool*vec,unsigned long long key,unsigned long long len)
{
	int  i = 0;
	int d = 2;
	//cout<<"key"<<key<<endl;
	while(i<len){
	//	cout<<(key+(d/2)*(d/2)+len)%len<<"&&&"<<(key-(d/2)*(d/2)+len)%len<<endl;
		if(d%2){
			if(!vec[(key-(d/2)*(d/2)+len*len)%len]){
				vec[(key-(d/2)*(d/2)+len*len)%len]=1;
				cout<<(key-(d/2)*(d/2)+len*len)%len<<" ";
				return;
			}
		}
		else{
			if(!vec[(key+(d/2)*(d/2))%len]){
				vec[(key+(d/2)*(d/2))%len]=1;
				cout<<(key+(d/2)*(d/2))%len<<" ";
				return;
			}
		}
		d++;
		i++;
	}
    cout<<"-"<<" ";
	return ;
}
int main()
{
	bool* vec;
	int n,p;
	cin>>n>>p;
	while(!is_prime(p))
	  p++;
	//cout<<"p:"<<p<<endl;
	string in;
	vec = new bool[p];
	for(int i = 0;i<p;i++)
	  vec[i]=0;
	unsigned long long key;
	for(int i = 0;i<n;i++){
		cin>>in;
		key = get_key(in);
	//	cout<<key<<endl;
		key%= p;
		if(!vec[key]){
			vec[key]=1;
			cout<<key<<" ";
		}
		else 
		  detect(vec,key,p);
	}
	return 0;
}
