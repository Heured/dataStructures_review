#include<iostream>
using namespace std;

#define MaxOp 7
#define MaxSize 50 
//�趨��������ȼ� 
struct{
	char ch;	//����� 
	int pri;	//���ȼ� 
}lpri[] = {{'=',0},{'(',1},{'*',5},{'/',5},{'+',3},{'-',3},{')',6}},
rpri[] = {{'=',0},{'(',6},{'*',4},{'/',4},{'+',2},{'-',2},{')',1}};

//������������ȵ�����£������ȼ� 
int leftpri(char op){
	int i;
	for(i=0; i<MaxOp; i++)
		if(lpri[i].ch == op) return lpri[i].pri;
}

//������������ȵ�����£������ȼ� 
int rightpri(char op){
	int i;
	for(i=0; i<MaxOp;i++)
		if(rpri[i].ch == op) return rpri[i].pri;
}

//�ж��Ƿ�Ϊ����� 
bool InOp(char ch){
	if(ch =='('||ch ==')'||ch =='+'||ch =='-'||ch =='*'||ch =='/')
		return true;
	else
		return false;
}

//op1��op2��������ȼ��ıȽϽ�� 
int Precede(char op1, char op2){
	if(leftpri(op1) == rightpri(op2))
		return 0;
	else if(leftpri(op1) < rightpri(op2))
		return -1;
	else
		return 1;
}

//���������ʽexpת���ɺ�׺���ʽpostexp
void trans(char *exp, char postexp[]){
	struct{
		char data[MaxSize];	//�������� 
		int top;	//ջָ�� 
	}op;	//����һ�������ջ
	
	int i = 0;	//i��Ϊpostexp���±� 
	op.top = -1;
	op.top++;
	op.data[op.top] = '=';
	while(*exp != '\0'){	//exp���ʽδɨ����ʱѭ�� 
//		Ϊ�����ַ������ 
		if(!InOp(*exp)){
//			�ж�Ϊ���� 
			while(*exp>='0' && *exp<='9'){
				postexp[i++] = *exp;
				exp++;
			}
			postexp[i++] = '#';	//��'#'��ʶһ����ֵ���Ľ��� 
		}else
			switch(Precede(op.data[op.top], *exp)){
//				ջ������������ȼ��ȱ�ɨ�赽����������ȼ��ͣ�����ɨ�赽�����������ջ 
				case -1:
					op.top++;
					op.data[op.top] = *exp;
					exp++;	//����ɨ�������ַ�
					break;
//				ջ������������ȼ��ϸߣ���ջ������������ں�׺���ʽ�� 
				case 1:
					postexp[i++] = op.data[op.top];
					op.top--;
					break;
//				ֻ�����������������
				case 0:
					op.top--;	//��'('��ջ 
					exp++;	//����ɨ�������ַ� 
					break;
				
			}
	}
	while(op.data[op.top] != '='){	//��ʱexpɨ����ϣ���ջ��'='Ϊֹ 
		postexp[i++] = op.data[op.top];
		op.top--;
	}
	postexp[i] = '\0';	//��postexp���ʽ��ӽ�����ʶ 
}

//��׺���ʽ���
//��׺���ʽ���������׺���ʽ������࣬��ɨ�赽�����ʱ��ջ�ڿ϶��������������������ֵ
//	ֻ��Ҫ��������ֵ��ջ��������㣬�ٽ���������ջ
//	���ջ��ʣ��Ψһһ�����ռ����� 
float compvalue(char *postexp){	//�����׺���ʽpostexo��ֵ 
	struct{
		float data[MaxSize];	//�����ֵ 
		int top;	//ջָ�� 
	}st;	//����һ��������ջ
	
	float d,a,b,c;
	st.top = -1;
	while(*postexp != '\0'){	//postexp�ַ���δɨ����ʱѭ�� 
		switch(*postexp){
			case '+':	//�ж�Ϊ+�� 
				a = st.data[st.top];
				st.top--;	//��ջȡ��ֵa
				b = st.data[st.top];
				st.top--;	//��ջȡ��ֵb
				c = a+b;	//����c
				st.top++;
				st.data[st.top] = c;	//����������ջ
				break;
			case '-':	//�ж�Ϊ-�� 
				a = st.data[st.top];
				st.top--;	//��ջȡ��ֵa
				b = st.data[st.top];
				st.top--;	//��ջȡ��ֵb
				c = b-a;	//����c
				st.top++;
				st.data[st.top] = c;	//����������ջ
				break;
			case '*':	//�ж�Ϊ*�� 
				a = st.data[st.top];
				st.top--;	//��ջȡ��ֵa
				b = st.data[st.top];
				st.top--;	//��ջȡ��ֵb
				c = a*b;	//����c
				st.top++;
				st.data[st.top] = c;	//����������ջ
				break;
			case '/':	//�ж�Ϊ/�� 
				a = st.data[st.top];
				st.top--;	//��ջȡ��ֵa
				b = st.data[st.top];
				st.top--;	//��ջȡ��ֵb
//				��Ϊ�ǳ������㣬������Ҫ�жϳ����Ƿ�Ϊ0 
				if(a!=0){
					c = b/a;	//����c������ջ���Ƚ������ԭ��������b/a������a/b 
					st.top++;
					st.data[st.top] = c;	//����������ջ
				}else{
					cout<<endl<<"������󣡣�"<<endl;
					exit(0);	//�쳣�˳� 
				}
				break;
			default:	//���������ַ� 
				d = 0;	//�������������ַ�ת������ֵ�ŵ�d�� 
				while(*postexp >= '0' && *postexp <= '9'){
					d = 10*d + *postexp-'0';
					postexp++;
				}
				st.top++;
				st.data[st.top] = d;
				break;
		}
		postexp++;	//�������������ַ� 
	}
	return(st.data[st.top]);
}

//���ʽ��ֵ
//�û��������=��-��*��/����������Բ����()�ĺϷ��������ʽ������ñ��ʽ������


main(){
	char exp[] = "(56-20)/(4+2)";
	char postexp[MaxSize];
	trans(exp,postexp);
	cout<<"��׺���ʽ: "<<exp<<endl;
	cout<<"��׺���ʽ: "<<postexp<<endl;
	cout<<"���ʽ��ֵ: "<<compvalue(postexp)<<endl;	
}
