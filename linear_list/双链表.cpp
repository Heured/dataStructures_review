#include<iostream>
using namespace std;
typedef int ElemType;

typedef struct DNode{	//����˫����ڵ����� 
	ElemType data;	//���Ԫ��ֵ 
	struct DNode *prior;	//ָ��ǰ���ڵ� 
	struct DNode *next;		//ָ���̽ڵ� 
}DLinkList;

//ͷ�巨����˫���� 
void CreateListF(DLinkList *&L, ElemType a[], int n){
	DLinkList *s;
	int i;
	L = (DLinkList *)malloc(sizeof(DLinkList));	//����ͷ�ڵ� 
	L->prior = L->next = NULL;	//ǰ��ָ������ΪNULL 
//	L->prior = L->next = L;
//	ѭ���������ݽڵ� 
	for(i=0; i<n; i++){
		s = (DLinkList *)malloc(sizeof(DLinkList));
		s->data = a[i];
		s->next = L->next;	//��*s����ͷ�ڵ�֮�� 
		if(L->next!=NULL)	//��L�������ݽڵ㣬�޸�L->next��ǰ��ָ�� 
			L->next->prior = s;
		L->next = s;
		s->prior = L;
	} 
}

//β�巨����˫���� 
void CreateListR(DLinkList *&L, ElemType a[], int n){
	DLinkList *s, *r;
	int i;
	L = (DLinkList *)malloc(sizeof(DLinkList));	//����ͷ�ڵ� 
	r = L;
	for(i=0; i<n; i++){
		s = (DLinkList *)malloc(sizeof(DLinkList));
		s->data = a[i];
		r->next = s; 
		s->prior = r;	//��*s����*r֮�� 
		r = s;	//rָ��β��� 
	}
	r->next = NULL;	//β�ڵ�next����ΪNULL 
//	r->next = L;
}

//����˫����ʱ�临�Ӷ�ΪO(n) 
void DestroyList(DLinkList *&L){
	DLinkList *pre = L, *p = L->next;	//preָ��p��ǰ���ڵ�
//	����������L
	while(p!=NULL){
		free(pre);	//�ͷ�*pre�ڴ� 
		pre = p;	//pre��pͬ������һ���ڵ� 
		p = p->next;
	}
	free(pre);	//ѭ���������ͷ�preָ���β�ڵ���ڴ� 
}

//�ж�˫�����Ƿ�Ϊ�գ�ʱ�临�Ӷ�ΪO(1)
bool ListEmpty(DLinkList *L){
	return L->next==NULL;
} 

//��˫�����ȣ�ʱ�临�Ӷ�ΪO(n)
int ListLength(DLinkList *L){
	int n=0;
	DLinkList *p = L;	//pָ��ͷ�ڵ㣬n��0 
	while(p->next!=NULL){
		n++;
		p = p->next;
	}
	return n;	//ѭ��������pָ��β�ڵ㣬�����nΪ�ڵ���� 
}

//���������ʱ�临�Ӷ�ΪO(n)
void DispList(DLinkList *L){
	DLinkList *p = L->next;	//pָ��ʼ�ڵ�
//	������������p��Ϊ��ʱ���*p�ڵ��dataֵ 
	while(p!=NULL){
		cout<<p->data<<' ';
		p = p->next;
	}
	cout<<endl;
}

//��������ĳ������Ԫ��ֵ��ʱ�临�Ӷ�ΪO(n)
bool GetElem(DLinkList *L, int i, ElemType &e){
	int j = 0;
	DLinkList *p = L;	//pָ��ͷ�ڵ㣬j��0
	while(j<i && p!=NULL){
		j++;
		p = p->next;
	}
//	�����ڵ�i�����ݽڵ㣬����false 
	if(p==NULL)
		return false;
//	���ڵ�i�����ݽڵ㣬����true 
	else{
		e = p->data;
		return true;
	}
}

//��Ԫ��ֵ��������λ�ã�ʱ�临�Ӷ�ΪO(n)
int LocateElem(DLinkList *L, ElemType e){
	int i=1;
	DLinkList *p = L->next;	//pָ��
	while(p!=NULL && p->data!=e){
		p=p->next;
		i++;
	}
//	������Ԫ��ֵΪe�Ľڵ㣬����0 
	if(p=NULL)
		return 0;
//	����Ԫ��ֵΪe�Ľڵ㣬���������߼����i 
	else
		return i;
}

