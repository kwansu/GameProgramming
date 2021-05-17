#include "StdAfx.h"
#include "cParticle.h"


cParticle::cParticle(void)
	: m_pVertex(NULL)
	, m_isRepeat(false)
	, m_isActive(false)
	, m_fLifeSpan(0.0f)
	, m_dwStartColor(D3DCOLOR_ARGB(0, 0, 0 ,0))
	, m_dwFinishColor(D3DCOLOR_ARGB(0, 0, 0 ,0))
{
}

cParticle::~cParticle(void)
{
}

void cParticle::Update()
{

}
