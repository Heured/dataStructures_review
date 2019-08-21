#include<iostream>
#define MaxSize 50
//#include<bits/stdc++.h>
using namespace std;
typedef int ElemType;

typedef struct{
	ElemType data[MaxSize];	//	元素 
	int length;//	长度
}SqList;	//类型定义

//由a中的n个元素建立顺序表 
void CreateList(SqList *&L, ElemType a[], int n){
	int i;
	L = (SqList *)malloc(sizeof(SqList));//	分配存放线性表的空间
	for(i=0;i<n;i++)//	放置数据元素 
		L->data[i] = a[i];
	L->length = n;//	设置长度 
}

//初始化，时间复杂度为O(1) 
void InitList(SqList *&L){

	L = (SqList *)malloc(sizeof(SqList));//	分配存放线性表的空间 
	L->length = 0;//	置空线性表长度为0 
}
//通过malloc函数分配顺序表的空间，顺序表不再需要时用free函数释放内存空间

//是否为空判断，时间复杂度为O(1) 
bool ListEmpty(SqList *L){
	return (L->length == 0);
}

//求线性表长度，时间复杂度为O(1) 
int ListLength(SqList *L){
	return (L->length);
}

//输出线性表，时间复杂度为O(L->length) 
void DispList(SqList *L){
//	遍历顺序表输出各元素 
	for(int i=0;i<L->length;i++)
		cout<<(L->data[i])<<" ";
	cout<<endl;
}

//求线性表某个元素，时间复杂度为O(1) 
bool GetElem(SqList *L, int i, ElemType &e){
//	参数错误时返回false 
	if(i<1 || i>L->length)
		return false;
	e = L->data[i-1];//	取元素值 
	return true;//	成功找到元素时返回true 
}

//按元素值查找，时间复杂度O(L->length)，因为基本语句为循环中的i++ 
int LocateElem(SqList *L, ElemType e){
	int i=0;

	while(i<L->length &&L->data[i]!=e)//	查找元素e 
		i++;
//	未找到时返回0 
	if(i>=L->length)
		return 0;
//	找到后返回序号
	else
		return i+1;
}

//插入数据元素，时间复杂度为O(n) 
bool ListInsert(SqList *&L, int i, ElemType e){
	int j;
//	参数错误时返回false 
	if(i<1||i>L->length+1)
		return false;
//	将顺序表逻辑下标转为物理下标
	i--;
//	将data[i]及后面的元素后移一个位置
	for(j=L->length;j>i;j--)
		L->data[j] = L->data[j-1];

	L->data[i] = e;	//插入元素e 
	L->length++;	//顺序表长度增1
	return true;	//成功插入返回true 
} 

//删除数据元素，时间复杂度为O(n) 
bool ListDelete(SqList *&L, int i, ElemType &e){
	int j;
//	参数错误时返回false 
	if(i<1||i>L->length+1)
		return false;
	i--;	//将顺序表逻辑下标转为物理下标
	e = L->data[i];	//获取被删除的元素值 
//	将data[i]之后的元素前移一个位置 
	for(j=i; j<L->length-1;j++)
		L->data[j] = L->data[j+1];
	L->length--;	//顺序表长度减1 
	return true;	//成功删除返回true 
}

//删除顺序表中等于x的元素，时间复杂度为O(n) 
void delnode_1(SqList *&L, ElemType x){
//	k记录值不等于x的元素个数
	int k=0, i;
	for(i=0;i<L->length;i++)
//	若当前元素不为x，将其插入L中 
		if(L->data[i]!=x){
			L->data[k] = L->data[i];
			k++;	//不等于x的元素增1 
		}
	L->length = k;	//顺序表长度为k 
}

void delnode_2(SqList *&L, ElemType x){
//	k记录值等于x的元素个数 
	int k=0, i=0;
	while(i<L->length){
//	当前元素值为x时k增1 
		if(L->data[i] == x)
			k++;
//	当前元素不为x时将其前移k个位置 
		else
			L->data[i-k] = L->data[i];
		i++;
	}
	L->length -= k;	//顺序表长度为原长度-k 
}

//以第一个元素为分界线，将所有小于等于它的元素置前
//	将所有大于它的元素置后 
void move_1(SqList *&L){
	int i=0, j=L->length-1;
	ElemType pivot = L->data[0];	//以data[0]为基准 
	ElemType tmp;
//	从区间两端交替向中间扫描直至i=j为止 
	while(i<j){
//		从右向左找小于等于pivot的元素 
		while(i<j && L->data[j]>pivot)
			j--;
//		从左向右找大于pivot的元素 
		while(i<j && L->data[i]<=pivot)
			i++;
//		i，j位置上的元素互换 
		if(i<j){
			tmp = L->data[i];
			L->data[i] = L->data[j];
			L->data[j] = tmp;
		}
	} 
//	循环结束时i，j一定停止在比pivot小的元素上
//	j，0位置上元素互换 
	tmp = L->data[0];
	L->data[0] = L->data[j];
	L->data[j] = tmp;
	cout<<"i = "<<i<<endl;
}

void move_2(SqList *&L){
	int i=0, j = L->length-1;
	ElemType pivot = L->data[0];	//以data[0]为基准
	while(i<j){
//		从右向左找一个小于等于pivot的data[j] 
		while(j>i && L->data[j]>pivot)
			j--;
		L->data[i] = L->data[j];	//将找到的j放入data[i] 
		i++;
//		从左向右找一个大于pivot的data[j] 
		while(i<j && L->data[i]<=pivot)
			i++;
		L->data[j] = L->data[i];	//将找到的i放入data[j]
		j--;
	}
//	循环结束时，位置i上的元素已经转移到位置j上了，此时位置i置pivot 
	L->data[i] = pivot;
	cout<<"i = "<<i<<endl;
} 

main(){
//	ElemType a[] = {1,2,3,4,5,6,7};
	ElemType a[] = {4,2,6,4,5,6,7};
	SqList *L;
	CreateList(L,a,7);
	ElemType e = 3;
//	GetElem(L,5,e);
//	e = LocateElem(L,4);
//	ListInsert(L,3,e);
//	ListDelete(L,5,e);
//	delnode_1(L,7);
//	delnode_2(L,7);
//	move_1(L);
//	move_2(L);


	DispList(L);
	cout<<e;
}
