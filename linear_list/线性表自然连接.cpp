#include<iostream>
using namespace std;
#define MaxCol 10

typedef int ElemType;
typedef struct Node1{	//定义数据节点类型 
	ElemType data[MaxCol];	//存放一行的数据 
	struct Node1 *next;	//指向后继节点 
}DList;	//行节点类型 

typedef struct Node2{
	int Row, Col;	//行数和列数 
	DList *next;	//指向第一个数据节点 
}HList;	//头节点类型

//采用尾插法建立单链表，选输入行数列数，然后输入各行数据
//时间复杂度为O(m*n) 
void CreateTable(HList *&h){
	int i,j;
	DList *r, *s;
	h = (HList *)malloc(sizeof(HList));
	h->next = NULL;
	cout<<"表的行数，列数(空格分隔)：";
	cin>>h->Row>>h->Col;	//输入表的行数和列数

	for(i=0; i<h->Row; i++){
		cout<<"第"<<i+1<<"行："; 
		s = (DList *)malloc(sizeof(DList));	//创建数据节点 
		for(j=0; j<h->Col; j++)	//输入一行的数据 
			cin>>s->data[j];
		if(h->next == NULL)	//插入第一个数据节点 
			h->next = s;
		else	//插入其他数据节点 
			r->next = s;	//将*s插入到*r节点之后 
		r = s;	//r始终指向尾节点 
	}
	r->next = NULL;	//尾节点next置空
}

//销毁单链表
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

//输出单链表
void DispTable(HList *h){
	int j;
	DList *p = h->next;	//p指向开始行节点 
	while(p!=NULL){
//		输出一行的数据 
		for(j=0; j<h->Col; j++)
			cout<<p->data[j]<<' ';
		cout<<endl;
		p = p->next;	//p指向下一行节点 
	}
}

//A表:m1行，n1列；	B表m2行n2列
//C表为A表与B表的自然连接，连接条件，A表的第i列与B表的第j列相等。
void LinkTable(HList *h1, HList *h2, HList *&h){
	int i,j,k;
	DList *p = h1->next, *q, *s, *r;
	cout<<"连接字段是：第1个表序号，第2个表序号：";
	cin>>i>>j;
	h = (HList *)malloc(sizeof(HList));	//创建结果表头节点
	h->Row = 0;
	h->Col = h1->Col + h2->Col;	//置列数为表1与表2的列数和 
	h->next = NULL;
	while(p!=NULL){	//遍历表1 
		q = h2->next;	//q指向表2的开始 
		while(q!=NULL){	//遍历表2 
			if(p->data[i-1] == q->data[j-1]){
				s = (DList *)malloc(sizeof(DList));	//创建一个数据节点*s
//				复制表1当前行 
				for(k=0;k<h1->Col;k++)
					s->data[k] = p->data[k];
//				复制表2当前行 
				for(k=0;k<h2->Col;k++)
					s->data[h1->Col+k] = q->data[k];
//				若插入第一个数据节点，将*s接在头节点之后 
				if(h->next == NULL)
					h->next = s;
//				若不是插入第一个数据节点，将*s接在*r节点之后 
				else
					r->next = s;
				r = s;	//r始终指向尾节点 
				h->Row++;	//表行数加1
			}
			q = q->next;	//表2下移一行 
		}
		p = p->next;	//表1下移一行 
	}
	r->next = NULL;	//表h尾节点置空
}
main(){
	HList *h1, *h2, *h;
	cout<<"表1："<<endl;
	CreateTable(h1);
	cout<<"表2："<<endl;
	CreateTable(h2);
	LinkTable(h1,h2,h);
	cout<<"连接结果表:"<<endl;
	DispTable(h);
	DestroyTable(h1); 
	DestroyTable(h2);
	DestroyTable(h);	 
}
