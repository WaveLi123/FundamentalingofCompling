#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//��������
bool program();
bool block();
bool declaration();
bool statement();
bool condation();
void expression();
//1.����->begin �ֳ��� .
bool program()
{
	if(sym==beginsym){
		sym=getsym();
	}
	else	error("Expected 'begin'!\n");
	block();
	if(sym==period){//'.'
		printf("ok!!!!!!\n");
	}
	else error("Expected '.'!\n");
	return true;
}
//2.�ֳ���->integer �򵥱���{,�򵥱���};���{;���} end
bool block()
{
	if(sym==integersym){
		sym=getsym();
	}
	else	error("Expected 'integer'!\n");
	declaration();
	while(sym==comma){//','
		sym=getsym();
		declaration();
	}
	//sym=getsym(); to be continued......
	if(sym==semicolon){//';'
		sym=getsym();
	}
	else	error("Expected 'semicolon'!\n");
	statement();
	while(sym==semicolon){//';'
		sym=getsym();
		statement();
	}
	if(sym==endsym){
		sym=getsym();
	}
	else	error("Expected 'end'!\n");
	return true;
}
//3.�򵥱���->��ʶ��(ident)
bool declaration()
{
	if(sym==ident){//��ʶ��
		sym=getsym();
		//printf("ok!!!!!!!!!!!!!!!!!!!\n");
	}
	else	error("Expected ident!\n");
	return true;
}
/*4.���->��ʶ�� := �򵥱��ʽ 
		| if �������ʽ then (������)���[else ���]
		| for ��ʶ�� := �򵥱��ʽ step �򵥱��ʽ until �򵥱��ʽ do ��� 
		| begin (�ֳ��� | ���{;���}end)
*/
bool statement()
{
	if(sym==ident){//��ʶ��
		sym=getsym();

		if(sym==becomes){//':='
			sym=getsym();
		}
		else	error("Expected ':='!\n");
		expression();
	}
	else if(sym==ifsym){//'if'
		sym=getsym();
		condation();
		if(sym==thensym){//'then'
			sym=getsym();
		}
		else	error("Expected 'then'!\n");
		if(sym==ifsym||sym==forsym){//'if'or'for'
			error("Unexpected 'if' or 'for'!\n");
		}
		else	statement();

		if(sym==elsesym){//'else'
			statement();
		}
		else ;//�����
	}
	else if(sym==forsym){//'for'
		sym=getsym();
		if(sym==ident){//��ʶ��
			sym=getsym();
		}
		else	error("Expected ident!\n");
		if(sym==becomes){//':='
			sym=getsym();
		}
		else	error("Expected ':='!\n");
		expression();
		if(sym==stepsym){//'step'
			sym=getsym();
		}
		else	error("Expected 'step'!\n");
		expression();
		if(sym==untilsym){//'until'
			sym=getsym();
		}
		else	error("Expected 'until'!\n");
		expression();
		if(sym==dosym){//'do'
			sym=getsym();
		}
		else	error("Expected 'do'!\n");
		statement();
	}
	else if(sym=beginsym){//'begin'
		sym=getsym();
		if(sym==integersym){//'integer'
			block();
		}
		else if(sym==ident||sym==ifsym||sym==forsym||sym==beginsym){//'if' or 'for' or 'begin' or ident
			statement();
			while(sym==semicolon){//';'
				sym=getsym();
				statement();
			}
			if(sym==endsym){//'end'
				sym=getsym();
			}
			else	error("Expected 'end'!\n");
		}
		else	error("Expected block() or statement()!\n");
	}
	else error("Expected ident or 'if' or 'for' or 'begin'!\n");

	return true;	
}
//5.�������ʽ->�򵥱��ʽ (= | > | <) �򵥱��ʽ
bool condation()
{
	expression();
	if(sym==eql){//'='
		sym=getsym();
	}
	else if(sym==gtr){//'>'
		sym=getsym();
	}
	else if(sym==lss){//'<'
		sym=getsym();
	}
	else	error("Expected '=' or '>' or '<'!\n");
	expression();
	return true;
}
/*
//6.�򵥱��ʽ->[+|-](��ʶ��|����|'('�򵥱��ʽ')'){(+|-|*|/)(��ʶ��|����|'('�򵥱��ʽ')')}
bool expression()
{
	while(sym!=semicolon&&sym!=thensym&&sym!=elsesym&&sym!=endsym&&sym!=stepsym&&sym!=untilsym&&sym!=dosym&&sym!=eql&&sym!=gtr&&sym!=lss){
		sym=getsym();
	}
	return true;
}
*/





















