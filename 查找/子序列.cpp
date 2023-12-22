//先排序，后前缀和，然后进行二分查找
#include<iostream>
#include<vector>
#include<algorithm>
#define OK 1

using namespace std;

typedef int Status;
typedef int ElemType;

int main()
{
	vector<ElemType> data,query,ans;
	int n,m,temp;
	cin>> n>>m;
	for(int i= 0;i<n;i++){
		cin>>temp;
		data.push_back(temp);
	}
	for(int i= 0;i<m;i++){
		cin>>temp;
		query.push_back(temp);
	} 
	sort(data.begin(),data.end());
	for(int i = 1;i<data.size();i++)
	  data[i]+=data[i-1];
	for(int i =0;i<query.size();i++){
		int l= 0,h = data.size()-1;
		while(l<=h){
			int mid = (l+h)/2;
			//cout<<"l:"<<l<<"   h:"<<h<<endl;
			if(data[mid]<=query[i]&&((mid==data.size()-1)||(data[mid+1]>query[i]))){
			  ans.push_back(mid+1);
			  break;
			}
			if(data[mid]<query[i])
			  l = mid+1;
			else
			  h = mid-1;
		}
		if(l>h)
			  ans.push_back(0);
	}
	for(int i = 0;i<ans.size();i++)
	  cout<<ans[i]<<" ";
	return 0;
}
