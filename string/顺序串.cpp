#include<iostream>
using namespace std;

#define MaxSize 50


typedef struct{
	char data[MaxSize];	//存放串字符 
	int length;		//存放串长 
}SqString;		//顺序串类型

//生成一个其值等于cstr的串s 
void StrAssign(SqString &s, char cstr[]){	//s为引用型参数 
	int i;
	for(i=0; cstr[i]!='\0'; i++)
		s.data[i] = cstr[i];
	s.length = i;
}

//将一个串复制给另一个串
void StrCopy(SqString &s, SqString t){	//s为引用型参数 
	int i;
	for(i=0;i<t.length;i++)
		s.data[i] = t.data[i];
	s.length = t.length;
}

//判断串相等
bool StrEqual(SqString s, SqString t){
	bool same = true;
	int i;
//	长度不相等 
	if(s.length != t.length)	//长度不相等时返回0 
		same = false;
	else
		for(i=0;i<s.length;i++)
//			有一个对应字符不相同时返回0 
			if(s.data[i] != t.data[i]){
				same = false;
				break;
			}
	return same;
}

//求串长
int StrLength(SqString s){
	return s.length;
}

//串连接
SqString Concat(SqString s, SqString t){
	SqString str;
	int i;
	str.length = s.length + t.length;
//	将s.data复制到str
	for(i=0; i<s.length;i++)
		str.data[i] = s.data[i];
//	将t.data接在str之后 
	for(i=0; i<t.length;i++)
		str.data[s.length+i] = t.data[i];
	return str;
}

//求子串，从i(1<=i<=StrLength(s))起,连续j个字符
SqString SubStr(SqString s, int i,int j){
	SqString str;
	int k;
	str.length = 0;
//	参数不正确时返回空串 
	if(i<=0||i>s.length||j<0||i+j-1>s.length)
		return str;
//	将s.data[i-1,i-1+j]复制到str 
	for(k=i-1;k<i-1+j;k++)
		str.data[k-(i-1)] = s.data[k];
	str.length = j;
	return str;
}

//将串s2插入到串s1的第i(1<=iStrLength(s)+1)个字符之前，
//	即将串s1分为[0,i-2]和[i-1,s1.length-1]两部分 
//	将s2插入s1两部分之间 
SqString InsStr(SqString s1, int i, SqString s2){
	int j;
	SqString str;
	str.length = 0;
//	参数不正确时返回空串 
	if(i<=0 || i>s1.length+1)
		return str;
//	将s1.data[0,i-2]复制到str 
	for(j=0;j<i-1;j++)
		str.data[j] = s1.data[j];
//	将s2.data[0,s2.length-1]接到str之后 
	for(j=0;j<s2.length;j++)
		str.data[i-1+j] = s2.data[j];
//	将s1[i-1,s1.length-1]接到str之后 
	for(j=i-1;j<s1.length;j++)
		str.data[s2.length+j] = s1.data[j];
	str.length = s1.length + s2.length;
	return str;
}

//从串删去第i起长度为j的子串，返回产生的新串
SqString DelStr(SqString s,int i,int j){
	int k;
	SqString str;
	str.length = 0;
//	参数不正确时返回空串 
	if(i<=0 || i>s.length || i-1+j>s.length)
		return str;
//	将s.data[0,i-2]复制到str 
	for(k=0;k<i-1;k++)
		str.data[k] = s.data[k];
//	将s.data[i-1+j,s.length-1]复制到str 
	for(k = i-1+j;k<s.length;k++)
		str.data[k-j] = s.data[k];
	str.length = s.length - j;
	return str;
}

//在串s中，将第i起长度为j的子串替换为串t，返回新串 
SqString RepStr(SqString s,int i,int j, SqString t){
	int k;
	SqString str;
	str.length = 0;
//	参数不正确时返回空串
	if(i<=0 || i>s.length || i-1+j>s.length)
		return str;
//	将s.data[0,i-2]复制到str 
	for(k=0;k<i-1;k++)
		str.data[k] = s.data[k];
//	将t.data[0.t.length-1]复制到str 
	for(k=0;k<t.length;k++)
		str.data[i-1+k] = t.data[k];
//	将s.data[i-1+j,s.length-1]复制到str 
	for(k = i-1+j;k<s.length;k++)
		str.data[k-j+t.length] = s.data[k];
	str.length = s.length - j + t.length;
	return str;
}

//输出串 
void DispStr(SqString s){
	int i;
	if(s.length>0){
		for(i=0; i<s.length;i++)
			cout<<s.data[i];
		cout<<endl;
	}
}

//比较两串
//	s>t返回1，相等返回0，s<t返回-1 
int Strcmp(SqString s,SqString t){
	int i,comlen;
//	求s和t的共同长度(之间较短的长度)
	if(s.length<t.length)
		comlen = s.length;
	else
		comlen = t.length;
//	共同长度下逐个字符比较
	for(i=0;i<comlen;i++)
		if(s.data[i] > t.data[i])
			return 1;
		else if(s.data[i] < t.data[i])
			return -1;
//	在共同长度下，每个字符相同，所以接下来比长度 
	if(s.length == t.length)
		return 0;
	else if(s.length > t.length)
		return 1;
	else
		return -1; 
}

//求串s中出现的第一个最长连续相同字符构成的子串
void LongestString(SqString s,int &index, int &max){
	int length=1,i=0,start=0;	//length保存子串长度
	index=0,max=0;	//index保存最长子串在s中开始位置，max保存长度
	while(i<s.length-1)
		if(s.data[i] == s.data[i+1]){
			i++;
			length++;
		}else{
			if(max<length){
				max = length;
				index = start;
			}
			i++;
			start = i;
			length = 1;	//初始化下一个子串的起始位置和长度 
		}
}

