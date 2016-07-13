#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct       /*定义分析栈的数据结构，每个进栈数据放在一个记录中,包含如下4个域(字段)*/
{	enum symbol sym ;/*此域保存进栈单词的种别编码或经归约后得到的非终结符E的种别编码temp*/
	alfa  name ;/*当sym域内容为变量标识符(ident)时，此域保存变量自身的值(即变量名).否则无用*/
	int  value ;/*当sym域内容为常量(number)时，此域保存常量(自身的)值.否则无用*/
	int  address ;/*当sym域为变量ident或临时工作变量temp，此域保存该变量被分配的内存地址,*/
}stack[50];  /*定义分析栈stack*/                                            /*否则无用.*/

char i;
int j,k;         /* k为栈顶位置指针;j 为距栈顶最近的终结符的位置指针 */
enum symbol previoussym;/*用于保存当前单词sym之前的一个单词，以便判断sym内是否为正负号*/
enum symbol originalsym;/*用于保存当前单词sym的原值，因需要将表达式的后继符号暂时换为#号*/
char M[8][10];

/*--------------------------------------------------第四次作业--------------------------------------------------*/
/* 每次调用expression( )之前，不需要超前读一个*/
void expression()
{
	k=1;
	stack[k].sym=layer;
	do{
		/*每次读下一单词,应先保存当前单词,以便观察两个相邻单词*/
		previoussym=sym;
		sym=getsym();
		/*集合中都是简单表达式的后继符号。暂时将后继符号变为 #(用layer代表)。当expression( )结束时再恢复原值。*/
		if(sym==thensym || sym==elsesym || sym==endsym || sym==stepsym || sym==untilsym || sym==dosym || sym==eql || sym==lss || sym==gtr || sym==semicolon){
			originalsym=sym;
			sym=layer;
		}
		/* 二个相继单词的这种组合表示sym中为正负号*/
		if((previoussym==eql || previoussym==gtr || previoussym==lss || previoussym==becomes || previoussym==lparen || previoussym==ifsym || previoussym==stepsym || previoussym==untilsym)&&(sym==plus || sym==minus)){
			/*正号无用,读掉*/
			if(sym==minus){
				 sym=negtive;
			}
			else{
				previoussym=sym;
				sym=getsym();
			}
		}
		/*  如果栈顶符号是（简单表达式中的）终结符，*/
		  /* 则,j 指向栈顶符号；*/  /*如上所述栈内的number和ident不认为是终结符了*/
		if(stack[k].sym==negtive || stack[k].sym==plus || stack[k].sym==minus || stack[k].sym==times || stack[k].sym==slash || stack[k].sym==lparen || stack[k].sym==rparen || stack[k].sym==layer){
			j=k;
		}
		else j=k-1;/* 否则，j 指向次栈顶符号。总之，j指向距栈顶最近的终结符*/
		/* 查M表：若条件成立则栈顶出现最左素短语，要归约*/
		while(M[stack[j].sym][sym]=='>'){		
			/*使用产生式E－＞－E,进行归约*/
			if(stack[j].sym==negtive){     
				k=k-2;   /*先从栈顶弹出对应于产生式右部“-E”的二个符号*/				
				/*将产生式左部E的种别编码temp压入栈*/
				k++; 
				stack[k].sym=temp;  
				j=k-1; /* 归约后,调整位置指针j的值使其总是指向距栈顶最近的终结符。*/
			}/*此分支的归约动作全部做完,以后还需插入一些语义(翻译)动作。*/
			/*   则，分别用 E－>E+E ，E－>E－E ，E－>E＊E ，E－>E／E 之一进行归约；*/
			if(stack[j].sym==plus || stack[j].sym==minus || stack[j].sym==times || stack[j].sym==slash){
				k=k-3;//先将产生式右部三个符号从栈顶弹出;
				j=k-1;/* 归约后,调整位置指针j的值使其总是指向距栈顶最近的终结符。*/
			}
			/*用E－>(E)归约.因该处语义动作简单，故一并完成*/
			if(stack[j].sym==rparen){
				k=k-3;	//先将产生式右部三个符号从栈顶弹出;
				k++;	/*设置左部E进栈位置,语义动作:右部E的全部域值抄送左部E的对应域*/
				stack[k].sym=stack[k+1].sym;
				for(int m=0;m<11;m++){
					stack[k].name[m]=stack[k+1].name[m];	
				}
				stack[k].value=stack[k+1].value;
				stack[k].address=stack[k+1].address;
				j=k-1; /* 归约后,调整位置指针j的值使其总是指向距栈顶最近的终结符。*/
			}
        }

		/*当前单词进栈*/
		if(M[stack[j].sym][sym]=='<' || M[stack[j].sym][sym]=='='){
			/*当前单词的种别编码进栈*/
			k=k+1;
			stack[k].sym=sym;               
			/* 常数单词的自身值也保存在栈中*/			
			if (sym==number){
				stack[k].value=num; 
			}
			/* 用户定义的变量的自身值保存在栈中*/
			if (sym==ident){
				for(int m=0;m<11;m++){
					stack[k].name[m]=id[m];  	
				}
			//	stack[k].address=id;/*此句可在下一阶段完成,id中的变量名已分配的内存地址;*/
			}
		}
		/* M[stack[j].sym][sym]必为表中错误代码1.2.3.4之一 ,所以调用error()报错*/
		else{
			i= M[stack[j].sym][sym];
			if (i=='1') error("非法负号!");
			if (i=='2') error("缺右括号!");
			if (i=='3') error("缺运算符!");
			if (i=='4') error("非法右括号!");
		}
	}while(sym!=layer);/* 若当前单词sym== #(用layer代表), 则 do- while循环结束 */

	if(!(stack[k-2].sym==layer&&stack[k-1].sym==temp&&stack[k].sym==layer)){
		error("简单表达式出错");/*分析成功的标志是分析栈内只剩三个符号：#E# 。否则,出现错误.*/
	}	
	sym=originalsym;  /* 将 #(用layer代表) 恢复为原值 */
}