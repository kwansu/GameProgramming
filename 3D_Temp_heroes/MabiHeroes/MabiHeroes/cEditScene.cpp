#include "stdafx.h"
#include "cEditScene.h"


cEditScene::cEditScene()
	: m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pPickedObject(NULL)
	, m_pPickedHitBox(NULL)
	, m_pPickedStructure(NULL)
	, m_pLocalEditor(NULL)
	, m_eCurrentMode(SELECT_OBJECT)
	, m_isRotateMode(false)
	, m_isDrag(false)
	, m_isDebugRender(false)
	, m_nStructureIndex(10000)
	, m_pLastPickedHitBox(NULL)
	, m_pLastPickedStructure(NULL)
	, m_hbIndex(0)
{


}


cEditScene::~cEditScene()
{
}

void cEditScene::Setup()
{
	g_pCamera->SetTarget(NULL);

	m_pGrid = new cGrid;
	m_pGrid->Setup(100, 1);

	m_pLocalEditor = new cLocalEditor;
	m_pLocalEditor->Setup();

	cObj_Fiona* pFiona = new cObj_Fiona;
	pFiona->Setup();
	pFiona->CreateAllHitBox();
	m_vecpCreature.push_back(pFiona);

	cNoll* pCreature = new cNoll;
	pCreature->Setup();
	pCreature->SetPosition(100, 0, 0);
	pCreature->SetTarget(&pFiona->m_vPos);
	pCreature->CreateAllHitBox();
	m_vecpCreature.push_back(pCreature);

	cLavasat* pLavasat = new cLavasat;
	pLavasat->Setup();
	pLavasat->CreateAllHitBox();
	pLavasat->SetPosition(-100, 0, -100);
	pLavasat->SetPysicsState(true);
	m_vecpCreature.push_back(pLavasat);

	// delta time zero
	g_pTimeManager->Update();
	g_pTimeManager->Update();
}

void cEditScene::Release()
{
	SafeDelete(m_pCamera);
	SafeDelete(m_pGrid);
	SafeDelete(m_pLocalEditor);

	for (int i = 0; i < m_vecpCreature.size(); ++i)
	{
		SafeDelete(m_vecpCreature[i]);
	}
}

