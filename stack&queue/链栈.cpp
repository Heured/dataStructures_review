#include<iostream>
using namespace std;

typedef char ElemType;

typedef struct linknode{
	ElemType data;	//������ 
	struct linknode *next;	//ָ����	
}LiStack;	//������ջ����

//��ʼ��ջ 
void InitStack(LiStack *&s){
	s = (LiStack *)malloc(sizeof(LiStack));
	s->next = NULL;
}

//����ջ
void DestroyStack(LiStack *&s){
	LiStack *p = s, *q = s->next;
	while(q!=NULL){
		free(p);
		p=q;
		q=q->next;
	}
	free(p);	//��ʱpָ��β�ڵ� 
}

//�ж��Ƿ�Ϊ��
bool StackEmpty(LiStack *s){
	return(s->next == NULL);
}

//��ջ���൱�ڵ������ͷ�巨 
void Push(LiStack *&s, ElemType e){
	LiStack *p;
	p = (LiStack *)malloc(sizeof(LiStack));
	p->data = e;	//�½�Ԫ��e��Ӧ�ڵ�*p 
	p->next = s->next;	//����*p�ڵ���Ϊ��ʼ�ڵ� 
	s->next = p;
}

//��ջ
bool Pop(LiStack *&s, ElemType &e){
	LiStack *p;
//	ջ�յ���� 
	if(s->next == NULL)
		return false;
	p = s->next;	//pָ��ʼ�ڵ�
	e = p->data;
	s->next = p->next;	//ɾ��*p�ڵ�
	free(p);
	return true; 
}

//ȡջ��Ԫ�� 
bool GetTop(LiStack *s, ElemType &e){
//	ջ�յ���� 
	if(s->next == NULL)
		return false;
	e = s->next->data;
	return true; 
}

//�ж�����ı��ʽ�е������Ƿ����(������ʽֻ������Բ����)
bool Match(char exp[], int n){
	int i=0;
	char e;
	bool match = true;
	LiStack *st;
	InitStack(st);	//��ʼ��ջ
//	����exp�������ַ� 
	while(i<n && match){
//		��ǰ�ַ�Ϊ�����ţ������ջ 
		if(exp[i] == '(')
			Push(st,exp[i]);
		else if(exp[i] == ')'){
			if(GetTop(st,e) == true){
				if(e != '(')
					match = false;
				else
					Pop(st,e);
			}else
				match = false;	//ջΪ�գ��޷�ȡ��ջ��Ԫ�� 
		}
		i++;
	}
//������exp��ջ��Ϊ�գ���ʾ���Ų�ƥ��	
	if(!StackEmpty(st))
		match = false;
	DestroyStack(st);	//����ջ 
	return match;
}

main(){
	char exp[] = "(()())";
	cout<<Match(exp,6);
}
