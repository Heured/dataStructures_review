#include<iostream>
using namespace std;
#define MaxCol 10

typedef int ElemType;
typedef struct Node1{	//�������ݽڵ����� 
	ElemType data[MaxCol];	//���һ�е����� 
	struct Node1 *next;	//ָ���̽ڵ� 
}DList;	//�нڵ����� 

typedef struct Node2{
	int Row, Col;	//���������� 
	DList *next;	//ָ���һ�����ݽڵ� 
}HList;	//ͷ�ڵ�����

//����β�巨����������ѡ��������������Ȼ�������������
//ʱ�临�Ӷ�ΪO(m*n) 
void CreateTable(HList *&h){
	int i,j;
	DList *r, *s;
	h = (HList *)malloc(sizeof(HList));
	h->next = NULL;
	cout<<"�������������(�ո�ָ�)��";
	cin>>h->Row>>h->Col;	//����������������

	for(i=0; i<h->Row; i++){
		cout<<"��"<<i+1<<"�У�"; 
		s = (DList *)malloc(sizeof(DList));	//�������ݽڵ� 
		for(j=0; j<h->Col; j++)	//����һ�е����� 
			cin>>s->data[j];
		if(h->next == NULL)	//�����һ�����ݽڵ� 
			h->next = s;
		else	//�����������ݽڵ� 
			r->next = s;	//��*s���뵽*r�ڵ�֮�� 
		r = s;	//rʼ��ָ��β�ڵ� 
	}
	r->next = NULL;	//β�ڵ�next�ÿ�
}

//���ٵ�����
void DestroyTable(HList *&h){
	DList *pre = h->next, *p = pre->next;
	while(p!=NULL){
		free(pre);
		pre = p;
		p = p->next;
	}
	free(pre);
	free(h);
}

//���������
void DispTable(HList *h){
	int j;
	DList *p = h->next;	//pָ��ʼ�нڵ� 
	while(p!=NULL){
//		���һ�е����� 
		for(j=0; j<h->Col; j++)
			cout<<p->data[j]<<' ';
		cout<<endl;
		p = p->next;	//pָ����һ�нڵ� 
	}
}

//A��:m1�У�n1�У�	B��m2��n2��
//C��ΪA����B�����Ȼ���ӣ�����������A��ĵ�i����B��ĵ�j����ȡ�
void LinkTable(HList *h1, HList *h2, HList *&h){
	int i,j,k;
	DList *p = h1->next, *q, *s, *r;
	cout<<"�����ֶ��ǣ���1������ţ���2������ţ�";
	cin>>i>>j;
	h = (HList *)malloc(sizeof(HList));	//���������ͷ�ڵ�
	h->Row = 0;
	h->Col = h1->Col + h2->Col;	//������Ϊ��1���2�������� 
	h->next = NULL;
	while(p!=NULL){	//������1 
		q = h2->next;	//qָ���2�Ŀ�ʼ 
		while(q!=NULL){	//������2 
			if(p->data[i-1] == q->data[j-1]){
				s = (DList *)malloc(sizeof(DList));	//����һ�����ݽڵ�*s
//				���Ʊ�1��ǰ�� 
				for(k=0;k<h1->Col;k++)
					s->data[k] = p->data[k];
//				���Ʊ�2��ǰ�� 
				for(k=0;k<h2->Col;k++)
					s->data[h1->Col+k] = q->data[k];
//				�������һ�����ݽڵ㣬��*s����ͷ�ڵ�֮�� 
				if(h->next == NULL)
					h->next = s;
//				�����ǲ����һ�����ݽڵ㣬��*s����*r�ڵ�֮�� 
				else
					r->next = s;
				r = s;	//rʼ��ָ��β�ڵ� 
				h->Row++;	//��������1
			}
			q = q->next;	//��2����һ�� 
		}
		p = p->next;	//��1����һ�� 
	}
	r->next = NULL;	//��hβ�ڵ��ÿ�
}
main(){
	HList *h1, *h2, *h;
	cout<<"��1��"<<endl;
	CreateTable(h1);
	cout<<"��2��"<<endl;
	CreateTable(h2);
	LinkTable(h1,h2,h);
	cout<<"���ӽ����:"<<endl;
	DispTable(h);
	DestroyTable(h1); 
	DestroyTable(h2);
	DestroyTable(h);	 
}
