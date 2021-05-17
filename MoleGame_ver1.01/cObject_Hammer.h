#pragma once
#include "cObject_Mole.h"
#include "cChildObject.h"

#define HAMMER_SWING_FRAME	13
#define HAMMER_SWING_ANGLE	90.f/HAMMER_SWING_FRAME
#define HAMMER_SWING_SPEED	10.f/HAMMER_SWING_FRAME
#define HAMMER_REACH		5
#define HAMMER_HEIGHT		20

class cObject_Hammer :
	public cObject
{
	cChildObject	m_childHead;
	cChildObject	m_childGrip;
	vector<cVec3>	m_aHolePos;
	cVec3			m_vecCenter;
	cVec3			m_vecMove, m_vecInter;
	float			m_fRot;
	bool			m_bAttack;
	bool			m_bReturn;
	bool			m_bCollision;
	int				m_nIndex;
	int				m_nScore;
	LPTSTR			m_str;
	TCHAR			m_strScore[50];

	vector<cObject_Mole>*	m_paMoles;

public:
	cObject_Hammer();
	~cObject_Hammer();
	void Setup();
	void Update();
	void Render();
	void SetSwing(int nIndex);
	void SetArrayCube(vector<cObject_Mole>* paMoles);
};

