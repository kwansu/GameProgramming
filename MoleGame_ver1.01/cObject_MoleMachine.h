#pragma once
#include "cObject_Mole.h"

class cObject_MoleMachine :
	public cObject_Cube
{
private:
	int						m_nMoleNum;
	int						m_nDeathCount;

public:
	vector<cObject_Mole>	m_aMole;

public:
	cObject_MoleMachine();
	~cObject_MoleMachine();
	void Setup();
	void Update();
	void Render();
};