void cEditScene::Update()
{
	g_pCamera->Update();
	g_pCamera->MousePickingRay(&m_rayMouse);
	m_pLocalEditor->Update(m_rayMouse.vOri);

	for each(const auto& pCreature in m_vecpCreature)
	{
		pCreature->DebugRender();
	}

	if (g_pInput->IsKeyDown('Z'))
		m_eCurrentMode = SELECT_OBJECT;

	if (g_pInput->IsKeyDown('Q'))
	{
		LoadData();
	}

	if (g_pInput->IsKeyDown('N'))
		SelectStructure(--m_nStructureIndex % CS_NUM_TYPE);

	if (g_pInput->IsKeyDown('M'))
		SelectStructure(++m_nStructureIndex  % CS_NUM_TYPE);

	if (g_pInput->IsKeyDown('V'))
		m_isDebugRender = m_isDebugRender ? false : true;

	if (g_pInput->IsKeyDown('R'))
		m_isRotateMode = true;

	if (g_pInput->IsKeyDown('T'))
		m_isRotateMode = false;

	if (g_pInput->IsKeyDown('1'))
	{
		if (m_pPickedStructure)
		{
			m_hbIndex--;
			if (m_hbIndex < 0) m_hbIndex = m_pPickedStructure->m_vecCollisionBox.size() - 1;

			m_pPickedHitBox = &m_pPickedStructure->m_vecCollisionBox[m_hbIndex];
		}

	}
	if (g_pInput->IsKeyDown('2'))
	{
		if (m_pPickedStructure)
		{
			m_hbIndex++;
			if (m_hbIndex > m_pPickedStructure->m_vecCollisionBox.size() - 1) m_hbIndex = 0;

			m_pPickedHitBox = &m_pPickedStructure->m_vecCollisionBox[m_hbIndex];
		}

	}

	if (g_pInput->IsKeyDown('3'))
	{
		if (m_pPickedStructure)
		{
			m_pPickedHitBox = &m_pPickedStructure->m_vecCollisionBox.back();
		}

	}





	if (m_eCurrentMode == COLLOCATE_STRUCTURE)
	{
		D3DXVECTOR3 vNewPos;

		if (RayPickPointFromPlane(vNewPos))
		{
			m_pPickedStructure->m_vPos = vNewPos;
			m_pPickedStructure->Update();
		}

		if (g_pInput->IsKeyDown(VK_LBUTTON))
			m_eCurrentMode = SELECT_OBJECT;
	}

	if (g_pInput->IsKeyDown(VK_LBUTTON))
	{
		if (m_eCurrentMode == COLLOCATE_STRUCTURE)
		{
			m_eCurrentMode = SELECT_OBJECT;
		}
		else
		{
			if (m_isRotateMode)
			{
				if (m_pLocalEditor->IsPickRotate(m_vTransformDir, m_rayMouse))
				{
					m_eCurrentMode = TRANSFORM_ROTATION;
				}
				else
					PickObject();
			}
			else
			{
				if (!SelectTransAixs())
					PickObject();
			}
		}
	}

	if (g_pInput->IsKeyUp(VK_LBUTTON))
	{
		m_eCurrentMode = SELECT_OBJECT;
		m_isDrag = false;
	}

	if (g_pInput->IsKeyDown('E'))
		DeleteObject();


	if (g_pKeyManager->IsOnceKeyDown(VK_F7))
		SaveData();

	if (g_pInput->IsKeyPress(VK_CONTROL))
	{

		if (g_pKeyManager->IsOnceKeyDown('L'))
		{
			LoadStructures();
			for each(const auto& pStructure in m_vecpStructure)
			{
				pStructure->Update();
			}
		}
		if (g_pKeyManager->IsOnceKeyDown(VK_F10))
		{
			m_vecpStructure[0]->CreateCollisionBox(&m_vecpStructure[0]->m_matWorld);
		}
		if (g_pKeyManager->IsOnceKeyDown(VK_F11))
		{
			m_vecpStructure[0]->CreateCollisionBox2(&m_vecpStructure[0]->m_matWorld, &m_vecpStructure[0]->m_vecCollisionBox.back().matOffset);
		}
		if (g_pKeyManager->IsOnceKeyDown(VK_F12))
		{
			m_vecpStructure[0]->CloneCollisionBox(&m_vecpStructure[0]->m_matWorld, &m_vecpStructure[0]->m_vecCollisionBox.back().matOffset, m_vecpStructure[0]->m_vecCollisionBox.back().vHalfSize);
		}

		if (g_pInput->IsKeyPress(VK_UP))
		{
			if (m_pPickedHitBox)
			{
				m_pPickedHitBox->matOffset._43 += 1.5;
			}
		}
		if (g_pInput->IsKeyPress(VK_DOWN))
		{
			if (m_pPickedHitBox)
			{
				m_pPickedHitBox->matOffset._43 -= 1.5;
			}
		}

		if (g_pInput->IsKeyPress(VK_LEFT))
		{
			if (m_pPickedHitBox)
			{
				m_pPickedHitBox->matOffset._41 -= 1.5;
			}
		}
		if (g_pInput->IsKeyPress(VK_RIGHT))
		{
			if (m_pPickedHitBox)
			{
				m_pPickedHitBox->matOffset._41 += 1.5;
			}
		}

		if (g_pInput->IsKeyPress('9'))
		{
			if (m_pPickedHitBox)
			{
				m_pPickedHitBox->matOffset._42 -= 1.5;
			}
		}
		if (g_pInput->IsKeyPress('0'))
		{
			if (m_pPickedHitBox)
			{
				m_pPickedHitBox->matOffset._42 += 1.5;
			}
		}



		if (g_pInput->IsKeyPress('6'))
		{
			if (m_pPickedHitBox)
			{
				D3DXMATRIXA16	matR;
				D3DXMatrixRotationX(&matR, D3DXToRadian(0.5));
				m_pPickedHitBox->matOffset = matR * m_pPickedHitBox->matOffset;
			}
		}
		if (g_pInput->IsKeyPress('7'))
		{
			if (m_pPickedHitBox)
			{
				D3DXMATRIXA16	matR;
				D3DXMatrixRotationY(&matR, D3DXToRadian(0.5));
				m_pPickedHitBox->matOffset = matR * m_pPickedHitBox->matOffset;

			}
		}
		if (g_pInput->IsKeyPress('8'))
		{
			if (m_pPickedHitBox)
			{
				D3DXMATRIXA16	matR;
				D3DXMatrixRotationZ(&matR, D3DXToRadian(0.5));
				m_pPickedHitBox->matOffset = matR * m_pPickedHitBox->matOffset;

			}
		}

		if (g_pInput->IsKeyDown('E') && m_pPickedStructure)
		{
			m_pPickedStructure->m_vecCollisionBox.pop_back();
		}

	}

	if (g_pInput->IsKeyPress(VK_SHIFT))
	{
		if (g_pInput->IsKeyPress(VK_UP))
		{
			if (m_pPickedHitBox)
			{
				m_pPickedHitBox->vHalfSize.z += 1.5;
			}
		}
		if (g_pInput->IsKeyPress(VK_DOWN))
		{
			if (m_pPickedHitBox)
			{
				m_pPickedHitBox->vHalfSize.z -= 1.5;
			}
		}

		if (g_pInput->IsKeyPress(VK_LEFT))
		{
			if (m_pPickedHitBox)
			{
				m_pPickedHitBox->vHalfSize.x -= 1.5;
			}
		}
		if (g_pInput->IsKeyPress(VK_RIGHT))
		{
			if (m_pPickedHitBox)
			{
				m_pPickedHitBox->vHalfSize.x += 1.5;
			}
		}


		if (g_pInput->IsKeyPress('9'))
		{
			if (m_pPickedHitBox)
			{
				m_pPickedHitBox->vHalfSize.y -= 1.5;
			}
		}
		if (g_pInput->IsKeyPress('0'))
		{
			if (m_pPickedHitBox)
			{
				m_pPickedHitBox->vHalfSize.y += 1.5;
			}
		}


		if (g_pInput->IsKeyPress('6'))
		{

			if (m_pPickedHitBox)
			{
				D3DXMATRIXA16	matR;
				D3DXMatrixRotationX(&matR, D3DXToRadian(-0.5));
				m_pPickedHitBox->matOffset = matR * m_pPickedHitBox->matOffset;
			}
		}
		if (g_pInput->IsKeyPress('7'))
		{
			if (m_pPickedHitBox)
			{
				D3DXMATRIXA16	matR;
				D3DXMatrixRotationY(&matR, D3DXToRadian(-0.5));
				m_pPickedHitBox->matOffset = matR * m_pPickedHitBox->matOffset;

			}
		}
		if (g_pInput->IsKeyPress('8'))
		{
			if (m_pPickedHitBox)
			{
				D3DXMATRIXA16	matR;
				D3DXMatrixRotationZ(&matR, D3DXToRadian(-0.5));
				m_pPickedHitBox->matOffset = matR * m_pPickedHitBox->matOffset;

			}
		}
	}


	DragObject();

	g_pInput->Update();
}

