#include "stdafx.h"
#include "cSurface.h"


cCeilling::cCeilling()
{
	m_nIndex = 1;
}


cCeilling::~cCeilling()
{
}

void cCeilling::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;

	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/ceilling/", "ceilling.X", sp);

}

cFloor::cFloor()
{
	m_nIndex = 0;
}


cFloor::~cFloor()
{
}

void cFloor::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;

	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/floor/", "floor.X", sp);

}
