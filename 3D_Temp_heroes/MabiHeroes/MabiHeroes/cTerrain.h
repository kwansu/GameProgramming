#pragma once

// 임시형 지형. 현재 스키닝 매쉬로 x파일을 불러오느중.
// 나중에 구조 개선 바람
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

