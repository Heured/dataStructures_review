#include<iostream>
using namespace std;

#define MaxSize 50


typedef struct snode{
	char data;
	struct snode * next;
}LiString;

//将一个字符串常量赋给串s，利用尾插法建立链串 
void StrAssign(LiString *&s,char cstr[]){
	int i;
	LiString *r, *p;
	s = (LiString *)malloc(sizeof(LiString));
	r = s;	//r始终指向尾节点 
	for(i=0; cstr[i]!='\0';i++){
		p = (LiString *)malloc(sizeof(LiString));
		p->data = cstr[i];
		r->next = p;
		r = p;
	}
	r->next = NULL;
}

//将串t复制给串s，使用尾插法实现
void StrCpy(LiString *&s,LiString *t){
	LiString *p = t->next, *q, *r;
	s = (LiString *)malloc(sizeof(LiString));
	r = s;	//r始终指向尾节点 
	while(p!=NULL){	//将t的所有节点复制到s
		q = (LiString *)malloc(sizeof(LiString));
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next; 
	}
	r->next = NULL;
}

//判断串相等
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

//求串长
int StrLength(LiString *s){
	int i=0;
	LiString *p = s->next;
	while(p!=NULL){
		i++;
		p = p->next;
	}
	return i;
}

//串连接,尾插法 
LiString * Concat(LiString *s, LiString *t){
	LiString *str,*p=s->next,*q,*r;
	str = (LiString *)malloc(sizeof(LiString));
	r = str;
	while(p!=NULL){	//将s的所有节点复制到str
		q = (LiString *)malloc(sizeof(LiString));
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
	p = t->next;
	while(p!=NULL){	//将t的所有节点复制到str 
		q = (LiString *)malloc(sizeof(LiString));
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
	r->next = NULL;
	return str;
} 

//求子串,第i开始j个字符，尾插法 
LiString * SubStr(LiString *s,int i,int j){
	int k;
	LiString *str, *p=s->next, *q, *r;
	str = (LiString *)malloc(sizeof(LiString));
	str->next = NULL;
	r = str;	//r指向子串的尾节点
//	参数不正确时返回空串 
	if(i<=0||i>StrLength(s)||j<0||i-1+j>StrLength(s))
		return str;
	for(k=0;k<i-1;k++)
		p=p->next;
//	将s的第i个节点开始的j个节点复制到str 
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

//将串s2插入到s1的第i个字符位置，返回新串 
LiString * InsStr(LiString *s, int i, LiString *t){
	int k;
	LiString *str, *p = s->next, *p1 = t->next, *q, *r;
	str = (LiString *)malloc(sizeof(LiString));
	str->next = NULL;
	r = str;	//r指向新链表的尾节点
//	参数不正确时返回空串 
	if(i<=0||i>StrLength(s)+1)
		return str;
//	将s的前i个字符复制到str 
	for(k=1;k<i;k++){
		q = (LiString *)malloc(sizeof(LiString));
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
//	将t的所有节点复制到str 
	while(p1 != NULL){
		q = (LiString *)malloc(sizeof(LiString));
		q->data = p1->data;
		r->next = q;
		r = q;
		p1 = p1->next;
	}
//	将s剩下的节点复制到str 
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

//删除子串，第i起j个字符，返回新串 
LiString * DelStr(LiString *s, int i, int j){
	int k;
	LiString *str, *p = s->next, *q, *r;
	str = (LiString *)malloc(sizeof(LiString));
	str->next = NULL;
	r = str;	//r指向新链串的尾节点 
//	参数不正确时返回空串 
	if(i<=0||i>StrLength(s)||j<0||i-1+j>StrLength(s))
		return str;
//	将s的前i-1个字符复制到str 
	for(k=0;k<i-1;k++){
		q = (LiString *)malloc(sizeof(LiString));
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
//	让p下跳j个节点 
	for(k=0;k<j;k++)
		p = p->next;
//	将*p及其后的节点复制到str 
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

//在串s中，将第i起j个字符的子串替换为串t，返回新串 
LiString * RepStr(LiString *s, int i,int j, LiString *t){
	int k;
	LiString *str, *p = s->next, *p1 = t->next, *q, *r;
	str = (LiString *)malloc(sizeof(LiString));
	str->next = NULL;
	r = str;	//r指向新链串的尾节点 
//	参数不正确时返回空串 
	if(i<=0||i>StrLength(s)||j<0||i-1+j>StrLength(s))
		return str;
//	将s的前i-1个字符复制到str 
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
//	让p下跳j个节点 
	for(k=0;k<j;k++)
		p = p->next;
//	将*p及其后的节点复制到str 
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

//输出串
void DispStr(LiString *s){
	LiString *p = s->next;
	while(p != NULL){
		cout<<p->data;
		p = p->next;
	}
	cout<<endl;
} 

//把最先出现的子串"ab"替换成"xyz"
void Repl(LiString *&s){
	LiString *p = s->next, *q;
	int find=0;
//	查找"ab"子串 
	while(p->next!=NULL && find==0){
//		查找到"ab"子串，替换为"xyz" 
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
