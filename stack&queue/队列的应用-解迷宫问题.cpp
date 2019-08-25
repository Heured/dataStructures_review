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
	int i,j;	//方块位置 
	int pre;	//本路径中上一个方块在队列中的下标 
}Box;	//方块类型 

typedef struct{
	Box data[MaxSize];
	int front, rear;	//队头和队尾指针 
}QuType;	//定义顺序队类型

void print(QuType qu, int front);

bool mgpath1(int xi, int yi, int xe, int ye){	//搜索路径为：(xi,yi)->(xe,ye) 
	int i,j,find=0,di;
	QuType qu;	//定义顺序队
	qu.front = qu.rear = -1;
	qu.rear++;
	qu.data[qu.rear].i = xi;
	qu.data[qu.rear].j = yi;	//(xi,yi)进队 
	qu.data[qu.rear].pre = -1;
	mg[xi][yi] = -1;	//将其赋值为-1，以免重复搜索
//	队列不为空且未找到路径时循环 
	while(qu.front != qu.rear && !find){
		qu.front++;	//将front指向当前方块 
		i = qu.data[qu.front].i;
		j = qu.data[qu.front].j;
		if(i == xe && j == ye){
			find = 1;
			print(qu, qu.front);	//调用print函数输出路径 
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
				qu.rear++;	//将该相邻方块插入队列中
				qu.data[qu.rear].i = i; 
				qu.data[qu.rear].j = j;
				qu.data[qu.rear].pre = qu.front;	//指向路径中上一个方块的下标 
				mg[i][j] = -1;	//避免重复搜索 
			}
		}
	}
	return false;	//未找到一条路径时返回false 
}

//从队列qu中输出路径 
void print(QuType qu, int front){
	int k=front,j,ns=0;
	cout<<endl;
	do{
		j = k;
		k = qu.data[k].pre;
		qu.data[j].pre = -1;
	}while(k!=0);
	cout<<"迷宫路径如下："<<endl;
	k=0;
//	正向搜索到pre为-1的方块，即构成正向的路径 
	while(k<MaxSize){
		if(qu.data[k].pre == -1){
			ns++;
			cout<<"	("<<qu.data[k].i<<','<<qu.data[k].j<<")";
			if(ns%5 == 0)
				cout<<endl;	//每输出5个方块换行 
		}
		k++;
	}
	cout<<endl;
}

//本次解迷宫算法与树的广度优先算法类似，先遍历出所有的儿子，再进入下一代进行遍历 
main(){
	if(!mgpath1(1,1,M,N))
		cout<<"该迷宫问题无解!";
} 
