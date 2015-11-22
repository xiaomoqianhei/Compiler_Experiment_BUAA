#include "stdafx.h"
#include "globals.h"
void error(int error_no);
void test(string *s1, string *s2, int error_no);
bool ifin(string symbol, string *symbols);
void getsym();
void block();
int check_ifexist(string id);
void generate(string opr, string src1, string src2, string des);
void enter(string type)//�����Ŀ��
{
	tx++;
	id_table[tx].name = iden;
	id_table[tx].obj = type;


}
void enterconst()//����ű��е�½�������ܼ򵥣�ͬʱ��ֵ���ȥ
{

	tx++;
	id_table[tx].name = iden;
	if (sym == "uinteger")
	{
		id_table[tx].type = "integersym";
		id_table[tx].value = number;
	}
	else if (sym == "char")
	{
		id_table[tx].type = "charsym";
		id_table[tx].value = iden[0];
	}
	id_table[tx].adr = sp_addr-sp_piece_top;//�������ջ֡����λ��

	id_table[tx].lev = level;
	id_table[tx].obj = "const";
	id_table[tx].able = true;
	id_table[tx].param_list = NULL;
	id_table[tx].arrayinfo = NULL;
}
void const_declaration()//������������declaration����,���ǵݹ��½���һ���֣����������ʱ������const�ͽ����������
{
	printf("now in constdeclaration\n");
	bool minus_symbol = false;
	do
	{
		if (sym == "ident")
		{
			getsym();
			if (sym == "eql" || sym == "becomes")
			{
				if (sym == "becomes")
					error(13);
				getsym();
				if (sym == "plus" || sym == "minus")
				{
					getsym();
					if (sym == "minus")
						minus_symbol=true;
				}
				if (sym == "uinteger" || sym == "char")
				{
					if (minus_symbol)
						number = -number;
					if (check_ifexist(iden) != 0)
					{
						error(1);
					}



					enterconst();
					getsym();
				}
				else
					error(31);
			}
			else
				error(32);
		}
		else
			error(2);
		
	} while (sym == ",");
	if (sym != "semicolon")
		error(33);//ȱ�ٷֺ�
	else
		getsym();
	string correctsymbols[] = {"varsym","funcsym","procsym","beginsym",""};
	string continuesymbols[] = {""};
	test(correctsymbols,continuesymbols,40);
}
void entervar(bool if_params)//�������Ļ�����Ϣ��¼�����ű��У���Ϊpascal�ķ������ƣ�var x,y,z��char;������Ҫ�ֽ����ֵ�½�����ű���¼��ʼλ�ã�Ȼ��ȥ������
{
	tx++;
	id_table[tx].name = iden;
	if (if_params)
		id_table[tx].lev = level + 1;
	else
		id_table[tx].lev = level;
	id_table[tx].obj = "var";
	id_table[tx].able = true;
	id_table[tx].param_list = NULL;
	id_table[tx].arrayinfo = NULL;
}
void entervartype(string type, int tx_start){//�������������������͵ĺ���,tx_start�Ѿ���variable_declaration�м�¼��,������ڵ㿪ʼ����������͡�
	int index = tx_start + 1;
	while (index <= tx)
	{
		id_table[index].type = type;
		index++;
	}
}
void enterarray(string type,int size,int tx_start)//����������������������΢�е㸴�ӣ���Ϊ����table�ڵ��е�������һ��ָ��array_info��ָ�룬array_info�д洢��array�������Ϣ��
{
	int index = tx_start + 1;
	while (index <= tx)
	{
		id_table[index].type = "array";
		id_table[index].arrayinfo = (struct array_info *)calloc(1,sizeof(ARRAY_INFO));
		id_table[index].arrayinfo->size = size;
		id_table[index].arrayinfo->type = type;
		index++;
	}
}
void variable_declaration()
{
	printf("now in variableblock\n");
	do{
		int curren_index = tx;//�ȼ�ס��ǰ���ű��λ��
		if (sym == "ident")
		{
			if (check_ifexist(iden) != 0)
			{
				error(1);
			}


			entervar(false);
			getsym();
		}
		else
			error(2);
		while (sym == "comma")
		{
			getsym();
			if (sym == "ident")
			{
				if (check_ifexist(iden) != 0)
				{
					error(1);
				}


				entervar(false);
				getsym();

			}
			else
				error(2);
		}
		if (sym == "colon")
			getsym();
		else
			error(34);
		if (sym == "integersym" || sym == "charsym")
		{
			entervartype(sym, curren_index);
			getsym();//�˴�Ӧ�����ģ����������ȥ��
		}
		else if (sym == "arraysym")
		{
			int size = 0;
			getsym();
			if (sym == "lbracket")
				getsym();
			else
				error(10);//ȱ����������
			if (sym != "uinteger")
				error(35);//�����±����
			else
			{
				size = number;
				getsym();
			}
			if (sym != "rbracket")
				error(11);//ȱ���������š�
			else
				getsym();
			if (sym != "ofsym")
				error(7);//ȱ��of
			else
				getsym();
			if (sym == "charsym" || sym == "integersym")
			{
				enterarray(sym, size, curren_index);
				getsym();
			}
			else
				error(12);//Ӧ��Ϊ��������
		}
		else
			error(18);
		if (sym != "semicolon")
			error(33);
		else
			getsym();
	} while (sym == "ident");
	string correctsymbols[] = { "funcsym", "procsym", "beginsym", "" };
	string continuesymbols[] = { "" };
	test(correctsymbols, continuesymbols, 40);
}
void enterfunction()//����function�Ļ�����Ϣ
{
	tx++;
	id_table[tx].name = iden;
	id_table[tx].lev = level;
	id_table[tx].obj = "function";
	id_table[tx].able = true;
	id_table[tx].param_list = NULL;
	id_table[tx].arrayinfo = NULL;
}
void func_parameters()//���������������param_listָ����ָ�Ŀռ䣬
{
	printf("now in func_parameter\n");
	id_table[tx].param_list = (struct params *)calloc(1, sizeof(PARAMS));
	id_table[tx].param_list->param_num=0;
	int current_tx = tx;
	int bottom_index = 0;
	int top_index = 0;

	do{
		bottom_index = top_index;
		if (sym == "semicolon")
			getsym();
		if (sym == "varsym")
			getsym();
		if (sym == "ident")
		{
			if (check_ifexist(iden) != 0)
			{
				error(1);
			}
			id_table[current_tx].param_list->param_names[top_index++] = sym;
			id_table[current_tx].param_list->param_num++;
			entervar(true);
			getsym();
		}
		else
			error(2);
		while (sym == "comma"&&id_table[current_tx].param_list->param_num<param_max)
		{
			getsym();
			if (sym == "ident")
			{
				if (check_ifexist(iden) != 0)
				{
					error(1);
				}
				id_table[current_tx].param_list->param_names[top_index++] = sym;//����������
				id_table[current_tx].param_list->param_num++;
				entervar(true);
				getsym();
			}
		}
		if (sym == "colon")
			getsym();
		else
			error(34);
		if (sym == "integersym" || sym == "charsym")
		{
			for (int i = bottom_index; i < top_index; i++)
			{
				id_table[current_tx].param_list->types[i] = sym;//���������͡�
				id_table[current_tx + 1 + i].type=sym;
			}
			getsym();//�˴�Ӧ�����ģ����������ȥ��
		}
		else
			error(12);
	} while (sym == "semicolon");
}

