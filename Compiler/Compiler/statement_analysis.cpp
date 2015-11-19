#include "stdafx.h"
#include "globals.h"
void error(int error_no);
int position(string id);
void test(string s1[], string s2[], int error_no);
bool ifin(string symbol, string symbols[]);
void getsym();
void expression();
void multi_statement();
void function_params(int posi){//���Ҳ�Ƿ����Ŀ��,�ðɣ��ⲻ��
	
	if (sym == "lparen")
	{
		int nums = 0;
		do{
			getsym();
			expression();
			nums++;
		} while (sym == "comma");

		if (sym != "rparen")
		{
			error(8);
		}
		if (nums != id_table[posi].param_list->param_num)
		{
			error(9);
		}
		//int paramnum;//����������
	}
	
}
void array_ident()
{
	if (sym != "lbracket")
	{
		error(10);
	}
	getsym();
	expression();
	if (sym != "rbracket")
	{
		error(11);
	}
}
void factor(){
	printf("now in factor\n");
	int i = 0;
//	test(facbegsys,fsys,24);
	while (ifin(sym,facbegsys))
	{
		if (sym == "ident")
		{
			int posi = position(iden);
//			int i = position();�ʷ����֡�
			//��ʱ��Ҫ�ڱ��в��ң��Ƿ��Ǻ�����
			//if�Ǻ������������������뺯�������б��֡�
			if (posi == 0)
			{
				error(5);
			}
			else
			{
				if (id_table[posi].obj == "function")
				{
					getsym();
					function_params(posi);
				}
				else if (id_table[posi].type == "array")
				{
					getsym();//�Ƿ������Խ����м�飬������
					array_ident();
				}
			}
			getsym();
			
		}
		else if (sym == "uinteger")
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
	printf("now in term\n");
	factor();
	while (sym == "times" || sym == "slash")
	{
		getsym();
		factor();
	}
}

void expression()
{
/*	if (sym == "ident")
	{
		//	getsym();
		int pos = position(iden);
		if (pos == 0)
		{
			error(5);
		}
	}
	else
		error(99);*/
	printf("now in expression\n");
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
	printf("now in condition\n");
	expression();
	string compare_symbols[] = { "eql", "neq", "lss", "leq", "gtr", "geq","" };
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
	printf("now in statement\n");
	if (sym == "ident")
	{
		//�ж��ǲ��Ǻ��������ǵĻ���Ҳûʲô���Բۺ������ֺ�ɵ�ư����ѵ��������͵������𣬿�����㸳ֵ��
		int pos = position(iden);

		if (pos == 0)
		{
			error(5);
		}
		if (id_table[pos].obj == "procedure")
		{
			printf("now in call_statement\n");
			getsym();
			function_params(pos);
			if (sym!="semicolon")
			getsym();
		}
		else
		{
			if (id_table[pos].type == "array")
			{
				getsym();//�Ƿ������Խ����м�飬������
				array_ident();
			}
			else if (id_table[pos].type=="integersym"||id_table[pos].type=="charsym")
			{
			}
			else
			{
				error(6);//�˴���Ҫ����
			}
			printf("now in assign_statement\n");
			getsym();
			if (sym == "becomes")
				getsym();
			else
				error(13);
			expression();
		}
		
	}
	else if (sym == "ifsym")
	{
		printf("now in if_statement\n");
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
	else if (sym == "dosym")
	{
		printf("now in dowhilestatement\n");
		getsym();
		statement();
		if (sym == "whilesym")
			getsym();
		else
			error(18);
		condition();
	}
	else if (sym == "beginsym")
	{
		printf("now in begin_statement\n");
		multi_statement();
	}
	else if (sym == "readsym")
	{
		printf("now in readstatement\n");
		getsym();
		if (sym == "lparen")
		{
			do{
				getsym();
				if (sym == "ident")
				{
					int pos = position(iden);

					if (pos == 0)
					{
						error(5);
					}
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
		printf("now in writestatement\n");
		getsym();
		if (sym == "lparen")
		{
			getsym();
			if (sym == "string")
			{
				getsym();
				if (sym == "comma")
				{
					getsym();
					expression();
				}
			}
			else
			    expression();
			if (sym != "rparen")
				error(22);
			getsym();
		}
		else
			error(40);
	}
	else if (sym == "forsym")
	{
		printf("now in forstatement\n");
		getsym();
		if (sym == "ident")
		{
			getsym();
			int pos = position(iden);
			if (pos == 0)
			{
				error(5);
			}
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
		if (sym == "downtosym" || sym == "tosym")
		{
			getsym();
			expression();
		}
		else
			error(40);
		if (sym == "dosym")
		{
			getsym();
			statement();
		}
		else
		{
			error(13);
		}
	}
}
void multi_statement()
{
	getsym();
	statement();
	while (sym == "semicolon")
	{
		getsym();
		statement();
	}
	if (sym == "endsym")
		getsym();
	else
		error(17);

} 