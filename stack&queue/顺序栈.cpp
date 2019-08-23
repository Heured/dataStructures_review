#include<iostream>
using namespace std;
#define MaxSize 100
//typedef int ElemType;
typedef char ElemType;

typedef struct{
	ElemType data[MaxSize];
	int top;	//ջ��ָ�� 
}SqStack;	//����˳��ջ���� 

//��ʼ��ջ 
void InitStack(SqStack *&s){
	s = (SqStack *)malloc(sizeof(SqStack));
	s->top = -1;	//ջ��ָ����-1 
}

//����ջ 
void DestroyStack(SqStack *&s){
	free(s);
}

//�ж��Ƿ�Ϊ�� 
bool StackEmpty(SqStack *s){
	return (s->top == -1);
}

//��ջ
bool Push(SqStack *&s, ElemType e){
	if(s->top == MaxSize-1){	//ջ�������(ջ�����) 
		return false;
	}
	s->top++;	//ջ��ָ���1 
	s->data[s->top] = e;	//Ԫ��e����ջ���� 
	return true;
}

//��ջ
bool Pop(SqStack *&s, ElemType &e){
	if(s->top == -1)
		return false;
	e = s->data[s->top];	//ȡջ��Ԫ�� 
	s->top--;	//ջ��ָ���1 
	return true;
}

//ȡջ��Ԫ�� 
bool GetTop(SqStack *s, ElemType &e){
//	���ջΪ�� 
	if(s->top == -1)
		return false;
	e = s->data[s->top];	//ȡջ��Ԫ�� 
	return true;
}

//����˳��ջ�ж�һ���ַ����Ƿ�Ϊ�Գƴ�
//	����ElemType����Ϊchar���� 
bool symmetry(ElemType str[]){
	int i;
	ElemType e;
	SqStack *st;
	InitStack(st);	//��ʼ��ջ
//	������Ԫ�ؽ�ջ 
	for(i=0; str[i]!='\0'; i++)
		Push(st,str[i]); 
	for(i=0; str[i]!='\0'; i++){
		Pop(st,e);
//		�������e�뵱ǰ��Ԫ�ز�ͬ,���ǶԳƴ� 
		if(str[i] != e){
			DestroyStack(st);	//����ջ 
			return false;
		}
	}
//	��������ڲ�һ�������,��ʾ���ַ���Ϊһ���Գƴ� 
	DestroyStack(st); 
	return true;
}

main(){
	ElemType str[] = "asdfgfdsa";
	cout<<symmetry(str);
		
}
