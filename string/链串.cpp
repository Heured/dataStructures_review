#include<iostream>
using namespace std;

#define MaxSize 50


typedef struct snode{
	char data;
	struct snode * next;
}LiString;

//��һ���ַ�������������s������β�巨�������� 
void StrAssign(LiString *&s,char cstr[]){
	int i;
	LiString *r, *p;
	s = (LiString *)malloc(sizeof(LiString));
	r = s;	//rʼ��ָ��β�ڵ� 
	for(i=0; cstr[i]!='\0';i++){
		p = (LiString *)malloc(sizeof(LiString));
		p->data = cstr[i];
		r->next = p;
		r = p;
	}
	r->next = NULL;
}

//����t���Ƹ���s��ʹ��β�巨ʵ��
void StrCpy(LiString *&s,LiString *t){
	LiString *p = t->next, *q, *r;
	s = (LiString *)malloc(sizeof(LiString));
	r = s;	//rʼ��ָ��β�ڵ� 
	while(p!=NULL){	//��t�����нڵ㸴�Ƶ�s
		q = (LiString *)malloc(sizeof(LiString));
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next; 
	}
	r->next = NULL;
}

//�жϴ����
bool StrEqual(LiString *s, LiString *t){
	LiString *p=s->next, *q=t->next;
	while(p!=NULL && q!=NULL && p->data==q->data){
		p = p->next;
		q = q->next;
	}
	if(p==NULL && q==NULL)
		return true;
	else
		return false;
}

//�󴮳�
int StrLength(LiString *s){
	int i=0;
	LiString *p = s->next;
	while(p!=NULL){
		i++;
		p = p->next;
	}
	return i;
}

