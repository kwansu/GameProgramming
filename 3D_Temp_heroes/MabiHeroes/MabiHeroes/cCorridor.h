#pragma once
#include "cStructure.h"
#include "cSkinnedMesh.h"

enum CORRIDOR_TYPE
{
	CORRIDOR_001,
	CORRIDOR_002,
	CORRIDOR_003,
	CORRIDOR_004,
	CORRIDOR_005,
	CORRIDOR_006,
	CORRIDOR_LH
};

class cCorridor1 : public cStructure
{
public:
	cCorridor1();
	~cCorridor1();
	virtual void Setup() override;
};
class cCorridor2 : public cStructure
{
public:
	cCorridor2();
	~cCorridor2();
	virtual void Setup() override;
};
class cCorridor3 : public cStructure
{
public:
	cCorridor3();
	~cCorridor3();
	virtual void Setup() override;
};
class cCorridor4 : public cStructure
{
public:
	cCorridor4();
	~cCorridor4();
	virtual void Setup() override;
};
class cCorridor5 : public cStructure
{
public:
	cCorridor5();
	~cCorridor5();
	virtual void Setup() override;
};
class cLongHall : public cStructure
{
public:
	cLongHall();
	~cLongHall();
	virtual void Setup() override;
};
