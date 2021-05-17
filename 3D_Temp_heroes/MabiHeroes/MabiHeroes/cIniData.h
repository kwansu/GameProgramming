#pragma once

struct ST_IniData
{
	const char* Category;
	const char* Datatype;
	float Value;
};

#define g_pIniData cIniData::GetInstance()

class cIniData
{
	SINGLETON(cIniData);

private:
	typedef vector<ST_IniData> arrIniData;
	typedef vector<ST_IniData>::iterator arrIniDataIter;
	typedef vector<arrIniData> arrIniDatas;
	typedef vector<arrIniData>::iterator arrIniDatasIter;

private:
	arrIniDatas _vIniData;

public:
	void Setup(void);
	void Release(void);

	void AddData(const char* category, const char* datatype, float value);
	float LoadData(const char* fullPath, const char* category, const char* datatype);
	void IniSave(const char* fullPath);

};

