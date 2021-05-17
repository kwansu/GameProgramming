#pragma once
class cParticle
{
private:
	ST_PC_VERTEX* m_pVertex;		// 버텍스
	bool		m_isRepeat;			// 반복여부
	bool		m_isActive;			// 활성화 됬나
	float		m_fLifeSpan;		// 수명
	D3DCOLOR	m_dwStartColor;		// 시작 색
	D3DCOLOR	m_dwFinishColor;	// 끝   색

public:
	cParticle(void);
	~cParticle(void);

	void Update();

	ST_PC_VERTEX* GetVertex() { return m_pVertex; }
	void SetVertex(ST_PC_VERTEX* pVertex) { m_pVertex = pVertex; }
};

