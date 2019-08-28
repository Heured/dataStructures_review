#include<iostream>
using namespace std;

#define MaxSize 50


typedef struct{
	char data[MaxSize];	//��Ŵ��ַ� 
	int length;		//��Ŵ��� 
}SqString;		//˳������

//����һ����ֵ����cstr�Ĵ�s 
void StrAssign(SqString &s, char cstr[]){	//sΪ�����Ͳ��� 
	int i;
	for(i=0; cstr[i]!='\0'; i++)
		s.data[i] = cstr[i];
	s.length = i;
}

//��һ�������Ƹ���һ����
void StrCopy(SqString &s, SqString t){	//sΪ�����Ͳ��� 
	int i;
	for(i=0;i<t.length;i++)
		s.data[i] = t.data[i];
	s.length = t.length;
}

//�жϴ����
bool StrEqual(SqString s, SqString t){
	bool same = true;
	int i;
//	���Ȳ���� 
	if(s.length != t.length)	//���Ȳ����ʱ����0 
		same = false;
	else
		for(i=0;i<s.length;i++)
//			��һ����Ӧ�ַ�����ͬʱ����0 
			if(s.data[i] != t.data[i]){
				same = false;
				break;
			}
	return same;
}

//�󴮳�
int StrLength(SqString s){
	return s.length;
}

//������
SqString Concat(SqString s, SqString t){
	SqString str;
	int i;
	str.length = s.length + t.length;
//	��s.data���Ƶ�str
	for(i=0; i<s.length;i++)
		str.data[i] = s.data[i];
//	��t.data����str֮�� 
	for(i=0; i<t.length;i++)
		str.data[s.length+i] = t.data[i];
	return str;
}

//���Ӵ�����i(1<=i<=StrLength(s))��,����j���ַ�
SqString SubStr(SqString s, int i,int j){
	SqString str;
	int k;
	str.length = 0;
//	��������ȷʱ���ؿմ� 
	if(i<=0||i>s.length||j<0||i+j-1>s.length)
		return str;
//	��s.data[i-1,i-1+j]���Ƶ�str 
	for(k=i-1;k<i-1+j;k++)
		str.data[k-(i-1)] = s.data[k];
	str.length = j;
	return str;
}

//����s2���뵽��s1�ĵ�i(1<=iStrLength(s)+1)���ַ�֮ǰ��
//	������s1��Ϊ[0,i-2]��[i-1,s1.length-1]������ 
//	��s2����s1������֮�� 
SqString InsStr(SqString s1, int i, SqString s2){
	int j;
	SqString str;
	str.length = 0;
//	��������ȷʱ���ؿմ� 
	if(i<=0 || i>s1.length+1)
		return str;
//	��s1.data[0,i-2]���Ƶ�str 
	for(j=0;j<i-1;j++)
		str.data[j] = s1.data[j];
//	��s2.data[0,s2.length-1]�ӵ�str֮�� 
	for(j=0;j<s2.length;j++)
		str.data[i-1+j] = s2.data[j];
//	��s1[i-1,s1.length-1]�ӵ�str֮�� 
	for(j=i-1;j<s1.length;j++)
		str.data[s2.length+j] = s1.data[j];
	str.length = s1.length + s2.length;
	return str;
}

//�Ӵ�ɾȥ��i�𳤶�Ϊj���Ӵ������ز������´�
SqString DelStr(SqString s,int i,int j){
	int k;
	SqString str;
	str.length = 0;
//	��������ȷʱ���ؿմ� 
	if(i<=0 || i>s.length || i-1+j>s.length)
		return str;
//	��s.data[0,i-2]���Ƶ�str 
	for(k=0;k<i-1;k++)
		str.data[k] = s.data[k];
//	��s.data[i-1+j,s.length-1]���Ƶ�str 
	for(k = i-1+j;k<s.length;k++)
		str.data[k-j] = s.data[k];
	str.length = s.length - j;
	return str;
}

//�ڴ�s�У�����i�𳤶�Ϊj���Ӵ��滻Ϊ��t�������´� 
SqString RepStr(SqString s,int i,int j, SqString t){
	int k;
	SqString str;
	str.length = 0;
//	��������ȷʱ���ؿմ�
	if(i<=0 || i>s.length || i-1+j>s.length)
		return str;
//	��s.data[0,i-2]���Ƶ�str 
	for(k=0;k<i-1;k++)
		str.data[k] = s.data[k];
//	��t.data[0.t.length-1]���Ƶ�str 
	for(k=0;k<t.length;k++)
		str.data[i-1+k] = t.data[k];
//	��s.data[i-1+j,s.length-1]���Ƶ�str 
	for(k = i-1+j;k<s.length;k++)
		str.data[k-j+t.length] = s.data[k];
	str.length = s.length - j + t.length;
	return str;
}