//��������Ԫ�أ�ʱ�临�Ӷ�ΪO(n) 
bool ListInsert(DLinkList *&L, int i, ElemType e){
	int j=0;
	DLinkList *p = L, *s;	//pָ��ͷ�ڵ㣬j����Ϊ0
//	���ҵ�i-1���ڵ� 
	while(j<i-1 && p!=NULL){
		j++;
		p=p->next;
	}
//	δ�ҵ���i-1���ڵ㣬����false 
	if(p == NULL)
		return false;
	else{
		s = (DLinkList *)malloc(sizeof(DLinkList));
		s->data = e;
		s->next = p->next;	//��*p֮�����*s�ڵ� 
//		��*p�ڵ���ں�̽ڵ㣬�޸���ǰ��ָ�� 
		if(p->next!=NULL)
			p->next->prior = s;
		s->prior = p;
		p->next = s;
		return true;
	}
}

//ɾ������Ԫ�أ�ʱ�临�Ӷ�ΪO(n)
bool ListDelete(DLinkList *&L, int i, ElemType e){
	int j=0;
	DLinkList *p=L, *q;
	while(j<i-1 && p!=NULL){
		j++;
		p = p->next;
	}
//	δ�ҵ���i-1���ڵ� 
	if(p==NULL)
		return false;
//	�ҵ���i-1���ڵ� 
	else{
		q = p->next;	//qָ���i���ڵ� 
//		�������ڵ�i���ڵ�ʱ������false 
		if(q==NULL)
			return false;
		e = q->data;
		p->next = q->next;	//��˫������ɾ��*q�ڵ� 
//		��*p�ڵ���ں�̽ڵ㣬�޸���ǰ��ָ�� 
		if(q->next!=NULL)
			q->next->prior = p;
		free(q);
		return true;
	}
}

//��˫���������Ԫ������ 
//	�ȹ���ֻ��һ��ͷ�ڵ��˫����L���ٲ���ͷ�巨���� 
void reverse(DLinkList *&L){
	DLinkList *p=L->next, *q;	//pָ��ʼ�ڵ� 
	L->next =NULL;	//����ֻ��ͷ�ڵ��˫����L 
//	����L�����ݽڵ� 
	while(p!=NULL){
		q = p->next;//��Ϊͷ�巨���޸�*p��next����q����p�ĺ�̽ڵ� 
		p->next = L->next;
//		��L�д������ݽڵ㣬�޸���ǰ��ָ�� 
		if(L->next!=NULL)
			L->next->prior = p;
		L->next = p;
		p->prior = L;
		p = q;	//��p����ָ�����̽ڵ㣻 
	}
}

//��˫����������� 
void sort(DLinkList *&L){
	DLinkList *p, *pre, *q;
	p = L->next->next;	//pָ���2�����ݽڵ� 
	L->next->next = NULL;//����ֻ��һ�����ݽڵ�������
	while(p!=NULL){
		q = p->next;	//q����*p�ĺ�̽ڵ��ָ��
		pre = L;	//�������ͷ���бȽϣ�preָ��*p��ǰ����� 
		while(pre->next!=NULL && pre->next->data < p->data)
			pre = pre->next;	//����������Ҳ���*p��ǰ���ڵ�*pre 
		p->next = pre->next;	//��*pre֮�����*p�ڵ�
		if(pre->next!=NULL)
			pre->next->prior = p;
		pre->next = p;
		p->prior = pre;
		p = q;	//ɨ��ԭ˫����ʣ��Ľڵ�
	}
}

//��ѭ��˫������ɾ����һ��data��ֵΪx�Ľڵ�
bool delElem(DLinkList *&L, ElemType x){
	DLinkList *p = L->next;	//pָ���1�����ݽڵ�
	while(p!=L && p->data != x)
		p = p->next;
//	�ҵ���һ��Ԫ��ֵΪx�Ľڵ� 
	if(p!=L){
		p->next->prior = p->prior;	//ɾ���ڵ�*p 
		p->prior->next = p->next;
		free(p);
		return true;
	}
	else
		return false;
}

main(){
	DLinkList *L;
	int a[] = {1,2,3,4,5,6};
	ElemType e=1;
	CreateListF(L,a,6);
//	CreateListR(L,a,6);
//	GetElem(L,3,e);
//	e = LocateElem(L,2);
//	ListInsert(L,3,e); 
//	ListDelete(L,3,e);
//	sort(L);
//	reverse(L);

//	delElem(L, 5);	//�˺�����Ҫ��˫����ѭ�������

	DispList(L);
	cout<<e;
}
