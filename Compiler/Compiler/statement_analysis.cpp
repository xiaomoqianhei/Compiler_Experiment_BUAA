#include "stdafx.h"
#include "globals.h"
void error(int error_no);
void test(string s1[], string s2[], int error_no);
bool ifin(string symbol, string symbols[]);
void getsym();
void expression();
void function_symbols(){
	
	if (sym == "(")
	{
		int paramnum;//����������
	}
}
void factor(){
	int i = 0;
//	test(facbegsys,fsys,24);
	while (ifin(sym,facbegsys))
	{
		if (sym == "ident")
		{
//			int i = position();�ʷ����֡�
			//��ʱ��Ҫ�ڱ��в��ң��Ƿ��Ǻ�����
			//if�Ǻ������������������뺯�������б��֡�
			getsym();
			
		}
		else if (sym == "unumber")
		{
			int num = number;
			if (num > amax)
			{
				error(11);
			}
			getsym();
		}
		else if (sym == "lparen")
		{
			getsym();
/*			int length_temp = sizeof(fsys) / sizeof(string);	
			string fsys_temp[sizeof(fsys)/sizeof(string)+1];
			memcpy(fsys_temp, fsys, length_temp);
			fsys_temp[length_temp] = "rparen";
*/			expression();
			if (sym == "rparen")
			{
				getsym();
			}
			else
			{
				error(22);
			}
		}
	}
}
void term()
{
	factor();
	while (sym == "times" || sym == "slash")
	{
		getsym();
		factor();
	}
}
void expression()
{
	if (sym=="plus"||sym=="minus")
	{
		getsym();
	}
	term();
	while (sym == "plus" || sym == "minus")
	{
		getsym();
		term();
	}
}
void condition()
{
	expression();
	getsym();
	string compare_symbols[] = { "eql", "neq", "lss", "leq", "gtr", "geq" };
	if (ifin(sym,compare_symbols))
	{
		getsym();
		expression();
	}
	else
		error(20);
}
void statement()
{
	if (sym == "ident")
	{
		//�ж��ǲ��Ǻ��������ǵĻ���Ҳûʲô���Բۺ������ֺ�ɵ�ư����ѵ��������͵������𣬿�����㸳ֵ��
		getsym();
		if (sym == "becomes")
			getsym();
		else
			error(13);
		expression();
	}
	else if (sym == "callsym")//����ķ����������ѽ�������������������ù��̲���Ҫcall��ѽ��������
	{
		getsym();
		if (sym == "ident")
		{

		}
	}
	else if (sym == "ifsym")
	{
		getsym();
		condition();
		if (sym == "thensym")
			getsym();
		else
			error(16);
		statement();
		if (sym == "else")
			statement();
	}
	else if (sym == "whilesym")
	{
		getsym();
		condition();
		if (sym == "dosym")
			getsym();
		else
			error(18);
		statement();
	}
	else if (sym == "beginsym")
	{
		getsym();
		statement();
		while (sym == "semicolon")
			statement();
		if (sym == "endsym")
			getsym();
		else
			error(17);
	}
	else if (sym == "readsym")
	{
		getsym();
		if (sym == "lparen")
		{
			do{
				getsym();
				if (sym == "ident")
				{

				}
				else
					error(4);
				getsym();
			} while (sym == "comma");
		}
		else
			error(40);
		if (sym != "rparen")
			error(22);
		getsym();
	}
	else if (sym == "writesym")
	{
		getsym();
		if (sym == "lparen")
		{
			do{
				getsym();
				expression();
			} while (sym == "comma");
			if (sym != "rparen")
				error(22);
			getsym();
		}
		else
			error(40);
	}
	else if (sym == "forsym")
	{
		getsym();
		if (sym == "ident")
		{
			getsym();	
		}
		else
			error(4);
		if (sym == "becomes")
		{
			getsym();
			expression();
		}
		else
			error(40);
		if (sym == "downto" || sym == "to")
		{
			getsym();
			expression();
		}
		else
			error(40);
	}
}