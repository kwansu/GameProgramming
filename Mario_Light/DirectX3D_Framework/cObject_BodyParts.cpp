#include "stdafx.h"
#include "cObject_BodyParts.h"


cObject_BodyParts::cObject_BodyParts()
{
	cObject_Cube* pCube = new cObject_Cube;
	cMatrixA matLocal;

	D3DXMatrixTranslation(&matLocal, 0, 1, 0);
	matLocal = m_matScale * matLocal;

	m_childCube.Setup(pCube, &m_matWolrd, &m_matRot, matLocal);
}


cObject_BodyParts::~cObject_BodyParts()
{
}


void cObject_BodyParts::Setup()
{
}


void cObject_BodyParts::Update()
{
	m_childCube.Update();
}


void cObject_BodyParts::Render()
{
	m_childCube.Render();
}
