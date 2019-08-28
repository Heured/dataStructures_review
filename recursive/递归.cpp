#include<iostream>
using namespace std;
typedef int ElemType;


//求n!,阶乘 
int factorial(int n){
	if(n==1||n==0)
		return 1;
	else
		return factorial(n-1)*n;
}

//求斐波那契数列{1,1,2,3,5,8.....},f(n) = f(n-1) + f(n-2)
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

//单链表求和 
int Sum(LinkList *L){
	if(L==NULL)
		return 0;
	else
		return (L->data+Sum(L->next));
}

//Hanoi问题
//	有x,y,z三个塔座，塔座上可以放盘片，原则是直径大的永远在直径小的下面
//	现在x塔座上有直径1~n的盘片，要将x塔座上的盘片全部转移到z塔座上
//	将每一次的移动分解为3步，
//		先将x上的前n-1个盘片通过z挪到y上，(这一步要向下分解)
//		再将最后一个盘片挪到z，
//		再将y上的n-1个盘片通过x挪到z，(这一步要向下分解)
//	步数: S(n) = 2*S(n-1)+1；S(1) = 1
void Hanoi(int n, char X, char Y, char Z){
	if(n==1)
		cout<<"将第"<<n<<"个盘片从"<<X<<"移动到"<<Z<<endl;
	else{
		Hanoi(n-1,X,Z,Y);
		cout<<"将第"<<n<<"个盘片从"<<X<<"移动到"<<Z<<endl;
		Hanoi(n-1,Y,X,Z);
	}
}

//递归求A[]中的最小值
//递归模型 f(A,i) = min(f(A,i-1),A[i])	f(A,0) = A[0]
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


//递归的原理类似于栈的操作，
//	在无法得到直接的解的递归出口情况下，将该递归体入栈，再执行该递归体的分解递归体 
//	在执行完了这个递归体的分解递归体后，再将该递归体出栈再执行

//	设计递归算法时，需要先设计递归模型，再转换成函数 
main(){
//	cout<<factorial();
//	cout<<Fib(6);
	Hanoi(4,'1','2','3');
} 
