#pragma once

// �ӽ��� ����. ���� ��Ű�� �Ž��� x������ �ҷ�������.
// ���߿� ���� ���� �ٶ�
class cTerrain
{
private:
	cSkinnedMesh*	m_pMesh;

public:
	cTerrain();
	~cTerrain();

	void Setup();
	void Render();
};

