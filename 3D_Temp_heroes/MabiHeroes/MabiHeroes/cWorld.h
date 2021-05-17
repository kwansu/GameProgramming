#pragma once
#include "cObj_Sendbag.h"
#include "stdObjects.h"

const float fMAXMOVECOS = cos(D3DXToRadian(45));
const float	fCOLLISION_PUSH_SPEED = 0.4f;			// PC�� ���� �浹ü�� �İ� ���� ��� �о��ִ� �ӷ�

class cWorld
{
	SINGLETON(cWorld);

private:
	vector<cStructure*>	m_vecStructure;
	vector<cCreature*>	m_vecCreature;
	cObj_Fiona*			m_pFiona;

	bool				m_isDebugRender;
	bool				m_isDebugRender2;
	bool				m_isDebugRender3;


public:
	void Setup();
	void Update();
	void Render();
	void Destroy();
	void LoadMap();

	// �̵� ��ġ�� �浹���θ� �˻��Ͽ�, �浹�� �̵��� ��ü�� �о��ش�.
	void ProcessMoveCollision(cCreature* pMover);
	// ���ݽ� �ǰ������� ���� �浿ó��
	bool ProcessAttackCollision(const ST_COLLISION_BOX_STICK& stAttackColl, 
		cGameObject* pAttacker, float fDamage, bool isSmash, vector<cGameObject*>& vecHitList);

	void CreateCollisionBox(ST_COLLISION_BOX_STICK& stBox);

private:
	// �浹 ���� �Լ�
	void ProcessMoveCollisionStructure(const ST_COLLISION_BOX_STICK& collStructure, cCreature* pMover);
	void ProcessMoveCollisionCreature(const cCreature* pCreature, cCreature* pMover);
	bool IsAttackCollisionCreature(const ST_COLLISION_BOX_STICK& stAttackColl, cCreature* pTarget);
	bool IsAttackCollisionStructure(const ST_COLLISION_BOX_STICK& stAttackColl, cStructure* pTarget);
	bool IsCollisionSphereMove(const cCreature& target, const cCreature* pMover) const;
	bool IsCollisionCapsuleAndBox(const ST_COLLISION_BOX_STICK& hitBox, const cCreature* pMover, OUT float& fDist, OUT D3DXVECTOR3& vDist) const;
	bool IsCollisionSphereAndBox(const D3DXVECTOR3& vPos, const ST_SPHERE& sphere, const ST_COLLISION_BOX_STICK& box);
	bool IsCollisionBoxAndBox(const ST_COLLISION_BOX_STICK& box1, const ST_COLLISION_BOX_STICK& box2) const;
	bool IsCallDamaged(const cCreature* target, const vector<cGameObject*>& vecHitList);
	bool AlignmentAxisCheck(const D3DXVECTOR3& vAxis, float fHalf, const ST_COLLISION_BOX_STICK& boxTarget,
		const D3DXVECTOR3& vCenterAxis, const D3DXVECTOR3& vCenterTar, const D3DXVECTOR3 arrAxis[]) const;
};

extern cWorld* g_pWorld;