void cEditScene::Render()
{
	m_pGrid->Render();

	for each(const auto& pStructure in m_vecpStructure)
	{
		if (m_eCurrentMode == COLLOCATE_STRUCTURE && pStructure == m_pPickedStructure)
		{
			g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 1);
			g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			pStructure->Render();

			g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 1);
			g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		}
		else
		{

			g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 1);
			g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			pStructure->Render();

			g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 1);
			g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		}
	}

	if (m_isDebugRender)
	{
		for each(const auto& pCreature in m_vecpCreature)
		{
			pCreature->RenderHitBox();
		}

		for each(const auto& pStructure in m_vecpStructure)
		{
			pStructure->RenderCollisionBox();
		}
	}

	for each(const auto& pCreature in m_vecpCreature)
	{
		if (pCreature == m_pPickedObject)
		{
			//g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			//g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 1);
			//g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			pCreature->Render();

			//g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			//g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 1);
			//g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		}
		else
		{
			pCreature->Render();
		}
	}

	if (m_pPickedObject)
	{
		D3DXCOLOR color(0, 1.f, 0, 1);
		m_pPickedObject->RenderHitBox(&color);
	}

	if (m_pPickedHitBox)
	{
		g_pCollisionRender->RenderBox(*m_pPickedHitBox, &D3DXCOLOR(0.5f, 0, 0, 1));
	}

	if (m_pPickedStructure || m_pPickedObject)
	{
		if (m_isRotateMode)
			m_pLocalEditor->RenderRotate();
		else
			m_pLocalEditor->Render();
	}
}

void cEditScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		g_pInput->KeyDown(wParam);
		break;
	case WM_KEYUP:
		g_pInput->KeyUp(wParam);
		break;
	case WM_LBUTTONDOWN:
		g_pInput->KeyDown(VK_LBUTTON);
		//SetCapture(g_hWnd);
		break;
	case WM_LBUTTONUP:
		g_pInput->KeyUp(VK_LBUTTON);
		ReleaseCapture();
		break;
	case WM_RBUTTONDOWN:
		g_pInput->KeyDown(VK_RBUTTON);
		//SetCapture(g_hWnd);
		break;
	case WM_RBUTTONUP:
		g_pInput->KeyUp(VK_RBUTTON);
		ReleaseCapture();
		break;
	case WM_MOUSEWHEEL:
		g_pInput->AddWheel(HIWORD(wParam));
		break;
	}
}

void cEditScene::PickObject()
{
	if (m_pPickedObject)
	{
		auto end = m_pPickedObject->m_mapHitBox.end();
		for (auto iter = m_pPickedObject->m_mapHitBox.begin(); iter != end; ++iter)
		{
			if (IsPickHitBox(iter->second))
			{
				m_pPickedHitBox = &iter->second;

				m_vPickOffset.x = m_pPickedHitBox->pmatSticking->_41;
				m_vPickOffset.y = m_pPickedHitBox->pmatSticking->_42;
				m_vPickOffset.z = m_pPickedHitBox->pmatSticking->_43;

				D3DXMATRIXA16 matS;
				D3DXMatrixScaling(&matS, 5, 5, 5);
				m_pLocalEditor->SetTarget(m_pPickedHitBox->pmatSticking, m_pPickedHitBox->pmatSticking, &matS);
				return;
			}
		}
	}
	else if (m_pPickedStructure)
	{
		auto end = m_pPickedStructure->m_vecCollisionBox.end();
		for (auto iter = m_pPickedStructure->m_vecCollisionBox.begin(); iter != end; ++iter)
		{
			if (IsPickHitBox(*iter))
			{
				m_pPickedHitBox = &(*iter);

				m_vPickOffset.x = m_pPickedHitBox->pmatSticking->_41;
				m_vPickOffset.y = m_pPickedHitBox->pmatSticking->_42;
				m_vPickOffset.z = m_pPickedHitBox->pmatSticking->_43;

				D3DXMATRIXA16 matS;
				D3DXMatrixInverse(&matS, NULL, &m_pPickedStructure->m_matS);
				m_pLocalEditor->SetTarget(m_pPickedHitBox->pmatSticking, m_pPickedHitBox->pmatSticking, &matS);
				return;
			}
		}
	}

	m_pPickedHitBox = NULL;

	for each(const auto& pCreature in m_vecpCreature)
	{
		if (IsPickCreature(pCreature))
		{
			m_pPickedStructure = NULL;
			m_pPickedObject = pCreature;
			m_vPickOffset = m_pPickedObject->m_vPos;
			m_pLocalEditor->SetTarget(&m_pPickedObject->m_matT, &m_pPickedObject->m_matR);
			return;
		}
	}

	for each(const auto& pStructure in m_vecpStructure)
	{
		for each(const auto& coll in pStructure->m_vecCollisionBox)
		{
			if (IsPickHitBox(coll))
			{
				m_pPickedObject = NULL;

				if (m_pPickedStructure)
				{
					m_pLastPickedStructure = m_pPickedStructure;
					m_pLastPickedStructure->m_vecCollisionBox.back();
				}
				m_pPickedStructure = pStructure;
				m_vPickOffset = m_pPickedStructure->m_vPos;

				m_pLocalEditor->SetTarget(&m_pPickedStructure->m_matT, &m_pPickedStructure->m_matR);
				return;
			}
		}
	}

	if (m_pPickedObject)
	{
		m_vPickOffset = m_pPickedObject->m_vPos;
		m_pLocalEditor->SetTarget(&m_pPickedObject->m_matT, &m_pPickedObject->m_matR);
	}
	else if (m_pPickedStructure)
	{
		m_vPickOffset = m_pPickedStructure->m_vPos;
		m_pLocalEditor->SetTarget(&m_pPickedStructure->m_matT, &m_pPickedStructure->m_matR);
	}
}

