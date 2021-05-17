#include "stdafx.h"
#include "cWorld.h"


cWorld* g_pWorld = NULL;

cWorld::cWorld()
	: m_pFiona(NULL)
	, m_isDebugRender(false)
	, m_isDebugRender2(false)
{
}


cWorld::~cWorld()
{
}

void cWorld::Setup()
{
	m_vecCreature.clear();
	m_vecStructure.clear();

	m_pFiona = new cObj_Fiona;
	m_pFiona->Setup();
	m_pFiona->SetPosition(0, 100, 0);
	m_pFiona->SetPysicsState(true);

	g_pCamera->SetTarget(&m_pFiona->m_vPos);

	cNoll* pNoll;
	//for (int i = 0; i < 5; ++i)
	//{
	//	for (int o = 0; o < 5; ++o)
	//	{
	//		pNoll = new cNoll;
	//		pNoll->Setup();
	//		pNoll->SetPosition(i * 10, 0, o * 10);
	//		pNoll->SetTarget(&m_pFiona->GetPosition());
	//		pNoll->SetTargetObj(m_pFiona);
	//		pNoll->SetPysicsState(true);
	//
	//		m_vecCreature.push_back(pNoll);
	//	}
	//}

	pNoll = new cNoll;
	pNoll->Setup();
	pNoll->SetPosition(100, 0, 0);
	pNoll->SetTarget(&m_pFiona->GetPosition());
	pNoll->SetTargetObj(m_pFiona);
	pNoll->SetPysicsState(true);
	m_vecCreature.push_back(pNoll);


	pNoll = new cNoll;
	pNoll->Setup();
	pNoll->SetPosition(100, 0, 100);
	pNoll->SetTarget(&m_pFiona->GetPosition());
	pNoll->SetTargetObj(m_pFiona);
	pNoll->SetPysicsState(true);
	m_vecCreature.push_back(pNoll);

	pNoll = new cNoll;
	pNoll->Setup();
	pNoll->SetPosition(150, 0, 150);
	pNoll->SetTarget(&m_pFiona->GetPosition());
	pNoll->SetTargetObj(m_pFiona);
	pNoll->SetPysicsState(true);
	m_vecCreature.push_back(pNoll);

	cEnemy::s_pTarget = m_pFiona;

	//cLavasat* pLavasat = new cLavasat;
	//pLavasat->Setup();
	//pLavasat->SetPosition(-100, 0, -100);
	//pLavasat->SetPysicsState(true);
	//m_vecCreature.push_back(pLavasat);

	cPrince* pPrince = new cPrince;
	pPrince->Setup();
	pPrince->SetPosition(-100, 0, 150);
	pPrince->SetPysicsState(true);
	m_vecCreature.push_back(pPrince);

	cWoodenElf* pWooden = new cWoodenElf;
	pWooden->Setup();
	pWooden->SetPosition(150, 0, -100);
	pWooden->SetPysicsState(true);
	m_vecCreature.push_back(pWooden);

	g_pLightManager->Setup();
}

void cWorld::Update()
{
	g_pLightManager->Updete(m_pFiona->m_vPos);

	for each(const auto& pCreature in m_vecCreature)
	{
		pCreature->Update();
	}

	if (g_pKeyManager->IsOnceKeyDown('V'))
		m_isDebugRender = m_isDebugRender ? false : true;

	if (g_pKeyManager->IsOnceKeyDown('C'))
		m_isDebugRender2 = m_isDebugRender2 ? false : true;

	if (g_pKeyManager->IsOnceKeyDown('B'))
		m_isDebugRender3 = m_isDebugRender3 ? false : true;

	m_pFiona->Update();
	g_pEffectManager->Update();

}

void cWorld::Render()
{
	m_pFiona->Render();

	if (m_isDebugRender)
	{
		m_pFiona->RenderHitBox();
		
		for each(const auto& pCreature in m_vecCreature)
		{
			pCreature->RenderHitBox();
		}
	}

	if (m_isDebugRender2)
	{
		m_pFiona->RenderSphere();

		for each(const auto& pCreature in m_vecCreature)
		{
			pCreature->RenderSphere();
		}
	}
	if (m_isDebugRender3)
	{
		m_pFiona->RenderAtkBox();

		for each(const auto& pCreature in m_vecCreature)
		{
			pCreature->RenderAtkBox();
		}
	}

	for each(const auto& pStructure in m_vecStructure)
	{
		pStructure->Render();
	}

	for each(const auto& pCreature in m_vecCreature)
	{
		pCreature->Render();
	}

	g_pEffectManager->Render();
}

