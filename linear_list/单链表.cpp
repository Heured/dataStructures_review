#include<iostream>
using namespace std;

typedef int ElemType;
 
//���嵥����ڵ����� 
typedef struct LNode{ 
	ElemType data;
	struct LNode *next;
}LinkList;

//ͷ�巨�����������о��й���ջ����˼��ʱ�临�Ӷ�O(n)
void CreateListF(LinkList *&L, ElemType a[],int n){
	LinkList *s;
	int i;
	L = (LinkList *)malloc(sizeof(LinkList));
	L->next = NULL;	//����ͷ�ڵ㣬��next����ΪNULL
//	L->next = L;
//	ѭ���������ݽڵ� 
	for(i=0; i<n; i++){
		s = (LinkList *)malloc(sizeof(LinkList));
		s->data = a[i];	//�������ݽڵ�*s 
		s->next = L->next;	//��*s����ԭ��ʼ�ڵ�֮ǰ��ͷ�ڵ�֮�� 
		L->next = s;
	}
}

//β�巨������������������˳����в��룬ʱ�临�Ӷ�ΪO(n) 
void CreateListR(LinkList *&L, ElemType a[],int n){
	LinkList *s, *r;
	int i;
	L = (LinkList *)malloc(sizeof(LinkList));	//����ͷ�ڵ� 
	r = L;	//r��ʼʱָ��ͷ�ڵ㣬�Ժ�ʼ��ָ��β�ڵ�
//	ѭ���������ݽڵ� 
	for(i=0; i<n; i++){
		s = (LinkList *)malloc(sizeof(LinkList));
		s->data = a[i];	//�������ݽڵ�*s 
		r->next = s;	//��*s����*r֮��
		r = s;
	}
	r->next = NULL;	//β�ڵ�next����ΪNULL 
//	r->next = L;
}

//��ʼ��������ʱ�临�Ӷ�ΪO(1) 
void InitList(LinkList *&L){
	L = (LinkList *)malloc(sizeof(LinkList));
	L->next = NULL;	//����ͷ�ڵ㣬��next����ΪNULL
}

//���ٵ�����ʱ�临�Ӷ�ΪO(n) 
void DestroyList(LinkList *&L){
	LinkList *pre = L, *p = L->next;	//preָ��p��ǰ���ڵ�
//	����������L 
	while(p!=NULL){
		free(pre);	//�ͷ�*pre�ڴ� 
		pre = p;	//pre��pͬ������һ���ڵ� 
		p = p->next;
	}
	free(pre);	//ѭ���������ͷ�preָ���β�ڵ���ڴ� 
}

//�жϵ������Ƿ�Ϊ�գ�ʱ�临�Ӷ�ΪO(1)
bool ListEmpty(LinkList *L){
	return L->next==NULL;
} 

//�������ȣ�ʱ�临�Ӷ�ΪO(n)
int ListLength(LinkList *L){
	int n=0;
	LinkList *p = L;	//pָ��ͷ�ڵ㣬n��0 
	while(p->next!=NULL){
		n++;
		p = p->next;
	}
	return n;	//ѭ��������pָ��β�ڵ㣬�����nΪ�ڵ���� 
}

//���������ʱ�临�Ӷ�ΪO(n)
void DispList(LinkList *L){
	LinkList *p = L->next;	//pָ��ʼ�ڵ�
//	������������p��Ϊ��ʱ���*p�ڵ��dataֵ 
	while(p!=NULL){
		cout<<p->data<<' ';
		p = p->next;
	}
	cout<<endl;
}

