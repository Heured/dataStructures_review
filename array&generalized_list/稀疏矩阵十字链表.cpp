#include<iostream>
using namespace std;

typedef int ElemType;

#define M 3
#define N 4
#define Max 4	//�������нϴ��� 

int B[3][4] = {
	{1,0,0,2},
	{0,0,3,0},
	{0,0,0,4},
};

//����ͷ�ڵ���tag.linkָ������һ��ѭ������
//	ÿ��ͷ�ڵ���������rightָ������һ��ѭ������
//	ÿ��ͷ�ڵ���������downָ������һ��ѭ������ 
typedef struct mtxn{
	int row;	//�к� 
	int col;	//�к� 
	struct mtxn *right, *down;	//���Һ����µ�ָ��
	union{
		ElemType value;	//����Ԫ��ֵ 
		struct mtxn *link;	//ָ����һ��ͷ�ڵ� 
	}tag;
}MatNode;	//ʮ���������Ͷ���

//��һ����ά���󴴽���ʮ������
void CreatMat(MatNode *&mh, ElemType a[M][N]){
	int i,j;
	MatNode *h[Max],*p,*q,*r;
	mh = (MatNode *)malloc(sizeof(MatNode));	//����ʮ������ͷ�ڵ� 
	mh->row = M;
	mh->col = N;
	r = mh;	//rָ��β�ڵ�
//	����β�巨����ͷ�ڵ�h[0],h[1],...ѭ������ 
	for(i=0;i<Max;i++){
		h[i] = (MatNode *)malloc(sizeof(MatNode));
		h[i]->down = h[i];
		h[i]->right = h[i];	//��down��right������Ϊѭ��
		r->tag.link = h[i];
		r = h[i];
	}
	r->tag.link = mh;	//��Ϊѭ������
//	����ÿһ��
	for(i=0;i<M;i++){
//		����ÿһ��
		for(j=0;j<N;j++){
//			�������Ԫ�� 
			if(a[i][j]!=0){
				p = (MatNode *)malloc(sizeof(MatNode));	//����һ���½ڵ�
				p->row = i;
				p->col = j;
				p->tag.value = a[i][j];
				q = h[i];	//�������б��еĲ���λ��
				while(q->right != h[i] && q->right->col<j)
					q = q->right;
				p->right = q->right;
				q->right = p;	//������б�Ĳ��� 
				q = h[j];	//�������б��еĲ���λ��
				while(q->down != h[j] && q->down->row<i)
					q = q->down;
				p->down = q->down;
				q->down = p;	//������б�Ĳ��� 
			}
		}
	}
}

//���ʮ���������
void DispMat(MatNode *mh){
	MatNode *p, *q;
	cout<<"�� = "<<mh->row<<" �� = "<<mh->col<<endl;
	p = mh->tag.link;
	cout<<"��"<<"	"<<"��"<<"	"<<"ֵ"<<endl; 
	while(p!=mh){
		q = p->right;
//		���һ�з���Ԫ�� 
		while(q != p){
			cout<<q->row<<"	"<<q->col<<"	"<<q->tag.value<<endl;
			q = q->right;
		}
		p = p->tag.link;
	} 
}

//��������ʮ�������˼·�����һ�����ڴ洢˫�㼯�ϵĴ洢�ṹ
//	˫�㼯��ʵ��:	s = {{1,3},{1,7,8},{5,6}}
//���ݽڵ�����Ͷ��� 
typedef struct dnode{
	ElemType data;
	struct dnode *next;
}DType;
//ͷ�ڵ����Ͷ���
typedef struct hnode{
	DType *next;
	struct hnode *link;
}HType;

main(){
	MatNode *mh;
	CreatMat(mh,B);
	DispMat(mh);
}
