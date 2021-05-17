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


// 두 값 중 큰 값을 반환
template <typename T>
inline T Greater(T val, T val2)
{
	return val > val2 ? val : val2;
}


// 두 값중 작은 값을 반환
template <typename T>
inline T Smaller(T val, T val2)
{
	return val < val2 ? val : val2;
}


// EPSILON을 이용한 실수검사
inline bool IsEqual(float valiable, float constant)
{
	if (valiable + EPSILON > constant && valiable - EPSILON < constant)
		return true;

	return false;
}


// 두 값을 정렬해서 반환
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

// 개인적 사용 함수들
namespace ns_SKS
{
	// 띄어쓰기, 줄내림, 들여쓰기등 단어의 끝인지 판단
	bool IsBlank(char c);

	void GetToken(std::ifstream& iFile, OUT char* szToken, unsigned uMaxLength = 1024);
	void GetToken(FILE* file, OUT char * szToken);
	void GetFloat(std::ifstream& iFile, OUT float* fOut);
	void GetInteger(std::ifstream& iFile, OUT int* nOut);
}