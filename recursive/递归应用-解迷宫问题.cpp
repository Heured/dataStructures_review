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
	int i;	//��ǰ������� 
	int j;	//��ǰ������� 
}Box;

typedef struct{
	Box data[MaxSize];
	int length;	//·������ 
}PathType;	//����·������

//���·��Ϊ:(xi,yi)->(xe,ye)
//	���㷨���г����н�·�� 
void mgpath(int xi, int yi, int xe, int ye, PathType path){
	int  di,k,i,j;
	static int count = 0;
//	�ҵ����ڣ����·�� 
	if(xi==xe && yi==ye){
		path.data[path.length].i = xi;
		path.data[path.length].j = yi;
		path.length++;
		cout<<"�Թ�·��"<<++count<<"����:"<<endl;
		for(k=0; k<path.length; k++){
			cout<<'('<<path.data[k].i<<','<<path.data[k].j<<')';
//			ÿ5����һ���� 
			if((k+1)%5==0)
				cout<<endl;
		}
		cout<<endl;
	}else{
//		(xi,yi)���ǳ��� 
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
				mg[xi][yi] = -1;	//�����ظ���·��
				mgpath(i,j,xe,ye,path);
				mg[xi][yi] = 0;	//�ָ�(xi,yi)Ϊ���߷��� 
				path.length--;	//����һ������ 
				di++; 
			}
		}
	}
}
//����(xi,yi)�����ҵ�һ���������ڷ���(i,j)��,mgpath(i,j,xe,ye,path)��ʾ���(i,j)��(xe,ye)��һ��·���� 
//	��Ȼmgpath(xi,yi,xe,ye,path)��"������"��mgpath(i,j,xe,ye,path)��"С����" 
main(){
	PathType path;
	path.length=0;
	mgpath(1,1,M,N,path);
}