//用BF算法(Brute-Force)，在串s中找到与串t相等的子串 
//	匹配成功返回子串开始位置，失败返回-1
int index(SqString s, SqString t){
	int i=0,j=0;
	while(i<s.length &&j<t.length){
		if(s.data[i] == t.data[j]){
			i++;
			j++;	//继续匹配下一个字符 
		}else{
//		如果当前字符不匹配，则i返回到s串与t串匹配的开始位置的下一位，j置0 
			i = i-j+1;
			j = 0;
		}
	}
//	如果j大等于串t的长度，表示串s包含于串t相等的子串，返回开始匹配位置 
	if(j>=t.length)
		return (i-t.length);
	else
		return -1;
}

//用KMP算法(Knuth = Morris-Pratt)，在串s中找到与串t相等的子串 
//	匹配成功返回子串开始位置，失败返回-1
//对模式串t求next[]值
//	个人理解为， data[0,i-1]与data[j-i,j-1]相等(j>i>0)，则next[j]=i 
void GetNext(SqString t,int next[]){
	int j,k;
	j = 0;
	k = -1;
	next[0] = -1;
	while(j<t.length-1){
//		k=-1有两种情况，1：开始时，需要将next[1]置为0，所以需要将k先置为-1
//						2：data[j]与data[0]匹配不成功，k置为-1，将导致next[j+1]置为0
//		如果data[j]与data[k]匹配成功，next[j+1]置为k+1 
		if(k == -1 || t.data[j] == t.data[k]){
			j++;
			k++;
			next[j] = k;
		}else
			k = next[k];
	}
}
int KMPIndex(SqString s, SqString t){
	int next[MaxSize], i=0, j=0;
	GetNext(t,next);
	while(i<s.length && j<t.length){
//		j=-1表示匹配第一个字符不成功，串s的开始匹配位置下移一位，j置0 
		if(j == -1 || s.data[i] == t.data[j]){
			i++;
			j++;
		}else
			j = next[j];	//i不变,j后退 
	}
	if(j>=t.length)
		return (i-t.length);
	else
		return -1;
}

//用修正过的KMP算法(Knuth = Morris-Pratt)，在串s中找到与串t相等的子串 
//	匹配成功返回子串开始位置，失败返回-1
//对模式串t求nextval[]值
//	个人理解为， data[0,i]与data[j-i,j]相等(j>i>0)，则next[j]=next[i]
//				data[0,i-1]与data[j-i,j-1]相等而且data[i]与data[j]不相等(j>i>0)，则next[j] = i;
void GetNextval(SqString t,int nextval[]){
	int j = 0, k = -1;
	nextval[0] = -1;
	while(j<t.length){
		if(k == -1 || t.data[j] == t.data[k]){
			j++;
			k++;
//			匹配成功后，j,k后移一位，若不相等 
			if(t.data[j]!=t.data[k])
				nextval[j] = k;
			else
//			匹配成功，j,k后移一位，若相等 
				nextval[j] = nextval[k];
		}else
			k = nextval[k];
	}
}
int KMPIndex1(SqString s,SqString t){
	int nextval[MaxSize], i=0, j=0;
	GetNextval(t,nextval);
	while(i<s.length && j<t.length){
		if(j == -1 || s.data[i] == t.data[j]){
			i++;
			j++;
		}else
			j = nextval[j];
	}
	if(j>=t.length)
		return (i-t.length);
	else
		return -1;
	
}

//	递归对串求逆
//	递归模型	f(s) = Concat(f(SubStr(s,2,StrLength(s)-1)), SubStr(s,1,1))	如果s="*"或为空 f(s) = s;
SqString invert(SqString s){
	SqString s1, s2;
	if(StrLength(s)>0){
		s1 = invert(SubStr(s, 2, StrLength(s)-1));
		s2 = Concat(s1,SubStr(s,1,1));
	}else
		StrCopy(s2,s);
	return s2;
}

main(){
	char a[] = "asddsea",b[] = "123", c[] = "dds", d[] = "abcacabc";
	SqString str,str2,str3;
	StrAssign(str,a);

//	StrCopy(str2,str);
//	DispStr(str2);

//	StrCopy(str2,str);
//	cout<<StrEqual(str,str2);

//	cout<<StrLength(str);

	
//	StrAssign(str2,b);
//	str3 = Concat(str,str2);
//	DispStr(str3);

//	str2 = SubStr(str,2,3);
//	DispStr(str2);

//	StrAssign(str2,b);
//	str3 = InsStr(str,3,str2);
//	DispStr(str3);


//	StrAssign(str2,b);
//	str3 = RepStr(str,2,2,str2);
//	DispStr(str3);
	
//	StrAssign(str2,b);
//	cout<<Strcmp(str,str2)<<" "<<Strcmp(str2,str2);

//	int index,max;
//	LongestString(str,index,max);
//	DispStr(str);
//	cout<<"最长连续相同字符子串: ";
//	DispStr(SubStr(str,index+1,max));

//	StrAssign(str2,c); 
//	cout<<index(str,str2)<<endl;
//	cout<<KMPIndex(str,str2)<<endl;
//	cout<<KMPIndex1(str,str2)<<endl;
	
//	int next[MaxSize],next1[MaxSize];
//	StrAssign(str2,d);
//	GetNext(str2,next);
//	GetNextval(str2,next1);
//	for(int i=0;i<8;i++)
//		cout<<next[i]<<" ";
//	cout<<endl;
//	for(int i=0;i<8;i++)
//		cout<<next1[i]<<" ";
//	cout<<endl;
	
	DispStr(invert(str));
	
}
