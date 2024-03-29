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

//********

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

//********


//********

//n个人站一排，从左到右1~n，现在从左往右报数"1,2,1,2,1..."，
//	数到1的人出列，数到2的人立即站到队伍最右端 
//	报数过程反复进行，直到n个人都出列为止
void number(int n){
	int i;
	ElemType e;
	SqQueue q;	//SqQueue为顺序队类型，ElemType为int类型 
	q.front = q.rear = 0;
	for(i=1;i<=n;i++){
		q.rear = (q.rear+1)%MaxSize;
		q.data[q.rear] = i;
	}
	cout<<"报数出列顺序：";
//	队列不为空时循环 
	while(q.front != q.rear){
		q.front = (q.front+1)%MaxSize;
		e = q.data[q.front];	//出队一个元素
		cout<<e<<" ";
		if(q.front != q.rear){
			q.front = (q.front+1)%MaxSize;
			e = q.data[q.front];	//出队一个元素
			q.rear = (q.rear+1)%MaxSize;
			q.data[q.rear] = e;	//将刚出列的元素进队 
			 
		}
	}
	cout<<endl;
}

//********

main(){
//	SqQueue *q;
//	ElemType a[] = {1,2,3,4,5},e;
//	InitQueue(q);
//	cout<<"是否为空:"<<QueueEmpty(q)<<endl;
//	for(int i=0;i<5;i++){
//		enQueue(q,a[i]);
//	}
//	cout<<q->data[q->front+1]<<" "<<q->data[q->rear]<<endl;
//	deQueue(q,e);
//	cout<<q->data[q->front+1]<<" "<<q->data[q->rear]<<endl;

	int i,n=8;
	cout<<"初始化序列：";
	for(int i=1;i<=n;i++)
		cout<<i<<" ";
	cout<<endl;
	number(n);
}
