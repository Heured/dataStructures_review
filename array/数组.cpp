#include<iostream>
#define MaxSize 50
using namespace std;
typedef int ElemType;

//Լɪ������
//	n����վһȦ�����1-n���ӱ��1��ʼѭ������������m���˳���
//	Ȼ��ӳ����ߵ���һλ��ʼ���±���������m���˳���
//	����ظ����У�ֱ��n���˶�����Ϊֹ
//	�����n���˵ĳ���˳�� 
void josephus(int n, int m){
	int p[MaxSize];
	int i,j,t;
	//������ʼ���� 
	for(i=0;i<n;i++)
		p[i] = i+1;
	t=0;	//�״α�������ʼλ�� 
	cout<<"����˳��";
//	iΪ����p��ʣ�µ����� 
	for(i=n;i>=1;i--){
		t = (t+m-1)%i;	//tΪ�����ߵ��±� 
		cout<<' '<<p[t];
//		�����Ԫ��ǰ��һ��λ�� 
		for(j=t+1; j<=i-1; j++)
			p[j-1] = p[j];
	}
}

main(){
	josephus(8,4); 
}