void cWorld::Destroy()
{
}

void cWorld::LoadMap()
{
	ifstream inFile("./GameData/mapData2.txt");

	if (!inFile.is_open())
		assert(false, "loadfile Unloaded");

	while (!inFile.eof())
	{

		cStructure * pStructure = NULL;
		int index;
		D3DXVECTOR3 Scale, Rot, Pos;
		int numColl;
		ST_COLLISION_BOX_STICK coll;

		inFile >> index;

		//switch (index)
		//{
				pStructure = CREATE_STRUCTURE(0);
		//case 1:		pStructure = CREATE_STRUCTURE(1);	break;
		//case 2:		pStructure = CREATE_STRUCTURE(2);	break;
		//case 3:		pStructure = CREATE_STRUCTURE(3);	break;
		//case 4:		pStructure = CREATE_STRUCTURE(4);	break;
		//case 5:		pStructure = CREATE_STRUCTURE(5);	break;
		//case 6:		pStructure = CREATE_STRUCTURE(6);	break;
		//case 7:		pStructure = CREATE_STRUCTURE(7);	break;
		//case 8:		pStructure = CREATE_STRUCTURE(8);	break;
		//case 9:		pStructure = CREATE_STRUCTURE(9);	break;
		//case 10:	pStructure = CREATE_STRUCTURE(10);	break;
		//case 11:	pStructure = CREATE_STRUCTURE(11);	break;
		//case 12:	pStructure = CREATE_STRUCTURE(12);	break;
		//case 13:	pStructure = CREATE_STRUCTURE(13);	break;
		//case 14:	pStructure = CREATE_STRUCTURE(14);	break;
		//case 15:	pStructure = CREATE_STRUCTURE(15);	break;
		//case 16:	pStructure = CREATE_STRUCTURE(16);	break;
		//case 17:	pStructure = CREATE_STRUCTURE(17);	break;
		//case 18:	pStructure = CREATE_STRUCTURE(18);	break;
		//case 19:	pStructure = CREATE_STRUCTURE(19);	break;
		//case 20:	pStructure = CREATE_STRUCTURE(20);	break;
		//case 21:	pStructure = CREATE_STRUCTURE(21);	break;
		//case 22:	pStructure = CREATE_STRUCTURE(22);	break;
		//case 23:	pStructure = CREATE_STRUCTURE(23);	break;
		//case 24:	pStructure = CREATE_STRUCTURE(24);	break;
		//case 25:	pStructure = CREATE_STRUCTURE(25);	break;
		//case 26:	pStructure = CREATE_STRUCTURE(26);	break;
		//case 27:	pStructure = CREATE_STRUCTURE(27);	break;
		//case 28:	pStructure = CREATE_STRUCTURE(28);	break;
		//case 29:	pStructure = CREATE_STRUCTURE(29);	break;
		//case 30:	pStructure = CREATE_STRUCTURE(30);	break;
		//case 31:	pStructure = CREATE_STRUCTURE(31);	break;
		//case 32:	pStructure = CREATE_STRUCTURE(32);	break;
		//case 33:	pStructure = CREATE_STRUCTURE(33);	break;
		//case 34:	pStructure = CREATE_STRUCTURE(34);	break;
		//case 35:	pStructure = CREATE_STRUCTURE(35);	break;
		//}

		coll.pmatSticking = &pStructure->m_matWorld;

		inFile >> Scale.x;
		inFile >> Scale.y;
		inFile >> Scale.z;
		inFile >> Rot.x;
		inFile >> Rot.y;
		inFile >> Rot.z;
		inFile >> Pos.x;
		inFile >> Pos.y;
		inFile >> Pos.z;

		if (pStructure)
		{
			pStructure->Setup();

			pStructure->m_vScale.x = Scale.x;
			pStructure->m_vScale.y = Scale.y;
			pStructure->m_vScale.z = Scale.z;
			pStructure->m_vRot.x = Rot.x;
			pStructure->m_vRot.y = Rot.y;
			pStructure->m_vRot.z = Rot.z;
			pStructure->m_vPos.x = Pos.x;
			pStructure->m_vPos.y = Pos.y;
			pStructure->m_vPos.z = Pos.z;

			m_vecStructure.push_back(pStructure);
		}

		inFile >> numColl;

		if (pStructure)
		{
			for (int p = 0; p < numColl; p++)
			{
				inFile >> coll.matOffset._11;
				inFile >> coll.matOffset._12;
				inFile >> coll.matOffset._13;
				inFile >> coll.matOffset._14;
				inFile >> coll.matOffset._21;
				inFile >> coll.matOffset._22;
				inFile >> coll.matOffset._23;
				inFile >> coll.matOffset._24;
				inFile >> coll.matOffset._31;
				inFile >> coll.matOffset._32;
				inFile >> coll.matOffset._33;
				inFile >> coll.matOffset._34;
				inFile >> coll.matOffset._41;
				inFile >> coll.matOffset._42;
				inFile >> coll.matOffset._43;
				inFile >> coll.matOffset._44;
				inFile >> coll.vHalfSize.x;
				inFile >> coll.vHalfSize.y;
				inFile >> coll.vHalfSize.z;



				m_vecStructure.back()->m_vecCollisionBox.push_back(coll);
			}
		}
	}

	inFile.close();

	for each(const auto& pStructure in m_vecStructure)
	{
		pStructure->Update();
	}
}