bool cEditScene::SelectTransAixs()
{
	DWORD dwPick = m_pLocalEditor->IsPickPyramid(m_rayMouse);

	if (dwPick != 0)
	{
		m_vTransformDir = D3DXVECTOR3(0, 0, 0);

		if (dwPick & eTRANSLATE_STATE::FRONT)
			m_vTransformDir.z = 1;

		if (dwPick & eTRANSLATE_STATE::UP)
			m_vTransformDir.y = 1;

		if (dwPick & eTRANSLATE_STATE::RIGHT)
			m_vTransformDir.x = 1;

		m_eCurrentMode = TRANSFORM_SIZE;
		return true;
	}

	if (m_pLocalEditor->IsPickPlane(m_pnPickPlane, m_rayMouse))
	{
		m_eCurrentMode = TRANSFORM_POSITION;
		RayPickPointFromPlane(m_vPickOffset);

		if (m_pPickedHitBox)
		{
			m_vPickOffset.x = m_pPickedHitBox->pmatSticking->_41;
			m_vPickOffset.y = m_pPickedHitBox->pmatSticking->_42;
			m_vPickOffset.z = m_pPickedHitBox->pmatSticking->_43;

			m_vPickOffset2.x = m_pPickedHitBox->matOffset._41;
			m_vPickOffset2.y = m_pPickedHitBox->matOffset._42;
			m_vPickOffset2.z = m_pPickedHitBox->matOffset._43;
		}
		else if (m_pPickedStructure)
		{
			m_vPickOffset.x -= m_pPickedStructure->m_vPos.x;
			m_vPickOffset.y -= m_pPickedStructure->m_vPos.y;
			m_vPickOffset.z -= m_pPickedStructure->m_vPos.z;
		}
		else if (m_pPickedObject)
		{
			m_vPickOffset.x -= m_pPickedObject->m_vPos.x;
			m_vPickOffset.y -= m_pPickedObject->m_vPos.y;
			m_vPickOffset.z -= m_pPickedObject->m_vPos.z;
		}

		m_isDrag = true;
		return true;
	}

	return false;
}

void cEditScene::SelectStructure(int nIndex)
{
	m_pPickedObject = NULL;
	m_pPickedHitBox = NULL;

	if (m_eCurrentMode == COLLOCATE_STRUCTURE)
	{
		m_vecpStructure.pop_back();
	}

	cStructure* pStructure = NULL;

	switch (nIndex)
	{
	case 0:		pStructure = CREATE_STRUCTURE(0);	break;

	}

	if (pStructure)
	{
		pStructure->Setup();
		if (m_pPickedStructure)
		{
			m_pLastPickedStructure = m_pPickedStructure;
			m_pLastPickedStructure->m_vecCollisionBox.back();
		}
		m_pPickedStructure = pStructure;
		m_vecpStructure.push_back(pStructure);
		m_eCurrentMode = COLLOCATE_STRUCTURE;

		m_pnPickPlane.vNormal = D3DXVECTOR3(0, 1, 0);
		m_pnPickPlane.vOther = D3DXVECTOR3(0, 0, 0);
	}
}

