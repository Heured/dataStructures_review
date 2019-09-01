#include<iostream>
using namespace std;

typedef char ElemType;

typedef struct lnode{
	int tag;	//节点类型标签
	union{
		ElemType data;	//原子值 
		struct lnode *sublist;	//指向子表的指针 
	}val;
	struct lnode *link;	//指向下一个元素 
}GLNode;	//广义表节点类型定义 

//求广义表的长度 
int GLLength(GLNode *g){	//求广义表g的长度
	int n=0;
	GLNode *g1;
	g1 = g->val.sublist;	//g1指向广义表的第一个元素
//	累加元素个数 
	while(g1 != NULL){
		n++;
		g1 = g1->link;
	}
	return n;
}

//求广义表g的深度
//	tag=0，表示该节点为原子节点，第二个域为data 
//	tag=1，表示该节点为表节点，第二个域为sublist 
int GLDepth(GLNode *g){
	GLNode *g1;
	int max=0, dep;
//	为原子时返回0 
	if(g->tag == 0)
		return 0;
	g1 = g->val.sublist;
//	为空表时返回1 
	if(g1 == NULL)
		return 1;
//	遍历每一个元素 
	while(g1 != NULL){
		if(g1->tag == 1){
			dep = GLDepth(g1);
			if(dep>max)
				max = dep;
		}
		g1 = g1->link;
	}
	return (max + 1);	//返回表的深度 
}

//输出广义表
void DispGL(GLNode *g){
	if(g != NULL){
//		g的元素为原子时，输出原子值 
		if(g->tag == 0)
			cout<<g->val.data;
//		g的元素为子表时 
		else{
			cout<<"(";
//			为空表时 
			if(g->val.sublist == NULL)
				cout<<"#";
//			为非空子表时，递归输出子表 
			else
				DispGL(g->val.sublist);
			cout<<")";
		}
		if(g->link != NULL){
			cout<<",";
//			递归输出g的兄弟 
			DispGL(g->link);
		}
	}
}

//建立字符串s的广义表
GLNode *CreateGL(char *&s){
	GLNode *g;
	char ch = *s++;	//取一个字符
	if(ch!='\0'){
		g = (GLNode *)malloc(sizeof(GLNode));	//创建一个新节点
//		当前字符为左括号时 
		if(ch == '('){
			g->tag = 1;	//新节点作为表头节点 
			g->val.sublist = CreateGL(s);	//递归构造子表并链接到表头节点
//		遇到")"字符，g置为空
//			这种情况如果是碰到()的情况会触发，但是触发后会造成不再读取()以后的兄弟节点
//			正常情况空表用(#)表示，')'的判断一般发生在判断是否为','时，如果为')'则g->link=NULL然后return g 
		}else if(ch == ')'){
			g = NULL;
//		遇到"#"字符，表示空表
		}else if(ch == '#'){
			g = NULL; 
//		为原子字符
		}else{
			g->tag = 0;	//新节点作为原子节点 
			g->val.data = ch;
		}
//	串结束，g置为空 
	}else
		g = NULL;
	ch = *s++;	//取下一个字符 
//	串未结束，继续构造兄弟节点 
	if(g!=NULL)
//		当前字符为","，递归构造兄弟节点 
		if(ch == ',')
			g->link = CreateGL(s);
//		没有兄弟了，将兄弟指针置为NULL 
		else
			g->link = NULL;
	return g;	//返回广义表g 
}

//求给定广义表g中原子个数
//	类似于树的深度优先算法 
int atomNum(GLNode *g){
	if(g!=NULL){
		if(g->tag == 0)
			return 1+atomNum(g->link);
		else
			return atomNum(g->val.sublist) + atomNum(g->link);
	}else
		return 0;
}

//广义表类似于树形结构
//	在当前等级内link连接下一个兄弟节点 
//	广义表可以是自己的子表，这种广义表称为递归表
main(){
	char s[] = "(b,(b,a,(#),d),((a,b),c,((#))))";
	char *st = s;
	GLNode *g;
	g = CreateGL(st);
	cout<<"原子个数："<<atomNum(g)<<endl;
	cout<<"长度："<<GLLength(g)<<endl;
	cout<<"深度："<<GLDepth(g)<<endl;
	DispGL(g);
}
