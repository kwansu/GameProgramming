#pragma once

struct stParticle
{
	D3DXVECTOR3*	m_vecpParticle;

	float			m_fSpeed;				// 속도
	float			m_fDeCreaseSpeed;		// 감속력

	bool			m_bLife;				// 생명
	float			m_fLifeCount;			// 남은 생명시간.
	float			m_fRemainCount;			// 남은 생명시간.

	float			m_fGravity;				// 중력

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


