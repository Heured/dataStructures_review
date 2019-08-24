#include<iostream>
using namespace std;
typedef int ElemType;
#define MaxSize 50

typedef struct{
	ElemType data[MaxSize];
	int front;	//队头指针 
	int count;	//队列中元素个数 
}QuType;

//初始化队列 
void InitQueue(QuType *&qu){
	qu = (QuType *)malloc(sizeof(QuType));
	qu->front = 0;
	qu->count = 0;
}

//判断队空
bool QueueEmpty(QuType *qu){
	return (qu->count == 0);
}

//进队 
bool EnQueue(QuType *&qu, ElemType x){
	int rear;	//临时队尾指针 
	if(qu->count == MaxSize){	//队满 
		return false;
	}else{
		rear = (qu->front + qu->count)%MaxSize;	//求队尾位置
		rear = (rear+1)%MaxSize;	//队尾循环增1 
		qu->data[rear] = x;
		qu->count++;	//元素个数增1 
		return true;
	}
}

bool DeQueue(QuType *&qu, ElemType &x){
	if(qu->count == 0)	//队空 
		return false;
	else{
		qu->front = (qu->front+1)%MaxSize;	//队头增1
		x = qu->data[qu->front];
 		qu->count--;	//元素个数减1 
		 return true; 
	}
}


main(){
	QuType *q;
	ElemType a[] = {1,2,3,4,5},e;
	InitQueue(q);
	cout<<"是否为空:"<<QueueEmpty(q)<<endl;
	for(int i=0;i<5;i++){
		EnQueue(q,a[i]);
	}
	cout<<q->data[q->front+1]<<" "<<q->count<<endl;
	DeQueue(q,e);
	cout<<q->data[q->front+1]<<" "<<q->count<<endl;
}
