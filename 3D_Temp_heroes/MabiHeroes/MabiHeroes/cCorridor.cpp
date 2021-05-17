#include "stdafx.h"
#include "cCorridor.h"


cCorridor1::cCorridor1()
{
	m_nIndex = 14;
}
cCorridor1::~cCorridor1()
{
}
void cCorridor1::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;
	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/corridor/", "corridor1.X", sp);
}

cCorridor2::cCorridor2()
{
	m_nIndex = 15;
}
cCorridor2::~cCorridor2()
{
}
void cCorridor2::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;
	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/corridor/", "corridor2.X", sp);
}

cCorridor3::cCorridor3()
{
	m_nIndex = 16;
}
cCorridor3::~cCorridor3()
{
}
void cCorridor3::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;
	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/corridor/", "corridor3.X", sp);
}

cCorridor4::cCorridor4()
{
	m_nIndex = 17;
}
cCorridor4::~cCorridor4()
{
}
void cCorridor4::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;
	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/corridor/", "corridor4.X", sp);
}

cCorridor5::cCorridor5()
{
	m_nIndex = 18;
}
cCorridor5::~cCorridor5()
{
}
void cCorridor5::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;
	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/corridor/", "corridor5.X", sp);
}

cLongHall::cLongHall()
{
	m_nIndex = 19;
}
cLongHall::~cLongHall()
{
}
void cLongHall::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;
	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/corridor/", "longhall.X", sp);
}
