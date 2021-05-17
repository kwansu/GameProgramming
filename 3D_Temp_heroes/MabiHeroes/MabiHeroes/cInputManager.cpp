#include "stdafx.h"
#include "cInputManager.h"


cInputManager* g_pInput = cInputManager::GetInstance();

cInputManager::cInputManager()
	: m_arrbInputKey()
	, m_arrbInputKeyBefore()
	, m_nMouseWheel(0)
	, m_pProcessor(NULL)
{
}


cInputManager::~cInputManager()
{
}

void cInputManager::Update()
{
	if (IsKeyDown(VK_RETURN))
	{
		ShowCursor(m_isHideMouse);
		m_isHideMouse = m_isHideMouse ? false : true;
		GetClientRect(g_hWnd, &m_rtClinet);
		InflateRect(&m_rtClinet, -20, -20);
	}

	memcpy(&m_arrbInputKeyBefore, m_arrbInputKey, sizeof(m_arrbInputKey));

	if (m_nMouseWheel)
	{
		m_nMouseWheel *= 0.9f;
		if (abs(m_nMouseWheel) < 10)
			m_nMouseWheel = 0;
	}

	GetCursorPos(&m_ptMousePos);
	ScreenToClient(g_hWnd, &m_ptMousePos);

	m_ptMousePosInterval.x = m_ptMousePos.x - m_ptMousePosBefore.x;
	m_ptMousePosInterval.y = m_ptMousePos.y - m_ptMousePosBefore.y;

	if (m_isHideMouse && !PtInRect(&m_rtClinet, m_ptMousePos))
	{
		m_ptMousePos.x = m_rtClinet.left + m_rtClinet.right * 0.5;
		m_ptMousePos.y = m_rtClinet.top + m_rtClinet.bottom * 0.5;
		m_ptMousePosBefore = m_ptMousePos;
		ClientToScreen(g_hWnd, &m_ptMousePos);
		SetCursorPos(m_ptMousePos.x, m_ptMousePos.y);
		return;
	}

	m_ptMousePosBefore = m_ptMousePos;
}

void cInputManager::SetProcessor(iInputProcessor * pProcessor)
{
	m_pProcessor = pProcessor;
}
