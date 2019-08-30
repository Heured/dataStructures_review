#include<iostream>
#define MaxSize 50
using namespace std;
typedef int ElemType;

//约瑟夫问题
//	n个人站一圈，编号1-n，从编号1开始循环报数，数到m的人出列
//	然后从出列者的下一位开始重新报数，数到m的人出列
//	如此重复进行，直到n个人都出列为止
//	输出这n个人的出列顺序 
void josephus(int n, int m){
	int p[MaxSize];
	int i,j,t;
	//构建初始序列 
	for(i=0;i<n;i++)
		p[i] = i+1;
	t=0;	//首次报数的起始位置 
	cout<<"出列顺序：";
//	i为数组p中剩下的人数 
	for(i=n;i>=1;i--){
		t = (t+m-1)%i;	//t为出列者的下标 
		cout<<' '<<p[t];
//		后面的元素前移一个位置 
		for(j=t+1; j<=i-1; j++)
			p[j-1] = p[j];
	}
}

main(){
	josephus(8,4); 
}