void cWorld::ProcessMoveCollision(cCreature * pMover)
{
	// 캐릭터간의 충돌처리
	for each(const auto& pCreatrue in m_vecCreature)
	{
		// 적은 PC를 밀지만, PC는 적을 밀수 없다.(미처리)
		ProcessMoveCollisionCreature(pCreatrue, pMover);
	}

	// 바닥과 벽, 물체에 대한 충돌처리. 
	for each(const auto& pStructure in m_vecStructure)
	{
		// 대각으로 밀 경우 일정각도 이하는 무조건 위쪽으로만 밀어낸다.
		for each(const auto& coll in pStructure->m_vecCollisionBox)
		{
			ProcessMoveCollisionStructure(coll, pMover);
		}
	}
}

bool cWorld::ProcessAttackCollision(const ST_COLLISION_BOX_STICK & stAttackColl,
	cGameObject* pAttacker, float fDamage, bool isSmash, vector<cGameObject*>& vecHitList)
{
	bool isHit = false;

	for each(const auto& pCreature in m_vecCreature)
	{
		if (pAttacker == pCreature)
			continue;

		if (IsCallDamaged(pCreature, vecHitList))
		{
			if (IsAttackCollisionCreature(stAttackColl, pCreature))
			{
				vecHitList.push_back(pCreature);
				pCreature->Damaged(fDamage, pAttacker, isSmash);
				isHit = true;

				g_pEffectManager->CreateSlashLine(D3DXVECTOR3(0, 0, 0), rand() % 10 - 5, stAttackColl.pmatSticking);
			}
		}
	}

	if (m_pFiona && pAttacker != m_pFiona)
	{
		if (IsAttackCollisionCreature(stAttackColl, m_pFiona))
		{
			isHit = true;
			if (IsCallDamaged(m_pFiona, vecHitList))
			{
				vecHitList.push_back(m_pFiona);
				m_pFiona->Damaged(fDamage, pAttacker, isSmash);
			}
		}
	}

	for each(const auto& pStructure in m_vecStructure)
	{
		if (IsAttackCollisionStructure(stAttackColl, pStructure))
		{
			pStructure->Damaged(fDamage, pAttacker, isSmash);
		}
	}

	return isHit;
}

void cWorld::CreateCollisionBox(ST_COLLISION_BOX_STICK & stBox)
{
	cStructure* pStructure = new cStructure;
	stBox.pmatSticking = &pStructure->m_matWorld;
	pStructure->m_vecCollisionBox.push_back(stBox);

	m_vecStructure.push_back(pStructure);
}

