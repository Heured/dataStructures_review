#include<iostream>
using namespace std;

typedef int ElemType;

#define M 3
#define N 4
#define Max 4	//矩阵行列较大者 

int B[3][4] = {
	{1,0,0,2},
	{0,0,3,0},
	{0,0,0,4},
};

//所有头节点用tag.link指针连成一个循环链表，
//	每个头节点所在行用right指针连成一个循环链表，
//	每个头节点所在列用down指针连成一个循环链表 
typedef struct mtxn{
	int row;	//行号 
	int col;	//列号 
	struct mtxn *right, *down;	//向右和向下的指针
	union{
		ElemType value;	//非零元素值 
		struct mtxn *link;	//指向下一个头节点 
	}tag;
}MatNode;	//十字链表类型定义

//对一个二维矩阵创建其十字链表
void CreatMat(MatNode *&mh, ElemType a[M][N]){
	int i,j;
	MatNode *h[Max],*p,*q,*r;
	mh = (MatNode *)malloc(sizeof(MatNode));	//创建十字链表头节点 
	mh->row = M;
	mh->col = N;
	r = mh;	//r指向尾节点
//	采用尾插法创建头节点h[0],h[1],...循环链表 
	for(i=0;i<Max;i++){
		h[i] = (MatNode *)malloc(sizeof(MatNode));
		h[i]->down = h[i];
		h[i]->right = h[i];	//将down和right方向置为循环
		r->tag.link = h[i];
		r = h[i];
	}
	r->tag.link = mh;	//置为循环链表
//	处理每一行
	for(i=0;i<M;i++){
//		处理每一列
		for(j=0;j<N;j++){
//			处理非零元素 
			if(a[i][j]!=0){
				p = (MatNode *)malloc(sizeof(MatNode));	//创建一个新节点
				p->row = i;
				p->col = j;
				p->tag.value = a[i][j];
				q = h[i];	//查找在行表中的插入位置
				while(q->right != h[i] && q->right->col<j)
					q = q->right;
				p->right = q->right;
				q->right = p;	//完成在行表的插入 
				q = h[j];	//查找在列表中的插入位置
				while(q->down != h[j] && q->down->row<i)
					q = q->down;
				p->down = q->down;
				q->down = p;	//完成在列表的插入 
			}
		}
	}
}

//输出十字链表矩阵
void DispMat(MatNode *mh){
	MatNode *p, *q;
	cout<<"行 = "<<mh->row<<" 列 = "<<mh->col<<endl;
	p = mh->tag.link;
	cout<<"行"<<"	"<<"列"<<"	"<<"值"<<endl; 
	while(p!=mh){
		q = p->right;
//		输出一行非零元素 
		while(q != p){
			cout<<q->row<<"	"<<q->col<<"	"<<q->tag.value<<endl;
			q = q->right;
		}
		p = p->tag.link;
	} 
}

//采用类似十字链表的思路，设计一个用于存储双层集合的存储结构
//	双层集合实例:	s = {{1,3},{1,7,8},{5,6}}
//数据节点的类型定义 
typedef struct dnode{
	ElemType data;
	struct dnode *next;
}DType;
//头节点类型定义
typedef struct hnode{
	DType *next;
	struct hnode *link;
}HType;

main(){
	MatNode *mh;
	CreatMat(mh,B);
	DispMat(mh);
}
