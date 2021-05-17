#include "stdafx.h"
#include "cIniData.h"
cIniData::cIniData()
{
}
cIniData::~cIniData()
{
}

void cIniData::Setup(void)
{
}

void cIniData::Release(void)
{
}

void cIniData::AddData(const char* category, const char* datatype, float value)
{
	ST_IniData IniData;
	IniData.Category = category;
	IniData.Datatype = datatype;
	IniData.Value = value;

	arrIniData vIniData;
	vIniData.push_back(IniData);
	_vIniData.push_back(vIniData);
}

void cIniData::IniSave(const char* fullPath)
{
	char str[256];
	char dir[128];

	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\%s.ini", fullPath);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	for (int i = 0; i < _vIniData.size(); i++)
	{
		arrIniData vData = _vIniData[i];

		std::ostringstream buffer;
		buffer << vData[0].Value;
		string val = buffer.str();

		WritePrivateProfileString(vData[0].Category, vData[0].Datatype, val.c_str(), str);
		
		vData.clear();
	}

	_vIniData.clear();
}

float cIniData::LoadData(const char* fullPath, const char* category, const char* datatype)
{
	char str[256];
	char dir[128];
	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\%s.ini", fullPath);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	char data[64] = { NULL };
	GetPrivateProfileString(category, datatype, "", data, 64, str);

	return stof(data);
}


