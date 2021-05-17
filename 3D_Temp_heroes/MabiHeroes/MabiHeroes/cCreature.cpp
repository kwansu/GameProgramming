#include "stdafx.h"
#include "cCreature.h"
#include "cSkinnedMesh.h"

cCreature::cCreature()
	: m_pState(STATE_NORMAL)
	, m_pMesh(NULL)
	, m_vVelocity(0, -fGRAVITY, 0)
	, m_isPhysics(false)
	, m_isAttackEnable(false)
	, m_isEnableReserve(false)
	, m_nAniCurrentState(0)
	, m_nAniPrevIndexState(0)
	, m_fMoveRadius(3)
	, m_stBoundingSphere(ST_SPHERE())
	, m_fAniSpeed(1)
{
	D3DXMatrixIdentity(&m_matOrigin);
}

cCreature::~cCreature()
{
}

void cCreature::Setup()
{
	this->SetupCreature();
}

void cCreature::Update()
{
	this->UpdateCreature();
	
	if (m_isPhysics)
	{
		m_vPos += m_vVelocity;

		//// 저항을 간단하게 흉내
		//m_vVelocity.x *= 0.9f;
		//m_vVelocity.z *= 0.9f;

		// 이동 충돌 처리
		g_pWorld->ProcessMoveCollision(this);
	}
	else
	{
		m_vPos.x += m_vVelocity.x;
		m_vPos.z += m_vVelocity.z;
	}

	if (m_pMesh)
	{
		D3DXMATRIXA16 mat = m_matOrigin * m_matWorld;
		m_pMesh->Update(mat);
	}

	AnimationRateProcess();
	m_nAniPrevIndexState = m_nAniCurrentState;
}

void cCreature::Render()
{
	if (m_pMesh)
		m_pMesh->Render();

	this->RenderCreature();

	for each(const auto& hitAttack in m_vecHitAttack)
	{
		if (hitAttack.isActive)
			g_pCollisionRender->RenderBox(*hitAttack.pHitBox);
	}
}

void cCreature::AnimationRateProcess()
{
	float fRate = m_pMesh->GetTrackRate();

	ShiftMoveUpdate(fRate);
	HitAttackUpdate(fRate);
	ReserveAniUpdate(fRate);
	AnimationRateProcessLocal(fRate);

	if (m_nAniPrevIndexState != m_nAniCurrentState)
	{
		m_pMesh->SwitchAnimationBlend(m_nAniCurrentState, m_fAniSpeed);
		m_isEnableReserve = false;
		m_stShiftMove.bIsShift = false;

		for (int i = 0; i < m_vecHitAttack.size(); ++i)
		{
			m_vecHitAttack[i].pHitBox->vHalfSize /= m_vecHitAttack[i].fScale;
		}

		m_vecHitAttack.clear();
		m_vecHitList.clear();
		AniSituation();
	}
}

void cCreature::ReserveAniUpdate(float fAniRate)
{
	if (m_isEnableReserve)
	{
		if (m_fReserveChangeRate < fAniRate)
		{
			m_nAniCurrentState = m_nAniReserveState;
			m_isEnableReserve = false;
		}
	}
}

void cCreature::ShiftMoveUpdate(float fAniRate)
{
	if (m_stShiftMove.bIsShift)
	{
 		if (fAniRate >= m_stShiftMove.fEndRate)
		{
			m_stShiftMove.bIsShift = false;
		}
		else if(fAniRate >= m_stShiftMove.fStartRate)
		{
			CalcShiftMovement(fAniRate);

			m_vPos.x -= m_stShiftMove.vShiftDir.x * m_stShiftMove.fPrevMovement;
			m_vPos.z -= m_stShiftMove.vShiftDir.z * m_stShiftMove.fPrevMovement;
			m_stShiftMove.fPrevRate = fAniRate;
		}
	}
}

