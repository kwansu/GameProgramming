#include "StdAfx.h"
#include "cMtlTex.h"

cMtlTex::cMtlTex(void)
	: m_pTexture(NULL)
	, m_nMtlRef(0)
{
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
}


cMtlTex::~cMtlTex(void)
{

}
