#pragma once


template <typename T>
inline void SafeDelete(T& p)
{
	if (p)
	{
		delete p;
		p = NULL;
	}
}


template <typename T>
inline void SafeRelease(T& p)
{
	if (p)
	{
		p->Release();
		p = NULL;
	}
}


// �� �� �� ū ���� ��ȯ
template <typename T>
inline T Greater(T val, T val2)
{
	return val > val2 ? val : val2;
}


// �� ���� ���� ���� ��ȯ
template <typename T>
inline T Smaller(T val, T val2)
{
	return val < val2 ? val : val2;
}


// EPSILON�� �̿��� �Ǽ��˻�
inline bool IsEqual(float valiable, float constant)
{
	if (valiable + EPSILON > constant && valiable - EPSILON < constant)
		return true;

	return false;
}


// �� ���� �����ؼ� ��ȯ
template <typename T>
inline void AlignMinMax(T& min, T& max)
{
	if (min > max)
	{
		T temp = min;
		min = max;
		max = temp;
	}
}

// ������ ��� �Լ���
namespace ns_SKS
{
	// ����, �ٳ���, �鿩����� �ܾ��� ������ �Ǵ�
	bool IsBlank(char c);

	void GetToken(std::ifstream& iFile, OUT char* szToken, unsigned uMaxLength = 1024);
	void GetToken(FILE* file, OUT char * szToken);
	void GetFloat(std::ifstream& iFile, OUT float* fOut);
	void GetInteger(std::ifstream& iFile, OUT int* nOut);
}