void cCreature::HitAttackUpdate(float fAniRate)
{
	for (auto iter = m_vecHitAttack.begin(); iter != m_vecHitAttack.end();)
	{
		if (iter->fEndRate < fAniRate)
		{
			iter->pHitBox->vHalfSize /= iter->fScale;
			iter = m_vecHitAttack.erase(iter);
			continue;
		}
		else if (iter->fStartRate < fAniRate)
		{
			iter->isActive = true;
			//iter->pHitBox->vHalfSize *= iter->fScale;

			if (g_pWorld->ProcessAttackCollision(*iter->pHitBox,
				this,
				iter->fDamage,
				iter->isSmash,
				m_vecHitList))
			{
				Slicing();
			}

			//iter->pHitBox->vHalfSize /= iter->fScale;
		}
		++iter;
	}
}

void cCreature::SetShiftMove(D3DXVECTOR3& vShiftDir, float fPower, float fStartRate, float fEndRate)
{
	D3DXVec3Normalize(&vShiftDir, &vShiftDir);
	m_stShiftMove.bIsShift = true;
	m_stShiftMove.vShiftDir = -vShiftDir;
	m_stShiftMove.fPower = fPower;
	m_stShiftMove.fPrevRate = fStartRate;
	m_stShiftMove.fStartRate = fStartRate;
	m_stShiftMove.fEndRate = fEndRate;
}

void cCreature::SetEnableHitAttack(char * szBoxName, float fDamage, 
	bool isSmash, float fStartRate, float fEndRate)
{
	auto iterResult = m_mapHitBox.find(szBoxName);

	if (iterResult == m_mapHitBox.end())
		return;

	ST_HitAttack stHitAttack;
	stHitAttack.pHitBox = &iterResult->second;
	stHitAttack.fStartRate = fStartRate;
	stHitAttack.fEndRate = fEndRate;
	stHitAttack.fDamage = fDamage;
	stHitAttack.isSmash = isSmash;
	stHitAttack.isActive = false;

	m_vecHitAttack.push_back(stHitAttack);
}

void cCreature::SetEnableHitAttack(int n, float fDamage, bool isSmash, float fStartRate, float fEndRate, float fScale)
{
	if (n >= m_vecAttackBox.size())
		return;						//	여기 걸리면 벡터보다 큰 인덱스 값이 들어온거임.
	
	ST_HitAttack stHitAttack;
	stHitAttack.pHitBox = &m_vecAttackBox[n];
	stHitAttack.fStartRate = fStartRate;
	stHitAttack.fEndRate = fEndRate;
	stHitAttack.fDamage = fDamage;
	stHitAttack.isSmash = isSmash;
	stHitAttack.fScale = fScale;
	stHitAttack.isActive = false;
	stHitAttack.pHitBox->vHalfSize *= fScale;

	m_vecHitAttack.push_back(stHitAttack);
}

void cCreature::SetReserveAnimation(int nReserveAni, float nChangeRate, float fAniSpeed)
{
	m_fAniSpeed = fAniSpeed;
	m_fReserveChangeRate = nChangeRate;
	m_nAniReserveState = nReserveAni;
	m_isEnableReserve = true;
}

void cCreature::CreateAllHitBox()
{
	m_mapHitBox.clear();
	m_pMesh->CreateHitBox(m_mapHitBox, NULL);
}

