#include<stdio.h>
#include<malloc.h>

#define OK 1
#define ERROR 0
#define OVERFLOW printf("\n\n---!!!OVERFLOW!!!---\n\n"); 

typedef int Status;
typedef struct{
	char * ch;
	int length;
}HString;

Status TraverseString(HString S,Status(*visit)(char)){
	printf("Begin Traversing\n");
	if(!S.length){
		printf("EMPTY\n");
		return OK;
	}
	for(int i = 0;i<S.length;i++)
	  visit(S.ch[i]);
	printf("\n");
	return OK;
}
Status visit(char ch){
	putchar(ch);
	return OK;
}
Status StrInsert(HString &S,int pos,HString T){
	printf("Begin inserting\n");
	printf("pos:%d\n",pos);
	printf("to insert\n");
	TraverseString(S,visit);
	printf("insert\n");
	TraverseString(T,visit);
int i;
	if(pos<1||pos>T.length+1)
	  return ERROR;
	if(!(S.ch= (char*)realloc(S.ch,(S.length +T.length)*sizeof(char))))
	  OVERFLOW
	for(int i = S.length-1;i>=pos-1;i--)
	  S.ch[i+T.length]=  S.ch[i];
	for(int i=0;i<T.length;i++)
	  S.ch[pos+i-1]=T.ch[i];
	S.length += T.length;
	printf("inserted\n");
	TraverseString(S,visit);
	return OK;
}

Status StrAssign(HString &S,char *chars){
	printf("Begin assigning\n");
	printf("to assign:\n");
	printf("%s\n",chars);
	int len=0;
	char *c=chars;
	while(*c){
		c++;
		len++;
	}
	if(!len){
		S.ch=NULL;
		S.length = 0;
		return OK;
	}
	if(!(S.ch=(char*)malloc(sizeof(char)*len)))
	  OVERFLOW
	for(int i =0;i<len;i++)
		S.ch[i]=chars[i];
	S.length = len;
	printf("assigned\n");
	TraverseString(S,visit);
	return OK;
}

int StrLength(HString S){
	printf("Get Length\n");
	return S.length;
}

int StrCompare(HString S,HString T){
	printf("Compare\n");
	for(int i =0;i<S.length && i<T.length;i++)
	  if(S.ch[i]-T.ch[i])
		return S.ch[i]-T.ch[i];
	return S.length-T.length;
}
Status Concat(HString &S,HString S1,HString S2){
	printf("concat\n");
	printf("to concat\n");
	TraverseString(S1,visit);
	TraverseString(S2,visit);
	if(!(S.ch= (char*)malloc((S1.length+S2.length)*sizeof(char))))
	  OVERFLOW
	S.length =S1.length + S2.length;
	for(int i = 0;i<S1.length;i++)
	  S.ch[i]= S1.ch[i];
	for(int i = 0;i<S2.length ;i++)
	  S.ch[S1.length +i]=S2.ch[i];
	printf("concated\n");
	TraverseString(S,visit);
	return OK;
}
Status SubString (HString&Sub,HString S,int pos,int len){
	printf("get substring\n");
	printf("from:\n");
	TraverseString(S,visit);
	printf("pos: %d, len:%d\n",pos,len);
	if(pos<1||pos>S.length ||pos+len-1>S.length||len<0)
	  return ERROR;
	if(!len){
		Sub.length = 0;
		Sub.ch=NULL;
		return OK;
	}
	if(!(Sub.ch =(char*)malloc(sizeof(char)*len)))
	  OVERFLOW
	for(int i =0;i<len;i++)
	   Sub.ch[i]= S.ch[pos+i-1];
	Sub.length = len;
	printf("sub:\n");
	TraverseString(Sub,visit);
	return OK;
}
Status EmptyString(HString&Sub){
	printf("empty string\n");
	if(Sub.ch){
	free(Sub.ch);
	Sub.ch = NULL;
	}
	Sub.length = 0;
	return OK;
}
int BruteSearch(HString pat,HString S){
	printf("Begin BruteSearch\n");
	int i =0,j=0;
	printf("S.length:%d pat.length: %d\n",S.length,pat.length);
	while(i<S.length ){
		while(j<pat.length){
		  if(pat.ch[j]!=S.ch[i+j])
			break;
		j++;
		}
		if(j==pat.length)
		  break;
		j=0;
		i++;
	}
	if(i==S.length)
	  return 0;
	return i+1;
}
Status Make_next(HString pat,int *&next){
	if(!(next=(int*)malloc(sizeof(int)*pat.length)))
	  OVERFLOW
	int now;
	next[0]=0;
	next[1]=0;
	for(int i =2;i<pat.length;i++){
		printf("i:%d\n\n",i);
		now = next[i-1];
		while(1){
			printf("now:%d\n",now);
			if(pat.ch[now]==pat.ch[i-1]){
				next[i]=now+1;
				break;
			}
			if(!now){
				next[i]=0;
				break;
			}
			now = next[now];
		}
		printf("next[%d]:%d\n",i,next[i]);
	}
	return OK;
}
int KMP(HString pat,HString S,int next []){
	int i =0,j=0;
	while(i<S.length){
		printf("i:%d j:%d\n",i,j);
		if(pat.ch[j]==S.ch[i]){//相同
		//		printf("***\n");
			i++;
			j++;
		}
		else{
		//		printf("%%%%\n");
			j=next[j];//跳转至下一个待判断的字符
			if(!j)//说明要重新判断
			  i++;
		}
		if(j==pat.length)
		  return i-pat.length+1;//最后一次判断后仍然加一，此时i视为pos而非下标
	}
	return 0;
}

int main()
{
	printf("----TEST BEGIN----\n");
	HString s,s1,s2,s3,pat,S;
	int temp;
	int * test;
	StrAssign(s,"main");
	StrAssign(s1,"insert");
	TraverseString(s,visit);
	StrInsert(s,2,s1);
	temp = StrLength(s);
	printf("length:%d\n",temp);
	EmptyString(s);
	temp = StrLength(s);
	printf("length:%d\n",temp);
	EmptyString(s1);
	StrAssign(s,"abcdefg");
	StrAssign(s1,"hijkl");
	temp = StrCompare(s,s1);
	printf("s vs s1:%d\n",temp);
	StrAssign(s2,"11");
	Concat(s3,s1,s2);
	temp = StrCompare(s,s3);
	printf("s vs s1:%d\n",temp);
	SubString(s2,s1,1,3);
	StrAssign(pat,"123");
	StrAssign(S,"333333333");
	temp= BruteSearch(pat,S);
	printf("pos:%d\n",temp);
	StrAssign(S,"21233523123");
	temp= BruteSearch(pat,S);
	printf("pos:%d\n",temp);

	Make_next(pat,test);
	printf("%d %d %d\n\n",test[0],test[1],test[2]);
	temp= KMP(pat,S,test);
	printf("pos:%d\n",temp);
	printf("----TEST FINISH----\n");
	return 0;
}
