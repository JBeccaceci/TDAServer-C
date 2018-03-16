#include "General.h"

////////////////////////////////////////////////////////////
// Characters valid
////////////////////////////////////////////////////////////
int LegalCharacter(int charID, int Numbers, int Special)
{
	int Result = 0;

	//	Check is numbers
	if (Numbers)
	{
		if (charID >= 48)
		{
			if (charID <= 57)
			{
				Result = 1;
			}
		}
	}

	//	A to Z
	if (charID >= 65)
	{
		if (charID <= 90)
		{
			Result = 1;
		}
	}

	//	a to z
	if (charID >= 97)
	{
		if (charID <= 128)
		{
			Result = 1;
		}
	}

	//	Specials characters
	if (Special)
	{
		if (charID >= 128)
		{
			if (charID <= 168)
			{
				Result = 1;
			}
		}
	}

	return Result;
}

////////////////////////////////////////////////////////////
// String is valid
////////////////////////////////////////////////////////////
int LegalString(char * Str, int Numbers, int Special)
{
	int Result = 1;
	int Lenght = strlen(Str);

	//	Loop chars
	for (int i = 0; i < Lenght; i++)
	{
		if (LegalCharacter((int)Str[i], Numbers, Special) != 1)
		{
			Result = 0;
			break;
		}
	}

	return Result;
}

////////////////////////////////////////////////////////////
// Separe string by char separator
////////////////////////////////////////////////////////////
char * General_Field_Read(int n, char * string, char * charSeparator)
{
	int a = n - 1;
	int b = strlen(string);
	int c = 0;
	int d;
	char Separator;
	char * tmpBuff;

	Separator = charSeparator[0];

	while ((a > 0) && (c < b))
	{
		if (string[c] == Separator)
		{
			a--;
		}
		c++;
	}

	if (a > 0)
	{
		return NULL;
	}

	for (d = 0; (string[c + d] != Separator) && ((c + d)<b); d++);
	tmpBuff = (char *)malloc(sizeof(char) * (d + 1));
	memcpy(tmpBuff, &string[c], d);
	tmpBuff[d] = 0;

	return tmpBuff;
};