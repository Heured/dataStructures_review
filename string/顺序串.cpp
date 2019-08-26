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

main(){
	char a[] = "asddsa",b[] = "123";
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

	int index,max;
	LongestString(str,index,max);
	DispStr(str);
	cout<<"�������ͬ�ַ��Ӵ�: ";
	DispStr(SubStr(str,index+1,max));
}
