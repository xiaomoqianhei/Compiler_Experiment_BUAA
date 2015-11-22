#include "stdafx.h"
#include "globals.h"
void getsym();
string errors[] = { "�ñ�ʶ��δ����", //0
"��ʶ���ظ�����",   //1
"Ӧ�Ǳ�ʶ��",   //2
"Ӧ��')'",//3
"Ӧ��':',��˵������ʱ�����д�ð��", //4
"�Ƿ����ţ�������",  //5
"��ʽ��������,�β�˵��Ӧ���Ա�ʶ����var��ͷ", //6
"Ӧ��of",//7
"Ӧ��'('",//8
"���Ͷ�������Ա�ʶ����ͷ",//9
"Ӧ��'['",//10
"Ӧ��']'",//11
"ӦΪchar����integer",//12
"Ӧ��'=',':='ֻ�����ڸ�ֵ���",//13
"ȱ���������",//14
"��ֵ̫��,ӦС��2**32",//15
"�����βӦ��Ϊ.",//16
"�ַ��к��зǷ��ַ�",//17
"Ӧ�����ͱ�ʾ��",//18
"�ַ����ַ�����",//19
"ӦΪ'('",//20
"��������̴��������������ȷ",//21
"ӦΪ�жϷ�,>=,>,<>...",//22
"�ҾͲ����������ᱻ��������",//23
"ӦΪ��ֵ��':='",//24
"Ӧ����then",//25
"ӦΪwhile",//26
"ӦΪdownto����to",//27
"ӦΪdo",//28
"ӦΪend",//29
"��ѩ��,�ֳ�����ô��û�и������",//30
"������ֵӦ�����ַ���������",//31
"Ӧ��'='",//32
"ӦΪ';'",//33
"ӦΪ':'",//34
"�����±����",//35
"���ӿ�ʼ����ӦΪ��ʶ�������ֻ���������",//36
"ӦΪ����������begin",//37
"�������������",//38
"�������俪ʼ��",//39
"�������ִ���Ľ�����",//40
"���ӽ�������"//41
};
int ifin(string symbl, string * symbs)
{
	for (int i=0; symbs[0] != "";symbs++,i++)
		if (symbl == symbs[0])
			return i+1;
	return 0;
}

void error(int error_no)
{
	//print out 
	printf("%s\n",errors[error_no]);
	err++;
	printf("error occur!\n");
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
	while (id_table[i].name != id&&i!=0)
	{
		i = i - 1;
	}
	return i;
}
int check_ifexist(string id)
{
	int i = 0;
	id_table[0].name = id;
	i = tx;
	while (id_table[i].name != id&&i != 0)
	{
		i = i - 1;
		if (id_table[i].lev != level)
		{
			return 0;
		}
	}
	return i;
}