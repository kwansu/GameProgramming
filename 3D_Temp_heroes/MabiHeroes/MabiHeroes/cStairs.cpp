#include "stdafx.h"
#include "cStairs.h"


cStairs1::cStairs1()
{
	m_nIndex = 28;
}
cStairs1::~cStairs1()
{
}
void cStairs1::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;
	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/stairs/", "stairs1.X", sp);
}

cStairs2::cStairs2()
{
	m_nIndex = 29;
}
cStairs2::~cStairs2()
{
}
void cStairs2::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;
	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/stairs/", "stairs2.X", sp);
}

cStairs3::cStairs3()
{
	m_nIndex = 30;
}
cStairs3::~cStairs3()
{
}
void cStairs3::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;
	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/stairs/", "stairs3.X", sp);
}

cStairs4::cStairs4()
{
	m_nIndex = 31;
}
cStairs4::~cStairs4()
{
}
void cStairs4::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;
	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/stairs/", "stairs4.X", sp);
}

cStairs5::cStairs5()
{
	m_nIndex = 32;
}
cStairs5::~cStairs5()
{
}
void cStairs5::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;
	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/stairs/", "stairs5.X", sp);
}

cStairs6::cStairs6()
{
	m_nIndex = 33;
}
cStairs6::~cStairs6()
{
}
void cStairs6::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;
	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/stairs/", "stairs6.X", sp);
}

cStairsC::cStairsC()
{
	m_nIndex = 34;
}
cStairsC::~cStairsC()
{
}
void cStairsC::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;
	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/stairs/", "stairsCorridor.X", sp);
}

