#include<iostream>
using namespace std;

#define MaxOp 7
#define MaxSize 50 
//设定运算符优先级 
struct{
	char ch;	//运算符 
	int pri;	//优先级 
}lpri[] = {{'=',0},{'(',1},{'*',5},{'/',5},{'+',3},{'-',3},{')',6}},
rpri[] = {{'=',0},{'(',6},{'*',4},{'/',4},{'+',2},{'-',2},{')',1}};

//在左运算符优先的情况下，求优先级 
int leftpri(char op){
	int i;
	for(i=0; i<MaxOp; i++)
		if(lpri[i].ch == op) return lpri[i].pri;
}

//在右运算符优先的情况下，求优先级 
int rightpri(char op){
	int i;
	for(i=0; i<MaxOp;i++)
		if(rpri[i].ch == op) return rpri[i].pri;
}

//判断是否为运算符 
bool InOp(char ch){
	if(ch =='('||ch ==')'||ch =='+'||ch =='-'||ch =='*'||ch =='/')
		return true;
	else
		return false;
}

//op1和op2运算符优先级的比较结果 
int Precede(char op1, char op2){
	if(leftpri(op1) == rightpri(op2))
		return 0;
	else if(leftpri(op1) < rightpri(op2))
		return -1;
	else
		return 1;
}

//将算术表达式exp转换成后缀表达式postexp
void trans(char *exp, char postexp[]){
	struct{
		char data[MaxSize];	//存放运算符 
		int top;	//栈指针 
	}op;	//定义一个运算符栈
	
	int i = 0;	//i作为postexp的下标 
	op.top = -1;
	op.top++;
	op.data[op.top] = '=';
	while(*exp != '\0'){	//exp表达式未扫描完时循环 
//		为数字字符的情况 
		if(!InOp(*exp)){
//			判定为数字 
			while(*exp>='0' && *exp<='9'){
				postexp[i++] = *exp;
				exp++;
			}
			postexp[i++] = '#';	//用'#'标识一个数值串的结束 
		}else
			switch(Precede(op.data[op.top], *exp)){
//				栈顶运算符的优先级比被扫描到的运算符优先级低，将被扫描到的运算符其入栈 
				case -1:
					op.top++;
					op.data[op.top] = *exp;
					exp++;	//继续扫描其他字符
					break;
//				栈顶运算符的优先级较高，将栈顶的运算符接在后缀表达式后 
				case 1:
					postexp[i++] = op.data[op.top];
					op.top--;
					break;
//				只有括号满足这种情况
				case 0:
					op.top--;	//将'('退栈 
					exp++;	//继续扫描其他字符 
					break;
				
			}
	}
	while(op.data[op.top] != '='){	//此时exp扫描完毕，退栈到'='为止 
		postexp[i++] = op.data[op.top];
		op.top--;
	}
	postexp[i] = '\0';	//给postexp表达式添加结束标识 
}

//后缀表达式求解
//后缀表达式求解会相对中缀表达式求解简单许多，在扫描到运算符时，栈内肯定至少有两个待运算的数值
//	只需要将两个数值出栈后进行运算，再将计算结果入栈
//	最后栈内剩下唯一一个最终计算结果 
float compvalue(char *postexp){	//计算后缀表达式postexo的值 
	struct{
		float data[MaxSize];	//存放数值 
		int top;	//栈指针 
	}st;	//定义一个运算数栈
	
	float d,a,b,c;
	st.top = -1;
	while(*postexp != '\0'){	//postexp字符串未扫描完时循环 
		switch(*postexp){
			case '+':	//判定为+号 
				a = st.data[st.top];
				st.top--;	//退栈取数值a
				b = st.data[st.top];
				st.top--;	//退栈取数值b
				c = a+b;	//计算c
				st.top++;
				st.data[st.top] = c;	//将计算结果进栈
				break;
			case '-':	//判定为-号 
				a = st.data[st.top];
				st.top--;	//退栈取数值a
				b = st.data[st.top];
				st.top--;	//退栈取数值b
				c = b-a;	//计算c
				st.top++;
				st.data[st.top] = c;	//将计算结果进栈
				break;
			case '*':	//判定为*号 
				a = st.data[st.top];
				st.top--;	//退栈取数值a
				b = st.data[st.top];
				st.top--;	//退栈取数值b
				c = a*b;	//计算c
				st.top++;
				st.data[st.top] = c;	//将计算结果进栈
				break;
			case '/':	//判定为/号 
				a = st.data[st.top];
				st.top--;	//退栈取数值a
				b = st.data[st.top];
				st.top--;	//退栈取数值b
//				因为是除法运算，所以需要判断除数是否为0 
				if(a!=0){
					c = b/a;	//计算c，由于栈是先进后出的原则，所以是b/a而不是a/b 
					st.top++;
					st.data[st.top] = c;	//将计算结果进栈
				}else{
					cout<<endl<<"除零错误！！"<<endl;
					exit(0);	//异常退出 
				}
				break;
			default:	//处理数字字符 
				d = 0;	//将连续的数字字符转换成数值放到d中 
				while(*postexp >= '0' && *postexp <= '9'){
					d = 10*d + *postexp-'0';
					postexp++;
				}
				st.top++;
				st.data[st.top] = d;
				break;
		}
		postexp++;	//继续处理其他字符 
	}
	return(st.data[st.top]);
}

//表达式求值
//用户输入包含=、-、*、/、正整数、圆括号()的合法算术表达式，计算该表达式运算结果


main(){
	char exp[] = "(56-20)/(4+2)";
	char postexp[MaxSize];
	trans(exp,postexp);
	cout<<"中缀表达式: "<<exp<<endl;
	cout<<"后缀表达式: "<<postexp<<endl;
	cout<<"表达式的值: "<<compvalue(postexp)<<endl;	
}
