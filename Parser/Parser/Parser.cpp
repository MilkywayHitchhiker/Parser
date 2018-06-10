#include"stdafx.h"
#include<string>
#include"Parser.h"

bool Parser::LoadFile (char *name)
{
	FILE *fp;
	fopen_s (&fp,name,"rb");
	if ( fp == NULL )
	{
		return false;
	}

	fseek (fp,0,SEEK_END);
	Size = ftell (fp);
	rewind (fp);

	pWBuffer = new WCHAR[Size];
	pBuffer = new char[Size];
	
	fread_s (pWBuffer,Size,Size,1,fp);

	fclose (fp);
	
	WideCharToMultiByte (CP_ACP, 0, pWBuffer, -1, pBuffer, Size, 0, 0);


	return true;

}

bool Parser::SetArea (char *name)
{
	char *Position = pBuffer;
	int Length;
	char Word[256];
	int Start = 0;
	int End = 0;
	int flag = 0;
	
	AreaStart = 0;
	AreaEnd = Size;


	while ( 1 )
	{
		// ':'�� �˻�
		if ( Position[0] == ':' )
		{
			Position++;
			Start++;
			Length = 0;
			// ':' �ڿ� ���� ���ڸ� �˻��ؼ� �Էµ� ���ڿ� �´��� Ȯ��.
			if ( GetNextWord (&Position, &Length) )
			{
				memset (Word,0,sizeof(Word));
				memcpy_s (Word,sizeof(Word),Position,Length);
				Start += Length;

				if ( 0 == strcmp (Word, name) )
				{
					// �´ٸ� �ٽ� �ݺ����� ���鼭 '{' �߰�ȣ �˻�.
					while ( 1 )
					{
						//�߰�ȣ ���°��� ã�Ҵٸ� �߰�ȣ �ݴ°��� �˻�.
						if ( Position[0] == '{' )
						{
							End = Start;
							while ( 1 )
							{
								//�߰�ȣ �ݴ°��� ã�Ҵٸ� �״�� �����ϰ� ����.
								if ( Position[0] == '}' )
								{
									AreaStart = Start;
									AreaEnd = End;
									return true;
								}
								
								if ( flag > Size )
								{
									return false;
								}

								
								Position++;
								End++;
								flag++;

								
							}
						}

						if ( flag > Size )
						{
							return false;
						}

						Position++;
						Start++;
						flag++;
					}
				}
			}
		}

		if ( flag > Size )
		{
			return false;
		}


		Position++;
		Start++;
		flag++;
	}


}


bool  Parser::SkipNoneCommand (char **p)
{
	char *Buffer = *p;
	int cnt;

	for(cnt = 0 ; cnt < (AreaEnd - AreaStart) ; cnt++ )
	{
		//�����̽�,����,�� ó��
		if ( Buffer[0] == ' ' || Buffer[0] == 0x0a || Buffer[0] == 0x0d || Buffer[0] == '\t' || Buffer[0] == ',' || Buffer[0] == 0x20 || Buffer[0] == 0x08 )
		{
			Buffer++;
		}

		//���� �ּ� ó��
		else if ( Buffer[0] == '/' && Buffer[1] == '/' )
		{
			for ( ; cnt < (AreaEnd - AreaStart); cnt++ )
			{
				if ( Buffer[0] == 0x0d && Buffer[1] == 0x0a )
				{
					Buffer++;
					Buffer++;
					break;
				}
				Buffer++;
			}
		}

		//�ٴ� �ּ� �ǳ� �ٱ�
		else if ( Buffer[0] == '/' && Buffer[1] == '*' )
		{
			for ( ; cnt < (AreaEnd - AreaStart); cnt++ )
			{
				if ( Buffer[0] == '*' && Buffer[1] == '/' )
				{
					Buffer++;
					Buffer++;
					break;
				}
				Buffer++;
			}
		}

		//���� ����,��,����,�ּ�ó���� �ϳ��� ���� ������ �����ͷ� �Ǵ�.
		else
		{
			*p = Buffer;
			return true;
		}
	}
	//������ ����� ��.
	return false;
}

