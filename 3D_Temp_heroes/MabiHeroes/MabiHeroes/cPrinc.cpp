#include "stdafx.h"
#include "cPrinc.h"


cPrinc::cPrinc()
{
}


cPrinc::~cPrinc()
{
}

void cPrinc::SetupCreature()
{
	m_pMesh = new cSkinnedMesh;
	m_pMesh->Load("./3dObject/Prince/", "prince.X", m_stBoundingSphere);
}
