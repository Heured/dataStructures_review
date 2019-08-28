#include<iostream>
using namespace std;
typedef int ElemType;


//��n!,�׳� 
int factorial(int n){
	if(n==1||n==0)
		return 1;
	else
		return factorial(n-1)*n;
}

//��쳲���������{1,1,2,3,5,8.....},f(n) = f(n-1) + f(n-2)
int Fib(int n){
	if(n==1||n==2)
		return 1;
	else
		return Fib(n-1)+Fib(n-2);
}

typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LinkList;

//��������� 
int Sum(LinkList *L){
	if(L==NULL)
		return 0;
	else
		return (L->data+Sum(L->next));
}

//Hanoi����
//	��x,y,z���������������Ͽ��Է���Ƭ��ԭ����ֱ�������Զ��ֱ��С������
//	����x��������ֱ��1~n����Ƭ��Ҫ��x�����ϵ���Ƭȫ��ת�Ƶ�z������
//	��ÿһ�ε��ƶ��ֽ�Ϊ3����
//		�Ƚ�x�ϵ�ǰn-1����Ƭͨ��zŲ��y�ϣ�(��һ��Ҫ���·ֽ�)
//		�ٽ����һ����ƬŲ��z��
//		�ٽ�y�ϵ�n-1����Ƭͨ��xŲ��z��(��һ��Ҫ���·ֽ�)
//	����: S(n) = 2*S(n-1)+1��S(1) = 1
void Hanoi(int n, char X, char Y, char Z){
	if(n==1)
		cout<<"����"<<n<<"����Ƭ��"<<X<<"�ƶ���"<<Z<<endl;
	else{
		Hanoi(n-1,X,Z,Y);
		cout<<"����"<<n<<"����Ƭ��"<<X<<"�ƶ���"<<Z<<endl;
		Hanoi(n-1,Y,X,Z);
	}
}

//�ݹ���A[]�е���Сֵ
//�ݹ�ģ�� f(A,i) = min(f(A,i-1),A[i])	f(A,0) = A[0]
double findMin(float A[], int i){
	double m;
	if(i==0)
		return A[0];
	else{
		m = f(A,i-1);
		if(m>a[i])
			return A[i];
		else
			return m;
	}
} 


//�ݹ��ԭ��������ջ�Ĳ�����
//	���޷��õ�ֱ�ӵĽ�ĵݹ��������£����õݹ�����ջ����ִ�иõݹ���ķֽ�ݹ��� 
//	��ִ����������ݹ���ķֽ�ݹ�����ٽ��õݹ����ջ��ִ��

//	��Ƶݹ��㷨ʱ����Ҫ����Ƶݹ�ģ�ͣ���ת���ɺ��� 
main(){
//	cout<<factorial();
//	cout<<Fib(6);
	Hanoi(4,'1','2','3');
} 
