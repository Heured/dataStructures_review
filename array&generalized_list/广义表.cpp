#include<iostream>
using namespace std;

typedef char ElemType;

typedef struct lnode{
	int tag;	//�ڵ����ͱ�ǩ
	union{
		ElemType data;	//ԭ��ֵ 
		struct lnode *sublist;	//ָ���ӱ��ָ�� 
	}val;
	struct lnode *link;	//ָ����һ��Ԫ�� 
}GLNode;	//�����ڵ����Ͷ��� 

//������ĳ��� 
int GLLength(GLNode *g){	//������g�ĳ���
	int n=0;
	GLNode *g1;
	g1 = g->val.sublist;	//g1ָ������ĵ�һ��Ԫ��
//	�ۼ�Ԫ�ظ��� 
	while(g1 != NULL){
		n++;
		g1 = g1->link;
	}
	return n;
}

//������g�����
//	tag=0����ʾ�ýڵ�Ϊԭ�ӽڵ㣬�ڶ�����Ϊdata 
//	tag=1����ʾ�ýڵ�Ϊ��ڵ㣬�ڶ�����Ϊsublist 
int GLDepth(GLNode *g){
	GLNode *g1;
	int max=0, dep;
//	Ϊԭ��ʱ����0 
	if(g->tag == 0)
		return 0;
	g1 = g->val.sublist;
//	Ϊ�ձ�ʱ����1 
	if(g1 == NULL)
		return 1;
//	����ÿһ��Ԫ�� 
	while(g1 != NULL){
		if(g1->tag == 1){
			dep = GLDepth(g1);
			if(dep>max)
				max = dep;
		}
		g1 = g1->link;
	}
	return (max + 1);	//���ر����� 
}

//��������
void DispGL(GLNode *g){
	if(g != NULL){
//		g��Ԫ��Ϊԭ��ʱ�����ԭ��ֵ 
		if(g->tag == 0)
			cout<<g->val.data;
//		g��Ԫ��Ϊ�ӱ�ʱ 
		else{
			cout<<"(";
//			Ϊ�ձ�ʱ 
			if(g->val.sublist == NULL)
				cout<<"#";
//			Ϊ�ǿ��ӱ�ʱ���ݹ�����ӱ� 
			else
				DispGL(g->val.sublist);
			cout<<")";
		}
		if(g->link != NULL){
			cout<<",";
//			�ݹ����g���ֵ� 
			DispGL(g->link);
		}
	}
}

//�����ַ���s�Ĺ����
GLNode *CreateGL(char *&s){
	GLNode *g;
	char ch = *s++;	//ȡһ���ַ�
	if(ch!='\0'){
		g = (GLNode *)malloc(sizeof(GLNode));	//����һ���½ڵ�
//		��ǰ�ַ�Ϊ������ʱ 
		if(ch == '('){
			g->tag = 1;	//�½ڵ���Ϊ��ͷ�ڵ� 
			g->val.sublist = CreateGL(s);	//�ݹ鹹���ӱ����ӵ���ͷ�ڵ�
//		����")"�ַ���g��Ϊ��
//			����������������()������ᴥ�������Ǵ��������ɲ��ٶ�ȡ()�Ժ���ֵܽڵ�
//			��������ձ���(#)��ʾ��')'���ж�һ�㷢�����ж��Ƿ�Ϊ','ʱ�����Ϊ')'��g->link=NULLȻ��return g 
		}else if(ch == ')'){
			g = NULL;
//		����"#"�ַ�����ʾ�ձ�
		}else if(ch == '#'){
			g = NULL; 
//		Ϊԭ���ַ�
		}else{
			g->tag = 0;	//�½ڵ���Ϊԭ�ӽڵ� 
			g->val.data = ch;
		}
//	��������g��Ϊ�� 
	}else
		g = NULL;
	ch = *s++;	//ȡ��һ���ַ� 
//	��δ���������������ֵܽڵ� 
	if(g!=NULL)
//		��ǰ�ַ�Ϊ","���ݹ鹹���ֵܽڵ� 
		if(ch == ',')
			g->link = CreateGL(s);
//		û���ֵ��ˣ����ֵ�ָ����ΪNULL 
		else
			g->link = NULL;
	return g;	//���ع����g 
}

//����������g��ԭ�Ӹ���
//	������������������㷨 
int atomNum(GLNode *g){
	if(g!=NULL){
		if(g->tag == 0)
			return 1+atomNum(g->link);
		else
			return atomNum(g->val.sublist) + atomNum(g->link);
	}else
		return 0;
}

//��������������νṹ
//	�ڵ�ǰ�ȼ���link������һ���ֵܽڵ� 
//	�����������Լ����ӱ����ֹ�����Ϊ�ݹ��
main(){
	char s[] = "(b,(b,a,(#),d),((a,b),c,((#))))";
	char *st = s;
	GLNode *g;
	g = CreateGL(st);
	cout<<"ԭ�Ӹ�����"<<atomNum(g)<<endl;
	cout<<"���ȣ�"<<GLLength(g)<<endl;
	cout<<"��ȣ�"<<GLDepth(g)<<endl;
	DispGL(g);
}
