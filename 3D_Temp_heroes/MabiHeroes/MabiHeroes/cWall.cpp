#include "stdafx.h"
#include "cWall.h"


cWall1::cWall1()
{
	m_nIndex = 2;
}
cWall1::~cWall1()
{
}
void cWall1::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;
	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/wall/", "wall001.X", sp);
}

cWall2::cWall2()
{
	m_nIndex = 3;
}
cWall2::~cWall2()
{
}
void cWall2::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;
	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/wall/", "wall002.X", sp);
}

cWall3::cWall3()
{
	m_nIndex = 4;
}
cWall3::~cWall3()
{
}
void cWall3::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;
	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/wall/", "wall003.X", sp);
}

cWall4::cWall4()
{
	m_nIndex = 5;
}
cWall4::~cWall4()
{
}
void cWall4::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;
	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/wall/", "wall004.X", sp);
}

cWall5::cWall5()
{
	m_nIndex = 6;
}
cWall5::~cWall5()
{
}
void cWall5::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;
	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/wall/", "wall005.X", sp);
}

cWall6::cWall6()
{
	m_nIndex = 7;
}
cWall6::~cWall6()
{
}
void cWall6::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;
	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/wall/", "wall006.X", sp);
}

cWall7::cWall7()
{
	m_nIndex = 138;
}
cWall7::~cWall7()
{
}
void cWall7::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;
	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/wall/", "wall007.X", sp);
}

cWall8::cWall8()
{
	m_nIndex = 9;
}
cWall8::~cWall8()
{
}
void cWall8::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;
	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/wall/", "wall1.X", sp);
}

cWall9::cWall9()
{
	m_nIndex = 10;
}
cWall9::~cWall9()
{
}
void cWall9::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;
	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/wall/", "wall2.X", sp);
}

cWall10::cWall10()
{
	m_nIndex = 11;
}
cWall10::~cWall10()
{
}
void cWall10::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;
	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/wall/", "wall3.X", sp);
}

cWall11::cWall11()
{
	m_nIndex = 12;
}
cWall11::~cWall11()
{
}
void cWall11::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;
	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/wall/", "wall4.X", sp);
}

cWall12::cWall12()
{
	m_nIndex = 13;
}
cWall12::~cWall12()
{
}
void cWall12::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;
	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/wall/", "wall5.X", sp);
}