void cWorld::ProcessMoveCollisionStructure(const ST_COLLISION_BOX_STICK& collStructure, cCreature * pMover)
{
	D3DXMATRIXA16 matInverse = collStructure.matOffset * *collStructure.pmatSticking;
	D3DXMatrixInverse(&matInverse, NULL, &matInverse);

	D3DXVECTOR3 vLocalOri(pMover->m_vPos);
	D3DXVECTOR3 vHalfSize = collStructure.vHalfSize;

	vLocalOri.y += pMover->m_fMoveRadius;
	D3DXVec3TransformCoord(&vLocalOri, &vLocalOri, &matInverse);

	if (fabs(vLocalOri.x) > pMover->m_fMoveRadius + vHalfSize.x) return;
	if (fabs(vLocalOri.y) > pMover->m_fMoveRadius + vHalfSize.y) return;
	if (fabs(vLocalOri.z) > pMover->m_fMoveRadius + vHalfSize.z) return;

	D3DXVECTOR3 vDir(vLocalOri);

	if (vHalfSize.x < vDir.x) vDir.x = vHalfSize.x;
	if (-vHalfSize.x > vDir.x) vDir.x = -vHalfSize.x;

	if (vHalfSize.y < vDir.y) vDir.y = vHalfSize.y;
	if (-vHalfSize.y > vDir.y) vDir.y = -vHalfSize.y;

	if (vHalfSize.z < vDir.z) vDir.z = vHalfSize.z;
	if (-vHalfSize.z > vDir.z) vDir.z = -vHalfSize.z;

	vDir = vLocalOri - vDir;

	float d = D3DXVec3LengthSq(&vDir);

	if (d > pMover->m_fMoveRadius * pMover->m_fMoveRadius)
		return;

	d = sqrt(d);
	D3DXVec3Normalize(&vDir, &vDir);

	D3DXVec3TransformNormal(&vDir, &vDir, collStructure.pmatSticking);

	// 최대 경사각 보다 작을 경우 위쪽으로만 밀어서 올라가게 만든다.
	if (vDir.y > fMAXMOVECOS /*&& vDir.y < 1*/)
	{
		pMover->m_vPos.y += pMover->m_fMoveRadius - d;
		pMover->m_vVelocity.y = 0;
		return;
	}

	vDir *= (pMover->m_fMoveRadius - d);
	pMover->m_vPos += vDir;
}

void cWorld::ProcessMoveCollisionCreature(const cCreature * pCreature, cCreature * pMover)
{
	if (pCreature == pMover)
		return;

	// 검사는 왠만하면 바운딩 스피어로 하는게 정확하다.
	D3DXVECTOR3 vDist = pMover->m_vPos - pCreature->m_vPos;
	float fDist = pCreature->m_fMoveRadius + pMover->m_fMoveRadius;


	if (D3DXVec3LengthSq(&vDist) >= fDist * fDist)
		return;

	vDist.y = 0;

	// 크리처와 크리처는 서로 원 범위로 겹치지 않게 한다.
	// PC는 크리처의 히트박스에 다시한번 충돌검사를 해서 천천히 밀려나가게 한다.
	D3DXVec3Normalize(&vDist, &vDist);

	// 크리처간의 충돌 처리부분
	if (pCreature != m_pFiona)
	{
		// 적끼리 충돌시 충돌한 사실을 크리처에게 알려줘야한다.(미구현)
		pMover->m_vPos = pCreature->m_vPos + vDist * fDist;
		return;
	}

	for each(const auto& hitBox in pCreature->m_mapHitBox)
	{
		if (IsCollisionCapsuleAndBox(hitBox.second, pMover, fDist, vDist))
		{
			// 충돌 처리 부분
			// 충돌한 박스의 벽면으로 밀어버린다.
			D3DXVECTOR3 vMovement(0, 0, 0);
			if (pMover->m_stShiftMove.bIsShift)
				vMovement -= pMover->m_stShiftMove.vShiftDir * pMover->m_stShiftMove.fPrevMovement;

			vMovement += pMover->m_vVelocity;

			if (fDist * fDist > D3DXVec3LengthSq(&vMovement) + fCOLLISION_PUSH_SPEED)
			{
				pMover->m_vPos -= vMovement;
				fDist = fCOLLISION_PUSH_SPEED;
			}

			pMover->m_vPos += vDist * fDist;

			return;
		}
	}
}

