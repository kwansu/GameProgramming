#pragma once
#include "cObject_Plane.h"
#include "cObject_Limbs.h"
#include "cObject_Mario_Head.h"
#include "cCollider.h"

#define GRVITY_ACCELERATION	0.1f
#define MARIO_ACCELERATION	0.03f
#define MARIO_ROTATE_SPEED	3.0f
#define	MARIO_JUMP_HEIGHT	25.f
#define MARIO_JUMP_POWER	sqrt(2.f*GRVITY_ACCELERATION*MARIO_JUMP_HEIGHT)

class cObject_Mario :
	public cObject_Cube
{
private:
	float						m_fLookSpeed;
	float						m_fUpSpeed;
	bool						m_bBottom;
	vector<cObject_Plane*>*		m_papPlane;
	stLight						m_pLight;
	stLight						m_pLight2;

	cObject_Mario_Head*			m_pChildHead;
	cObject_Limbs*				m_pChildLArm;
	cObject_Limbs*				m_pChildRArm;
	cObject_Limbs*				m_pChildLLeg;
	cObject_Limbs*				m_pChildRLeg;

public:
	cObject_Mario();
	~cObject_Mario();
	void Setup(vector<cObject_Plane*>* papPlane);
	void Update();
	void Render();
	void CollisionHandling();
};

