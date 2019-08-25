#include<iostream>
using namespace std;
typedef int ElemType;
#define MaxSize 50

typedef struct qnode{
	ElemType data;
	struct qnode* next;
}QNode;	//链队数据节点类型定义 

typedef struct{
	QNode *front;
	QNode *rear;
}LiQueue;	//链队类型定义

//初始化队列 
void InitQueue(LiQueue *&q){
	q = (LiQueue *)malloc(sizeof(LiQueue));
	q->front = q->rear = NULL;
}

//销毁队列 
void DestroyQueue(LiQueue *&q){
	QNode *p = q->front, *r;
	if(p!=NULL){
		r = p->next;
		while(r != NULL){
			free(p);
			p = r;
			r = p->next;
		}
	}
	free(p);
	free(q);	//释放链队节点内存 
}

//判断是否为空
bool QueueEmpty(LiQueue *q){
	return (q->rear == NULL);
}

//进队
void enQueue(LiQueue *&q, ElemType e){
	QNode *p;
	p = (QNode *)malloc(sizeof(QNode));
	p->data = e;
	p->next = NULL;
//	若链队为空，则新节点既是队首也是队尾 
	if(q->rear == NULL){
		q->front = q->rear = p;
	}else{
		q->rear->next = p;	//将*p节点连到队尾，并将rear指向它 
		q->rear = p;
	}
}

//出队
bool deQueue(LiQueue *&q, ElemType &e){
	QNode *t;
	if(q->rear == NULL)
		return false;
	t = q->front;	//t指向第一个数据节点 
//	队列中只有一个节点 
	if(q->front == q->rear) 
		q->front = q->rear = NULL;
//	队列中有多个节点 
	else
		q->front = q->front->next;
	e = t->data;
	free(t);
	return true;
}

//********

//采用不带头节点只有一个尾节点指针rear的循环单链表存储队列
//	当队列只有一个节点的时候，这个节点是头节点也是尾节点 
//	当队列中有多个节点的时候，循环队列的尾节点的next节点便是头节点 

//初始化队列 
void initRQueue(QNode *&rear){
	rear = NULL;
}

//判断队列是否为空
bool RqueueEmpty(QNode *rear){
	return (rear == NULL);
}

//进队 
void enRQueue(QNode *&rear, ElemType x){
	QNode *p;
	p = (QNode *)malloc(sizeof(QNode));
	p->data = x;
//	如果链队为空 
	if(rear == NULL){
		p->next = p;	//构成循环链队 
		rear = p;
	}else{
		p->next = rear->next;	//将*p节点插入*rear节点之后 
		rear->next = p;
		rear = p;	//让rear指向新插入的节点 
	}
}

//出队
bool deRQueue(QNode *&rear, ElemType &e){
	QNode *q;
	if(rear == NULL)	//队空 
		return false;
//	原队中只有一个节点 
	else if(rear->next == rear){
		e = rear->data;
		free(rear);
		rear = NULL;
	}else{
		q = rear->next;	//原队中有多个节点
		e = q->data;
		rear->next = q->next;
		free(q); 
	}
	return true;
}

//********



main(){
//	LiQueue *q;
//	InitQueue(q);
//	ElemType a[] = {1,2,3,4,5},e;
//	for(int i=0;i<5;i++)
//		enQueue(q,a[i]);
//	cout<<q->rear->data<<endl;
//	deQueue(q,e);
//	cout<<e;

//	QNode *rear;
//	initRQueue(rear);
//	ElemType a[] = {1,2,3,4,5},e;
//	for(int i=0;i<5;i++)
//		enRQueue(rear,a[i]);
//	cout<<rear->data<<endl;


}
