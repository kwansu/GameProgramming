#include "stdafx.h"
#include "stdObjects.h"
#include "cChildObject.h"


cChildObject::cChildObject(cMatrixA* pParentWorld)
	: m_pChildObject(NULL), m_pMatParentWorld(pParentWorld)
{
	D3DXMatrixIdentity(&m_matPos);
}


cChildObject::~cChildObject()
{
	SAFE_DELETE(m_pChildObject);
}


void cChildObject::Setup()
{
	if (m_pChildObject)
		m_pChildObject->Setup();
}


void cChildObject::Update()
{
	if (m_pChildObject)
		m_pChildObject->Update();
}


void cChildObject::Render()
{
	m_matWorld = m_matPos;

	if (m_pMatParentWorld)
		m_matWorld *= *m_pMatParentWorld;

	m_pChildObject->SetWorldMatrix(&m_matWorld);
	m_pChildObject->Render();
}