void cEditScene::DeleteObject()
{
	if (m_pPickedHitBox)
	{
		if (m_pPickedObject)
		{
			auto& mapHitBox = m_pPickedObject->m_mapHitBox;

			for (auto iter = mapHitBox.begin(); iter != mapHitBox.end(); ++iter)
			{
				if (&(iter->second) == m_pPickedHitBox)
				{
					mapHitBox.erase(iter);
					m_pPickedHitBox = NULL;
					return;
				}
			}
		}
		else
		{
			auto& vecColl = m_pPickedStructure->m_vecCollisionBox;
		}
	}
	else if (m_pPickedStructure)
	{
		auto end = m_vecpStructure.end();
		for (auto iter = m_vecpStructure.begin(); iter != end; ++iter)
		{
			if (*iter == m_pPickedStructure)
			{
				m_vecpStructure.erase(iter);
				m_pPickedStructure = NULL;
				return;
			}
		}
	}
}

void cEditScene::DragObject()
{
	switch (m_eCurrentMode)
	{
	case TRANSFORM_POSITION:
		ObjectTranslate();
		break;
	case TRANSFORM_SIZE:
		ObjectScaling();
		break;
	case TRANSFORM_ROTATION:
		ObjectRotation();
		break;
	}
}

void cEditScene::ObjectTranslate()
{
	D3DXVECTOR3 vNewPos;

	if (RayPickPointFromPlane(vNewPos))
	{
		if (m_pPickedHitBox)
		{
			D3DXVECTOR3 vPos = vNewPos - m_vPickOffset;

			D3DXVECTOR3 vAxis;
			D3DXVec3TransformNormal(&vAxis, &D3DXVECTOR3(1, 0, 0), m_pPickedHitBox->pmatSticking);
			D3DXVec3Normalize(&vAxis, &vAxis);
			m_pPickedHitBox->matOffset._41 = D3DXVec3Dot(&vPos, &vAxis) * 5 + m_vPickOffset2.x;

			D3DXVec3TransformNormal(&vAxis, &D3DXVECTOR3(0, 1, 0), m_pPickedHitBox->pmatSticking);
			D3DXVec3Normalize(&vAxis, &vAxis);
			m_pPickedHitBox->matOffset._42 = D3DXVec3Dot(&vPos, &vAxis) * 5 + m_vPickOffset2.y;

			D3DXVec3TransformNormal(&vAxis, &D3DXVECTOR3(0, 0, 1), m_pPickedHitBox->pmatSticking);
			D3DXVec3Normalize(&vAxis, &vAxis);
			m_pPickedHitBox->matOffset._43 = D3DXVec3Dot(&vPos, &vAxis) * 5 + m_vPickOffset2.z;
		}
		else if (m_pPickedObject)
		{
			m_pPickedObject->m_vPos = vNewPos - m_vPickOffset;
		}
		else if (m_pPickedStructure)
		{
			m_pPickedStructure->m_vPos = vNewPos - m_vPickOffset;
			m_pPickedStructure->Update();
		}
	}
}

void cEditScene::ObjectRotation()
{
	float t = g_pInput->GetMouseInterval().x;
	t += g_pInput->GetMouseInterval().y;

	if (m_pPickedHitBox)
	{
		D3DXMATRIXA16 matR;
		UpdateRotation(matR);
		m_pPickedHitBox->matOffset = matR * m_pPickedHitBox->matOffset;
	}

	else if (m_pPickedObject)
	{
		m_pPickedObject->m_vRot.x += t * m_vTransformDir.x;
		m_pPickedObject->m_vRot.y += t * m_vTransformDir.y;
		m_pPickedObject->m_vRot.z += t * m_vTransformDir.z;
	}

	else if (m_pPickedStructure)
	{
		m_pPickedStructure->m_vRot.x += t * m_vTransformDir.x;
		m_pPickedStructure->m_vRot.y += t * m_vTransformDir.y;
		m_pPickedStructure->m_vRot.z += t * m_vTransformDir.z;
		m_pPickedStructure->Update();
	}
}

