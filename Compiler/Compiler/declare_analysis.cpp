#include "stdafx.h"
#include "globals.h"
void error(int error_no);
void test(string *s1, string *s2, int error_no);
int ifin(string symbol, string *symbols);
void getsym();
void block(string func_name, int code);
int check_var_ifexist(string id);
int check_func_assign_ifOK(string id);
void generate(string opr, string src1, string src2, string des);
string generate_func_proc_label(string name, int code);
void enter(string type)//�����Ŀ��
{
	tx++;
	id_table[tx].name = iden;
	id_table[tx].obj = type;
}
void enter_const(string name_)//����ű��е�½�������ܼ򵥣�ͬʱ��ֵ���ȥ
{
	tx++;
	id_table[tx].name = name_;
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
//	printf("now in constdeclaration\n");
	string name;
	bool minus_symbol = false;
	do
	{
		if (sym == "ident")
		{
			name = iden;
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
					if (check_var_ifexist(iden) != 0)
					{
						error(1);
					}
					enter_const(name);
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
void enter_var(bool if_params)//�������Ļ�����Ϣ��¼�����ű��У���Ϊpascal�ķ������ƣ�var x,y,z��char;������Ҫ�ֽ����ֵ�½�����ű���¼��ʼλ�ã�Ȼ��ȥ������
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
	id_table[tx].addr_or_value = false;
}
void enter_var_type(string type, int tx_start){//�������������������͵ĺ���,tx_start�Ѿ���variable_declaration�м�¼��,������ڵ㿪ʼ����������͡�
	int index = tx_start + 1;
	while (index <= tx)
	{
		id_table[index].type = type;
		index++;
	}
}
void enter_array(string type,int size,int tx_start)//����������������������΢�е㸴�ӣ���Ϊ����table�ڵ��е�������һ��ָ��array_info��ָ�룬array_info�д洢��array�������Ϣ��
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
//	printf("now in variableblock\n");
	do{
		int curren_index = tx;//�ȼ�ס��ǰ���ű��λ��
		if (sym == "ident")
		{
			if (check_var_ifexist(iden) != 0)
			{
				error(1);
			}


			enter_var(false);
			getsym();
		}
		else
			error(2);
		while (sym == "comma")
		{
			getsym();
			if (sym == "ident")
			{
				if (check_var_ifexist(iden) != 0)
				{
					error(1);
				}


				enter_var(false);
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
			enter_var_type(sym, curren_index);
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
				enter_array(sym, size, curren_index);
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
void enter_function()//����function�Ļ�����Ϣ
{
	tx++;
	id_table[tx].name = iden;
	id_table[tx].lev = level;
	id_table[tx].obj = "function";
	id_table[tx].able = true;
	id_table[tx].param_list = NULL;
	id_table[tx].arrayinfo = NULL;
	id_table[tx].param_list = (struct params *)calloc(1, sizeof(PARAMS));
	id_table[tx].param_list->function_code = function_num++;
}
void enter_func_parameters()//���������������param_listָ����ָ�Ŀռ䣬
{
//	printf("now in func_parameter\n");
	id_table[tx].param_list->param_num=0;
	int current_tx = tx;
	int bottom_index = 0;
	int top_index = 0;
	bool addr_or_value;
	do{
		bottom_index = top_index;
		if (sym == "semicolon")
			getsym();
		if (sym == "varsym")
		{
			addr_or_value = true;//����ַ
			getsym();
		}
		else
			addr_or_value = false;//��ֵ
		if (sym == "ident")
		{
			if (check_var_ifexist(iden) != 0)
			{
				error(1);
			}
			id_table[current_tx].param_list->param_names[top_index++] = sym;
			id_table[current_tx].param_list->param_num++;

			enter_var(true);
			getsym();
		}
		else
			error(2);
		while (sym == "comma"&&id_table[current_tx].param_list->param_num<param_max)
		{
			getsym();
			if (sym == "ident")
			{
				if (check_var_ifexist(iden) != 0)
				{
					error(1);
				}

				id_table[current_tx].param_list->param_names[top_index++] = sym;//����������
				id_table[current_tx].param_list->param_num++;
				enter_var(true);
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
				id_table[current_tx].param_list->addr_or_value[i] = addr_or_value;
				id_table[current_tx + 1 + i].type=sym;
				id_table[current_tx + 1 + i].addr_or_value = addr_or_value;
			}
			getsym();//�˴�Ӧ�����ģ����������ȥ��
		}
		else
			error(12);
	} while (sym == "semicolon");
}

void function_declaration()
{//������������
//	printf("now in funcdeclaration\n");
	if (sym == "ident")
	{
		if (check_var_ifexist(iden) != 0)
		{
			error(1);
		}
		

		enter_function();
		getsym();
	}
	else
		error(2);//Ӧ��Ϊ��ʶ����
	int current_tx = tx;
	if (sym == "lparen")
	{
		getsym();
		enter_func_parameters();
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
		error(33);//ȱ�ٷֺš�
	else
		getsym();
	block(id_table[current_tx].name,id_table[current_tx].param_list->function_code);
	if (sym != "semicolon")
		error(33);//ȱʧ�ֺ�
	else
		getsym();
	generate("RETURN", "", "", "");
	string correctsymbols[] = {  "funcsym", "procsym", "beginsym", "" };
	string continuesymbols[] = { "" };
	test(correctsymbols, continuesymbols, 40);
}
void enter_procedure()
{
	tx++;
	id_table[tx].name = iden;
	id_table[tx].lev = level;
	id_table[tx].obj = "procedure";
	id_table[tx].type = "null";
	id_table[tx].able = true;
	id_table[tx].param_list = NULL;
	id_table[tx].arrayinfo = NULL;
	id_table[tx].param_list = (struct params *)calloc(1, sizeof(PARAMS));
	id_table[tx].param_list->function_code = function_num++;
}
void procedure_declaration()
{//��������̵���������û�з���ֵ����
//	printf("now in proceduredeclaration\n");
	if (sym == "ident")
	{
		if (check_var_ifexist(iden) != 0)
		{
			error(1);
		}
//		generate("LABEL", "", "", iden);

		enter_procedure();
		getsym();
	}
	else
		error(2);//Ӧ��Ϊ��ʶ����
	int current_tx = tx;
	if (sym == "lparen")
	{
		getsym();
		enter_func_parameters();
		if (sym == "rparen")
			getsym();
		else
			error(3);//ȱʧ�����š�
	}
	if (sym != "semicolon")
		error(33);//ȱ�ٷֺš�
	else
		getsym();
	block(id_table[current_tx].name, id_table[current_tx].param_list->function_code);
	if (sym != "semicolon")
		error(33);//ȱʧ�ֺ�
	else
		getsym();
	generate("RETURN","","","");
	string correctsymbols[] = { "funcsym", "procsym", "beginsym", "" };
	string continuesymbols[] = { "" };
	test(correctsymbols, continuesymbols, 40);
}