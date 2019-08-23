#include<iostream>
using namespace std;
#define MaxSize 100
//typedef int ElemType;
typedef char ElemType;

typedef struct{
	ElemType data[MaxSize];
	int top;	//栈顶指针 
}SqStack;	//定义顺序栈类型 

//初始化栈 
void InitStack(SqStack *&s){
	s = (SqStack *)malloc(sizeof(SqStack));
	s->top = -1;	//栈顶指针置-1 
}

//销毁栈 
void DestroyStack(SqStack *&s){
	free(s);
}

//判断是否为空 
bool StackEmpty(SqStack *s){
	return (s->top == -1);
}

//进栈
bool Push(SqStack *&s, ElemType e){
	if(s->top == MaxSize-1){	//栈满的情况(栈上溢出) 
		return false;
	}
	s->top++;	//栈顶指针加1 
	s->data[s->top] = e;	//元素e放于栈顶处 
	return true;
}

//出栈
bool Pop(SqStack *&s, ElemType &e){
	if(s->top == -1)
		return false;
	e = s->data[s->top];	//取栈顶元素 
	s->top--;	//栈顶指针减1 
	return true;
}

//取栈顶元素 
bool GetTop(SqStack *s, ElemType &e){
//	如果栈为空 
	if(s->top == -1)
		return false;
	e = s->data[s->top];	//取栈顶元素 
	return true;
}

//利用顺序栈判断一个字符串是否为对称串
//	条件ElemType定义为char类型 
bool symmetry(ElemType str[]){
	int i;
	ElemType e;
	SqStack *st;
	InitStack(st);	//初始化栈
//	将所有元素进栈 
	for(i=0; str[i]!='\0'; i++)
		Push(st,str[i]); 
	for(i=0; str[i]!='\0'; i++){
		Pop(st,e);
//		如果存在e与当前串元素不同,则不是对称串 
		if(str[i] != e){
			DestroyStack(st);	//销毁栈 
			return false;
		}
	}
//	如果不存在不一样的情况,表示此字符串为一个对称串 
	DestroyStack(st); 
	return true;
}

main(){
	ElemType str[] = "asdfgfdsa";
	cout<<symmetry(str);
		
}
