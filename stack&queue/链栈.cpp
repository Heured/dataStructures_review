#include<iostream>
using namespace std;

typedef char ElemType;

typedef struct linknode{
	ElemType data;	//数据域 
	struct linknode *next;	//指针域	
}LiStack;	//定义链栈类型

//初始化栈 
void InitStack(LiStack *&s){
	s = (LiStack *)malloc(sizeof(LiStack));
	s->next = NULL;
}

//销毁栈
void DestroyStack(LiStack *&s){
	LiStack *p = s, *q = s->next;
	while(q!=NULL){
		free(p);
		p=q;
		q=q->next;
	}
	free(p);	//此时p指向尾节点 
}

//判断是否为空
bool StackEmpty(LiStack *s){
	return(s->next == NULL);
}

//进栈，相当于单链表的头插法 
void Push(LiStack *&s, ElemType e){
	LiStack *p;
	p = (LiStack *)malloc(sizeof(LiStack));
	p->data = e;	//新建元素e对应节点*p 
	p->next = s->next;	//插入*p节点作为开始节点 
	s->next = p;
}

//出栈
bool Pop(LiStack *&s, ElemType &e){
	LiStack *p;
//	栈空的情况 
	if(s->next == NULL)
		return false;
	p = s->next;	//p指向开始节点
	e = p->data;
	s->next = p->next;	//删除*p节点
	free(p);
	return true; 
}

//取栈顶元素 
bool GetTop(LiStack *s, ElemType &e){
//	栈空的情况 
	if(s->next == NULL)
		return false;
	e = s->next->data;
	return true; 
}

//判断输入的表达式中的括号是否配对(假设表达式只含左右圆括号)
bool Match(char exp[], int n){
	int i=0;
	char e;
	bool match = true;
	LiStack *st;
	InitStack(st);	//初始化栈
//	遍历exp中所有字符 
	while(i<n && match){
//		当前字符为左括号，将其进栈 
		if(exp[i] == '(')
			Push(st,exp[i]);
		else if(exp[i] == ')'){
			if(GetTop(st,e) == true){
				if(e != '(')
					match = false;
				else
					Pop(st,e);
			}else
				match = false;	//栈为空，无法取到栈顶元素 
		}
		i++;
	}
//遍历完exp后，栈不为空，表示括号不匹配	
	if(!StackEmpty(st))
		match = false;
	DestroyStack(st);	//销毁栈 
	return match;
}

main(){
	char exp[] = "(()())";
	cout<<Match(exp,6);
}
