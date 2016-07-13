#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct       /*�������ջ�����ݽṹ��ÿ����ջ���ݷ���һ����¼��,��������4����(�ֶ�)*/
{	enum symbol sym ;/*���򱣴��ջ���ʵ��ֱ����򾭹�Լ��õ��ķ��ս��E���ֱ����temp*/
	alfa  name ;/*��sym������Ϊ������ʶ��(ident)ʱ�����򱣴���������ֵ(��������).��������*/
	int  value ;/*��sym������Ϊ����(number)ʱ�����򱣴泣��(�����)ֵ.��������*/
	int  address ;/*��sym��Ϊ����ident����ʱ��������temp�����򱣴�ñ�����������ڴ��ַ,*/
}stack[50];  /*�������ջstack*/                                            /*��������.*/

char i;
int j,k;         /* kΪջ��λ��ָ��;j Ϊ��ջ��������ս����λ��ָ�� */
enum symbol previoussym;/*���ڱ��浱ǰ����sym֮ǰ��һ�����ʣ��Ա��ж�sym���Ƿ�Ϊ������*/
enum symbol originalsym;/*���ڱ��浱ǰ����sym��ԭֵ������Ҫ�����ʽ�ĺ�̷�����ʱ��Ϊ#��*/
char M[8][10];

/*--------------------------------------------------���Ĵ���ҵ--------------------------------------------------*/
/* ÿ�ε���expression( )֮ǰ������Ҫ��ǰ��һ��*/
void expression()
{
	k=1;
	stack[k].sym=layer;
	do{
		/*ÿ�ζ���һ����,Ӧ�ȱ��浱ǰ����,�Ա�۲��������ڵ���*/
		previoussym=sym;
		sym=getsym();
		/*�����ж��Ǽ򵥱��ʽ�ĺ�̷��š���ʱ����̷��ű�Ϊ #(��layer����)����expression( )����ʱ�ٻָ�ԭֵ��*/
		if(sym==thensym || sym==elsesym || sym==endsym || sym==stepsym || sym==untilsym || sym==dosym || sym==eql || sym==lss || sym==gtr || sym==semicolon){
			originalsym=sym;
			sym=layer;
		}
		/* ������̵��ʵ�������ϱ�ʾsym��Ϊ������*/
		if((previoussym==eql || previoussym==gtr || previoussym==lss || previoussym==becomes || previoussym==lparen || previoussym==ifsym || previoussym==stepsym || previoussym==untilsym)&&(sym==plus || sym==minus)){
			/*��������,����*/
			if(sym==minus){
				 sym=negtive;
			}
			else{
				previoussym=sym;
				sym=getsym();
			}
		}
		/*  ���ջ�������ǣ��򵥱��ʽ�еģ��ս����*/
		  /* ��,j ָ��ջ�����ţ�*/  /*��������ջ�ڵ�number��ident����Ϊ���ս����*/
		if(stack[k].sym==negtive || stack[k].sym==plus || stack[k].sym==minus || stack[k].sym==times || stack[k].sym==slash || stack[k].sym==lparen || stack[k].sym==rparen || stack[k].sym==layer){
			j=k;
		}
		else j=k-1;/* ����j ָ���ջ�����š���֮��jָ���ջ��������ս��*/
		/* ��M��������������ջ�����������ض��Ҫ��Լ*/
		while(M[stack[j].sym][sym]=='>'){		
			/*ʹ�ò���ʽE������E,���й�Լ*/
			if(stack[j].sym==negtive){     
				k=k-2;   /*�ȴ�ջ��������Ӧ�ڲ���ʽ�Ҳ���-E���Ķ�������*/				
				/*������ʽ��E���ֱ����tempѹ��ջ*/
				k++; 
				stack[k].sym=temp;  
				j=k-1; /* ��Լ��,����λ��ָ��j��ֵʹ������ָ���ջ��������ս����*/
			}/*�˷�֧�Ĺ�Լ����ȫ������,�Ժ������һЩ����(����)������*/
			/*   �򣬷ֱ��� E��>E+E ��E��>E��E ��E��>E��E ��E��>E��E ֮һ���й�Լ��*/
			if(stack[j].sym==plus || stack[j].sym==minus || stack[j].sym==times || stack[j].sym==slash){
				k=k-3;//�Ƚ�����ʽ�Ҳ��������Ŵ�ջ������;
				j=k-1;/* ��Լ��,����λ��ָ��j��ֵʹ������ָ���ջ��������ս����*/
			}
			/*��E��>(E)��Լ.��ô����嶯���򵥣���һ�����*/
			if(stack[j].sym==rparen){
				k=k-3;	//�Ƚ�����ʽ�Ҳ��������Ŵ�ջ������;
				k++;	/*������E��ջλ��,���嶯��:�Ҳ�E��ȫ����ֵ������E�Ķ�Ӧ��*/
				stack[k].sym=stack[k+1].sym;
				for(int m=0;m<11;m++){
					stack[k].name[m]=stack[k+1].name[m];	
				}
				stack[k].value=stack[k+1].value;
				stack[k].address=stack[k+1].address;
				j=k-1; /* ��Լ��,����λ��ָ��j��ֵʹ������ָ���ջ��������ս����*/
			}
        }

		/*��ǰ���ʽ�ջ*/
		if(M[stack[j].sym][sym]=='<' || M[stack[j].sym][sym]=='='){
			/*��ǰ���ʵ��ֱ�����ջ*/
			k=k+1;
			stack[k].sym=sym;               
			/* �������ʵ�����ֵҲ������ջ��*/			
			if (sym==number){
				stack[k].value=num; 
			}
			/* �û�����ı���������ֵ������ջ��*/
			if (sym==ident){
				for(int m=0;m<11;m++){
					stack[k].name[m]=id[m];  	
				}
			//	stack[k].address=id;/*�˾������һ�׶����,id�еı������ѷ�����ڴ��ַ;*/
			}
		}
		/* M[stack[j].sym][sym]��Ϊ���д������1.2.3.4֮һ ,���Ե���error()����*/
		else{
			i= M[stack[j].sym][sym];
			if (i=='1') error("�Ƿ�����!");
			if (i=='2') error("ȱ������!");
			if (i=='3') error("ȱ�����!");
			if (i=='4') error("�Ƿ�������!");
		}
	}while(sym!=layer);/* ����ǰ����sym== #(��layer����), �� do- whileѭ������ */

	if(!(stack[k-2].sym==layer&&stack[k-1].sym==temp&&stack[k].sym==layer)){
		error("�򵥱��ʽ����");/*�����ɹ��ı�־�Ƿ���ջ��ֻʣ�������ţ�#E# ������,���ִ���.*/
	}	
	sym=originalsym;  /* �� #(��layer����) �ָ�Ϊԭֵ */
}