void cEditScene::ObjectScaling()
{
	float t = g_pInput->GetMouseInterval().x;
	t += g_pInput->GetMouseInterval().y;

	if (m_pPickedHitBox)
	{
		m_pPickedHitBox->vHalfSize += m_vTransformDir * t * 0.05f;
	}
	else if (m_pPickedStructure)
	{
		m_pPickedStructure->m_vScale += m_vTransformDir * t * 0.05f;
		m_pPickedStructure->Update();
	}
}

bool cEditScene::RayPickPointFromPlane(OUT D3DXVECTOR3 & vPickPos)
{
	float t = D3DXVec3Dot(&m_rayMouse.vDir, &m_pnPickPlane.vNormal);

	if (IsEqual(t, 0))
		return false;

	t = D3DXVec3Dot(&(m_pnPickPlane.vOther - m_rayMouse.vOri), &m_pnPickPlane.vNormal) / t;

	if (t < 0)
		return false;

	vPickPos = m_rayMouse.vOri + t * m_rayMouse.vDir;

	return true;
}

void cEditScene::SaveData()
{
	// 크리처 정보 저장
	ofstream outFile("./GameData/data.txt");

	if (!outFile.is_open())
		assert(false, "saveFile create failed");

	if (m_pPickedObject)
		SaveCreatureData(m_pPickedObject, outFile);
	/*for each(const auto& pCreature in m_vecpCreature)
	{
	SaveCreatureData(pCreature, outFile);
	}*/

	outFile.close();


	// 구조물 정보 저장



	ofstream outMapFile("./GameData/mapData2.txt");

	if (!outMapFile.is_open())
		assert(false, "saveFile create failed");

	for (int p = 0; p < m_vecpStructure.size(); p++)
	{
		m_vecpStructure[p]->SaveData(outMapFile);
	}
	//g_pIniData->AddData("TOTALNUM", "STRUCTURES", m_vecpStructure.size());


	outMapFile.close();
}

void cEditScene::LoadData()
{
	//if (m_pPickedObject)
	//{
	//	m_pPickedObject->LoadHitBox("./GameData/data.txt");
	//}

}


void cEditScene::LoadStructures()
{
	m_vecpStructure.clear();

	ifstream inFile("./GameData/mapData2.txt");

	if (!inFile.is_open())
		assert(false, "loadfile Unloaded");

	while (!inFile.eof())
	{

		cStructure * pStructure = NULL;
		int index;
		D3DXVECTOR3 Scale, Rot, Pos;
		int numColl;
		ST_COLLISION_BOX_STICK coll;

		inFile >> index;

		pStructure = new cMap;
		coll.pmatSticking = &pStructure->m_matWorld;

		inFile >> Scale.x;
		inFile >> Scale.y;
		inFile >> Scale.z;
		inFile >> Rot.x;
		inFile >> Rot.y;
		inFile >> Rot.z;
		inFile >> Pos.x;
		inFile >> Pos.y;
		inFile >> Pos.z;

		if (pStructure)
		{
			pStructure->Setup();

			pStructure->m_vScale.x = Scale.x;
			pStructure->m_vScale.y = Scale.y;
			pStructure->m_vScale.z = Scale.z;
			pStructure->m_vRot.x = Rot.x;
			pStructure->m_vRot.y = Rot.y;
			pStructure->m_vRot.z = Rot.z;
			pStructure->m_vPos.x = Pos.x;
			pStructure->m_vPos.y = Pos.y;
			pStructure->m_vPos.z = Pos.z;

			m_vecpStructure.push_back(pStructure);
		}

		inFile >> numColl;

		if (pStructure)
		{
			for (int p = 0; p < numColl; p++)
			{
				inFile >> coll.matOffset._11;
				inFile >> coll.matOffset._12;
				inFile >> coll.matOffset._13;
				inFile >> coll.matOffset._14;
				inFile >> coll.matOffset._21;
				inFile >> coll.matOffset._22;
				inFile >> coll.matOffset._23;
				inFile >> coll.matOffset._24;
				inFile >> coll.matOffset._31;
				inFile >> coll.matOffset._32;
				inFile >> coll.matOffset._33;
				inFile >> coll.matOffset._34;
				inFile >> coll.matOffset._41;
				inFile >> coll.matOffset._42;
				inFile >> coll.matOffset._43;
				inFile >> coll.matOffset._44;
				inFile >> coll.vHalfSize.x;
				inFile >> coll.vHalfSize.y;
				inFile >> coll.vHalfSize.z;

				m_vecpStructure[0]->m_vecCollisionBox.push_back(coll);
			}
		}

		break;
	}


	inFile.close();
}


