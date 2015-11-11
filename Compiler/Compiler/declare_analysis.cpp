#include "stdafx.h"
#include "globals.h"
void error(int error_no);
void test(string s1[], string s2[], int error_no);
bool ifin(string symbol, string symbols[]);
void getsym();
void block();
void enter(string type)
{
	tx++;
	id_table[tx].name = iden;
	id_table[tx].kind = type;

}
void const_declaration()
{
	printf("now in constdeclaration\n");
	do
	{
		if (sym == "ident")
		{
			getsym();
			if (sym == "eql" || sym == "becomes")
			{
				if (sym == "becomes")
					error(1);
				getsym();
				if (sym == "plus" || sym == "minus")
				{
					getsym();
					if (sym == "minus")
						number = -number;
				}
				if (sym == "uinteger" || sym == "char")
				{
					enter("constant");
					getsym();
				}
				else
					error(2);
			}
			else
				error(3);
		}
		else
			error(4);
	} while (sym == ",");
	if (sym != "semicolon")
		error(99);//ȱ�ٷֺ�
	else
		getsym();
}
void variable_declaration()
{
	printf("now in variableblock\n");
	do{
		if (sym == "ident")
		{
			getsym();
		}
		else
			error(99);
		while (sym == "comma")
		{
			getsym();
			if (sym == "ident")
			{
				getsym();
			}
		}
		if (sym == "colon")
			getsym();
		else
			error(99);
		if (sym == "integer" || sym == "charsym")
			getsym();//�˴�Ӧ�����ģ����������ȥ��
		else if (sym == "arraysym")
		{
			getsym();
			if (sym == "lbracket")
				getsym();
			else
				error(99);//ȱ����������
			if (sym != "uinteger")
				error(99);//�����±����
			else
				getsym();
			if (sym != "rbracket")
				error(99);//ȱ���������š�
			else
				getsym();
			if (sym != "of")
				error(99);//ȱ��of
			else
				getsym();
			if (sym == "charsym" || sym == "uinteger")
			{
				getsym();
			}
			else
				error(99);//Ӧ��Ϊ��������
		}
		if (sym != "semicolon")
			error(99);
		else
			getsym();
	} while (sym == "ident");
}
void func_parameters()
{
	printf("now in func_parameter\n");
	do{
		if (sym == "semicolon")
			getsym();
		if (sym == "varsym")
			getsym();
		if (sym == "ident")
		{
			getsym();
		}
		else
			error(99);
		while (sym == "comma")
		{
			getsym();
			if (sym == "ident")
			{
				getsym();
			}
		}
		if (sym == "colon")
			getsym();
		else
			error(99);
		if (sym == "integer" || sym == "charsym")
			getsym();//�˴�Ӧ�����ģ����������ȥ��
		else
			error(99);
	} while (sym == "semicolon");
}
void function_declaration()
{
	printf("now in funcdeclaration\n");
	if (sym != "ident")
		getsym();
	else
		error(99);//Ӧ��Ϊ��ʶ����
	if (sym == "lparen")
	{
		getsym();
		func_parameters();
		if (sym == "rparen")
			getsym();
		else
			error(99);//ȱʧ�����š�
	}
	if (sym != "colon")
		error(99);//ȱʧð��
	else
		getsym();
	if (sym == "charsym" || sym == "intsym")
	{
		getsym();
	}
	else
		error(99);//��������ȱʧ
	if (sym != "semicolon")
		error(99);//ȱ�ٷֺš�
	else
		getsym();
	block();
	if (sym != "semicolon")
		error(99);//ȱʧ�ֺ�
	else
		getsym();
}
void procedure_declaration()
{//��������̵���������
	printf("now in proceduredeclaration\n");
	if (sym == "ident")
		getsym();
	else
		error(99);//Ӧ��Ϊ��ʶ����
	if (sym == "lparen")
	{
		getsym();
		func_parameters();
		if (sym == "rparen")
			getsym();
		else
			error(99);//ȱʧ�����š�
	}
	if (sym != "semicolon")
		error(99);//ȱ�ٷֺš�
	else
		getsym();
	block();
	if (sym != "semicolon")
		error(99);//ȱʧ�ֺ�
	else
		getsym();
}