#include<stack>
#include<set>
#include<map>
#include<queue>
#include<iostream>
using namespace std;
#define MAXN 60
typedef struct Node{
	char ch;
	int data;
	Node* lchild;
	Node* rchild;
}Node,*Tree;
int compare(char in,char top)//返回1说明不能直接进栈，还要进行处理，右括号包括在内
{
	switch(in){
		case '*':
			if(top=='*')
			  return 1;
			if(top=='+')
			  return 0;
			if(top=='-')
			  return 0;
			if(top=='(')
			  return 0;
			if(top=='/')
			  return 1;
			break;
		case '+':
			if(top=='*')
			  return 1;
			if(top=='+')
			  return 1;
			if(top=='-')
			  return 1;
			if(top=='(')
			  return 0;
			if(top=='/')
			  return 1;
			break;
		case '-':
			if(top=='*')
			  return 1;
			if(top=='+')
			  return 1;
			if(top=='-')
			  return 1;
			if(top=='(')
			  return 0;
			if(top=='/')
			  return 1;
			break;
		case '(':
			if(top=='*')
			  return 0;
			if(top=='+')
			  return 0;
			if(top=='-')
			  return 0;
			if(top=='(')
			  return 0;
			if(top=='/')
			  return 0;
			break;
		case ')':
			if(top=='*')
			  return 1;
			if(top=='+')
			  return 1;
			if(top=='-')
			  return 1;
			if(top=='(')
			  return 1;
			if(top=='/')
			  return 1;
			break;
		case '/':
			if(top=='*')
			  return 1;
			if(top=='+')
			  return 0;
			if(top=='-')
			  return 0;
			if(top=='(')
			  return 0;
			if(top=='/')
			  return 1;
			break;
	}
	cout<<"compare error"<<endl;
	cout<<in<<"  "<<top<<endl;
	return 0;
}
void in_to_pos(string in,string &pos)
{
	char temp[10]="*+-()/";
	stack <char>opt;
	set <char> opt_set(temp,temp+6); 
	int n = 0;
	while(n<in.length()){
		char now= in[n];
		if(opt_set.find(now)!=opt_set.end()){//为操作符
			while(!opt.empty()&&compare(now,opt.top())){
				if(opt.top()=='('){
					opt.pop();
					break;
				}
				else{
					pos.push_back(opt.top());
					opt.pop();
				}
			}
			if(now!=')')
			  opt.push(now);
		}
		else//为字母
		  pos.push_back(now);
		n++;
	}
	while(!opt.empty()){
		pos.push_back(opt.top());
		opt.pop();
	}	
	return;
}
int Depth(Tree T)//非递归
{
	int depth=0,now=1;
	stack <Tree>s;
	stack<int>temp;
	Tree p = T;
	while(!s.empty()||p){
		while(p){
			s.push(p);
			temp.push(now);
			now++;
			p=p->lchild;
		}
		p = s.top();
		s.pop();
		now = temp.top();
		temp.pop();
		p = p->rchild;
		if(p)
		  now++;
		if(depth<now)
		  depth = now;
	}
	return depth;
}
void display(Tree T){
	int depth = Depth(T);
	int offset = 0 ;
	for(int i = 0;i<depth-1;i++)
	  offset = 2*offset+1;
	queue<Tree>to_display;
	queue<Tree>temp;
	Tree p,q;
	if(!T){
		cout<<"ERROR"<<endl;
		return ;
	}
	to_display.push(T);
	while(1){
		for(int i = 0;i<offset;i++)
		  cout<<" ";
		int finish = 1;
		int c = 1;
		while(!to_display.empty()){
			p = to_display.front();
			to_display.pop();
			if(p){
				temp.push(p->lchild);
				temp.push(p->rchild);
				if(p->lchild||p->rchild)
				  finish=0;
				cout<<p->ch;
				for(int i =0;i<offset*2+1;i++)
				  cout<<" ";
			}
			else{
				temp.push(NULL);
				temp.push(NULL);
				cout<<" ";
				for(int i = 0;i<offset*2+1;i++)
				  cout<<" ";
			}
		}
		if(finish){
			cout<<endl;
		  return;
		}
		cout<<endl;
		for(int i = 0;i<offset-1;i++)
		  cout<<" ";
		c=1;
		while(!temp.empty()){
			q = temp.front();
			if(q){
				if(c%2)
				  cout<<"/ ";
				else{
				  cout<<"\\";
				  for(int i = 0;i<offset*2-1;i++)
					cout<<" ";
				}
				c++;
			}
			else{
				if(c%2)
				cout<<"  ";
				else
				  for(int i = 0;i<offset*2;i++)
					cout<<" ";
				c++;
			}
			to_display.push(q);
			temp.pop();
		}
		offset--;
		offset/=2;
		cout<<endl;
	}
	cout<<"ERROR"<<endl;
	return ;
}
Tree make_tree(string pos,map<char,int>val)
{
	char temp[10]="*+-()/";
	set <char> opt_set(temp,temp+6); 
	stack<Tree> node;
	int i = 0;
	while(i<pos.length()){
		char now = pos[i];
		if(opt_set.find(now)!=opt_set.end()){//是运算符
			Tree T = new Node;
			T->rchild= node.top();
			node.pop();
			T->lchild = node.top();
			node.pop();
			T->ch = now;
			switch(now){
				case '+':
					T->data= T->lchild->data+T->rchild->data; 
					break;
				case '-':
					T->data= T->lchild->data-T->rchild->data; 
					break;
				case '*':
					T->data= T->lchild->data*T->rchild->data; 
					break;
				case '/':
					T->data= T->lchild->data/T->rchild->data; 
					break;
			}
			node.push(T);
		}
		else{//是操作数
			Tree leaf = new Node;
			leaf ->data = val[now];
			leaf->lchild = NULL;
			leaf->rchild = NULL;
			leaf ->ch = now;
			node.push(leaf);
		}
		i++;
	}
	display(node.top());
	return node.top();
}
int main()
{
	string in,pos;
	cin>> in;
	in_to_pos(in,pos);
	int n;
	cout<<pos<<endl;
	cin>>n;
	map<char,int>val;
	char para;
	int para_val;
	while(n){
		cin >> para>>para_val;
		val[para]=para_val;
		n--;
	}
	Tree T= make_tree(pos,val);
	cout<<T->data<<endl;
	return 0;
}
