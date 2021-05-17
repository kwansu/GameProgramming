#pragma once
#include "cStructure.h"
#include "cSkinnedMesh.h"

enum STAIRS_TYPE
{
	STAIRS_001,
	STAIRS_002,
	STAIRS_003,
	STAIRS_004,
	STAIRS_005,
	STAIRS_006,
	STAIRS_C
};

class cStairs1 : public cStructure
{
public:
	cStairs1();
	~cStairs1();
	virtual void Setup() override;
};
class cStairs2 : public cStructure
{
public:
	cStairs2();
	~cStairs2();
	virtual void Setup() override;
};
class cStairs3 : public cStructure
{
public:
	cStairs3();
	~cStairs3();
	virtual void Setup() override;
};
class cStairs4 : public cStructure
{
public:
	cStairs4();
	~cStairs4();
	virtual void Setup() override;
};
class cStairs5 : public cStructure
{
public:
	cStairs5();
	~cStairs5();
	virtual void Setup() override;
};
class cStairs6 : public cStructure
{
public:
	cStairs6();
	~cStairs6();
	virtual void Setup() override;
};
class cStairsC : public cStructure
{
public:
	cStairsC();
	~cStairsC();
	virtual void Setup() override;
};
