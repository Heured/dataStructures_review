#include<iostream>
using namespace std;
typedef int ElemType;

typedef struct DNode{	//定义双链表节点类型 
	ElemType data;	//存放元素值 
	struct DNode *prior;	//指向前驱节点 
	struct DNode *next;		//指向后继节点 
}DLinkList;

//头插法建立双链表 
void CreateListF(DLinkList *&L, ElemType a[], int n){
	DLinkList *s;
	int i;
	L = (DLinkList *)malloc(sizeof(DLinkList));	//创建头节点 
	L->prior = L->next = NULL;	//前后指针域置为NULL 
//	L->prior = L->next = L;
//	循环建立数据节点 
	for(i=0; i<n; i++){
		s = (DLinkList *)malloc(sizeof(DLinkList));
		s->data = a[i];
		s->next = L->next;	//将*s插入头节点之后 
		if(L->next!=NULL)	//若L存在数据节点，修改L->next的前驱指针 
			L->next->prior = s;
		L->next = s;
		s->prior = L;
	} 
}

//尾插法建立双链表 
void CreateListR(DLinkList *&L, ElemType a[], int n){
	DLinkList *s, *r;
	int i;
	L = (DLinkList *)malloc(sizeof(DLinkList));	//创建头节点 
	r = L;
	for(i=0; i<n; i++){
		s = (DLinkList *)malloc(sizeof(DLinkList));
		s->data = a[i];
		r->next = s; 
		s->prior = r;	//将*s接在*r之后 
		r = s;	//r指向尾结点 
	}
	r->next = NULL;	//尾节点next域置为NULL 
//	r->next = L;
}

//销毁双链表，时间复杂度为O(n) 
void DestroyList(DLinkList *&L){
	DLinkList *pre = L, *p = L->next;	//pre指向p的前驱节点
//	遍历单链表L
	while(p!=NULL){
		free(pre);	//释放*pre内存 
		pre = p;	//pre与p同步后移一个节点 
		p = p->next;
	}
	free(pre);	//循环结束后，释放pre指向的尾节点的内存 
}

//判断双链表是否为空，时间复杂度为O(1)
bool ListEmpty(DLinkList *L){
	return L->next==NULL;
} 

//求双链表长度，时间复杂度为O(n)
int ListLength(DLinkList *L){
	int n=0;
	DLinkList *p = L;	//p指向头节点，n置0 
	while(p->next!=NULL){
		n++;
		p = p->next;
	}
	return n;	//循环结束，p指向尾节点，其序号n为节点个数 
}

//输出单链表，时间复杂度为O(n)
void DispList(DLinkList *L){
	DLinkList *p = L->next;	//p指向开始节点
//	遍历单链表，当p不为空时输出*p节点的data值 
	while(p!=NULL){
		cout<<p->data<<' ';
		p = p->next;
	}
	cout<<endl;
}

//求单链表中某个数据元素值，时间复杂度为O(n)
bool GetElem(DLinkList *L, int i, ElemType &e){
	int j = 0;
	DLinkList *p = L;	//p指向头节点，j置0
	while(j<i && p!=NULL){
		j++;
		p = p->next;
	}
//	不存在第i个数据节点，返回false 
	if(p==NULL)
		return false;
//	存在第i个数据节点，返回true 
	else{
		e = p->data;
		return true;
	}
}

//按元素值查找所在位置，时间复杂度为O(n)
int LocateElem(DLinkList *L, ElemType e){
	int i=1;
	DLinkList *p = L->next;	//p指向
	while(p!=NULL && p->data!=e){
		p=p->next;
		i++;
	}
//	不存在元素值为e的节点，返回0 
	if(p=NULL)
		return 0;
//	存在元素值为e的节点，返回它的逻辑序号i 
	else
		return i;
}

//插入数据元素，时间复杂度为O(n) 
bool ListInsert(DLinkList *&L, int i, ElemType e){
	int j=0;
	DLinkList *p = L, *s;	//p指向头节点，j设置为0
//	查找第i-1个节点 
	while(j<i-1 && p!=NULL){
		j++;
		p=p->next;
	}
//	未找到第i-1个节点，返回false 
	if(p == NULL)
		return false;
	else{
		s = (DLinkList *)malloc(sizeof(DLinkList));
		s->data = e;
		s->next = p->next;	//在*p之后插入*s节点 
//		若*p节点存在后继节点，修改其前驱指针 
		if(p->next!=NULL)
			p->next->prior = s;
		s->prior = p;
		p->next = s;
		return true;
	}
}

//删除数据元素，时间复杂度为O(n)
bool ListDelete(DLinkList *&L, int i, ElemType e){
	int j=0;
	DLinkList *p=L, *q;
	while(j<i-1 && p!=NULL){
		j++;
		p = p->next;
	}
//	未找到第i-1个节点 
	if(p==NULL)
		return false;
//	找到第i-1个节点 
	else{
		q = p->next;	//q指向第i个节点 
//		当不存在第i个节点时，返回false 
		if(q==NULL)
			return false;
		e = q->data;
		p->next = q->next;	//从双链表中删除*q节点 
//		若*p节点存在后继节点，修改其前驱指针 
		if(q->next!=NULL)
			q->next->prior = p;
		free(q);
		return true;
	}
}

//将双链表的所有元素逆置 
//	先构造只有一个头节点的双链表L，再采用头插法逆置 
void reverse(DLinkList *&L){
	DLinkList *p=L->next, *q;	//p指向开始节点 
	L->next =NULL;	//构造只有头节点的双链表L 
//	遍历L的数据节点 
	while(p!=NULL){
		q = p->next;//因为头插法会修改*p的next域，用q保存p的后继节点 
		p->next = L->next;
//		若L中存在数据节点，修改其前驱指针 
		if(L->next!=NULL)
			L->next->prior = p;
		L->next = p;
		p->prior = L;
		p = q;	//让p重新指向其后继节点； 
	}
}

//将双链表递增排序 
void sort(DLinkList *&L){
	DLinkList *p, *pre, *q;
	p = L->next->next;	//p指向第2个数据节点 
	L->next->next = NULL;//构造只有一个数据节点的有序表
	while(p!=NULL){
		q = p->next;	//q保存*p的后继节点的指针
		pre = L;	//从有序表开头进行比较，pre指向*p的前驱结点 
		while(pre->next!=NULL && pre->next->data < p->data)
			pre = pre->next;	//在有序表中找插入*p的前驱节点*pre 
		p->next = pre->next;	//在*pre之后插入*p节点
		if(pre->next!=NULL)
			pre->next->prior = p;
		pre->next = p;
		p->prior = pre;
		p = q;	//扫描原双链表剩余的节点
	}
}

//在循环双链表中删除第一个data域值为x的节点
bool delElem(DLinkList *&L, ElemType x){
	DLinkList *p = L->next;	//p指向第1个数据节点
	while(p!=L && p->data != x)
		p = p->next;
//	找到第一个元素值为x的节点 
	if(p!=L){
		p->next->prior = p->prior;	//删除节点*p 
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

//	delElem(L, 5);	//此函数需要在双链表循环情况下

	DispList(L);
	cout<<e;
}
