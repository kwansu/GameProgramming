#include "stdafx.h"
#include "cObject_MoleMachine.h"


cObject_MoleMachine::cObject_MoleMachine()
	: m_nMoleNum(0), m_nDeathCount(10)
{
}


cObject_MoleMachine::~cObject_MoleMachine()
{
}


void cObject_MoleMachine::Setup()
{
	D3DXMatrixScaling(&m_matScale, 15, 3, 15);
	m_vecPos.y = -3;
	UpdateWorldMatrix();
	
	cObject_Mole::s_pDeathCount = &m_nDeathCount;
	cObject_Mole::s_pActiveCount = &m_nMoleNum;
	cObject_Mole tmpMole;

	for (int x = -10; x <= 10; x += 10)
	{
		for (int z = 10; z >= -10; z -= 10)
		{
			tmpMole.SetPosition(x, -MOLE_HEIGHT, z);
			m_aMole.push_back(tmpMole);
		}
	}
}


void cObject_MoleMachine::Update()
{
	int size = m_aMole.size();
	for (int i = 0; i < size; ++i)
		m_aMole[i].Update();

	if (m_nMoleNum < 2)
	{
		int r = rand() % 9;
		while (m_aMole[r].IsActicve())
			r = rand() % 9;

		m_aMole[r].Setup();
	}

	if (m_nDeathCount <= 0)
	{
		MessageBox(g_hWnd, TEXT("GAME OVER"), NULL, MB_OK);
		PostQuitMessage(0);
	}
}


void cObject_MoleMachine::Render()
{
	cObject_Cube::Render();

	int size = m_aMole.size();
	for (int i = 0; i < size; ++i)
		m_aMole[i].Render();
}
