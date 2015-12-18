#include "stdafx.h"
#include "globals.h"
void getsym();
string errors[] = { "�ñ�ʶ��δ����", //0
"��ʶ���ظ�����",   //1
"Ӧ�Ǳ�ʶ��",   //2
"Ӧ�� )",//3
"Ӧ�� : ,��˵������ʱ�����д�ð��", //4
"�Ƿ����ţ�������",  //5
"��ʽ��������,�β�˵��Ӧ���Ա�ʶ����var��ͷ", //6
"Ӧ��of",//7
"Ӧ��( ",//8
"���Ͷ�������Ա�ʶ����ͷ",//9
"Ӧ�� [ ",//10
"Ӧ�� ] ",//11
"ӦΪchar����integer",//12
"Ӧ�� = , := ֻ�����ڸ�ֵ���",//13
"ȱ���������",//14
"��ֵ̫��,ӦС��2**32",//15
"�����βӦ��Ϊ.",//16
"�ַ��к��зǷ��ַ�",//17
"Ӧ�����ͱ�ʾ��",//18
"�ַ����ַ�����",//19
"ӦΪ ( ",//20
"��������̴��������������ȷ",//21
"ӦΪ�жϷ�,>=,>,<>...",//22
"�ҾͲ����������ᱻ��������",//23
"ӦΪ��ֵ�� := ",//24
"Ӧ����then",//25
"ӦΪwhile",//26
"ӦΪdownto����to",//27
"ӦΪdo",//28
"ӦΪend",//29
"��ѩ��,�ֳ�����ô��û�и������",//30
"������ֵӦ�����ַ���������",//31
"Ӧ�� =",//32
"ӦΪ ;",//33
"ӦΪ : ",//34
"�����±����",//35
"���ӿ�ʼ����ӦΪ��ʶ�������ֻ���������",//36
"ӦΪ����������begin",//37
"�������������",//38
"�������俪ʼ��",//39
"�������ִ���Ľ�����",//40
"���ӽ�������",//41
"����ƥ���������",//42
"������ֵ����",//43
"ʵ�δ������",//44
"���������Ը�ֵ",//45
"����ַ�����Դ�����"//46
};
int ifin(string symbl, string * symbs)
{
	for (int i=0; symbs[i] != "";i++)
		if (symbl == symbs[i])
			return i+1;
	return 0;
}

void error(int error_no)
{
	//print out 
	printf("����:��%d��%d�ַ�����%s\n",ln,cc,errors[error_no].c_str());
	err++;
//	printf("error occur!\n");
}

void test(string *s1, string *s2, int error_no)
{
	if (!ifin(sym, s1))
	{
		error(error_no);
		while (!(ifin(sym, s1) || ifin(sym, s2)))
			getsym();
	}
}

int position(string id){
	int i = 0;
	id_table[0].name = id;
	i = tx;
	while (i!=0)
	{
		if (id_table[i].name == id&&id_table[i].able)
			break;
		i = i - 1;
	}
	return i;
}
int check_var_ifexist(string id,int level_temp)
{
	int i = 0;
	id_table[0].name = id;
	i = tx;
	while (id_table[i].name != id&&i != 0)
	{
	
		if (id_table[i].lev != level_temp)
		{
			if (id_table[i].name == id)
				return i;
			return 0;
		}
		i = i - 1;
	}
	return i;
}
int check_func_assign_ifOK(string id)
{
	int i = 0;
	id_table[0].name = id;
	i = tx;
	while (id_table[i].lev != (level-1)&&i!=0)
	{
		i--;
	}
	if (id_table[i].name == id&&i!=0)
		return 1;
	else
		return 0;
}
int find_func_proc_position(string label)
{
	string name;
	string code_temp;
	int code;
	int i;
	for (i = 0; i < label.size(); i++)
	{
		char c = label.at(i);
		if (c != '_')
		{
			name.append(1,c);
		}
		else
			break;
	}
	for (i++; i < label.size(); i++)
	{
		code_temp.append(1, label.at(i));
	}
	code = atoi(code_temp.c_str());
	for (int i = 1; i <= tx; i++)
	{
		if ((id_table[i].obj == "function" || id_table[i].obj == "procedure") &&id_table[i].param_list->function_code == code)
		{
			return i;
		}
	}
	return 0;
}
int get_the_variable(int posi,string name)
{
	//һ�������������ұ������ܱ��İ취��
	for (int j = posi,level=id_table[posi].lev+1; id_table[j].obj == "procedure" || id_table[j].obj == "function";)
	{
		for (int i = j+1; i <= tx && (id_table[i].obj == "var" || id_table[i].obj == "const"); i++)
		{
			if (id_table[i].name == name)
			{
				return i;
			}
		}
		level--;
		while (id_table[j].lev >= level&&j>0&&level>0)
			j--;
	}
}
string int_to_string(int num)
{
	stringstream ss;
	ss << num;
	return ss.str();
}