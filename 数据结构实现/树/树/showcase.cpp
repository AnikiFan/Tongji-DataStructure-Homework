#include"树.h"
int main()
{
	printf("=======TEST BEGIN=======\n");
	Tree T,t;
	CreateTree(T);
	printf("----PreOrderTraverse----\n");
	PreOrderTraverse(T,visit);
	printf("----PreOrderTraverseWithLoop----\n");
	printf("----V1----\n");
	PreOrder1(T,visit);
	printf("----V2----\n");
	PreOrder2(T,visit);
	printf("------------------------\n");
	printf("----InOrderTraverse----\n");
	InOrderTraverse(T,visit);
	printf("----InOrderTraverseWithLoop----\n");
	InOrder(T,visit);
	printf("-----------------------\n");
	printf("----PosOrderTraverse----\n");
	PosOrderTraverse(T,visit);
	printf("----PosOrderTraverseWithLoop----\n");
	PosOrder1(T,visit);
	printf("------------------------\n");
	printf("----Depth----\n");
	printf("%d\n",Depth(T));	
	printf("----Size----\n");
	printf("%d\n",size(T));
	printf("-----Copy-------\n");
	Copy(t,T);
	printf("----LevelTraverse----\n");
	LevelTraverse(t,visit);
	printf("-----Switch------\n");
	Switch(t);
	printf("----LevelTraverse----\n");
	LevelTraverse(t,visit);
	printf("=======TEST END=======\n");
	return 0;
}
