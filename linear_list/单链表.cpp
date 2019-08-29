#include<iostream>
using namespace std;

typedef int ElemType;
 
//定义单链表节点类型 
typedef struct LNode{ 
	ElemType data;
	struct LNode *next;
}LinkList;

//头插法建立单链表，感觉有股入栈的意思，时间复杂度O(n)
void CreateListF(LinkList *&L, ElemType a[],int n){
	LinkList *s;
	int i;
	L = (LinkList *)malloc(sizeof(LinkList));
	L->next = NULL;	//创建头节点，其next域置为NULL
//	L->next = L;
//	循环建立数据节点 
	for(i=0; i<n; i++){
		s = (LinkList *)malloc(sizeof(LinkList));
		s->data = a[i];	//创建数据节点*s 
		s->next = L->next;	//将*s插在原开始节点之前，头节点之后 
		L->next = s;
	}
}

//尾插法建立单链表，按人理解的顺序进行插入，时间复杂度为O(n) 
void CreateListR(LinkList *&L, ElemType a[],int n){
	LinkList *s, *r;
	int i;
	L = (LinkList *)malloc(sizeof(LinkList));	//创建头节点 
	r = L;	//r开始时指向头节点，以后始终指向尾节点
//	循环建立数据节点 
	for(i=0; i<n; i++){
		s = (LinkList *)malloc(sizeof(LinkList));
		s->data = a[i];	//创建数据节点*s 
		r->next = s;	//将*s接在*r之后
		r = s;
	}
	r->next = NULL;	//尾节点next域置为NULL 
//	r->next = L;
}

//初始化单链表，时间复杂度为O(1) 
void InitList(LinkList *&L){
	L = (LinkList *)malloc(sizeof(LinkList));
	L->next = NULL;	//创建头节点，其next域置为NULL
}

//销毁单链表，时间复杂度为O(n) 
void DestroyList(LinkList *&L){
	LinkList *pre = L, *p = L->next;	//pre指向p的前驱节点
//	遍历单链表L 
	while(p!=NULL){
		free(pre);	//释放*pre内存 
		pre = p;	//pre与p同步后移一个节点 
		p = p->next;
	}
	free(pre);	//循环结束后，释放pre指向的尾节点的内存 
}

//判断单链表是否为空，时间复杂度为O(1)
bool ListEmpty(LinkList *L){
	return L->next==NULL;
} 

//求单链表长度，时间复杂度为O(n)
int ListLength(LinkList *L){
	int n=0;
	LinkList *p = L;	//p指向头节点，n置0 
	while(p->next!=NULL){
		n++;
		p = p->next;
	}
	return n;	//循环结束，p指向尾节点，其序号n为节点个数 
}

//输出单链表，时间复杂度为O(n)
void DispList(LinkList *L){
	LinkList *p = L->next;	//p指向开始节点
//	遍历单链表，当p不为空时输出*p节点的data值 
	while(p!=NULL){
		cout<<p->data<<' ';
		p = p->next;
	}
	cout<<endl;
}

