// Parser.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "Parser.h"

int main()
{
	int Value;
	double dou;
	char p[30];
	int MaxLength = 30;

	Parser parser;
	parser.LoadFile ("test.txt");
	parser.SetArea ("2");
	parser.GetValue ("Value",&Value);
	parser.GetValue ("dou", &dou);
	parser.GetValue ("char", p,&MaxLength);




    return 0;
}

