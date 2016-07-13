#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//=======================================================================================================//
#define	norw 10  //关键字的个数
//下面设计枚举类型，类型名为symbol，内容为列出全部的值，它们是单词的种别编码
enum  symbol{
	negtive,plus,minus,times,slash,lparen,rparen,layer,ident,number,becomes,
/*分别为:负号的种别编码,加号的,减号的,乘号的,除号的,左括号的,右括号的,标识符的,数字的,赋值号的*/
	beginsym, endsym, forsym, stepsym, untilsym, dosym,integersym, ifsym, thensym, elsesym,
/*------------------------------------10个关键字的种别编码------------------------------------*/
	eql,lss,gtr,comma,semicolon,period,nul,temp
/*等号的,小于号的,大于号的,逗号的,分号的,句号的,错误单词的,表达式分析栈栈底符,临时工作单元*/ 
};
enum symbol sym;	//枚举变量sym用于接收由函数getsym( )识别并返回的单词的种别编码,例如sym=getsym( );
int  num;			//保存常数单词自身的值                              
char id[11];		//id为装11个字符的数组，保存标识符和关键字自身值
char *word[norw]; //关键字表，用于区分关键字和标识符(后者是用户定义的变量名，例如,x1)
enum symbol wsym[norw];  //关键字的种别编码表，各编码与关键字表中关键字一一对应

//=======================================================================================================//
//子程序getsym( )的结构
enum symbol getsym(){
	int i=0;
//滤掉单词前可能有的空格符'',换行符'\n'或跳格符'\t'
	while(ch==' '||ch=='\n'||ch=='\t'){	
		ch=getcha( ); 
	}
//此分支处理标识符(包括关键字)
	if(ch>='a'&&ch<='z'){	
		/*逐个读入该标识符的所有字符，装入全程变量id中。若该单词不足al长，则id尾部
			填满空格。若长度超过al,则将超长部分的字符读掉并按如下方式报警(然后继续执行)*/		
		i=0;
		while(ch!=' '&&ch!='\n'&&ch!='\t'&&ch!=','&&ch!=':'&&ch!=';'&&ch!='.'&&ch!='('&&ch!=')'&&ch!='+'&&ch!='-'&&ch!='*'&&ch!='/'&&ch!='>'&&ch!='='&&ch!='<'&&i<=10){
			id[i]=ch;
			i++;
			ch=getcha();
		}
		while(ch!=' '&&ch!='\n'&&ch!='\t'&&ch!=','&&ch!=':'&&ch!=';'&&ch!='.'&&ch!='('&&ch!=')'&&ch!='+'&&ch!='-'&&ch!='*'&&ch!='/'&&ch!='>'&&ch!='='&&ch!='<'){
			ch=getcha();
		}
		if(i>10){
			//显示屏操作
			printf("***");
			for(i=0;i<cc;i++){
				printf(" ");
			}
			printf("Alarm: ident is too long!\n");
			//文件操作
			fprintf(foutput,"***");
			fprintf(foutput,"  ");
			fprintf(foutput,"Alarm: ident is too long!\n");
		}
		if(i<=10){
			for(int j=i;j<=10;j++){
				id[j]=' ';
			}
		}
		/*用id去查关键字表word，若查到是第i个关键字，则返回其种别编码return( wsym[i]);
			若查不到，则返回标识符的种别编码return(ident)，此时标识符自身值仍在id中保存;*/
		for(i=0;i<=9;i++){
			for(int k=0;k<=10;k++){
				if(id[k]!=word[i][k]){
					break;
				}
			}
			if(k==11){
				break;
			}
		}
		if(i<10){
			return(wsym[i]);
		}
		else{
			return(ident);
		}
	}
//此分支处理整常数单词.(条件意为ch中内容为字母)
	else if(ch>='0'&&ch<='9'){	//逐个读入数字字符并将数字转换为十进制数，将整常数自身的值送入num中保存；
		num=0;
		i=0;
		while(ch>='0'&&ch<='9'&&i<=10){
			id[i]=ch;
			i++;
			ch=getcha();
		}
		if(ch>='a'&&ch<='z'){
				error("ident input is wrong!\n");
		}
		if(i>10){
			//显示屏操作
			printf("***");
			for(i=0;i<cc;i++){
				printf("Alarm: ident is too long!\n");
			}
			//文件操作
			fprintf(foutput,"***");
			fprintf(foutput,"  ");
			fprintf(foutput,"Alarm: ident is too long!\n");
		}
		if(i<=10){
			for(int m=i;m<=10;m++){
				id[m]=' ';
			}
		}
		for(int j=0;j<=i;j++){
			num=num+id[j]-'0';
			if(id[++j]!=' '){
				num=num*10;
				j--;
			}
		}
		return (number);
	}
//此分支处理赋值号单词
	else if(ch==':'){
	/*判断是否为赋值号（:=）,若是赋值号则再超前读一个字符，然后return (becomes);
       若不是赋值号，则返回错误单词的种别编码return (nul);*/
		ch=getcha();
		if(ch=='='){
			ch=getcha();//超前读取一个字符
			return(becomes);
		}
		else{
			ch=getcha();//超前读取一个字符
			return(nul);
		}
	}
//此分支识别逗号单词
	else if(ch==','){
		ch=getcha();//超前读取一个字符
		return(comma);
	}
//此分支识别分号单词
	else if(ch==';'){
		ch=getcha();//超前读取一个字符
		return(semicolon);
	}
//此分支识别句号单词
	else if(ch=='.'){
		ch=getcha();//超前读取一个字符
		return(period);
	}
//此分支识别左括号单词
	else if(ch=='('){
		ch=getcha();//超前读取一个字符
		return(lparen);
	}
//此分支识别右括号单词
	else if(ch==')'){
		ch=getcha();//超前读取一个字符
		return(rparen);
	}
//此分支识别加号单词
	else if(ch=='+'){
		ch=getcha();//超前读取一个字符
		return(plus);
	}
//此分支识别减号单词
	else if(ch=='-'){
		ch=getcha();//超前读取一个字符
		return(minus);
	}
//此分支识别乘号单词
	else if(ch=='*'){
		ch=getcha();//超前读取一个字符
		return(times);
	}
//此分支识别除号单词
	else if(ch=='/'){
		ch=getcha();//超前读取一个字符
		return(slash);
	}
//此分支识别大于号单词
	else if(ch=='>'){
		ch=getcha();//超前读取一个字符
		return(gtr);
	}
//此分支识别等号单词
	else if(ch=='='){
		ch=getcha();//超前读取一个字符
		return(eql);
	}
//此分支识别小于号单词
	else if(ch=='<'){
		ch=getcha();//超前读取一个字符
		return(lss);
	}
	else{
		return(nul);//最后的分支是返回错误单词的种别编码,留待语法分析程序报错
	}
}   