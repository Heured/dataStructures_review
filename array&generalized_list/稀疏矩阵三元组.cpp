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


// M:��������	N:�������� 
#define M 6
#define N 7
#define MaxSize 50

typedef struct{
	int r;	//�к� 
	int c;	//�к� 
	ElemType d;	//Ԫ��ֵ 
}TupNode;	//��Ԫ�鶨��

typedef struct{
	int rows;	//���� 
	int cols;	//���� 
	int nums;	//����Ԫ�ظ��� 
	TupNode data[MaxSize];
}TSMatrix;	//��Ԫ��˳�����

//�Զ�άϡ����󴴽�����Ԫ���ʾ 
void CreateMat(TSMatrix &t, ElemType A[M][N]){
	int i,j;
	t.rows = M;
	t.cols = N;
	t.nums = 0;
	for(i=0; i<M; i++){
		for(j=0; j<N; j++){
//			ֻ�洢����Ԫ��
			if(A[i][j]!=0){ 
				t.data[t.nums].r = i;
				t.data[t.nums].c = j;
				t.data[t.nums].d = A[i][j];
				t.nums++;
			}
		}
	}
}

//��Ԫ��Ԫ�ظ�ֵ   A[i][j] = x
bool Value(TSMatrix &t, ElemType x, int i, int j){
	int k=0,k1;
//	ʧ��ʱ����false 
	if(i>=t.rows || j>=t.cols)
		return false;
//	������ 
	while(k<t.nums && i>t.data[k].r)
		k++;
//	������ 
	while(k<t.nums && i == t.data[k].r && j>t.data[k].c)
		k++;
	if(t.data[k].r == i && t.data[k].c == j)
		t.data[k].d = x;
//	������������Ԫ��ʱ����һ��Ԫ�� 
	else{
//		��k�Ժ��Ԫ�غ���һλ(����k) 
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

//��ָ��λ�õ�Ԫ��ֵ��������	x = A[i][j]
bool Assign(TSMatrix t, ElemType &x, int i, int j){
	int k=0;
//	ʧ��ʱ����false 
	if(i>=t.rows || j>=t.cols)
		return false;
//	������ 
	while(k<t.nums && i>t.data[k].r)
		k++;
//	������ 
	while(k<t.nums && i == t.data[k].r && j>t.data[k].c)
		k++;
	if(t.data[k].r == i && t.data[k].c == j)
		x = t.data[k].d;
	else
		x = 0;	//����Ԫ����û���ҵ�����ʾ����Ԫ��
	return true; 
}

//�����Ԫ�� 
void DispMat(TSMatrix t){
	int i;
//	û�з���Ԫ��ʱ���� 
	if(t.nums<=0)
		return;
	cout<<"������"<<t.rows<<"	������"<<t.cols<<"	����Ԫ�ظ�����"<<t.nums<<endl;
	cout<<"---------------------------------------"<<endl;
	cout<<"	"<<"��"<<"	"<<"��"<<"	"<<"ֵ"<<endl;
	for(i=0;i<t.nums;i++)
		cout<<"	"<<t.data[i].r<<"	"<<t.data[i].c<<"	"<<t.data[i].d<<endl;
}

//����ת��
//	ʱ�临�Ӷ�ΪO(t.cols x t.nums),�ʱt.nums = t.cols x t.rows 
void TranTat(TSMatrix t, TSMatrix &tb){
	int p,q=0,v;
	tb.rows = t.cols;
	tb.cols = t.rows;
	tb.nums = t.nums;
//	�����ڷ���Ԫ��ʱִ��ת�� 
	if(t.nums!=0){
//		tb.data[q]�еļ�¼��t��c��Ĵ�������
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

//������Ԫ��洢ϡ������������ϡ�������ӵ������㷨
bool MatAdd(TSMatrix a, TSMatrix b, TSMatrix &c){
	int i=0,j=0,k=0;
	ElemType v;
//	�������������� 
	if(a.rows != b.rows ||a.cols != b.cols)
		return false;
	c.rows = a.rows;
	c.cols = a.cols;
//	����a��b�е�ÿһ��Ԫ�� 
	while(i<a.nums && j<b.nums){
//		�к���� 
		if(a.data[i].r == b.data[j].r){
//			aԪ�ص��к�С��bԪ�ص��кţ���aԪ����ӵ�c�� 
			if(a.data[i].c < b.data[j].c){
				c.data[k].r = a.data[i].r;
				c.data[k].c = a.data[i].c;
				c.data[k].d = a.data[i].d;
				k++;i++;
//			aԪ�ص��кŴ���bԪ�ص��кţ���bԪ����ӵ�c�� 
			}else if(a.data[i].c > b.data[j].c){
				c.data[k].r = b.data[i].r;
				c.data[k].c = b.data[i].c;
				c.data[k].d = b.data[i].d;
				k++;j++;
//			aԪ�ص��кŵ���bԪ�ص��к�
			}else{
				v = a.data[i].d + b.data[j].d;
//				��a��bԪ��ֵ�ĺͲ�Ϊ0ʱ����ӵ�c
				if(v!=0){
					c.data[k].r = a.data[i].r;
					c.data[k].c = a.data[i].c;
					c.data[k].d = v;
					k++;
				}
				i++;j++;	
			}
//		aԪ�ص��к�С��bԪ�ص��кţ���aԪ����ӵ�c��  
		}else if(a.data[i].r < b.data[j].r){
			c.data[k].r = a.data[i].r;
			c.data[k].c = a.data[i].c;
			c.data[k].d = a.data[i].d;
			k++;i++;
//		aԪ�ص��кŴ���bԪ�ص��кţ���bԪ����ӵ�c�� 
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
