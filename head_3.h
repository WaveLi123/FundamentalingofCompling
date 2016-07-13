#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//函数声明
bool program();
bool block();
bool declaration();
bool statement();
bool condation();
void expression();
//1.程序->begin 分程序 .
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
//2.分程序->integer 简单变量{,简单变量};语句{;语句} end
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
//3.简单变量->标识符(ident)
bool declaration()
{
	if(sym==ident){//标识符
		sym=getsym();
		//printf("ok!!!!!!!!!!!!!!!!!!!\n");
	}
	else	error("Expected ident!\n");
	return true;
}
/*4.语句->标识符 := 简单表达式 
		| if 条件表达式 then (无条件)语句[else 语句]
		| for 标识符 := 简单表达式 step 简单表达式 until 简单表达式 do 语句 
		| begin (分程序 | 语句{;语句}end)
*/
bool statement()
{
	if(sym==ident){//标识符
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
		else ;//空语句
	}
	else if(sym==forsym){//'for'
		sym=getsym();
		if(sym==ident){//标识符
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
//5.条件表达式->简单表达式 (= | > | <) 简单表达式
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
//6.简单表达式->[+|-](标识符|常数|'('简单表达式')'){(+|-|*|/)(标识符|常数|'('简单表达式')')}
bool expression()
{
	while(sym!=semicolon&&sym!=thensym&&sym!=elsesym&&sym!=endsym&&sym!=stepsym&&sym!=untilsym&&sym!=dosym&&sym!=eql&&sym!=gtr&&sym!=lss){
		sym=getsym();
	}
	return true;
}
*/





















