#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define al 11              /*��ʶ������󳤶�*/
typedef  char  alfa[al];   /*����10�������ַ�����������alfa */
char ch;                   /*���ڽ���getcha()������line�ж�ȡ���ַ�*/
char line[81];			   /*���뻺����,�����Դ���Գ����ļ��ж����һ��(���۳���)*/
int ll;					   /*line����������Դ���Գ����ļ�(finput)��ǰ�е�ʵ�ʳ���*/
int cc;					   /*��¼line����һ�α���ȡ�ұ����ص��ַ���line�е�λ���±�*/
alfa fname;                /*10�������ַ������������������ļ���*/
FILE *finput, *foutput;    /*�ֱ�ΪԴ���Գ���(����)�ļ���,������ļ���*/
//========================================================================
void error(char *string){ 
	int i ;
	printf("****");           /* ���"****" ,��־��������Ǵ�����ʾ��*/
	for(i=1; i<cc; i++)       /*������ɿո��Ա�ʹ���š�������׼����λ��*/
		printf(" ");
	printf("! %s",string);    /*�������λ��ָʾ�����������ʹ�����ʾ��Ϣ*/

	fprintf (foutput,"****"); /*��������ʾ��Ϣͬ���͵�����ļ�*/
	for(i=1; i<cc; i++)
		fprintf(foutput," ");
	fprintf (foutput ,"!%s",string);

	exit(0);  /*��ֹ�����������У����û��޸Ĵ�����������������������*/
} 

/*��������ֵΪ(��line�ж�ȡ��)һ���ַ�*/
char  getcha(){
	if(ll==0||ll==cc+1){
		//���ļ�ǰ�����ж������ļ��Ƿ��ѿ� 
		if(feof(finput)){
			error("Դ���Գ����ļ�������");
 			exit(0); //ÿ���������ش����˳���������ִ�����û��޸�
		}
		//�������ļ�finput����һ�ж���line��(�ڴ˹�������ll��������ʵ�ʳ���)��
/*����һ*/	//�÷���Ϊʲô���ԣ�������������������
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
/*������*/
		fgets(line,81,finput);
		ll=strlen(line);
		//ͬʱ������ԭ��������Ļ������ļ�foutput��ע�⣺��һ�������ڴ�ʱ��ɣ���
		for (cc=0;cc<ll;cc++){
			putchar(line[cc]);
			fputc(line[cc],foutput);
		}
		cc=-1;
	}
	cc++;               /*����line�е���һ�ַ�(ע�⣺�����ǻ��з�)�� */
	return (line[cc]);  /*���Ǳ���������Ҫ���ܡ�                  */
}
