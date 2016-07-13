#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define al 11              /*标识符的最大长度*/
typedef  char  alfa[al];   /*定义10个长的字符串的类型名alfa */
char ch;                   /*用于接受getcha()函数从line中读取的字符*/
char line[81];			   /*输入缓冲区,保存从源语言程序文件中读入的一行(无论长短)*/
int ll;					   /*line中最近输入的源语言程序文件(finput)当前行的实际长度*/
int cc;					   /*记录line中上一次被读取且被返回的字符在line中的位置下标*/
alfa fname;                /*10个长的字符串变量，用来保存文件名*/
FILE *finput, *foutput;    /*分别为源语言程序(输入)文件名,和输出文件名*/
//========================================================================
void error(char *string){ 
	int i ;
	printf("****");           /* 输出"****" ,标志本输出行是错误提示行*/
	for(i=1; i<cc; i++)       /*输出若干空格以便使符号‘！’对准出错位置*/
		printf(" ");
	printf("! %s",string);    /*输出出错位置指示符‘！’，和错误提示信息*/

	fprintf (foutput,"****"); /*将错误提示信息同步送到输出文件*/
	for(i=1; i<cc; i++)
		fprintf(foutput," ");
	fprintf (foutput ,"!%s",string);

	exit(0);  /*终止编译程序的运行，待用户修改错误后再重新启动本编译程序*/
} 

/*函数返回值为(从line中读取的)一个字符*/
char  getcha(){
	if(ll==0||ll==cc+1){
		//读文件前，先判断输入文件是否已空 
		if(feof(finput)){
			error("源语言程序文件不完整");
 			exit(0); //每当出现严重错误都退出编译程序的执行让用户修改
		}
		//将输入文件finput的下一行读入line中(在此过程中用ll计数该行实际长度)；
/*方法一*/	//该方法为什么不对？？？？？？？？？？
		/*ll=0;
		ch=getc(finput);
		while(!feof(finput) && ch!='\n')
		{
			line[ll]=ch;
			ll++;
			ch=getc(finput);
		}
		line[ll]='\0';
		ll=0;
		for(int i=0;(feof(finput)!=NULL)&&(line[i]!='\n');i++){
		//for(int i=0;line[i]!='\n';i++){
			line[i]=fgetc(finput);
			ll++;
		}	
		line[ll]='\0';*/
/*方法二*/
		fgets(line,81,finput);
		ll=strlen(line);
		//同时将此行原样抄送屏幕和输出文件foutput（注意：这一步必需在此时完成）；
		for (cc=0;cc<ll;cc++){
			putchar(line[cc]);
			fputc(line[cc],foutput);
		}
		cc=-1;
	}
	cc++;               /*返回line中的下一字符(注意：可能是换行符)， */
	return (line[cc]);  /*这是本函数的主要功能。                  */
}
