#pragma once
#include "cStructure.h"
#include "cSkinnedMesh.h"

enum PILLAR_TYPE
{
	PILLAR_001,
	PILLAR_002,
	PILLAR_003,
	PILLAR_004,
	PILLAR_005,
	PILLAR_006,
	PILLAR_007,
	PILLAR_008,

};

class cPillar1 : public cStructure
{
public:
	cPillar1();
	~cPillar1();
	virtual void Setup() override;
};
class cPillar2 : public cStructure
{
public:
	cPillar2();
	~cPillar2();
	virtual void Setup() override;
};
class cPillar3 : public cStructure
{
public:
	cPillar3();
	~cPillar3();
	virtual void Setup() override;
};
class cPillar4 : public cStructure
{
public:
	cPillar4();
	~cPillar4();
	virtual void Setup() override;
};
class cPillar5 : public cStructure
{
public:
	cPillar5();
	~cPillar5();
	virtual void Setup() override;
};
class cPillar6 : public cStructure
{
public:
	cPillar6();
	~cPillar6();
	virtual void Setup() override;
};
class cPillar7 : public cStructure
{
public:
	cPillar7();
	~cPillar7();
	virtual void Setup() override;
};
class cPillar8 : public cStructure
{
public:
	cPillar8();
	~cPillar8();
	virtual void Setup() override;
};