void cCreature::LoadHitBox(char * szFile, const D3DXMATRIXA16& matR)
{
	m_mapHitBox.clear();

	string AtkBoxFileNAme = szFile ;
	int lenght = AtkBoxFileNAme.size();
	AtkBoxFileNAme.insert(lenght - 4, "Attack");			// 4 == ".txt"

	ifstream openFile(szFile);

	if (!openFile.is_open())
	{
		cout << "file open failed" << endl;
		openFile.close();
		return;
	}

	int nSize;
	openFile >> nSize;

	ST_COLLISION_BOX_STICK stColl;
	char szName[256];

	for (int i = 0; i < nSize; ++i)
	{
		ns_SKS::GetToken(openFile, szName);

		openFile >> stColl.matOffset._41;
		openFile >> stColl.matOffset._42;
		openFile >> stColl.matOffset._43;
		openFile >> stColl.vHalfSize.x;
		openFile >> stColl.vHalfSize.y;
		openFile >> stColl.vHalfSize.z;

		D3DXVec3TransformNormal(&stColl.vHalfSize, &stColl.vHalfSize, &matR);

		m_mapHitBox.insert(pair<string, ST_COLLISION_BOX_STICK>(szName, stColl));
	}

	m_pMesh->ConnectHitBox(m_mapHitBox, NULL);

	openFile.close();

	ifstream openAtkBoxFile(AtkBoxFileNAme);

	if (!openAtkBoxFile.is_open())
	{
		cout << "file open failed" << endl;
		openAtkBoxFile.close();
		return;
	}

	openAtkBoxFile >> nSize;

	ST_COLLISION_BOX_STICK stAttkColl;
	vector<string>			boxName;

	for (int i = 0; i < nSize; ++i)
	{
		ns_SKS::GetToken(openAtkBoxFile, szName);

		openAtkBoxFile >> stAttkColl.matOffset._41;
		openAtkBoxFile >> stAttkColl.matOffset._42;
		openAtkBoxFile >> stAttkColl.matOffset._43;
		openAtkBoxFile >> stAttkColl.vHalfSize.x;
		openAtkBoxFile >> stAttkColl.vHalfSize.y;
		openAtkBoxFile >> stAttkColl.vHalfSize.z;

		D3DXVec3TransformNormal(&stAttkColl.vHalfSize, &stAttkColl.vHalfSize, &matR);

		boxName.push_back(szName);
		m_vecAttackBox.push_back(ST_COLLISION_BOX_STICK(stAttkColl));
	}

	m_pMesh->ConnectHitBox(boxName, m_vecAttackBox, NULL);

	openAtkBoxFile.close();
}

void cCreature::RenderHitBox(const D3DXCOLOR* pColor)
{
	for each(const auto& coll in m_mapHitBox)
	{
		g_pCollisionRender->RenderBox(coll.second, pColor);
	}
}
void cCreature::RenderAtkBox(const D3DXCOLOR* pColor)
{
	for each(const auto& coll in m_vecAttackBox)
	{
		g_pCollisionRender->RenderBox(coll, pColor);
	}
}
void cCreature::RenderSphere()
{
	D3DXVECTOR3 vOri;
	D3DXVec3TransformCoord(&vOri, &m_stBoundingSphere.vOffset, &m_matWorld);
	g_pCollisionRender->RenderSphere(vOri, m_stBoundingSphere.fRadius);
}

void cCreature::DebugRender()
{
	UpdateTransform();

	if (m_pMesh)
	{
		D3DXMATRIXA16 mat = m_matOrigin * m_matWorld;
		m_pMesh->Update(mat);
	}

	AnimationRateProcessLocal(0);
}

void cCreature::CalcShiftMovement(float fAniRate)
{
	float p = (fAniRate - m_stShiftMove.fStartRate)
		/ (m_stShiftMove.fEndRate - m_stShiftMove.fStartRate);

	m_stShiftMove.fPrevMovement = (1 - p * p) * m_stShiftMove.fPower
		* (fAniRate - m_stShiftMove.fPrevRate);
}

void cCreature::SetOriginMatrix(const D3DXMATRIXA16 & mat)
{
	m_matOrigin = mat;
	D3DXVec3TransformCoord(&m_stBoundingSphere.vOffset, &m_stBoundingSphere.vOffset, &m_matOrigin);

	D3DXVECTOR3 vRidius(0, 0, m_stBoundingSphere.fRadius);
	D3DXVec3TransformNormal(&vRidius, &vRidius, &m_matOrigin);
	m_stBoundingSphere.fRadius = D3DXVec3Length(&vRidius);
}

ST_SPHERE & cCreature::GetBoundingSphere()
{
	return m_stBoundingSphere;
}