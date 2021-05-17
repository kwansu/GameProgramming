#include "stdafx.h"
#include "cTi.h"


cTi::cTi()
{
}


cTi::~cTi()
{
}

void cTi::SetupCreature()
{
	m_pMesh = new cSkinnedMesh;
	m_pMesh->Load("./3dObject/Ti/", "ti.X", m_stBoundingSphere);
}