//��������ĳ������Ԫ��ֵ��ʱ�临�Ӷ�ΪO(n)
bool GetElem(LinkList *L, int i, ElemType &e){
	int j = 0;
	LinkList *p = L;	//pָ��ͷ�ڵ㣬j��0
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
int LocateElem(LinkList *L, ElemType e){
	int i=1;
	LinkList *p = L->next;	//pָ��
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
bool ListInsert(LinkList *&L, int i, ElemType e){
	int j=0;
	LinkList *p = L, *s;	//pָ��ͷ�ڵ㣬j��Ϊ0
//	���ҵ�i-1���ڵ� 
	while(j<i-1 && p!=NULL){
		j++;
		p=p->next;
	}
//	û���ҵ���i-1���ڵ㣬����false 
	if(p==NULL)
		return false;
//	�ҵ���i-1���ڵ�֮�󣬲����½ڵ㲢����true 
	else{
		s = (LinkList *)malloc(sizeof(LinkList));
		s->data = e;
		s->next = p->next;
		p->next = s;
		return true;
	}
}

//���������������²�������Ԫ�� 
void OrderListInsert(LinkList *&L, ElemType e){
	LinkList *pre = L, *p;
//	����Ҫ����ڵ��ǰ���ڵ�*pre 
	while(pre->next!=NULL &&pre->next->data<e)
		pre = pre->next;
	p = (LinkList *)malloc(sizeof(LinkList));
	p->data = e;	//�������e�����ݽڵ�*p 
	p->next = pre->next;	//��*pre�ڵ�֮�����*p�ڵ� 
	pre->next = p;
}

//ɾ������Ԫ�أ�ʱ�临�Ӷ�ΪO(n)
bool ListDelete(LinkList *&L, int i, ElemType &e){
	int j=0;
	LinkList *p=L, *q;
	while(j<i-1 && p!=NULL){
		j++;
		p = p->next;
	}
//	δ�ҵ���i-1���ڵ㣬����false 
	if(p==NULL)
		return false;
//	�ҵ���i-1���ڵ� 
	else{
		q = p->next;	//qָ���i���ڵ�
//		��������ڵ�i���ڵ㣬����false 
		if(q==NULL)
			return false;
		e=q->data;	//��ȡ��ɾ��Ԫ�ص�ֵ 
		p->next = q->next;	//�ӵ�������ɾ��*q�ڵ� 
		free(q);	//�ͷ�*q�ڵ��ڴ� 
		return true;
	} 
}

//��L={a1,b1,a2,b2,...,an,bn}����ΪL1={a1,...,an}��L2={bn,...b1}
//	����L1ʹ��L��ͷ�ڵ�
void split(LinkList *&L, LinkList *&L1, LinkList *&L2){
	LinkList *p = L->next, *q, *r1;	//pָ���һ�����ݽڵ�
	L1 = L;	//L1����ԭ����L��ͷ�ڵ�
	r1 = L1;	//r1ʼ��ָ��L1��β�ڵ�
	L2 = (LinkList *)malloc(sizeof(LinkList));	//����L2��ͷ�ڵ�
	L2->next = NULL;	//��L2��nextΪNULL
	while(p!=NULL){
		r1->next = p;
		r1 = p;
		p = p->next;
		q = p->next;	//����ͷ�巨�޸�p��next��������q����*p�ĺ�̽ڵ� 
		p->next = L2->next;	//����ͷ�巨��*p����L2�� 
		L2->next = p; 
		p = q;	//p����ָ��ai+1�ڵ� 	
	}
	r1->next = NULL;	//L1β�ڵ�next�ÿ� 
}

//ɾ��һ��������L��Ԫ��ֵ���Ľڵ�
void delMaxNode(LinkList *&L){
	LinkList *p = L->next, *pre = L, *maxp = p, *maxpre = pre;
	while(p!=NULL){
//		����ҵ�����ֵ�ڵ㣬����maxp�Լ�maxpre 
		if(maxp->data < p->data){
			maxp = p; 
			maxpre = pre;
		}
		pre = p; 
		p = p->next;	//p��preͬ������һ���ڵ� 
	}
	maxpre->next = maxp->next;	//�ڵ�������ɾ��*maxp�ڵ� 
	free(maxp);	//�ͷ�*maxp�ڵ��ڴ� 
}

//��һ��������һ�����ݽڵ�ĵ�����L�����е�������
//	��ֻ����һ��Ԫ����Ϊһ��������
//	��һ��һ���Ƚ�������ͷ�巨����β�巨 
void sort(LinkList *&L){
	LinkList *p, *pre, *q;
	p = L->next->next;	//pָ��ڶ������ݽڵ� 
	L->next->next = NULL;	//����ֻ��һ�����ݽڵ�������
	while(p!=NULL){
		q = p->next;	//q����*p�ĺ�̽ڵ��ָ�� 
		pre = L;	//�������ͷ���бȽϣ�preָ�����*p��ǰ���ڵ� 
		//����������ҵ�����*p��ǰ���ڵ�*pre 
		while(pre->next!=NULL && pre->next->data<p->data)
			pre = pre->next;
		p->next = pre->next;	//��*p������*pre֮�� 
		pre->next = p;
		p = q;	//��������������ʣ��Ľڵ� 
	} 
}

//��n�ۼ�ѭ����������data��ֵΪx�Ľڵ����
int count(LinkList *L, ElemType x){
	int n=0;
	LinkList *p = L->next;	//pָ���1�����ݽڵ�,n��0
	while(p!=L){
//		�ҵ�ֵΪx�Ľڵ��n��1
		if(p->data == x)
			n++;
		p = p->next;	//pָ����һ���ڵ� 
	}
	return n;
}

//����������Ĺ鲢 
//	��������С�������� 
void UnionList1(LinkList *LA, LinkList *LB, LinkList *&LC){
	LinkList *pa=LA->next, *pb=LB->next, *r, *s;
	LC = (LinkList *)malloc(sizeof(LinkList));	//����LCͷ�ڵ�
	r = LC;
	while(pa!=NULL && pb!= NULL){
		if(pa->data < pb->data){
			s = (LinkList *)malloc(sizeof(LinkList));	//����*pa�ڵ�
			s->data = pa->data;
			r->next = s;	//����β�巨��*s�ڵ�ӵ�LCβ�� 
			r=s;
			pa=pa->next;
		}else{
			s = (LinkList *)malloc(sizeof(LinkList));	//����*pb�ڵ�
			s->data = pb->data;
			r->next = s;	//����β�巨��*s�ڵ�ӵ�LCβ�� 
			r=s;
			pb=pb->next;
		}
	}
	while(pa!=NULL){
		s = (LinkList *)malloc(sizeof(LinkList));	//����*pa�ڵ�
			s->data = pb->data;
		r->next = s;	//����β�巨��*s�ڵ�ӵ�LCβ�� 
		r=s;
		pa=pa->next;
	}
	while(pb!=NULL){
		s = (LinkList *)malloc(sizeof(LinkList));	//����*pb�ڵ�
			s->data = pb->data;
		r->next = s;	//����β�巨��*s�ڵ�ӵ�LCβ�� 
		r=s;
		pb=pb->next;
	}
	r->next = NULL;	//β�ڵ�next�ÿ� 
}

//3�������������������(ÿ����������������ֵ��ͬ�Ľڵ㣬��3���������п��ܴ�������ֵ��ͬ�Ľڵ�)
//���������������������������Ԫ�����ϵ�LA�У�ֻ���¹����Ҳ��ظ���Ԫ��
//ʱ�临�Ӷ�ΪO(m+n+p)��m��n��p�ֱ�Ϊ3����ĳ���
//ͬ��������β�巨���� 
void Commnode(LinkList *&LA, LinkList *LB, LinkList *LC){
	LinkList *pa=LA->next, *pb=LB->next, *pc=LC->next, *q, *r;
	LA->next = NULL;	//��ʱLA��Ϊ�½��������ͷ�ڵ� 
	r = LA;	//rʼ��ָ���µ������β�ڵ� 
	while(pa!=NULL){
//		*pa�ڵ���LB�нڵ���бȽ� 
		while(pb!=NULL && pa->data > pb->data)
			pb = pb->next;
//		*pa�ڵ���LC�нڵ���бȽ� 
		while(pc!=NULL && pa->data >pc->data)
			pc = pc->next;
		if(pb!=NULL && pc!=NULL &&pa->data==pb->data && pa->data==pc->data){
			r->next = pa;	//��*pa�ڵ���뵽LA�� 
			r=pa;
			pa = pa->next;	//pa�Ƶ���һ���ڵ� 
		}else{	//pa��ָ�ڵ㲻�ǹ����ڵ㣬��ɾ���� 
			q=pa;
			pa=pa->next;	//pa�Ƶ���һ���ڵ� 
			free(q);	//�ͷŷǹ����ڵ� 
		}
	}
	r->next = NULL;	//β�ڵ��next�ÿ� 
}

//ɾ������������ظ�ֵ�ڵ㣬ʱ�临�Ӷ�O(n) 
void dels(LinkList *&L){
	LinkList *p = L->next,*q;
	while(p->next!=NULL){
		//�ҵ��ظ�ֵ�Ľڵ�
		if(p->data==p->next->data){
			q = p->next;	//qָ������ظ�ֵ�Ľڵ�
			p->next = q->next;	//�ͷ�*q�ڵ��ڴ� 
			free(q); 
		}
		else
			p = p->next;	//�����ظ��ڵ㣬pָ������ 
	}
} 

//�ݹ�ʵ���ͷŵ����� 
//	���Կ����Ǵ�β�ڵ㿪ʼ�ͷ��ڴ�� 
void release(LinkList *L){
	if(L!=NULL){
		release(L->next);
		free(L);
	}
}

main(){
	LinkList *L;
//	LinkList *L1, *L2;
	int a[] = {1,2,3,4,5,6};
	ElemType e=1;
//	CreateListF(L,a,6);
	CreateListR(L,a,6);
//	GetElem(L,3,e);
//	e = LocateElem(L,2);
//	ListInsert(L,3,e); 
//	ListDelete(L,3,e);
//	split(L,L1,L2);
//	delMaxNode(L);
//	sort(L); 
//	e = count(L,9);		//��ʱ������Ϊѭ��״̬ 

	DispList(L);
//	DispList(L1);
//	DispList(L2);
	cout<<e;
	
} 

