#include "stdafx.h"
#include "cInput.h"


cInput::cInput()
	: m_nMouseWheel(0), m_aInputKey()
{
}


cInput::~cInput()
{
}


void cInput::Update()
{
	if (m_nMouseWheel)
		m_nMouseWheel += (m_nMouseWheel > 0 ? -15 : 15);

	if (m_nMouseWheel > 480) m_nMouseWheel = 480;
	if (m_nMouseWheel < -480) m_nMouseWheel = -480;

	m_ptMouseInterval.x = m_ptMouse.x - m_ptMouseBefore.x;
	m_ptMouseInterval.y = m_ptMouse.y - m_ptMouseBefore.y;
	m_ptMouseBefore = m_ptMouse;
}