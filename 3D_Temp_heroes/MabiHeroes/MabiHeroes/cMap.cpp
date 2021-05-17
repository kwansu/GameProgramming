#include "stdafx.h"
#include "cSurface.h"


cMap::cMap()
{
	m_nIndex = 0;
}


cMap::~cMap()
{
}

void cMap::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;

	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/map/", "mapFInal.X", sp);

	


}
