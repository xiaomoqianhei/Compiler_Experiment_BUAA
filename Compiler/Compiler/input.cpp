#include "stdafx.h"
#include "globals.h"

#include<stdio.h>
void error(int error_no);
void getch()
{
	if (cc == ll)
	{
		char c_temp = 0;
		if ((c_temp=fgetc(IN))==EOF)
		{
			fclose(IN);
		}
		ungetc(c_temp,IN);
		ll = 0;
		cc = 0;
		c_temp = 0;
		while (c_temp != '\n' && c_temp != '.')
		{
			line[ll++] = c_temp;
		}
		line[ll++] = ' ';//����һ�����壬���ڻ���
	}
	ch = line[cc];
	cc++;
}
void ugetch()
{
	cc--;
	ch = line[cc];
	cc++;
}
void getsym()
{
	//��Ҫ��ǰ�������Ҿ����������ǰԤ֪��һ����ʲô��������
	sym = nextsym;
	while (ch == ' ')
	{
		getch();
	}
	if (ch >= 'a'&&ch <= 'z')
	{
		int i = 0;
		a = "";
		while ((ch >= 'a'&&ch <= 'z')||(ch>='0'&&ch<='9'))
		{
			if (i > al)
			{

			}
			a.append(1,ch);
			getch();
		}
		a.append(1,'\0');
		iden = a;
		i = 0;
		for (i = 0; i < rwnu; i++)
		{
			if (iden == reser_word[i])
			{
				break;
			}
		}
		if (i != rwnu)
		{
			nextsym = "ident";
		}
		else
		{
			nextsym = wsym[i];
		}
	}
	else if (ch == '-' || ch == '+')
	{
		char c_temp = ch;
		number = 0;
		getch();
		if (ch >= '0'&&ch <= '9')
		{
			int i = 0;
//			int point_flag = 0;
			while (ch >= '0'&&ch <= '9')
			{
//				if (ch == '.')
//					point_flag = 1;
				number = 10 * number + (ch - '0');
				getch();
			}
//			if (point_flag==0)
			nextsym = "integer";
			if (c_temp == '-')
			{
				number = -number;
			}
//			else
//				sym = "real";
		}
		else
		{
			nextsym = ssym[c_temp];
		}
	}
	else if (ch >= '0'&&ch <= '9')
	{
		int i = 0;
//		int point_flag = 0;
		number = 0;
		while (ch >= '0'&&ch <= '9')
		{
//			if (ch == '.')
//				point_flag = 1;//����ʵ��֮������һ�����⣬�����βҲ��һ����ţ�����������Ѫ
			
			number = 10 * number + (ch - '0');
			getch();
		}
		//			if (point_flag==0)
		nextsym = "uinteger";
//		else
//			sym = "ureal";
	}
	else if (ch==':')
	{
		getch();
		if (ch == '=')
		{
			nextsym = "becomes";
			getch();
		}
		else
			nextsym = "colon";//���Ҫע�������һ��,���ˣ����ÿ���
	}
	else if (ch == '<')
	{
		getch();
		if (ch == '=')
		{
			nextsym = "leq";
			getch();
		}
		else if (ch == '>')
		{
			nextsym = "neq";
			getch();
		}
		else
			nextsym = "lss";
	}
	else if (ch == '>')
	{
		getch();
		if (ch == '=')
		{
			nextsym = "geq";
			getch();
		}
		else
			nextsym = "gtr";
	}
	else if (ch=='\'')
	{
		getch();
		int i = 0;
		a = "";
		if ((ch >= 'a'&&ch <= 'z') || (ch >= '0'&&ch <= '9'))
		{
			a.append(1, ch);
			getch();
			if (ch == '\'')
			{
				a.append(1, '\0');
				nextsym = "char";
				getch();
			}
			else
			{
				nextsym = "nul";
				error(1);
			}
		}
		else
		{
			nextsym = "nul";
			error(1);
		}
	}
	else if (ch == '\"')
	{
		getch();
		int i = 0;
		a = "";
		while (ch != '\"')
		{
			if (ch)//���Ӧ���ǺϷ��ַ����Բۣ��Ϸ��Ǹ�ʲô���壡
			{
				a.append(1,ch);
			}
			else
			{
				error(1);
				break;
			}
		}
		a.append(1,'\0');
		if (ch == '\"')
		{
			nextsym = "string";
			getch();
		}
		else
		{
			error(1);
			nextsym = "nul";
		}
	}
	else
	{
		nextsym= ssym[ch];
		getch();
	}
	if (sym == "")
		getsym();
}
