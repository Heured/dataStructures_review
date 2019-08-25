#include<iostream>
using namespace std;

#define MaxSize 50 
#define M 8
#define N 8
typedef int ElemType;

int mg[M+2][N+2] = {
	{1,1,1,1,1,1,1,1,1,1},
	{1,0,0,1,0,0,0,1,0,1},
	{1,0,0,1,0,0,0,1,0,1},
	{1,0,0,0,0,1,1,0,0,1},
	{1,0,1,1,1,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,1},
	{1,0,1,0,0,0,1,0,0,1},
	{1,0,1,1,1,0,1,1,0,1},
	{1,1,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1},
};

typedef struct{
	int i,j;	//����λ�� 
	int pre;	//��·������һ�������ڶ����е��±� 
}Box;	//�������� 

typedef struct{
	Box data[MaxSize];
	int front, rear;	//��ͷ�Ͷ�βָ�� 
}QuType;	//����˳�������

void print(QuType qu, int front);

bool mgpath1(int xi, int yi, int xe, int ye){	//����·��Ϊ��(xi,yi)->(xe,ye) 
	int i,j,find=0,di;
	QuType qu;	//����˳���
	qu.front = qu.rear = -1;
	qu.rear++;
	qu.data[qu.rear].i = xi;
	qu.data[qu.rear].j = yi;	//(xi,yi)���� 
	qu.data[qu.rear].pre = -1;
	mg[xi][yi] = -1;	//���丳ֵΪ-1�������ظ�����
//	���в�Ϊ����δ�ҵ�·��ʱѭ�� 
	while(qu.front != qu.rear && !find){
		qu.front++;	//��frontָ��ǰ���� 
		i = qu.data[qu.front].i;
		j = qu.data[qu.front].j;
		if(i == xe && j == ye){
			find = 1;
			print(qu, qu.front);	//����print�������·�� 
			return true;
		}
		for(di=0;di<4;di++){
			switch(di){
				case 0: i = qu.data[qu.front].i-1; j = qu.data[qu.front].j; break;
				case 1: i = qu.data[qu.front].i; j = qu.data[qu.front].j+1; break;
				case 2: i = qu.data[qu.front].i+1; j = qu.data[qu.front].j; break;
				case 3: i = qu.data[qu.front].i; j = qu.data[qu.front].j-1; break;
			}
			if(mg[i][j] == 0){
				qu.rear++;	//�������ڷ�����������
				qu.data[qu.rear].i = i; 
				qu.data[qu.rear].j = j;
				qu.data[qu.rear].pre = qu.front;	//ָ��·������һ��������±� 
				mg[i][j] = -1;	//�����ظ����� 
			}
		}
	}
	return false;	//δ�ҵ�һ��·��ʱ����false 
}

//�Ӷ���qu�����·�� 
void print(QuType qu, int front){
	int k=front,j,ns=0;
	cout<<endl;
	do{
		j = k;
		k = qu.data[k].pre;
		qu.data[j].pre = -1;
	}while(k!=0);
	cout<<"�Թ�·�����£�"<<endl;
	k=0;
//	����������preΪ-1�ķ��飬�����������·�� 
	while(k<MaxSize){
		if(qu.data[k].pre == -1){
			ns++;
			cout<<"	("<<qu.data[k].i<<','<<qu.data[k].j<<")";
			if(ns%5 == 0)
				cout<<endl;	//ÿ���5�����黻�� 
		}
		k++;
	}
	cout<<endl;
}

//���ν��Թ��㷨�����Ĺ�������㷨���ƣ��ȱ��������еĶ��ӣ��ٽ�����һ�����б��� 
main(){
	if(!mgpath1(1,1,M,N))
		cout<<"���Թ������޽�!";
} 
