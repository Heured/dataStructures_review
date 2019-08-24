#include<iostream>
using namespace std;
typedef int ElemType;
#define MaxSize 50

typedef struct{
	ElemType data[MaxSize];
	int front;	//��ͷָ�� 
	int count;	//������Ԫ�ظ��� 
}QuType;

//��ʼ������ 
void InitQueue(QuType *&qu){
	qu = (QuType *)malloc(sizeof(QuType));
	qu->front = 0;
	qu->count = 0;
}

//�ж϶ӿ�
bool QueueEmpty(QuType *qu){
	return (qu->count == 0);
}

//���� 
bool EnQueue(QuType *&qu, ElemType x){
	int rear;	//��ʱ��βָ�� 
	if(qu->count == MaxSize){	//���� 
		return false;
	}else{
		rear = (qu->front + qu->count)%MaxSize;	//���βλ��
		rear = (rear+1)%MaxSize;	//��βѭ����1 
		qu->data[rear] = x;
		qu->count++;	//Ԫ�ظ�����1 
		return true;
	}
}

bool DeQueue(QuType *&qu, ElemType &x){
	if(qu->count == 0)	//�ӿ� 
		return false;
	else{
		qu->front = (qu->front+1)%MaxSize;	//��ͷ��1
		x = qu->data[qu->front];
 		qu->count--;	//Ԫ�ظ�����1 
		 return true; 
	}
}


main(){
	QuType *q;
	ElemType a[] = {1,2,3,4,5},e;
	InitQueue(q);
	cout<<"�Ƿ�Ϊ��:"<<QueueEmpty(q)<<endl;
	for(int i=0;i<5;i++){
		EnQueue(q,a[i]);
	}
	cout<<q->data[q->front+1]<<" "<<q->count<<endl;
	DeQueue(q,e);
	cout<<q->data[q->front+1]<<" "<<q->count<<endl;
}
