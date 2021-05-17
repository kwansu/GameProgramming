#include "stdafx.h"
#include "cDummyBox.h"


cDummyBox::cDummyBox()
{
}


cDummyBox::~cDummyBox()
{
}

void cDummyBox::Setup()
{
	m_stColl.pmatSticking = &m_matWorld;
}

void cDummyBox::Render()
{
	g_pCollisionRender->RenderBox(m_stColl);
}
