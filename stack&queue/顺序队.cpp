#include<iostream>
using namespace std;

#define MaxSize 50
typedef int ElemType;

typedef struct{
	ElemType data[MaxSize];	//��Ŷ���Ԫ��
	int front, rear;	//��ͷ�Ͷ�βָ�� 
}SqQueue;	//����˳�������

//��ʼ������ 
void InitQueue(SqQueue *&q){
	q = (SqQueue *)malloc(sizeof(SqQueue));
	q->front = q->rear = -1;
}

//���ٶ���
void DestroyQueue(SqQueue *&q){
	free(q);
}

//�ж϶����Ƿ�Ϊ��
bool QueueEmpty(SqQueue *q){
	return (q->front == q->rear);
}

//������
bool enQueue(SqQueue *&q, ElemType e){
//	���������
	if(q->rear == MaxSize-1)
		return false;
	q->rear++;	//�Ӷ�β���� 
	q->data[q->rear] = e;
	return true; 
}

//������
bool deQueue(SqQueue *&q, ElemType &e){
//	�ӿ������ 
	if(q->front == q->rear)
		return false;
	q->front++;	//�Ӷ�ͷ����
	e = q->data[q->front];

	return true;
}

//���ζӳ�ʼ������
void InitRQueue(SqQueue *&q){
	q = (SqQueue *)malloc(sizeof(SqQueue));
	q->front = q->rear = 0;
}

//���ζ����ٶ��� 
void DestroyRQueue(SqQueue *&q){
	free(q);
}

//���ζ��ж��Ƿ�Ϊ��
bool RQueueEmpty(SqQueue *q){
	return(q->front == q->rear);
}

//���ζӽ�����
bool enRQueue(SqQueue *&q, ElemType e){
//	��������� 
	if((q->rear + 1)%MaxSize == q->front)
		return false;
	q->rear = (q->rear +1)%MaxSize;
	q->data[q->rear] = e;
	return true;
}

//���ζӳ�����
bool deRQueue(SqQueue *&q, ElemType &e){
//	�ӿ������ 
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
	cout<<"�Ƿ�Ϊ��:"<<QueueEmpty(q)<<endl;
	for(int i=0;i<5;i++){
		enQueue(q,a[i]);
	}
	cout<<q->data[q->front+1]<<" "<<q->data[q->rear]<<endl;
	deQueue(q,e);
	cout<<q->data[q->front+1]<<" "<<q->data[q->rear]<<endl;
}
