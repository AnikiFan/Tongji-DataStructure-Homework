#include<iostream>
#define MAXR 100
#define MAXC 100
using namespace std;
typedef int Status;
typedef int AdjMatrix[MAXR][MAXC] ;
typedef char ElemType;
typedef struct {
	ElemType * Vertices;	
	AdjMatrix Mat;
	int ArcN;
	int VerN;
}Graph;

int main()
{
	cout<<"=======TEST BEGIN======="<<endl;
	
	cout<<"=======TEST E N D======="<<endl;
	return 0;
}
