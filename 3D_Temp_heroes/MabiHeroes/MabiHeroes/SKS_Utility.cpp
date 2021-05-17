#include "stdafx.h"

bool ns_SKS::IsBlank(char c)
{
	return c < 33;
}

void ns_SKS::GetToken(std::ifstream & iFile, OUT char * szToken, unsigned uMaxLength)
{
	unsigned uTokenLen = 0;

	while (uTokenLen < uMaxLength)
	{
		char c = iFile.get();

		if (iFile.eof())
			break;

		if (IsBlank(c))
		{
			if (uTokenLen == 0)
				continue;

			break;
		}

		szToken[uTokenLen++] = c;
	}

	szToken[uTokenLen] = '\0';
}

void ns_SKS::GetToken(FILE* file, OUT char * szToken)
{
	int ReadCount = 0;

	while (true)
	{
		char c = fgetc(file);

		if (feof(file)) 
		{
			ZeroMemory(szToken, sizeof(szToken));
			break;
		}

		if (c == '=' || c == '\n' || c == '-')
		{
			if (ReadCount == 0)
				continue;
			break;
		}

		szToken[ReadCount++] = c;
	}
	if (ReadCount == 0)
		szToken = NULL;

	if (szToken != NULL)
		szToken[ReadCount] = '\0';
}

void ns_SKS::GetFloat(std::ifstream & iFile, OUT float * fOut)
{
	char szToken[1024];
	GetToken(iFile, szToken);

	*fOut = atof(szToken);
}

void ns_SKS::GetInteger(std::ifstream & iFile, OUT int * nOut)
{
	char szToken[1024];
	GetToken(iFile, szToken);

	*nOut = atoi(szToken);
}