bool cWorld::IsAttackCollisionCreature(const ST_COLLISION_BOX_STICK & stAttackColl, cCreature * pTarget)
{
	if (!IsCollisionSphereAndBox(pTarget->m_vPos, pTarget->m_stBoundingSphere, stAttackColl))
		return false;

	for each(const auto& stTargetColl in pTarget->m_mapHitBox)
	{
		if (IsCollisionBoxAndBox(stAttackColl, stTargetColl.second))
		{
			return true;
		}
	}

	return false;
}

bool cWorld::IsAttackCollisionStructure(const ST_COLLISION_BOX_STICK & stAttackColl, cStructure * pTarget)
{
	//for each(const auto& stTargetColl in pTarget->m_vecCollisionBox)
	//{
	//	if (IsCollisionBoxAndBox(stAttackColl, stTargetColl))
	//		return true;
	//}

	return false;
}

bool cWorld::IsCollisionSphereMove(const cCreature & target, const cCreature * pMover) const
{
	float d = D3DXVec3LengthSq(&(target.m_stBoundingSphere.vOffset + target.m_vPos
		- pMover->m_stBoundingSphere.vOffset - pMover->m_vPos));

	float r = target.m_stBoundingSphere.fRadius + pMover->m_stBoundingSphere.fRadius;

	if (d > r*r)
		return false;

	return true;
}

bool cWorld::IsCollisionCapsuleAndBox(const ST_COLLISION_BOX_STICK & hitBox, 
	const cCreature * pMover, OUT float& fDist, OUT D3DXVECTOR3& vDist) const
{
	D3DXMATRIXA16 mat = hitBox.matOffset * *hitBox.pmatSticking;

	D3DXVECTOR3 vCenter(mat._41, mat._42, mat._43);
	vDist = pMover->m_vPos - vCenter;

	D3DXVECTOR3 vAxis[3];
	D3DXVec3TransformNormal(&vAxis[0], &D3DXVECTOR3(hitBox.vHalfSize.x * 5, 0, 0), &mat);
	D3DXVec3TransformNormal(&vAxis[1], &D3DXVECTOR3(0, hitBox.vHalfSize.y * 5, 0), &mat);
	D3DXVec3TransformNormal(&vAxis[2], &D3DXVECTOR3(0, 0, hitBox.vHalfSize.z * 5), &mat);

	if (vCenter.y < pMover->m_vPos.y)
	{
		fDist = fabsf(vAxis[0].y) + fabsf(vAxis[1].y) + fabsf(vAxis[2].y);

		if (fDist < fabs(vDist.y))	return false;
	}
	else if (vCenter.y > pMover->m_vPos.y + pMover->m_fMoveHeight)
	{
		fDist = fabsf(vAxis[0].y) + fabsf(vAxis[1].y) + fabsf(vAxis[2].y);

		if (fDist < fabs(vDist.y) - pMover->m_fMoveHeight)	return false;
	}

	vDist.y = 0;
	float fRealDist = D3DXVec3Length(&vDist);
	vDist /= fRealDist;

	fDist = fabsf(D3DXVec3Dot(&vAxis[0], &vDist))
		+ fabsf(D3DXVec3Dot(&vAxis[1], &vDist))
		+ fabsf(D3DXVec3Dot(&vAxis[2], &vDist));

	fDist += pMover->m_fMoveRadius;

	if (fRealDist > fDist)
		return false;

	fDist -= fRealDist;

	return true;
}

bool cWorld::IsCollisionSphereAndBox(const D3DXVECTOR3& vPos, const ST_SPHERE & sphere, const ST_COLLISION_BOX_STICK & box)
{
	D3DXMATRIXA16 mat = box.matOffset * *box.pmatSticking;

	D3DXVECTOR3 vCenter(mat._41, mat._42, mat._43);
	D3DXVECTOR3 vDir = vPos + sphere.vOffset - vCenter;

	D3DXVECTOR3 vAxis[3];
	D3DXVec3TransformNormal(&vAxis[0], &D3DXVECTOR3(box.vHalfSize.x, 0, 0), &mat);
	D3DXVec3TransformNormal(&vAxis[1], &D3DXVECTOR3(0, box.vHalfSize.y, 0), &mat);
	D3DXVec3TransformNormal(&vAxis[2], &D3DXVECTOR3(0, 0, box.vHalfSize.z), &mat);

	float fRealDist = D3DXVec3LengthSq(&vDir);
	D3DXVec3Normalize(&vDir, &vDir);

	float fDist = fabsf(D3DXVec3Dot(&vAxis[0], &vDir))
		+ fabsf(D3DXVec3Dot(&vAxis[1], &vDir))
		+ fabsf(D3DXVec3Dot(&vAxis[2], &vDir));

	fDist += sphere.fRadius;

	if (fRealDist > fDist * fDist)
		return false;

	return true;
}