//������,β�巨 
LiString * Concat(LiString *s, LiString *t){
	LiString *str,*p=s->next,*q,*r;
	str = (LiString *)malloc(sizeof(LiString));
	r = str;
	while(p!=NULL){	//��s�����нڵ㸴�Ƶ�str
		q = (LiString *)malloc(sizeof(LiString));
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
	p = t->next;
	while(p!=NULL){	//��t�����нڵ㸴�Ƶ�str 
		q = (LiString *)malloc(sizeof(LiString));
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
	r->next = NULL;
	return str;
} 

//���Ӵ�,��i��ʼj���ַ���β�巨 
LiString * SubStr(LiString *s,int i,int j){
	int k;
	LiString *str, *p=s->next, *q, *r;
	str = (LiString *)malloc(sizeof(LiString));
	str->next = NULL;
	r = str;	//rָ���Ӵ���β�ڵ�
//	��������ȷʱ���ؿմ� 
	if(i<=0||i>StrLength(s)||j<0||i-1+j>StrLength(s))
		return str;
	for(k=0;k<i-1;k++)
		p=p->next;
//	��s�ĵ�i���ڵ㿪ʼ��j���ڵ㸴�Ƶ�str 
	for(k=1;k<=j;k++){
		q = (LiString *)malloc(sizeof(LiString));
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
	r->next = NULL;
	return str;
}

//����s2���뵽s1�ĵ�i���ַ�λ�ã������´� 
LiString * InsStr(LiString *s, int i, LiString *t){
	int k;
	LiString *str, *p = s->next, *p1 = t->next, *q, *r;
	str = (LiString *)malloc(sizeof(LiString));
	str->next = NULL;
	r = str;	//rָ���������β�ڵ�
//	��������ȷʱ���ؿմ� 
	if(i<=0||i>StrLength(s)+1)
		return str;
//	��s��ǰi���ַ����Ƶ�str 
	for(k=1;k<i;k++){
		q = (LiString *)malloc(sizeof(LiString));
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
//	��t�����нڵ㸴�Ƶ�str 
	while(p1 != NULL){
		q = (LiString *)malloc(sizeof(LiString));
		q->data = p1->data;
		r->next = q;
		r = q;
		p1 = p1->next;
	}
//	��sʣ�µĽڵ㸴�Ƶ�str 
	while(p != NULL){
		q = (LiString *)malloc(sizeof(LiString));
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
	r->next = NULL;
	return str;
}

//ɾ���Ӵ�����i��j���ַ��������´� 
LiString * DelStr(LiString *s, int i, int j){
	int k;
	LiString *str, *p = s->next, *q, *r;
	str = (LiString *)malloc(sizeof(LiString));
	str->next = NULL;
	r = str;	//rָ����������β�ڵ� 
//	��������ȷʱ���ؿմ� 
	if(i<=0||i>StrLength(s)||j<0||i-1+j>StrLength(s))
		return str;
//	��s��ǰi-1���ַ����Ƶ�str 
	for(k=0;k<i-1;k++){
		q = (LiString *)malloc(sizeof(LiString));
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
//	��p����j���ڵ� 
	for(k=0;k<j;k++)
		p = p->next;
//	��*p�����Ľڵ㸴�Ƶ�str 
	while(p != NULL){
		q = (LiString *)malloc(sizeof(LiString));
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
	r->next = NULL;
	return str; 
}

//�ڴ�s�У�����i��j���ַ����Ӵ��滻Ϊ��t�������´� 
LiString * RepStr(LiString *s, int i,int j, LiString *t){
	int k;
	LiString *str, *p = s->next, *p1 = t->next, *q, *r;
	str = (LiString *)malloc(sizeof(LiString));
	str->next = NULL;
	r = str;	//rָ����������β�ڵ� 
//	��������ȷʱ���ؿմ� 
	if(i<=0||i>StrLength(s)||j<0||i-1+j>StrLength(s))
		return str;
//	��s��ǰi-1���ַ����Ƶ�str 
	for(k=0;k<i-1;k++){
		q = (LiString *)malloc(sizeof(LiString));
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
	while(p1 != NULL){
		q = (LiString *)malloc(sizeof(LiString));
		q->data = p1->data;
		r->next = q;
		r = q;
		p1 = p1->next;
	}
//	��p����j���ڵ� 
	for(k=0;k<j;k++)
		p = p->next;
//	��*p�����Ľڵ㸴�Ƶ�str 
	while(p != NULL){
		q = (LiString *)malloc(sizeof(LiString));
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
	r->next = NULL;
	return str; 
}

//�����
void DispStr(LiString *s){
	LiString *p = s->next;
	while(p != NULL){
		cout<<p->data;
		p = p->next;
	}
	cout<<endl;
} 

//�����ȳ��ֵ��Ӵ�"ab"�滻��"xyz"
void Repl(LiString *&s){
	LiString *p = s->next, *q;
	int find=0;
//	����"ab"�Ӵ� 
	while(p->next!=NULL && find==0){
//		���ҵ�"ab"�Ӵ����滻Ϊ"xyz" 
		if(p->data=='a'&&p->next->data=='b'){
			p->data='x';
			p->next->data='z';
			q = (LiString *)malloc(sizeof(LiString));
			q->data = 'y';
			q->next = p->next;
			p->next = q;
			find = 1;
		}else
			p = p->next;
	}
}

main(){
	LiString *str, *str2, *str3;
	char a[] = "asddsa", b[] = "asdabdsaab"; 
	StrAssign(str,a);
//	DispStr(str);
	
//	StrCpy(str2,str);
//	DispStr(str2);

//	StrCpy(str2,str);
//	cout<<StrEqual(str,str2);

//	cout<<StrLength(str);
	
//	StrCpy(str2,str);
//	str3 = Concat(str,str2);
//	DispStr(str3);

//	str2 = SubStr(str,2,3);
//	DispStr(str2);

//	StrCpy(str2,str);
//	str3 = InsStr(str,4,str2);
//	DispStr(str3);
	
//	str2 = DelStr(str,3,2);
//	DispStr(str2);

//	StrCpy(str2,str);	
//	str3 = RepStr(str,2,4,str2);
//	DispStr(str3);

	 
	StrAssign(str2,b);
	Repl(str2);
	DispStr(str2);
}