//求单链表中某个数据元素值，时间复杂度为O(n)
bool GetElem(LinkList *L, int i, ElemType &e){
	int j = 0;
	LinkList *p = L;	//p指向头节点，j置0
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
int LocateElem(LinkList *L, ElemType e){
	int i=1;
	LinkList *p = L->next;	//p指向
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
bool ListInsert(LinkList *&L, int i, ElemType e){
	int j=0;
	LinkList *p = L, *s;	//p指向头节点，j置为0
//	查找第i-1个节点 
	while(j<i-1 && p!=NULL){
		j++;
		p=p->next;
	}
//	没有找到第i-1个节点，返回false 
	if(p==NULL)
		return false;
//	找到第i-1个节点之后，插入新节点并返回true 
	else{
		s = (LinkList *)malloc(sizeof(LinkList));
		s->data = e;
		s->next = p->next;
		p->next = s;
		return true;
	}
}

//在有序单链表的情况下插入数据元素 
void OrderListInsert(LinkList *&L, ElemType e){
	LinkList *pre = L, *p;
//	查找要插入节点的前驱节点*pre 
	while(pre->next!=NULL &&pre->next->data<e)
		pre = pre->next;
	p = (LinkList *)malloc(sizeof(LinkList));
	p->data = e;	//创建存放e的数据节点*p 
	p->next = pre->next;	//在*pre节点之后插入*p节点 
	pre->next = p;
}

//删除数据元素，时间复杂度为O(n)
bool ListDelete(LinkList *&L, int i, ElemType &e){
	int j=0;
	LinkList *p=L, *q;
	while(j<i-1 && p!=NULL){
		j++;
		p = p->next;
	}
//	未找到第i-1个节点，返回false 
	if(p==NULL)
		return false;
//	找到第i-1个节点 
	else{
		q = p->next;	//q指向第i个节点
//		如果不存在第i个节点，返回false 
		if(q==NULL)
			return false;
		e=q->data;	//获取被删除元素的值 
		p->next = q->next;	//从单链表中删除*q节点 
		free(q);	//释放*q节点内存 
		return true;
	} 
}

//将L={a1,b1,a2,b2,...,an,bn}区分为L1={a1,...,an}、L2={bn,...b1}
//	并且L1使用L的头节点
void split(LinkList *&L, LinkList *&L1, LinkList *&L2){
	LinkList *p = L->next, *q, *r1;	//p指向第一个数据节点
	L1 = L;	//L1利用原来的L的头节点
	r1 = L1;	//r1始终指向L1的尾节点
	L2 = (LinkList *)malloc(sizeof(LinkList));	//创建L2的头节点
	L2->next = NULL;	//置L2的next为NULL
	while(p!=NULL){
		r1->next = p;
		r1 = p;
		p = p->next;
		q = p->next;	//由于头插法修改p的next域，所以用q保存*p的后继节点 
		p->next = L2->next;	//采用头插法将*p插入L2中 
		L2->next = p; 
		p = q;	//p重新指向ai+1节点 	
	}
	r1->next = NULL;	//L1尾节点next置空 
}

//删除一个单链表L中元素值最大的节点
void delMaxNode(LinkList *&L){
	LinkList *p = L->next, *pre = L, *maxp = p, *maxpre = pre;
	while(p!=NULL){
//		如果找到更大值节点，更改maxp以及maxpre 
		if(maxp->data < p->data){
			maxp = p; 
			maxpre = pre;
		}
		pre = p; 
		p = p->next;	//p、pre同步后移一个节点 
	}
	maxpre->next = maxp->next;	//在单链表中删除*maxp节点 
	free(maxp);	//释放*maxp节点内存 
}

//将一个至少有一个数据节点的单链表L，进行递增排序
//	先只留第一个元素作为一个单链表
//	再一个一个比较来决定头插法还是尾插法 
void sort(LinkList *&L){
	LinkList *p, *pre, *q;
	p = L->next->next;	//p指向第二个数据节点 
	L->next->next = NULL;	//构造只含一个数据节点的有序表
	while(p!=NULL){
		q = p->next;	//q保存*p的后继节点的指针 
		pre = L;	//从有序表开头进行比较，pre指向插入*p的前驱节点 
		//在有序表中找到插入*p的前驱节点*pre 
		while(pre->next!=NULL && pre->next->data<p->data)
			pre = pre->next;
		p->next = pre->next;	//将*p插入于*pre之后 
		pre->next = p;
		p = q;	//继续遍历单链表剩余的节点 
	} 
}

//用n累计循环单链表中data域值为x的节点个数
int count(LinkList *L, ElemType x){
	int n=0;
	LinkList *p = L->next;	//p指向第1个数据节点,n置0
	while(p!=L){
//		找到值为x的节点后n增1
		if(p->data == x)
			n++;
		p = p->next;	//p指向下一个节点 
	}
	return n;
}

//两有序单链表的归并 
//	条件：从小到大排列 
void UnionList1(LinkList *LA, LinkList *LB, LinkList *&LC){
	LinkList *pa=LA->next, *pb=LB->next, *r, *s;
	LC = (LinkList *)malloc(sizeof(LinkList));	//创建LC头节点
	r = LC;
	while(pa!=NULL && pb!= NULL){
		if(pa->data < pb->data){
			s = (LinkList *)malloc(sizeof(LinkList));	//复制*pa节点
			s->data = pa->data;
			r->next = s;	//采用尾插法将*s节点接到LC尾部 
			r=s;
			pa=pa->next;
		}else{
			s = (LinkList *)malloc(sizeof(LinkList));	//复制*pb节点
			s->data = pb->data;
			r->next = s;	//采用尾插法将*s节点接到LC尾部 
			r=s;
			pb=pb->next;
		}
	}
	while(pa!=NULL){
		s = (LinkList *)malloc(sizeof(LinkList));	//复制*pa节点
			s->data = pb->data;
		r->next = s;	//采用尾插法将*s节点接到LC尾部 
		r=s;
		pa=pa->next;
	}
	while(pb!=NULL){
		s = (LinkList *)malloc(sizeof(LinkList));	//复制*pb节点
			s->data = pb->data;
		r->next = s;	//采用尾插法将*s节点接到LC尾部 
		r=s;
		pb=pb->next;
	}
	r->next = NULL;	//尾节点next置空 
}

//3个递增排序的有序单链表(每个单链表不存在数据值相同的节点，但3个单链表中可能存在数据值相同的节点)
//将三个有序单链表包含的所有数据元素整合到LA中，只留下共有且不重复的元素
//时间复杂度为O(m+n+p)，m、n、p分别为3个表的长度
//同样是利用尾插法建表 
void Commnode(LinkList *&LA, LinkList *LB, LinkList *LC){
	LinkList *pa=LA->next, *pb=LB->next, *pc=LC->next, *q, *r;
	LA->next = NULL;	//此时LA作为新建单链表的头节点 
	r = LA;	//r始终指向新单链表的尾节点 
	while(pa!=NULL){
//		*pa节点与LB中节点进行比较 
		while(pb!=NULL && pa->data > pb->data)
			pb = pb->next;
//		*pa节点与LC中节点进行比较 
		while(pc!=NULL && pa->data >pc->data)
			pc = pc->next;
		if(pb!=NULL && pc!=NULL &&pa->data==pb->data && pa->data==pc->data){
			r->next = pa;	//将*pa节点插入到LA中 
			r=pa;
			pa = pa->next;	//pa移到下一个节点 
		}else{	//pa所指节点不是公共节点，则删除它 
			q=pa;
			pa=pa->next;	//pa移到下一个节点 
			free(q);	//释放非公共节点 
		}
	}
	r->next = NULL;	//尾节点的next置空 
}

//删除有序单链表的重复值节点，时间复杂度O(n) 
void dels(LinkList *&L){
	LinkList *p = L->next,*q;
	while(p->next!=NULL){
		//找到重复值的节点
		if(p->data==p->next->data){
			q = p->next;	//q指向这个重复值的节点
			p->next = q->next;	//释放*q节点内存 
			free(q); 
		}
		else
			p = p->next;	//不是重复节点，p指针下移 
	}
} 

//递归实现释放单链表 
//	可以看出是从尾节点开始释放内存的 
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
//	e = count(L,9);		//此时单链表为循环状态 

	DispList(L);
//	DispList(L1);
//	DispList(L2);
	cout<<e;
	
} 

