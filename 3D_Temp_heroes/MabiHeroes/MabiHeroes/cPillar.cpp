#include "stdafx.h"
#include "cPillar.h"


cPillar1::cPillar1()
{
	m_nIndex = 20;
}
cPillar1::~cPillar1()
{
}
void cPillar1::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;
	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/pillar/", "pillar1.X", sp);
}

cPillar2::cPillar2()
{
	m_nIndex = 21;
}
cPillar2::~cPillar2()
{
}
void cPillar2::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;
	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/pillar/", "pillar2.X", sp);
}

cPillar3::cPillar3()
{
	m_nIndex = 22;
}
cPillar3::~cPillar3()
{
}
void cPillar3::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;
	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/pillar/", "pillar3.X", sp);
}

cPillar4::cPillar4()
{
	m_nIndex = 23;
}
cPillar4::~cPillar4()
{
}
void cPillar4::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;
	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/pillar/", "pillar4.X", sp);
}

cPillar5::cPillar5()
{
	m_nIndex = 24;
}
cPillar5::~cPillar5()
{
}
void cPillar5::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;
	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/pillar/", "pillar5.X", sp);
}

cPillar6::cPillar6()
{
	m_nIndex = 25;
}
cPillar6::~cPillar6()
{
}
void cPillar6::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;
	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/pillar/", "pillar6.X", sp);
}

cPillar7::cPillar7()
{
	m_nIndex = 26;
}
cPillar7::~cPillar7()
{
}
void cPillar7::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;
	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/pillar/", "pillar7.X", sp);
}

cPillar8::cPillar8()
{
	m_nIndex = 27;
}
cPillar8::~cPillar8()
{
}
void cPillar8::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;
	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/pillar/", "pillar8.X", sp);
}

