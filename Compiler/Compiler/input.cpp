#include "stdafx.h"
#include "globals.h"

#include<stdio.h>
void error(int error_no);
void getch()
{
	if (cc == ll)
	{
		ln++;
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
		while (c_temp != '\n')
		{
			c_temp = fgetc(IN);
			if (c_temp!='\n')
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
	while (ch == ' '||ch=='\t')
	{
		getch();
	}
	if (ch >= 'a'&&ch <= 'z' || (ch >= 'A'&&ch <= 'Z'))
	{
		int i = 0;
		a = "";
		while ((ch >= 'a'&&ch <= 'z') || (ch >= '0'&&ch <= '9') || (ch >= 'A'&&ch <= 'Z'))
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
//		cout<<sym+","<<iden<<endl;
	}
	else if (ch >= '0'&&ch <= '9')
	{
		int i = 0;
//		int point_flag = 0;
		number = ch-'0';
		getch();
		while (ch >= '0'&&ch <= '9')
		{
//			if (ch == '.')
//				point_flag = 1;//����ʵ��֮������һ�����⣬�����βҲ��һ����ţ�����������Ѫ
			
			number = 10 * number + (ch - '0');
			getch();
		}
		//			if (point_flag==0)
		sym = "uinteger";
//		cout << sym + "," << number << endl;
//		else
//			sym = "ureal";
	}
	else if (ch==':')
	{
		getch();
		if (ch == '=')
		{
			sym = "becomes";
//			cout << sym + "," << ":=" << endl;
			getch();
		}
		else
		{
			sym = "colon";//���Ҫע�������һ��,���ˣ����ÿ�
//			cout << sym + "," << ":"<< endl;
		}
	}
	else if (ch == '<')
	{
		getch();
		if (ch == '=')
		{
			sym = "leq";
//			cout << sym + "," << "<=" << endl;
			getch();
		}
		else if (ch == '>')
		{
			sym = "neq";
//			cout << sym + "," << "<>" << endl;
			getch();
		}
		else
		{
			sym = "lss";
//			cout << sym + "," << "<" << endl;
		}
	}
	else if (ch == '>')
	{
		getch();
		if (ch == '=')
		{
			sym = "geq";
//			cout << sym + "," << ">=" << endl;
			getch();
		}
		else
		{
			sym = "gtr";
//			cout << sym + "," << ">" << endl;
		}
	}
	else if (ch=='\'')
	{
		getch();
		int i = 0;
		a = "";
		if ((ch >= 'a'&&ch <= 'z') || (ch >= '0'&&ch <= '9')||(ch>='A'&&ch<='Z'))
		{
			a.append(1, ch);
			getch();
			if (ch == '\'')
			{
				a.append(1, '\0');
				sym = "char";
				iden = a;
			}
			else
			{
				sym = "nul";
				iden = "";
				error(17);
				while (ch != '\'')
				{
					getch();
				}

			}
		}
		else
		{
			sym = "nul";
			iden = "";
			error(17);
			while (ch != '\'')
			{
				getch();
			}
		}
		getch();
//		cout << sym + "," << iden << endl;
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
				error(23);
			}
			getch();
		}
		a.append(1,'\0');
		iden = a;
		sym = "string";
//		cout << sym + "," << iden << endl;
		getch();
	}
	else
	{
		sym= ssym[ch];
		if (sym == "")
		{
			error(9);//illegal charactor
		}
		else
//		  cout << sym + "," << ch << endl;
		getch();
	}
}