bool  Parser::GetNextWord (char **Buffer, int *Length)
{
	char *p=*Buffer;
	int Len=0;
	int cnt;
	p = p + *Length;

	//������ ũ�⸦ �Ѿ���
	if ( !SkipNoneCommand (&p) )
	{
		return false;
	}
	*Buffer = p;

	for ( cnt = 0 ; cnt < (AreaEnd - AreaStart); cnt++ )
	{


		//�����̽�,����,�� ó��
		if ( p[0] == ' ' || p[0] == 0x0a || p[0] == 0x0d || p[0] == '\t' || p[0] == ',' || p[0] == 0x20 || p[0] == 0x08 || p[0] == ':' || p[0] == '{' || p[0] == '}')
		{
			*Length = Len;
			return true;
		}

		p++;
		Len++;


	}
	return false;
}

bool  Parser::GetValue (char *name, int *p)
{
	char *Position = &pBuffer[AreaStart];
	char chWord[256];
	int Length = 0;

	//���ѹݺ��� ���鼭 �ܾ�˻�.
	while ( GetNextWord(&Position,&Length) )
	{
		//Word���ۿ� ã�� �ܾ ����
		memset (chWord,0,256);
		memcpy_s (chWord,sizeof(chWord),Position,Length);

		//ã�� �ܾ �Է��� �ܾ�� ������ �˻�.
		if ( 0 == strcmp (chWord, name) )
		{
			//�´ٸ� �ڿ��� = �� ã�´�.
			if ( GetNextWord (&Position, &Length) )
			{
				memset (chWord, 0, 256);
				memcpy_s (chWord, sizeof (chWord), Position, Length);

				if ( 0 == strcmp (chWord, "=") )
				{
					if ( GetNextWord (&Position, &Length) )
					{
						memset (chWord, 0, 256);
						memcpy_s (chWord, sizeof (chWord), Position, Length);
						*p = atoi (chWord);
						return true;
					}

					return false;
				}
			}
			return false;
		}

	}
	return false;
}
bool  Parser::GetValue (char *name, char *p,int *MaxLength)
{
	char *Position = &pBuffer[AreaStart];
	char chWord[256];
	int Length = 0;

	//���ѹݺ��� ���鼭 �ܾ�˻�.
	while ( GetNextWord (&Position, &Length) )
	{
		//Word���ۿ� ã�� �ܾ ����
		memset (chWord, 0, 256);
		memcpy_s (chWord, sizeof (chWord), Position, Length);

		//ã�� �ܾ �Է��� �ܾ�� ������ �˻�.
		if ( 0 == strcmp (chWord, name) )
		{
			//�´ٸ� �ڿ��� = �� ã�´�.
			if ( GetNextWord (&Position, &Length) )
			{
				memset (chWord, 0, 256);
				memcpy_s (chWord, sizeof (chWord), Position, Length);

				if ( 0 == strcmp (chWord, "=") )
				{
					if ( GetNextWord (&Position, &Length) )
					{
						memset (chWord, 0, 256);
						memcpy_s (chWord, sizeof (chWord), Position, Length);

						//���ڷ� ���� �ִ� ���� ��ŭ memcpy�� Word�� �Ѱ� �ش�.
						memcpy_s (p,*MaxLength,chWord,Length);
						*MaxLength = Length;
						return true;
					}

					return false;
				}
			}
			return false;
		}

	}
	return false;
	return true;
}
bool  Parser::GetValue (char *name, float *p)
{

	return true;
}
bool  Parser::GetValue (char *name, double *p)
{
	char *Position = &pBuffer[AreaStart];
	char chWord[256];
	int Length = 0;

	//���ѹݺ��� ���鼭 �ܾ�˻�.
	while ( GetNextWord (&Position, &Length) )
	{
		//Word���ۿ� ã�� �ܾ ����
		memset (chWord, 0, 256);
		memcpy_s (chWord, sizeof (chWord), Position, Length);

		//ã�� �ܾ �Է��� �ܾ�� ������ �˻�.
		if ( 0 == strcmp (chWord, name) )
		{
			//�´ٸ� �ڿ��� = �� ã�´�.
			if ( GetNextWord (&Position, &Length) )
			{
				memset (chWord, 0, 256);
				memcpy_s (chWord, sizeof (chWord), Position, Length);

				if ( 0 == strcmp (chWord, "=") )
				{
					if ( GetNextWord (&Position, &Length) )
					{
						memset (chWord, 0, 256);
						memcpy_s (chWord, sizeof (chWord), Position, Length);
						*p = atof (chWord);
						return true;
					}

					return false;
				}
			}
			return false;
		}

	}
	return false;
}





