#pragma once

class cPyramid;

class cGrid
{
private:
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	std::vector<cPyramid*>		m_vecPyramid;
	int							m_nNumLine;
public:
	cGrid(void);
	~cGrid(void);

	void Setup(int nLine, float m_nInterval);
	void Render();
};