//����� 
void DispStr(SqString s){
	int i;
	if(s.length>0){
		for(i=0; i<s.length;i++)
			cout<<s.data[i];
		cout<<endl;
	}
}

//�Ƚ�����
//	s>t����1����ȷ���0��s<t����-1 
int Strcmp(SqString s,SqString t){
	int i,comlen;
//	��s��t�Ĺ�ͬ����(֮��϶̵ĳ���)
	if(s.length<t.length)
		comlen = s.length;
	else
		comlen = t.length;
//	��ͬ����������ַ��Ƚ�
	for(i=0;i<comlen;i++)
		if(s.data[i] > t.data[i])
			return 1;
		else if(s.data[i] < t.data[i])
			return -1;
//	�ڹ�ͬ�����£�ÿ���ַ���ͬ�����Խ������ȳ��� 
	if(s.length == t.length)
		return 0;
	else if(s.length > t.length)
		return 1;
	else
		return -1; 
}

//��s�г��ֵĵ�һ���������ͬ�ַ����ɵ��Ӵ�
void LongestString(SqString s,int &index, int &max){
	int length=1,i=0,start=0;	//length�����Ӵ�����
	index=0,max=0;	//index������Ӵ���s�п�ʼλ�ã�max���泤��
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
			length = 1;	//��ʼ����һ���Ӵ�����ʼλ�úͳ��� 
		}
}

//��BF�㷨(Brute-Force)���ڴ�s���ҵ��봮t��ȵ��Ӵ� 
//	ƥ��ɹ������Ӵ���ʼλ�ã�ʧ�ܷ���-1
int index(SqString s, SqString t){
	int i=0,j=0;
	while(i<s.length &&j<t.length){
		if(s.data[i] == t.data[j]){
			i++;
			j++;	//����ƥ����һ���ַ� 
		}else{
//		�����ǰ�ַ���ƥ�䣬��i���ص�s����t��ƥ��Ŀ�ʼλ�õ���һλ��j��0 
			i = i-j+1;
			j = 0;
		}
	}
//	���j����ڴ�t�ĳ��ȣ���ʾ��s�����ڴ�t��ȵ��Ӵ������ؿ�ʼƥ��λ�� 
	if(j>=t.length)
		return (i-t.length);
	else
		return -1;
}

//��KMP�㷨(Knuth = Morris-Pratt)���ڴ�s���ҵ��봮t��ȵ��Ӵ� 
//	ƥ��ɹ������Ӵ���ʼλ�ã�ʧ�ܷ���-1
//��ģʽ��t��next[]ֵ
//	�������Ϊ�� data[0,i-1]��data[j-i,j-1]���(j>i>0)����next[j]=i 
void GetNext(SqString t,int next[]){
	int j,k;
	j = 0;
	k = -1;
	next[0] = -1;
	while(j<t.length-1){
//		k=-1�����������1����ʼʱ����Ҫ��next[1]��Ϊ0��������Ҫ��k����Ϊ-1
//						2��data[j]��data[0]ƥ�䲻�ɹ���k��Ϊ-1��������next[j+1]��Ϊ0
//		���data[j]��data[k]ƥ��ɹ���next[j+1]��Ϊk+1 
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
//		j=-1��ʾƥ���һ���ַ����ɹ�����s�Ŀ�ʼƥ��λ������һλ��j��0 
		if(j == -1 || s.data[i] == t.data[j]){
			i++;
			j++;
		}else
			j = next[j];	//i����,j���� 
	}
	if(j>=t.length)
		return (i-t.length);
	else
		return -1;
}

//����������KMP�㷨(Knuth = Morris-Pratt)���ڴ�s���ҵ��봮t��ȵ��Ӵ� 
//	ƥ��ɹ������Ӵ���ʼλ�ã�ʧ�ܷ���-1
//��ģʽ��t��nextval[]ֵ
//	�������Ϊ�� data[0,i]��data[j-i,j]���(j>i>0)����next[j]=next[i]
//				data[0,i-1]��data[j-i,j-1]��ȶ���data[i]��data[j]�����(j>i>0)����next[j] = i;
void GetNextval(SqString t,int nextval[]){
	int j = 0, k = -1;
	nextval[0] = -1;
	while(j<t.length){
		if(k == -1 || t.data[j] == t.data[k]){
			j++;
			k++;
//			ƥ��ɹ���j,k����һλ��������� 
			if(t.data[j]!=t.data[k])
				nextval[j] = k;
			else
//			ƥ��ɹ���j,k����һλ������� 
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

//	�ݹ�Դ�����
//	�ݹ�ģ��	f(s) = Concat(f(SubStr(s,2,StrLength(s)-1)), SubStr(s,1,1))	���s="*"��Ϊ�� f(s) = s;
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
//	cout<<"�������ͬ�ַ��Ӵ�: ";
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
