#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//=======================================================================================================//
#define	norw 10  //�ؼ��ֵĸ���
//�������ö�����ͣ�������Ϊsymbol������Ϊ�г�ȫ����ֵ�������ǵ��ʵ��ֱ����
enum  symbol{
	negtive,plus,minus,times,slash,lparen,rparen,layer,ident,number,becomes,
/*�ֱ�Ϊ:���ŵ��ֱ����,�Ӻŵ�,���ŵ�,�˺ŵ�,���ŵ�,�����ŵ�,�����ŵ�,��ʶ����,���ֵ�,��ֵ�ŵ�*/
	beginsym, endsym, forsym, stepsym, untilsym, dosym,integersym, ifsym, thensym, elsesym,
/*------------------------------------10���ؼ��ֵ��ֱ����------------------------------------*/
	eql,lss,gtr,comma,semicolon,period,nul,temp
/*�Ⱥŵ�,С�ںŵ�,���ںŵ�,���ŵ�,�ֺŵ�,��ŵ�,���󵥴ʵ�,���ʽ����ջջ�׷�,��ʱ������Ԫ*/ 
};
enum symbol sym;	//ö�ٱ���sym���ڽ����ɺ���getsym( )ʶ�𲢷��صĵ��ʵ��ֱ����,����sym=getsym( );
int  num;			//���泣�����������ֵ                              
char id[11];		//idΪװ11���ַ������飬�����ʶ���͹ؼ�������ֵ
char *word[norw]; //�ؼ��ֱ��������ֹؼ��ֺͱ�ʶ��(�������û�����ı�����������,x1)
enum symbol wsym[norw];  //�ؼ��ֵ��ֱ�������������ؼ��ֱ��йؼ���һһ��Ӧ

//=======================================================================================================//
//�ӳ���getsym( )�Ľṹ
enum symbol getsym(){
	int i=0;
//�˵�����ǰ�����еĿո��'',���з�'\n'�������'\t'
	while(ch==' '||ch=='\n'||ch=='\t'){	
		ch=getcha( ); 
	}
//�˷�֧�����ʶ��(�����ؼ���)
	if(ch>='a'&&ch<='z'){	
		/*�������ñ�ʶ���������ַ���װ��ȫ�̱���id�С����õ��ʲ���al������idβ��
			�����ո������ȳ���al,�򽫳������ֵ��ַ������������·�ʽ����(Ȼ�����ִ��)*/		
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
			//��ʾ������
			printf("***");
			for(i=0;i<cc;i++){
				printf(" ");
			}
			printf("Alarm: ident is too long!\n");
			//�ļ�����
			fprintf(foutput,"***");
			fprintf(foutput,"  ");
			fprintf(foutput,"Alarm: ident is too long!\n");
		}
		if(i<=10){
			for(int j=i;j<=10;j++){
				id[j]=' ';
			}
		}
		/*��idȥ��ؼ��ֱ�word�����鵽�ǵ�i���ؼ��֣��򷵻����ֱ����return( wsym[i]);
			���鲻�����򷵻ر�ʶ�����ֱ����return(ident)����ʱ��ʶ������ֵ����id�б���;*/
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
//�˷�֧��������������.(������Ϊch������Ϊ��ĸ)
	else if(ch>='0'&&ch<='9'){	//������������ַ���������ת��Ϊʮ���������������������ֵ����num�б��棻
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
			//��ʾ������
			printf("***");
			for(i=0;i<cc;i++){
				printf("Alarm: ident is too long!\n");
			}
			//�ļ�����
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
//�˷�֧����ֵ�ŵ���
	else if(ch==':'){
	/*�ж��Ƿ�Ϊ��ֵ�ţ�:=��,���Ǹ�ֵ�����ٳ�ǰ��һ���ַ���Ȼ��return (becomes);
       �����Ǹ�ֵ�ţ��򷵻ش��󵥴ʵ��ֱ����return (nul);*/
		ch=getcha();
		if(ch=='='){
			ch=getcha();//��ǰ��ȡһ���ַ�
			return(becomes);
		}
		else{
			ch=getcha();//��ǰ��ȡһ���ַ�
			return(nul);
		}
	}
//�˷�֧ʶ�𶺺ŵ���
	else if(ch==','){
		ch=getcha();//��ǰ��ȡһ���ַ�
		return(comma);
	}
//�˷�֧ʶ��ֺŵ���
	else if(ch==';'){
		ch=getcha();//��ǰ��ȡһ���ַ�
		return(semicolon);
	}
//�˷�֧ʶ���ŵ���
	else if(ch=='.'){
		ch=getcha();//��ǰ��ȡһ���ַ�
		return(period);
	}
//�˷�֧ʶ�������ŵ���
	else if(ch=='('){
		ch=getcha();//��ǰ��ȡһ���ַ�
		return(lparen);
	}
//�˷�֧ʶ�������ŵ���
	else if(ch==')'){
		ch=getcha();//��ǰ��ȡһ���ַ�
		return(rparen);
	}
//�˷�֧ʶ��Ӻŵ���
	else if(ch=='+'){
		ch=getcha();//��ǰ��ȡһ���ַ�
		return(plus);
	}
//�˷�֧ʶ����ŵ���
	else if(ch=='-'){
		ch=getcha();//��ǰ��ȡһ���ַ�
		return(minus);
	}
//�˷�֧ʶ��˺ŵ���
	else if(ch=='*'){
		ch=getcha();//��ǰ��ȡһ���ַ�
		return(times);
	}
//�˷�֧ʶ����ŵ���
	else if(ch=='/'){
		ch=getcha();//��ǰ��ȡһ���ַ�
		return(slash);
	}
//�˷�֧ʶ����ںŵ���
	else if(ch=='>'){
		ch=getcha();//��ǰ��ȡһ���ַ�
		return(gtr);
	}
//�˷�֧ʶ��Ⱥŵ���
	else if(ch=='='){
		ch=getcha();//��ǰ��ȡһ���ַ�
		return(eql);
	}
//�˷�֧ʶ��С�ںŵ���
	else if(ch=='<'){
		ch=getcha();//��ǰ��ȡһ���ַ�
		return(lss);
	}
	else{
		return(nul);//���ķ�֧�Ƿ��ش��󵥴ʵ��ֱ����,�����﷨�������򱨴�
	}
}   