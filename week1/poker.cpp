#include<stdio.h>
#include<string.h>
#define MAXN 700
#define MAXL 10
int n;
int top = 0;
char suit_list [MAXN][MAXL],pt_list[MAXN],suit,opt[MAXL],pt;
void Pop()
{
		if(!top){
				printf("NULL\n");
				return;
		}
		top--;
		if(pt_list[top]!='9'+1&&pt_list[top]!='1'&&pt_list[top]!='Q'&&pt_list[top]!='K')
		printf("%s %c\n",suit_list[top],pt_list[top]);
		else if (pt_list[top]=='9'+1)
		printf("%s 10\n",suit_list[top]);
		else if(pt_list[top]=='1')
				printf("%s A\n",suit_list[top]);
		else if(pt_list[top]=='Q')
				printf("%s K\n",suit_list[top]);
		else if(pt_list[top]=='K')
				printf("%s Q\n",suit_list[top]);
		return ;
}
void swap(int i,int j)
{
		char temp[MAXL];
		strcpy(temp,suit_list[i]);
		strcpy(suit_list[i],suit_list[j]);
		strcpy(suit_list[j],temp);
		pt = pt_list[i];
		pt_list[i]=pt_list[j];
		pt_list[j]= pt;
		return ;
}
void Revert()
{
		for(int i = 0;i<top/2;i++)
				swap(i,top-i-1);
		return ;
}
void Append()
{
		for(int i=top-1;i>=0;i--){
				strcpy(suit_list[i+1],suit_list[i]);
				pt_list[i+1]=pt_list[i];
		}
		pt_list[0]=pt;
		strcpy(suit_list[0],opt);
		top++;
		return ;
}
void sort()
{
		for(int i =0;i<top;i++){
				if(strcmp(opt,suit_list[i]))
						continue;
				else{
						int k =i;
						for(int j=i;j<top;j++){
								if(strcmp(opt,suit_list[j]))
										continue;
								if(pt_list[j]>pt_list[k])
										k=j;
						}
						swap(k,i);
				}
		}
		return ;
}
void Extract()
{
		sort();
		for(int i =top-2;i>=0;i--){
				for(int j = i;j<=top-2;j++)
				if(!strcmp(suit_list[j],opt)&&strcmp(suit_list[j+1],opt))
						swap(j,j+1);
		}
		return;
}
int main()
{
		scanf("%d",&n);
		while(n--){
				scanf("%s",&opt);
				if(!strcmp(opt,"Pop"))
						Pop();
				else if(!strcmp(opt,"Revert"))
						Revert();
				else if(!strcmp(opt,"Append")){
						scanf("%s %c",&opt,&pt);
						if(pt=='1'){
								pt='9'+1;
								getchar();
						}
						else if(pt=='A')
								pt='1';
						else if(pt=='Q')
								pt='K';
						else if(pt=='K')
								pt='Q';
				//		printf("%c\n",pt);
						Append();
				}
				else{
						scanf("%s",&opt);
						Extract();
				}
		}
		for(int i =top-1;i>=0;i--){
				if(pt_list[i]!='9'+1&&pt_list[i]!='1'&&pt_list[i]!='Q'&&pt_list[i]!='K')
				printf("%s %c\n",suit_list[i],pt_list[i]);
				else if(pt_list[i]=='9'+1)
				printf("%s 10\n",suit_list[i]);
				else if(pt_list[i]=='1')
						printf("%s A\n",suit_list[i]);
				else if(pt_list[i]=='Q')
						printf("%s K\n",suit_list[i]);
				else if(pt_list[i]=='K')
						printf("%s Q\n",suit_list[i]);
		}
		return 0;
}
