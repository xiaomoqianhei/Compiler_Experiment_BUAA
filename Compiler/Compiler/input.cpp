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
			error(2);
			fclose(IN);
		}
		ungetc(c_temp,IN);
		ll = 0;
		cc = 0;
		c_temp = 0;
		while (c_temp != '\n' && c_temp != '.')
		{
			c_temp = fgetc(IN);
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
	//sym = nextsym;
	while (ch == ' ')
	{
		getch();
	}
	if (ch >= 'a'&&ch <= 'z')
	{
		int i = 0;
		a = "";
		while ((ch >= 'a'&&ch <= 'z') || (ch >= '0'&&ch <= '9'))
		{
			if (i > al)
			{

			}
			a.append(1, ch);
			getch();
		}
		//	a.append(1,'\0');
		iden = a;
		i = 0;
		for (i = 0; i < rwnu; i++)
		{
			if (iden == reser_word[i])
			{
				break;
			}
		}
		if (i == rwnu)
		{
			sym = "ident";
		}
		else
		{
			sym = wsym[i];
		}
		printf("%s,%s\n",sym,iden);
	}
	else if (ch >= '0'&&ch <= '9')
	{
		int i = 0;
//		int point_flag = 0;
		number = ch-'0';
		while (ch >= '0'&&ch <= '9')
		{
//			if (ch == '.')
//				point_flag = 1;//����ʵ��֮������һ�����⣬�����βҲ��һ����ţ�����������Ѫ
			
			number = 10 * number + (ch - '0');
			getch();
		}
		//			if (point_flag==0)
		sym = "uinteger";
		printf("%s,%d\n",sym,number);
//		else
//			sym = "ureal";
	}
	else if (ch==':')
	{
		getch();
		if (ch == '=')
		{
			sym = "becomes";
			printf("%s,:=\n",sym);
			getch();
		}
		else
		{
			sym = "colon";//���Ҫע�������һ��,���ˣ����ÿ�
			printf("%s,=\n",sym);
		}
	}
	else if (ch == '<')
	{
		getch();
		if (ch == '=')
		{
			sym = "leq";
			printf("%s,<=\n",sym);
			getch();
		}
		else if (ch == '>')
		{
			sym = "neq";
			printf("%s,<>\n",sym);
			getch();
		}
		else
		{
			sym = "lss";
			printf("%s,<\n",sym);
		}
	}
	else if (ch == '>')
	{
		getch();
		if (ch == '=')
		{
			sym = "geq";
			printf("%s,>=\n", sym);
			getch();
		}
		else
		{
			sym = "gtr";
			printf("%s,>\n", sym);
		}
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
				sym = "charsym";
				iden = a;
				getch();
			}
			else
			{
				sym = "nul";
				iden = "";
				error(1);
			}
		}
		else
		{
			sym = "nul";
			iden = "";
			error(1);
		}
		
		printf("%s,%s\n", sym,iden);
	}
	else if (ch == '\"')
	{
		getch();
		int i = 0;
		a = "";
		while (ch != '\"')
		{
			if (ch==32||ch==33||(ch>=35&&ch<=126))//���Ӧ���ǺϷ��ַ����Բۣ��Ϸ��Ǹ�ʲô���壡
			{
				a.append(1,ch);
			}
			else
			{
				error(1);
			}
			getch();
		}
		a.append(1,'\0');
		iden = a;
		sym = "string";
		printf("%s,%s\n", sym, iden);
		getch();
	}
	else
	{
		sym= ssym[ch];
		printf("%s,%c\n", sym, ch);
		getch();
	}
}