bool cWorld::IsCollisionBoxAndBox(const ST_COLLISION_BOX_STICK & box1, const ST_COLLISION_BOX_STICK & box2) const
{
	D3DXMATRIXA16 mat1 = box1.matOffset * *box1.pmatSticking;
	D3DXMATRIXA16 mat2 = box2.matOffset * *box2.pmatSticking;

	D3DXVECTOR3 vCenter1(mat1._41, mat1._42, mat1._43);
	D3DXVECTOR3 vCenter2(mat2._41, mat2._42, mat2._43);

	// x, y, z 양의 방향으로 축을 만들어 검사
	D3DXVECTOR3 vAxis1[3];
	D3DXVec3TransformNormal(&vAxis1[0], &D3DXVECTOR3(1, 0, 0), &mat1);
	D3DXVec3TransformNormal(&vAxis1[1], &D3DXVECTOR3(0, 1, 0), &mat1);
	D3DXVec3TransformNormal(&vAxis1[2], &D3DXVECTOR3(0, 0, 1), &mat1);

	D3DXVECTOR3 vAxis2[3];
	D3DXVec3TransformNormal(&vAxis2[0], &D3DXVECTOR3(1, 0, 0), &mat2);
	D3DXVec3TransformNormal(&vAxis2[1], &D3DXVECTOR3(0, 1, 0), &mat2);
	D3DXVec3TransformNormal(&vAxis2[2], &D3DXVECTOR3(0, 0, 1), &mat2);

	// box1 번의 축으로 box2를 검사
	if (!AlignmentAxisCheck(vAxis1[0], box1.vHalfSize.x, box2, vCenter1, vCenter2, vAxis2))
		return false;

	if (!AlignmentAxisCheck(vAxis1[1], box1.vHalfSize.y, box2, vCenter1, vCenter2, vAxis2))
		return false;

	if (!AlignmentAxisCheck(vAxis1[2], box1.vHalfSize.z, box2, vCenter1, vCenter2, vAxis2))
		return false;

	// box2 번의 축으로 box1를 검사
	if (!AlignmentAxisCheck(vAxis2[0], box2.vHalfSize.x, box1, vCenter2, vCenter1, vAxis1))
		return false;

	if (!AlignmentAxisCheck(vAxis2[1], box2.vHalfSize.y, box1, vCenter2, vCenter1, vAxis1))
		return false;

	if (!AlignmentAxisCheck(vAxis2[2], box2.vHalfSize.z, box1, vCenter2, vCenter1, vAxis1))
		return false;

	return true;
}

bool cWorld::IsCallDamaged(const cCreature * target, const vector<cGameObject*>& vecHitList)
{
	for each(const auto& pHitted in vecHitList)
	{
		if (pHitted == target)
			return false;
	}

	return true;
}

bool cWorld::AlignmentAxisCheck(const D3DXVECTOR3 & vAxis, float fHalf, const ST_COLLISION_BOX_STICK & boxTarget
	, const D3DXVECTOR3 & vCenterAxis, const D3DXVECTOR3 & vCenterTar, const D3DXVECTOR3 arrAxis[]) const
{
	float fParam1, fParam2, fParamDelta;

	fParam1 = D3DXVec3Dot(&vAxis, &vCenterAxis);
	fParam2 = D3DXVec3Dot(&vAxis, &vCenterTar);

	fParamDelta = fabsf(D3DXVec3Dot(&arrAxis[0], &vAxis) * boxTarget.vHalfSize.x)
		+ fabsf(D3DXVec3Dot(&arrAxis[1], &vAxis) * boxTarget.vHalfSize.y)
		+ fabsf(D3DXVec3Dot(&arrAxis[2], &vAxis) * boxTarget.vHalfSize.z);

	if (fabsf(fParam1 - fParam2) > fParamDelta + fHalf)
		return false;

	return true;
}
