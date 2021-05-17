#pragma once

struct stParticle
{
	D3DXVECTOR3*	m_vecpParticle;

	float			m_fSpeed;				// �ӵ�
	float			m_fDeCreaseSpeed;		// ���ӷ�

	bool			m_bLife;				// ����
	float			m_fLifeCount;			// ���� ����ð�.
	float			m_fRemainCount;			// ���� ����ð�.

	float			m_fGravity;				// �߷�

	D3DXVECTOR3		m_vecPrevPos;


};



class cSparkParticle
{
private:
	D3DXMATRIXA16						m_matWorld;
	vector<stParticle*>					m_vStParticle;
	vector<stParticle*>::iterator		m_viStParticle;
	vector<ST_PC_VERTEX>				m_vParticle;
	vector<ST_PC_VERTEX>::iterator		m_viParticle;

public:
	cSparkParticle();
	~cSparkParticle();

	void Setup();
	void Render();
	void Update();
};