void function_declaration()
{//������������
	printf("now in funcdeclaration\n");
	
	if (sym == "ident")
	{
		if (check_ifexist(iden) != 0)
		{
			error(1);
		}
		generate("LABEL","","",iden);

		enterfunction();
		getsym();
	}
	else
		error(2);//Ӧ��Ϊ��ʶ����
	int current_tx = tx;
	if (sym == "lparen")
	{
		getsym();
		func_parameters();
		if (sym == "rparen")
			getsym();
		else
			error(3);//ȱʧ�����š�
	}
	if (sym != "colon")
		error(34);//ȱʧð��
	else
		getsym();
	if (sym == "charsym" || sym == "integersym")
	{//�������һ�㣬�Ǿ���һ��Ҫ�Ѻ����ķ���ֵ���ȥ
		id_table[current_tx].type = sym;
		getsym();
	}
	else
		error(12);//��������ȱʧ
	if (sym != "semicolon")
		error(99);//ȱ�ٷֺš�
	else
		getsym();
	block();
	if (sym != "semicolon")
		error(33);//ȱʧ�ֺ�
	else
		getsym();
	string correctsymbols[] = {  "funcsym", "procsym", "beginsym", "" };
	string continuesymbols[] = { "" };
	test(correctsymbols, continuesymbols, 40);
}
void enterprocedure()
{
	tx++;
	id_table[tx].name = iden;
	id_table[tx].lev = level;
	id_table[tx].obj = "procedure";
	id_table[tx].type = "null";
	id_table[tx].able = true;
	id_table[tx].param_list = NULL;
	id_table[tx].arrayinfo = NULL;
}
void procedure_declaration()
{//��������̵���������û�з���ֵ����
	printf("now in proceduredeclaration\n");
	if (sym == "ident")
	{
		if (check_ifexist(iden) != 0)
		{
			error(1);
		}
		generate("LABEL", "", "", iden);

		enterprocedure();
		getsym();
	}
	else
		error(2);//Ӧ��Ϊ��ʶ����
	if (sym == "lparen")
	{
		getsym();
		func_parameters();
		if (sym == "rparen")
			getsym();
		else
			error(3);//ȱʧ�����š�
	}
	if (sym != "semicolon")
		error(33);//ȱ�ٷֺš�
	else
		getsym();
	block();
	if (sym != "semicolon")
		error(33);//ȱʧ�ֺ�
	else
		getsym();
	string correctsymbols[] = { "funcsym", "procsym", "beginsym", "" };
	string continuesymbols[] = { "" };
	test(correctsymbols, continuesymbols, 40);
}