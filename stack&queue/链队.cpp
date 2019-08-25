#include<iostream>
using namespace std;
typedef int ElemType;
#define MaxSize 50

typedef struct qnode{
	ElemType data;
	struct qnode* next;
}QNode;	//�������ݽڵ����Ͷ��� 

typedef struct{
	QNode *front;
	QNode *rear;
}LiQueue;	//�������Ͷ���

//��ʼ������ 
void InitQueue(LiQueue *&q){
	q = (LiQueue *)malloc(sizeof(LiQueue));
	q->front = q->rear = NULL;
}

//���ٶ��� 
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
	free(q);	//�ͷ����ӽڵ��ڴ� 
}

//�ж��Ƿ�Ϊ��
bool QueueEmpty(LiQueue *q){
	return (q->rear == NULL);
}

//����
void enQueue(LiQueue *&q, ElemType e){
	QNode *p;
	p = (QNode *)malloc(sizeof(QNode));
	p->data = e;
	p->next = NULL;
//	������Ϊ�գ����½ڵ���Ƕ���Ҳ�Ƕ�β 
	if(q->rear == NULL){
		q->front = q->rear = p;
	}else{
		q->rear->next = p;	//��*p�ڵ�������β������rearָ���� 
		q->rear = p;
	}
}

//����
bool deQueue(LiQueue *&q, ElemType &e){
	QNode *t;
	if(q->rear == NULL)
		return false;
	t = q->front;	//tָ���һ�����ݽڵ� 
//	������ֻ��һ���ڵ� 
	if(q->front == q->rear) 
		q->front = q->rear = NULL;
//	�������ж���ڵ� 
	else
		q->front = q->front->next;
	e = t->data;
	free(t);
	return true;
}

//********

//���ò���ͷ�ڵ�ֻ��һ��β�ڵ�ָ��rear��ѭ��������洢����
//	������ֻ��һ���ڵ��ʱ������ڵ���ͷ�ڵ�Ҳ��β�ڵ� 
//	���������ж���ڵ��ʱ��ѭ�����е�β�ڵ��next�ڵ����ͷ�ڵ� 

//��ʼ������ 
void initRQueue(QNode *&rear){
	rear = NULL;
}

//�ж϶����Ƿ�Ϊ��
bool RqueueEmpty(QNode *rear){
	return (rear == NULL);
}

//���� 
void enRQueue(QNode *&rear, ElemType x){
	QNode *p;
	p = (QNode *)malloc(sizeof(QNode));
	p->data = x;
//	�������Ϊ�� 
	if(rear == NULL){
		p->next = p;	//����ѭ������ 
		rear = p;
	}else{
		p->next = rear->next;	//��*p�ڵ����*rear�ڵ�֮�� 
		rear->next = p;
		rear = p;	//��rearָ���²���Ľڵ� 
	}
}

//����
bool deRQueue(QNode *&rear, ElemType &e){
	QNode *q;
	if(rear == NULL)	//�ӿ� 
		return false;
//	ԭ����ֻ��һ���ڵ� 
	else if(rear->next == rear){
		e = rear->data;
		free(rear);
		rear = NULL;
	}else{
		q = rear->next;	//ԭ�����ж���ڵ�
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
