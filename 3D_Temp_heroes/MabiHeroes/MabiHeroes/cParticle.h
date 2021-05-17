#pragma once
class cParticle
{
private:
	ST_PC_VERTEX* m_pVertex;		// ���ؽ�
	bool		m_isRepeat;			// �ݺ�����
	bool		m_isActive;			// Ȱ��ȭ �糪
	float		m_fLifeSpan;		// ����
	D3DCOLOR	m_dwStartColor;		// ���� ��
	D3DCOLOR	m_dwFinishColor;	// ��   ��

public:
	cParticle(void);
	~cParticle(void);

	void Update();

	ST_PC_VERTEX* GetVertex() { return m_pVertex; }
	void SetVertex(ST_PC_VERTEX* pVertex) { m_pVertex = pVertex; }
};

