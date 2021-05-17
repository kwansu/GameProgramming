#pragma once
#include "cObject.h"

class cObject_Grid :
	public cObject
{
private:
	vector<stVertex_PC>	m_aVertex;
	int	m_nLine;

public:
	cObject_Grid();
	~cObject_Grid();
	void Setup();
	void Update();
	void Render();
	void SetLine(int nLine);
};

