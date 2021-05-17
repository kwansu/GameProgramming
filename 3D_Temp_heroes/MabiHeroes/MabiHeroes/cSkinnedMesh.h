#pragma once

#include "cAllocateHierarchy.h"

#define fSTD_ADANCE_SPEED	1.5f

class cSkinnedMesh
{
private:
	ST_BONE*					m_pRootFrame;
	DWORD						m_dwWorkingPaletteSize;
	D3DXMATRIX*					m_pmWorkingPalette;
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;

	float	m_fAnimationWeight;
	float	m_fChangeMotiontime;
	float	m_saveBeginTime;
	int		m_currentAnimTrack;
	float	m_TotalLenght;
	float	m_TrackRate;

	map<string, D3DXMATRIXA16*>	m_pNameMat;

public:
	cSkinnedMesh(void);
	~cSkinnedMesh(void);

	// �ѹ��� ȣ��� �Լ�. �δ��� �Ŵ����� ����°� ��õ
	void Load(char* szFolder, char* szFile, OUT ST_SPHERE& stSphere);
	void LoadNew(char* szFolder, char* szFile, OUT ST_SPHERE& stSphere);
	void Update(const D3DXMATRIXA16& matWorld);
	void Render();
	void RenderInAnimateObject(ST_BONE* pBone = NULL);
	// �ִϸ��̼��� ����. index = �ٲ� �ִϸ��̼ǹ�ȣ, fIntervalRate = �����ð� (��ü�ִϸ��̼� ������)
	void SwitchAnimationBlend(int nIndex, float fSpeed = 1.f, float fIntervalRate = 0.09f);
	void SetAnimationTrack(int n){ m_currentAnimTrack = n; }


	ST_BONE* GetRootBone() { return m_pRootFrame; }
	float GetTrackRate() { return m_TrackRate;}
	D3DXMATRIXA16* SearchMat(string NodeName);

	// ��Ʈ �ڽ� ���̺�/�ε�
	void CreateHitBox(OUT map<string, ST_COLLISION_BOX_STICK>& mapHitBox, ST_BONE* pBone);
	void ConnectHitBox(IN OUT map<string, ST_COLLISION_BOX_STICK>& mapHitBox, ST_BONE* pBone);
	void ConnectHitBox(IN vector<string>& vecBoxName,IN OUT vector<ST_COLLISION_BOX_STICK>& mapHitBox, ST_BONE* pBone);

	void SetAnimaionSpeed(float fAnispeed);
private:
	LPD3DXEFFECT LoadEffect(char* szFileName);
	void Update(ST_BONE* pBone, const D3DXMATRIXA16& matParent);
	void Render(ST_BONE* pBone);
	void RenderBad(ST_BONE* pBone);
	void SetupBoneMatrixPtrs(LPD3DXFRAME pFrame);
	void UpdateSkinnedMesh(LPD3DXFRAME pFrame);
	void TestUpdate(ST_BONE* pBone, const D3DXMATRIXA16& matParent);
	void AnimationChangeBlend();


	// �������� Ȯ�ο�
	void ShowHierarchy(const LPD3DXFRAME pFrame, int nLayer = 0);

	void SaveNameMat(LPD3DXFRAME pFrame = NULL);

};

