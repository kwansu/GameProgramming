#pragma once
#include "cGameObject.h"

class cDummyBox :
	public cGameObject
{
private:
	ST_COLLISION_BOX_STICK	m_stColl;

public:
	cDummyBox();
	~cDummyBox();

	// cGameObject override
	void Setup()	override;
	void Render()	override;
};

