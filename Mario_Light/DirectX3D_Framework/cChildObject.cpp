#include "stdafx.h"
#include "cChildObject.h"


cChildObject::cChildObject()
:m_pChild(NULL), m_pmatParentT(NULL), m_pmatParentR(NULL)
{
	D3DXMatrixIdentity(&m_matLocal);
}


cChildObject::~cChildObject()
{
	SAFE_DELETE(m_pChild);
}


void cChildObject::Setup(cObject* pChild, cMatrixA* pmatParentT,
	cMatrixA* pmatParentR, cMatrixA& matLocal)
{
	m_pChild = pChild;
	m_pmatParentT = pmatParentT;
	m_pmatParentR = pmatParentR;
	m_matLocal = matLocal;
}


void cChildObject::Update()
{
	if (m_pChild)
		m_pChild->Update();
}


void cChildObject::Render()
{
	if (!m_pChild)
		return;

	cMatrixA matTmp = m_matLocal;
	matTmp *= *m_pmatParentR * *m_pmatParentT;
	
	m_pChild->UpdateWorld(&matTmp);
	m_pChild->Render();
}


cObject* cChildObject::GetChildObject()
{
	return m_pChild;
}
