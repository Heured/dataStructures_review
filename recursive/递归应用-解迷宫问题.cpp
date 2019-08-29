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
	int i;	//当前方块的行 
	int j;	//当前方块的列 
}Box;

typedef struct{
	Box data[MaxSize];
	int length;	//路径长度 
}PathType;	//定义路径类型

//求解路径为:(xi,yi)->(xe,ye)
//	本算法会列出所有解路径 
void mgpath(int xi, int yi, int xe, int ye, PathType path){
	int  di,k,i,j;
	static int count = 0;
//	找到出口，输出路径 
	if(xi==xe && yi==ye){
		path.data[path.length].i = xi;
		path.data[path.length].j = yi;
		path.length++;
		cout<<"迷宫路径"<<++count<<"如下:"<<endl;
		for(k=0; k<path.length; k++){
			cout<<'('<<path.data[k].i<<','<<path.data[k].j<<')';
//			每5个换一次行 
			if((k+1)%5==0)
				cout<<endl;
		}
		cout<<endl;
	}else{
//		(xi,yi)不是出口 
		if(mg[xi][yi] == 0){
			di = 0;
			while(di<4){
				path.data[path.length].i = xi;
				path.data[path.length].j = yi;
				path.length++;
				switch(di){
					case 0 : i=xi-1;j=yi;break;
					case 1 : i=xi;j=yi+1;break;
					case 2 : i=xi+1;j=yi;break;
					case 3 : i=xi;j=yi-1;break;
				}
				mg[xi][yi] = -1;	//避免重复找路径
				mgpath(i,j,xe,ye,path);
				mg[xi][yi] = 0;	//恢复(xi,yi)为可走方块 
				path.length--;	//回退一个方块 
				di++; 
			}
		}
	}
}
//当从(xi,yi)方块找到一个可走相邻方块(i,j)后,mgpath(i,j,xe,ye,path)表示求从(i,j)到(xe,ye)的一条路径。 
//	显然mgpath(xi,yi,xe,ye,path)是"大问题"，mgpath(i,j,xe,ye,path)是"小问题" 
main(){
	PathType path;
	path.length=0;
	mgpath(1,1,M,N,path);
}
