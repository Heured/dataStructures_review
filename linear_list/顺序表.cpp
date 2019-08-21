#include<iostream>
#define MaxSize 50
//#include<bits/stdc++.h>
using namespace std;
typedef int ElemType;

typedef struct{
	ElemType data[MaxSize];	//	Ԫ�� 
	int length;//	����
}SqList;	//���Ͷ���

//��a�е�n��Ԫ�ؽ���˳��� 
void CreateList(SqList *&L, ElemType a[], int n){
	int i;
	L = (SqList *)malloc(sizeof(SqList));//	���������Ա�Ŀռ�
	for(i=0;i<n;i++)//	��������Ԫ�� 
		L->data[i] = a[i];
	L->length = n;//	���ó��� 
}

//��ʼ����ʱ�临�Ӷ�ΪO(1) 
void InitList(SqList *&L){

	L = (SqList *)malloc(sizeof(SqList));//	���������Ա�Ŀռ� 
	L->length = 0;//	�ÿ����Ա���Ϊ0 
}
//ͨ��malloc��������˳���Ŀռ䣬˳�������Ҫʱ��free�����ͷ��ڴ�ռ�

//�Ƿ�Ϊ���жϣ�ʱ�临�Ӷ�ΪO(1) 
bool ListEmpty(SqList *L){
	return (L->length == 0);
}

//�����Ա��ȣ�ʱ�临�Ӷ�ΪO(1) 
int ListLength(SqList *L){
	return (L->length);
}

//������Ա�ʱ�临�Ӷ�ΪO(L->length) 
void DispList(SqList *L){
//	����˳��������Ԫ�� 
	for(int i=0;i<L->length;i++)
		cout<<(L->data[i])<<" ";
	cout<<endl;
}

//�����Ա�ĳ��Ԫ�أ�ʱ�临�Ӷ�ΪO(1) 
bool GetElem(SqList *L, int i, ElemType &e){
//	��������ʱ����false 
	if(i<1 || i>L->length)
		return false;
	e = L->data[i-1];//	ȡԪ��ֵ 
	return true;//	�ɹ��ҵ�Ԫ��ʱ����true 
}

//��Ԫ��ֵ���ң�ʱ�临�Ӷ�O(L->length)����Ϊ�������Ϊѭ���е�i++ 
int LocateElem(SqList *L, ElemType e){
	int i=0;

	while(i<L->length &&L->data[i]!=e)//	����Ԫ��e 
		i++;
//	δ�ҵ�ʱ����0 
	if(i>=L->length)
		return 0;
//	�ҵ��󷵻����
	else
		return i+1;
}

//��������Ԫ�أ�ʱ�临�Ӷ�ΪO(n) 
bool ListInsert(SqList *&L, int i, ElemType e){
	int j;
//	��������ʱ����false 
	if(i<1||i>L->length+1)
		return false;
//	��˳����߼��±�תΪ�����±�
	i--;
//	��data[i]�������Ԫ�غ���һ��λ��
	for(j=L->length;j>i;j--)
		L->data[j] = L->data[j-1];

	L->data[i] = e;	//����Ԫ��e 
	L->length++;	//˳�������1
	return true;	//�ɹ����뷵��true 
} 

//ɾ������Ԫ�أ�ʱ�临�Ӷ�ΪO(n) 
bool ListDelete(SqList *&L, int i, ElemType &e){
	int j;
//	��������ʱ����false 
	if(i<1||i>L->length+1)
		return false;
	i--;	//��˳����߼��±�תΪ�����±�
	e = L->data[i];	//��ȡ��ɾ����Ԫ��ֵ 
//	��data[i]֮���Ԫ��ǰ��һ��λ�� 
	for(j=i; j<L->length-1;j++)
		L->data[j] = L->data[j+1];
	L->length--;	//˳����ȼ�1 
	return true;	//�ɹ�ɾ������true 
}

//ɾ��˳����е���x��Ԫ�أ�ʱ�临�Ӷ�ΪO(n) 
void delnode_1(SqList *&L, ElemType x){
//	k��¼ֵ������x��Ԫ�ظ���
	int k=0, i;
	for(i=0;i<L->length;i++)
//	����ǰԪ�ز�Ϊx���������L�� 
		if(L->data[i]!=x){
			L->data[k] = L->data[i];
			k++;	//������x��Ԫ����1 
		}
	L->length = k;	//˳�����Ϊk 
}

void delnode_2(SqList *&L, ElemType x){
//	k��¼ֵ����x��Ԫ�ظ��� 
	int k=0, i=0;
	while(i<L->length){
//	��ǰԪ��ֵΪxʱk��1 
		if(L->data[i] == x)
			k++;
//	��ǰԪ�ز�Ϊxʱ����ǰ��k��λ�� 
		else
			L->data[i-k] = L->data[i];
		i++;
	}
	L->length -= k;	//˳�����Ϊԭ����-k 
}

//�Ե�һ��Ԫ��Ϊ�ֽ��ߣ�������С�ڵ�������Ԫ����ǰ
//	�����д�������Ԫ���ú� 
void move_1(SqList *&L){
	int i=0, j=L->length-1;
	ElemType pivot = L->data[0];	//��data[0]Ϊ��׼ 
	ElemType tmp;
//	���������˽������м�ɨ��ֱ��i=jΪֹ 
	while(i<j){
//		����������С�ڵ���pivot��Ԫ�� 
		while(i<j && L->data[j]>pivot)
			j--;
//		���������Ҵ���pivot��Ԫ�� 
		while(i<j && L->data[i]<=pivot)
			i++;
//		i��jλ���ϵ�Ԫ�ػ��� 
		if(i<j){
			tmp = L->data[i];
			L->data[i] = L->data[j];
			L->data[j] = tmp;
		}
	} 
//	ѭ������ʱi��jһ��ֹͣ�ڱ�pivotС��Ԫ����
//	j��0λ����Ԫ�ػ��� 
	tmp = L->data[0];
	L->data[0] = L->data[j];
	L->data[j] = tmp;
	cout<<"i = "<<i<<endl;
}

void move_2(SqList *&L){
	int i=0, j = L->length-1;
	ElemType pivot = L->data[0];	//��data[0]Ϊ��׼
	while(i<j){
//		����������һ��С�ڵ���pivot��data[j] 
		while(j>i && L->data[j]>pivot)
			j--;
		L->data[i] = L->data[j];	//���ҵ���j����data[i] 
		i++;
//		����������һ������pivot��data[j] 
		while(i<j && L->data[i]<=pivot)
			i++;
		L->data[j] = L->data[i];	//���ҵ���i����data[j]
		j--;
	}
//	ѭ������ʱ��λ��i�ϵ�Ԫ���Ѿ�ת�Ƶ�λ��j���ˣ���ʱλ��i��pivot 
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
