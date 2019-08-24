#include<iostream>
using namespace std;

#define MaxSize 50
typedef int ElemType;

typedef struct{
	ElemType data[MaxSize];	//存放队中元素
	int front, rear;	//队头和队尾指针 
}SqQueue;	//定义顺序队类型

//初始化队列 
void InitQueue(SqQueue *&q){
	q = (SqQueue *)malloc(sizeof(SqQueue));
	q->front = q->rear = -1;
}

//销毁队列
void DestroyQueue(SqQueue *&q){
	free(q);
}

//判断队列是否为空
bool QueueEmpty(SqQueue *q){
	return (q->front == q->rear);
}

//进队列
bool enQueue(SqQueue *&q, ElemType e){
//	队满上溢出
	if(q->rear == MaxSize-1)
		return false;
	q->rear++;	//从队尾进队 
	q->data[q->rear] = e;
	return true; 
}

//出队列
bool deQueue(SqQueue *&q, ElemType &e){
//	队空下溢出 
	if(q->front == q->rear)
		return false;
	q->front++;	//从队头出队
	e = q->data[q->front];

	return true;
}

//环形队初始化队列
void InitRQueue(SqQueue *&q){
	q = (SqQueue *)malloc(sizeof(SqQueue));
	q->front = q->rear = 0;
}

//环形队销毁队列 
void DestroyRQueue(SqQueue *&q){
	free(q);
}

//环形队判断是否为空
bool RQueueEmpty(SqQueue *q){
	return(q->front == q->rear);
}

//环形队进队列
bool enRQueue(SqQueue *&q, ElemType e){
//	队满上溢出 
	if((q->rear + 1)%MaxSize == q->front)
		return false;
	q->rear = (q->rear +1)%MaxSize;
	q->data[q->rear] = e;
	return true;
}

//环形队出队列
bool deRQueue(SqQueue *&q, ElemType &e){
//	队空下溢出 
	if(q->front == q->rear)
		return false;
	q->front = (q->front+1)%MaxSize;
	e = q->data[q->front];
	return true;
}


main(){
	SqQueue *q;
	ElemType a[] = {1,2,3,4,5},e;
	InitQueue(q);
	cout<<"是否为空:"<<QueueEmpty(q)<<endl;
	for(int i=0;i<5;i++){
		enQueue(q,a[i]);
	}
	cout<<q->data[q->front+1]<<" "<<q->data[q->rear]<<endl;
	deQueue(q,e);
	cout<<q->data[q->front+1]<<" "<<q->data[q->rear]<<endl;
}
