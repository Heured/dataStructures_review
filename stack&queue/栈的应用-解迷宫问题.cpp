#include<iostream>
using namespace std;

#define MaxSize 50 
#define M 8
#define N 8

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
	int i;	//当前方块的行号 
	int j;	//当前方块的列号 
	int di;	//di是下一个可走的相邻方块的方位号 
}Box;

typedef struct{
	Box data[MaxSize];
	int top;	//栈顶指针 
}StType;	//定义顺序栈类型

//为了方便回溯，对于可走的方块都要进栈,
//	试探它的下一个可走的方向，将可走的方向也保存到栈内 
bool mgpath(int xi, int yi, int xe, int ye){	//求解路径为(xi,yi)->(xe,ye)
	int i,j,k,di,find;
	StType st;	//定义栈st
	st.top = -1;	//初始化栈顶指针
	st.top++;	//初始方块进栈 
	st.data[st.top].i = xi;
	st.data[st.top].j = yi;
	st.data[st.top].di = -1;
	mg[xi][yi] = -1; //将当前方块值改为-1是为了防止下一个方块在遍历方向时往回走导致死循环 
	
	while(st.top>-1){	//栈不空时循环 
		i = st.data[st.top].i;
		j = st.data[st.top].j;
		di = st.data[st.top].di;
		if(i==xe && j==ye){
			cout<<"迷宫路径如下"<<endl;
			for(k=0; k<=st.top; k++){
				cout<<"	("<<st.data[k].i<<"，"<<st.data[k].j<<")";
//				每输出5个方块后换行 
				if((k+1)%5 == 0)
					cout<<endl;
			}
			cout<<endl;
			return true;	//找到一条路径后返回true 
		}
		find = 0;
		while(di<4 && find == 0){
			di++;
			switch(di){
				case 0:i=st.data[st.top].i-1;j=st.data[st.top].j;break;
				case 1:i=st.data[st.top].i;j=st.data[st.top].j+1;break;
				case 2:i=st.data[st.top].i+1;j=st.data[st.top].j;break;
				case 3:i=st.data[st.top].i;j=st.data[st.top].j-1;break;
			}
			if(mg[i][j] == 0) find = 1;	//找到下一个可走相邻方块 
		}
		if(find == 1){	//找到了下一个可走方块 
			st.data[st.top].di = di;	//修改原栈顶元素的di值
			st.top++;	//下一个可走的方块进栈
			st.data[st.top].i = i;
			st.data[st.top].j = j;
			st.data[st.top].di = -1;
			mg[i][j] = -1;
		}else{	//没有路径可走，退栈 
			mg[st.data[st.top].i][st.data[st.top].j] = 0;	//让该位置变为其他路径可走放走 
			st.top--;	//将该方块退栈 
		}
	}
	return false;	//表示没有可走路径，返回false 
}

main(){
	if(!mgpath(1,1,M,N))
		cout<<"该迷宫问题无解！";
}

 
