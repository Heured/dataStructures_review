#include<iostream>
using namespace std;

typedef int ElemType;

int A[6][7] = {
	{0,0,1,0,0,0,0},
	{0,2,0,0,0,0,0},
	{3,0,0,0,0,0,0},
	{0,0,0,5,0,0,0},
	{0,0,0,0,6,0,0},
	{0,0,0,0,0,7,4}};


// M:矩阵行数	N:矩阵列数 
#define M 6
#define N 7
#define MaxSize 50

typedef struct{
	int r;	//行号 
	int c;	//列号 
	ElemType d;	//元素值 
}TupNode;	//三元组定义

typedef struct{
	int rows;	//行数 
	int cols;	//列数 
	int nums;	//非零元素个数 
	TupNode data[MaxSize];
}TSMatrix;	//三元组顺序表定义

//对二维稀疏矩阵创建其三元组表示 
void CreateMat(TSMatrix &t, ElemType A[M][N]){
	int i,j;
	t.rows = M;
	t.cols = N;
	t.nums = 0;
	for(i=0; i<M; i++){
		for(j=0; j<N; j++){
//			只存储非零元素
			if(A[i][j]!=0){ 
				t.data[t.nums].r = i;
				t.data[t.nums].c = j;
				t.data[t.nums].d = A[i][j];
				t.nums++;
			}
		}
	}
}

//三元组元素赋值   A[i][j] = x
bool Value(TSMatrix &t, ElemType x, int i, int j){
	int k=0,k1;
//	失败时返回false 
	if(i>=t.rows || j>=t.cols)
		return false;
//	查找行 
	while(k<t.nums && i>t.data[k].r)
		k++;
//	查找列 
	while(k<t.nums && i == t.data[k].r && j>t.data[k].c)
		k++;
	if(t.data[k].r == i && t.data[k].c == j)
		t.data[k].d = x;
//	不存在这样的元素时插入一个元素 
	else{
//		将k以后的元素后移一位(包括k) 
		for(k1 = t.nums - 1; k1>= k; k1--){
			t.data[k1 + 1].r = t.data[k1].r;
			t.data[k1 + 1].c = t.data[k1].c;
			t.data[k1 + 1].d = t.data[k1].d;
		}
		t.data[k].r = i;
		t.data[k].c = j;
		t.data[k].d = x;
		t.nums++;
	}
	return true;
}

//将指定位置的元素值赋给变量	x = A[i][j]
bool Assign(TSMatrix t, ElemType &x, int i, int j){
	int k=0;
//	失败时返回false 
	if(i>=t.rows || j>=t.cols)
		return false;
//	查找行 
	while(k<t.nums && i>t.data[k].r)
		k++;
//	查找列 
	while(k<t.nums && i == t.data[k].r && j>t.data[k].c)
		k++;
	if(t.data[k].r == i && t.data[k].c == j)
		x = t.data[k].d;
	else
		x = 0;	//在三元组中没有找到，表示是零元素
	return true; 
}

//输出三元组 
void DispMat(TSMatrix t){
	int i;
//	没有非零元素时返回 
	if(t.nums<=0)
		return;
	cout<<"行数："<<t.rows<<"	列数："<<t.cols<<"	非零元素个数："<<t.nums<<endl;
	cout<<"---------------------------------------"<<endl;
	cout<<"	"<<"行"<<"	"<<"列"<<"	"<<"值"<<endl;
	for(i=0;i<t.nums;i++)
		cout<<"	"<<t.data[i].r<<"	"<<t.data[i].c<<"	"<<t.data[i].d<<endl;
}

//矩阵转置
//	时间复杂度为O(t.cols x t.nums),最坏时t.nums = t.cols x t.rows 
void TranTat(TSMatrix t, TSMatrix &tb){
	int p,q=0,v;
	tb.rows = t.cols;
	tb.cols = t.rows;
	tb.nums = t.nums;
//	当存在非零元素时执行转置 
	if(t.nums!=0){
//		tb.data[q]中的记录以t的c域的次序排列
		for(v=0;v<t.cols;v++){
			for(p=0;p<t.nums;p++)
				if(t.data[p].c == v){
					tb.data[q].r = t.data[p].c;
					tb.data[q].c = t.data[p].r;
					tb.data[q].d = t.data[p].d;
					q++;
				}
		} 
	}
}

//采用三元组存储稀疏矩阵，设计两个稀疏矩阵相加的运算算法
bool MatAdd(TSMatrix a, TSMatrix b, TSMatrix &c){
	int i=0,j=0,k=0;
	ElemType v;
//	行数或列数不等 
	if(a.rows != b.rows ||a.cols != b.cols)
		return false;
	c.rows = a.rows;
	c.cols = a.cols;
//	处理a，b中的每一个元素 
	while(i<a.nums && j<b.nums){
//		行号相等 
		if(a.data[i].r == b.data[j].r){
//			a元素的列号小于b元素的列号，将a元素添加到c中 
			if(a.data[i].c < b.data[j].c){
				c.data[k].r = a.data[i].r;
				c.data[k].c = a.data[i].c;
				c.data[k].d = a.data[i].d;
				k++;i++;
//			a元素的列号大于b元素的列号，将b元素添加到c中 
			}else if(a.data[i].c > b.data[j].c){
				c.data[k].r = b.data[i].r;
				c.data[k].c = b.data[i].c;
				c.data[k].d = b.data[i].d;
				k++;j++;
//			a元素的列号等于b元素的列号
			}else{
				v = a.data[i].d + b.data[j].d;
//				当a，b元素值的和不为0时，添加到c
				if(v!=0){
					c.data[k].r = a.data[i].r;
					c.data[k].c = a.data[i].c;
					c.data[k].d = v;
					k++;
				}
				i++;j++;	
			}
//		a元素的行号小于b元素的行号，将a元素添加到c中  
		}else if(a.data[i].r < b.data[j].r){
			c.data[k].r = a.data[i].r;
			c.data[k].c = a.data[i].c;
			c.data[k].d = a.data[i].d;
			k++;i++;
//		a元素的行号大于b元素的行号，将b元素添加到c中 
		}else{
			c.data[k].r = b.data[i].r;
			c.data[k].c = b.data[i].c;
			c.data[k].d = b.data[i].d;
			k++;j++;
		}
		c.nums = k; 
	}
	return true;
}

main(){
	ElemType x;
	TSMatrix t,tb,tc;
	CreateMat(t,A);
	
//	Value(t,1,0,0);
//	Assign(t,x,0,0);
//	cout<<x<<endl;

//	DispMat(t);
	
//	TranTat(t,tb);
//	DispMat(tb);

	CreateMat(tb,A);
	MatAdd(t,tb,tc);
	DispMat(tc);
	
}