void cEditScene::SaveCreatureData(const cCreature * pCreature, OUT ofstream& outFile)
{
	outFile << pCreature->m_mapHitBox.size();

	for each(const auto& hitBox in pCreature->m_mapHitBox)
	{
		outFile << hitBox.first << endl;
		outFile << hitBox.second.matOffset._41 << endl;
		outFile << hitBox.second.matOffset._42 << endl;
		outFile << hitBox.second.matOffset._43 << endl;
		outFile << hitBox.second.vHalfSize.x << endl;
		outFile << hitBox.second.vHalfSize.y << endl;
		outFile << hitBox.second.vHalfSize.z << endl;
	}
}

bool cEditScene::IsPickCreature(cCreature * pCreature)
{
	ST_SPHERE stColl(pCreature->GetBoundingSphere());

	D3DXVECTOR3 vDist = pCreature->m_vPos + stColl.vOffset - m_rayMouse.vOri;
	float t = D3DXVec3Dot(&vDist, &m_rayMouse.vDir);

	if (t < 0)
		return false;

	if (D3DXVec3LengthSq(&vDist) - t*t > stColl.fRadius * stColl.fRadius)
		return false;

	return true;
}

bool cEditScene::IsPickHitBox(const ST_COLLISION_BOX_STICK & stHitBox)
{
	D3DXVECTOR3 vDist, vAxis;
	D3DXMATRIXA16 mat = stHitBox.matOffset * *stHitBox.pmatSticking;
	vDist.x = mat._41;
	vDist.y = mat._42;
	vDist.z = mat._43;

	vDist -= m_rayMouse.vOri;

	float t = D3DXVec3Dot(&vDist, &m_rayMouse.vDir);

	if (t < 0) return false;

	vDist -= t * m_rayMouse.vDir;

	D3DXVec3TransformNormal(&vAxis, &D3DXVECTOR3(stHitBox.vHalfSize.x, 0, 0), &mat);
	float d = fabs(D3DXVec3Dot(&vDist, &vAxis));

	D3DXVec3TransformNormal(&vAxis, &D3DXVECTOR3(0, stHitBox.vHalfSize.y, 0), &mat);
	d += fabs(D3DXVec3Dot(&vDist, &vAxis));

	D3DXVec3TransformNormal(&vAxis, &D3DXVECTOR3(0, 0, stHitBox.vHalfSize.z), &mat);
	d += fabs(D3DXVec3Dot(&vDist, &vAxis));

	t = D3DXVec3LengthSq(&vDist);
	return (d * d > t * t);
}

void cEditScene::UpdateRotation(OUT D3DXMATRIXA16 & matR)
{
	D3DXMATRIXA16 matY, matZ;

	D3DXMatrixRotationX(&matR, m_vTransformDir.x);
	D3DXMatrixRotationX(&matY, m_vTransformDir.y);
	D3DXMatrixRotationX(&matZ, m_vTransformDir.z);

	matR *= matY * matZ;
}
