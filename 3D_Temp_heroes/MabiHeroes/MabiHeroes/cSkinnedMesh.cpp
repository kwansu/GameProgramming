#include "StdAfx.h"
#include "cSkinnedMesh.h"

cSkinnedMesh::cSkinnedMesh(void)
	: m_pRootFrame(NULL)
	, m_pAnimController(NULL)
	, m_fChangeMotiontime(0.f)
	, m_saveBeginTime(0.f)
	, m_currentAnimTrack(0)
	, m_TrackRate(-1.f)
	, m_pmWorkingPalette(NULL)
	, m_dwWorkingPaletteSize(0)
{
}


cSkinnedMesh::~cSkinnedMesh()
{
	cAllocateHierarchy alloc;
	D3DXFrameDestroy(m_pRootFrame, &alloc);
}

void cSkinnedMesh::Load(char* szFolder, char* szFile, OUT ST_SPHERE& stSphere)
{
	//m_pEffect = LoadEffect("MultiAnimation.hpp");
	//m_pEffect = LoadEffect("NormalMapping.fx");
	//m_pEffect = LoadEffect("MultiLight.hpp");

	//int nPaletteSize = 0;
	//m_pEffect->GetInt("MATRIX_PALETTE_SIZE", &nPaletteSize);

	cAllocateHierarchy alloc;
	
	alloc.SetFolder(szFolder);
	//alloc.SetPalettSize(nPaletteSize);

	std::string sFullPath = std::string(szFolder) +
		std::string(szFile);

	D3DXLoadMeshHierarchyFromX(
		sFullPath.c_str(),
		D3DXMESH_MANAGED,
		g_pD3DDevice,
		&alloc,
		NULL,
		(LPD3DXFRAME*)&m_pRootFrame,
		&m_pAnimController);

	assert(m_pRootFrame);

	if (m_pmWorkingPalette)
		delete[] m_pmWorkingPalette;

	m_dwWorkingPaletteSize = alloc.GetMaxPalettSize();
	m_pmWorkingPalette = new D3DXMATRIX[m_dwWorkingPaletteSize];
	if (m_pmWorkingPalette == NULL)
	{
		m_dwWorkingPaletteSize = 0;
	}

	stSphere = alloc.GetBoundSphere();

	SetupBoneMatrixPtrs(m_pRootFrame);
	//ShowHierarchy(m_pRootFrame);
	SaveNameMat();
}

void cSkinnedMesh::LoadNew(char * szFolder, char * szFile, OUT ST_SPHERE & stSphere)
{
	//m_pEffect = LoadEffect("MultiAnimation.hpp");
	//m_pEffect = LoadEffect("NormalMapping.fx");
	//m_pEffect = LoadEffect("MultiLight.hpp");

	//int nPaletteSize = 0;
	//m_pEffect->GetInt("MATRIX_PALETTE_SIZE", &nPaletteSize);

	cAllocateHierarchy alloc;
	alloc.m_isGereric = false;

	alloc.SetFolder(szFolder);
	//alloc.SetPalettSize(nPaletteSize);

	std::string sFullPath = std::string(szFolder) +
		std::string(szFile);

	D3DXLoadMeshHierarchyFromX(
		sFullPath.c_str(),
		D3DXMESH_MANAGED,
		g_pD3DDevice,
		&alloc,
		NULL,
		(LPD3DXFRAME*)&m_pRootFrame,
		&m_pAnimController);

	assert(m_pRootFrame);

	if (m_pmWorkingPalette)
		delete[] m_pmWorkingPalette;

	m_dwWorkingPaletteSize = alloc.GetMaxPalettSize();
	m_pmWorkingPalette = new D3DXMATRIX[m_dwWorkingPaletteSize];
	if (m_pmWorkingPalette == NULL)
	{
		m_dwWorkingPaletteSize = 0;
	}

	stSphere = alloc.GetBoundSphere();

	SetupBoneMatrixPtrs(m_pRootFrame);
	//ShowHierarchy(m_pRootFrame);
	SaveNameMat();
}

void cSkinnedMesh::Update(const D3DXMATRIXA16& matWorld)
{
	if (m_pAnimController)
	{
		if (m_fAnimationWeight < 1)
			AnimationChangeBlend();
		
		m_pAnimController->AdvanceTime(g_pTimeManager->GetDeltaTime() * fSTD_ADANCE_SPEED, NULL);
		
		float Postion;
		D3DXTRACK_DESC trackDesc;
		m_pAnimController->GetTrackDesc(0, &trackDesc);
		m_TrackRate = trackDesc.Position / m_TotalLenght;
	}

	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	Update(m_pRootFrame, mat);
	UpdateSkinnedMesh(m_pRootFrame);

	TestUpdate(m_pRootFrame, matWorld);
}
 
void cSkinnedMesh::Render()
{
	RenderBad(m_pRootFrame);
}

void cSkinnedMesh::RenderInAnimateObject(ST_BONE* pBone)
{
	if (!pBone)
		pBone = m_pRootFrame;

	ST_BONE_MESH* pBoneMesh = NULL;
	if(pBone && pBone->pMeshContainer)
	{
		pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
	}

	while (pBoneMesh)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &pBone->matCombinedTransformationMatrix);
		
		if(pBoneMesh->MeshData.pMesh)
		{
			LPD3DXMESH pMesh = pBoneMesh->MeshData.pMesh;
			DWORD dwNumAttr = 0;
			pMesh->GetAttributeTable(NULL, &dwNumAttr);
			for (size_t i = 0; i < dwNumAttr; ++i)
			{
				g_pD3DDevice->SetMaterial(&pBoneMesh->vecMtlTex[i]->m_stMtl);
				g_pD3DDevice->SetTexture(0, pBoneMesh->vecMtlTex[i]->GetTexture());
				pMesh->DrawSubset(i);
			}
		}

		pBoneMesh = (ST_BONE_MESH*)pBoneMesh->pNextMeshContainer;
	}
	
	if (pBone->pFrameFirstChild)
	{
		RenderInAnimateObject((ST_BONE*)pBone->pFrameFirstChild);
	}

	if (pBone->pFrameSibling)
	{
		RenderInAnimateObject((ST_BONE*)pBone->pFrameSibling);
	}
}

void cSkinnedMesh::Update(ST_BONE * pBone, const D3DXMATRIXA16& matParent)
{
	pBone->matCombinedTransformationMatrix = pBone->TransformationMatrix * matParent;

	if (pBone->pFrameSibling)
	{
		Update((ST_BONE*)pBone->pFrameSibling, matParent);
	}

	if (pBone->pFrameFirstChild)
	{
		Update((ST_BONE*)pBone->pFrameFirstChild, pBone->matCombinedTransformationMatrix);
	}
}

void cSkinnedMesh::Render(ST_BONE* pBone)
{
	//if (pBone->pMeshContainer)
	//{
	//	ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;

	//	// get bone combinations
	//	LPD3DXBONECOMBINATION pBoneCombos =
	//		(LPD3DXBONECOMBINATION)(pBoneMesh->pBufBoneCombos->GetBufferPointer());

	//	D3DXVECTOR3 vEye = g_pCamera->GetPosition();
	//	m_pEffect->SetMatrix("g_mViewProj", g_pCamera->GetViewProjection());
	//	//m_pEffect->SetVector("vLightDiffuse", &D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
	//	m_pEffect->SetVector("vWorldCameraPos", &D3DXVECTOR4(vEye, 1.0f));
	//	m_pEffect->SetTechnique("Skinning20");

	//	m_pEffect->SetVector("vMaterialAmbient", &D3DXVECTOR4(0.53f, 0.53f, 0.53f, 0.53f));
	//	m_pEffect->SetVector("vMaterialDiffuse", &D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));

	//	// for each palette
	//	for (DWORD dwAttrib = 0; dwAttrib < pBoneMesh->dwNumAttrGroups; ++dwAttrib)
	//	{
	//		// set each transform into the palette
	//		for (DWORD dwPalEntry = 0; dwPalEntry < pBoneMesh->dwNumPaletteEntries; ++dwPalEntry)
	//		{
	//			DWORD dwMatrixIndex = pBoneCombos[dwAttrib].BoneId[dwPalEntry];
	//			if (dwMatrixIndex != UINT_MAX)
	//			{
	//				m_pmWorkingPalette[dwPalEntry] =
	//					pBoneMesh->pBoneOffsetMatrices[dwMatrixIndex] *
	//					(*pBoneMesh->ppBoneMatrixPtrs[dwMatrixIndex]);
	//			}
	//		}

	//		// set the matrix palette into the effect
	//		m_pEffect->SetMatrixArray("amPalette",
	//			m_pmWorkingPalette,
	//			pBoneMesh->dwNumPaletteEntries);

	//		// we're pretty much ignoring the materials we got from the x-file; just set
	//		// the texture here
	//		if (pBoneMesh->vecNormalMap[pBoneCombos[dwAttrib].AttribId])
	//		{
	//			m_pEffect->SetTexture("Diffuse_tex",
	//				pBoneMesh->vecMtlTex[pBoneCombos[dwAttrib].AttribId]->GetTexture());
	//			m_pEffect->SetTexture("Normal_tex", pBoneMesh->vecNormalMap[pBoneCombos[dwAttrib].AttribId]);

	//			// set the current number of bones; this tells the effect which shader to use
	//			m_pEffect->SetInt("CurNumBones", pBoneMesh->dwMaxNumFaceInfls - 1);

	//			UINT uiPasses, uiPass;

	//			// run through each pass and draw
	//			m_pEffect->Begin(&uiPasses, 0);
	//			for (uiPass = 0; uiPass < uiPasses; ++uiPass)
	//			{
	//				m_pEffect->BeginPass(uiPass);
	//				pBoneMesh->pWorkingMesh->DrawSubset(dwAttrib);
	//				m_pEffect->EndPass();
	//			}
	//			m_pEffect->End();
	//		}
	//		else
	//		{
	//			g_pD3DDevice->SetTransform(D3DTS_WORLD, &pBone->matCombinedTransformationMatrix);

	//			LPD3DXMESH pMesh = pBoneMesh->MeshData.pMesh;
	//			DWORD dwNumAttr = 0;
	//			pMesh->GetAttributeTable(NULL, &dwNumAttr);
	//			for (size_t i = 0; i < dwNumAttr; ++i)
	//			{
	//				g_pD3DDevice->SetMaterial(&pBoneMesh->vecMtlTex[i]->m_stMtl);
	//				g_pD3DDevice->SetTexture(0, pBoneMesh->vecMtlTex[i]->GetTexture());
	//				pMesh->DrawSubset(i);
	//			}
	//		}
	//	}
	//}

	////재귀적으로 모든 프레임에 대해서 실행.
	//if (pBone->pFrameSibling)
	//{
	//	Render((ST_BONE*)pBone->pFrameSibling);
	//}

	//if (pBone->pFrameFirstChild)
	//{
	//	Render((ST_BONE*)pBone->pFrameFirstChild);
	//}
}

void cSkinnedMesh::RenderBad(ST_BONE * pBone)
{

	ST_BONE_MESH* pBoneMesh = NULL;
	if (pBone && pBone->pMeshContainer)
	{
		pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
	}

	while (pBoneMesh)
	{
		if (pBoneMesh->MeshData.pMesh)
		{
			g_pNormalEffect->SetMatrix("gWorldMatrix", &pBone->matCombinedTransformationMatrix);

			g_pNormalEffect->SetFloatArray("garrLightPos", g_pLightManager->GetActiveLightsPosArray(), 8);
			g_pNormalEffect->SetInt("nLightNum", g_pLightManager->GetActiveLightNum());
			g_pD3DDevice->SetFVF(pBoneMesh->MeshData.pMesh->GetFVF());

			LPD3DXMESH pMesh = pBoneMesh->MeshData.pMesh;
			DWORD dwNumAttr = 0;

			pMesh->GetAttributeTable(NULL, &dwNumAttr);
			for (size_t i = 0; i < dwNumAttr; ++i)
			{

				if (pBoneMesh->vecNormalMap[i])
				{
					g_pNormalEffect->SetTexture("DiffuseMap_Tex", pBoneMesh->vecMtlTex[i]->GetTexture());
					g_pNormalEffect->SetTexture("NormalMap_Tex", pBoneMesh->vecNormalMap[i]);

					UINT numPasses = 0;
					g_pNormalEffect->Begin(&numPasses, NULL);

					for (UINT j = 0; j < numPasses; ++j)
					{
						g_pNormalEffect->BeginPass(j);

						pMesh->DrawSubset(i);

						g_pNormalEffect->EndPass();
					}

					g_pNormalEffect->End();
				}
				else
				{
					//g_pDiffuseEffect->SetTexture("DiffuseMap_Tex", pBoneMesh->vecMtlTex[i]->GetTexture());

					//UINT numPasses = 0;
					//g_pDiffuseEffect->Begin(&numPasses, NULL);

					//for (UINT j = 0; j < numPasses; ++j)
					//{
					//	g_pDiffuseEffect->BeginPass(j);

					//	pMesh->DrawSubset(i);

					//	g_pDiffuseEffect->EndPass();
					//}

					//g_pDiffuseEffect->End();
					g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
					g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 1);
					g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
					g_pD3DDevice->SetTransform(D3DTS_WORLD, &pBone->matCombinedTransformationMatrix);

					g_pD3DDevice->SetMaterial(&pBoneMesh->vecMtlTex[i]->m_stMtl);
					g_pD3DDevice->SetTexture(0, pBoneMesh->vecMtlTex[i]->GetTexture());
					pBoneMesh->MeshData.pMesh->DrawSubset(i);
				}
			}
		}

		pBoneMesh = (ST_BONE_MESH*)pBoneMesh->pNextMeshContainer;
	}

	if (pBone->pFrameFirstChild)
	{	
		RenderBad((ST_BONE*)pBone->pFrameFirstChild);
	}

	if (pBone->pFrameSibling)
	{
		RenderBad((ST_BONE*)pBone->pFrameSibling);
	}
}

// 이 함수는 같은 애니메이션이 실행될 경우 다시 처음부터 재생한다.
// 또 한 애니메이션 보간 중 다시 호출된다면 이상한 결과를 초래한다.(사용할 때 처리하거나 함수자체 변경)
void cSkinnedMesh::SwitchAnimationBlend(int nIndex, float fSpeed, float fIntervalRate)
{
	D3DXTRACK_DESC trackDesc;
	LPD3DXANIMATIONSET pAnimSet = NULL;

	// 재생되던 0번 트랙의 애니메이션과 그 정보를 저장
	m_pAnimController->GetTrackAnimationSet(0, &pAnimSet);
	m_pAnimController->GetTrackDesc(0, &trackDesc);

	m_fChangeMotiontime = fSTD_ADANCE_SPEED / (fIntervalRate * pAnimSet->GetPeriod());

	// 저장한 정보를 1번 트랙에 실행
	m_pAnimController->SetTrackAnimationSet(1, pAnimSet);
	m_pAnimController->SetTrackDesc(1, &trackDesc);
	m_pAnimController->SetTrackEnable(1, true);
	SafeRelease(pAnimSet);

	// 새로운 애니메이션을 0번 트랙에 실행
	m_pAnimController->GetAnimationSet(nIndex, &pAnimSet);
	m_TotalLenght = pAnimSet->GetPeriod();
	m_pAnimController->SetTrackAnimationSet(0, pAnimSet);
	m_pAnimController->SetTrackPosition(0, 0);
	m_pAnimController->SetTrackSpeed(0, fSpeed);
	SafeRelease(pAnimSet);

	m_fAnimationWeight = 0;
}

void cSkinnedMesh::CreateHitBox(OUT map<string, ST_COLLISION_BOX_STICK>& mapHitBox, ST_BONE * pBone)
{
	if (!pBone)
		pBone = m_pRootFrame;

	ST_COLLISION_BOX_STICK stHitBox;
	stHitBox.pmatSticking = &pBone->matCombinedTransformationMatrix;

	if(pBone->Name)
		mapHitBox.insert(pair<string, ST_COLLISION_BOX_STICK>(pBone->Name ,stHitBox));

	if (pBone->pFrameFirstChild)
	{
		CreateHitBox(mapHitBox, (ST_BONE*)pBone->pFrameFirstChild);
	}

	if (pBone->pFrameSibling)
	{
		CreateHitBox(mapHitBox, (ST_BONE*)pBone->pFrameSibling);
	}
}

void cSkinnedMesh::ConnectHitBox(IN OUT map<string, ST_COLLISION_BOX_STICK>& mapHitBox, ST_BONE * pBone)
{
	if (!pBone)
		pBone = m_pRootFrame;

	if (pBone->Name)
	{
		auto iter = mapHitBox.find(pBone->Name);
		if (iter != mapHitBox.end())
		{
			iter->second.pmatSticking = &pBone->matCombinedTransformationMatrix;
		}
	}

	if (pBone->pFrameFirstChild)
	{
		ConnectHitBox(mapHitBox, (ST_BONE*)pBone->pFrameFirstChild);
	}

	if (pBone->pFrameSibling)
	{
		ConnectHitBox(mapHitBox, (ST_BONE*)pBone->pFrameSibling);
	}
}

void cSkinnedMesh::ConnectHitBox(IN vector<string>& vecBoxName, IN OUT vector<ST_COLLISION_BOX_STICK>& mapHitBox, ST_BONE * pBone)
{
	if (!pBone)
		pBone = m_pRootFrame;

	if (pBone->Name)
	{
		int i = 0;
		for each(const auto& p in vecBoxName)
		{
			if (p == pBone->Name)
			{
				mapHitBox[i].pmatSticking = &pBone->matCombinedTransformationMatrix;
				break;
			}
			++i;
		}
	}

	if (pBone->pFrameFirstChild)
	{
		ConnectHitBox(vecBoxName, mapHitBox, (ST_BONE*)pBone->pFrameFirstChild);
	}

	if (pBone->pFrameSibling)
	{
		ConnectHitBox(vecBoxName, mapHitBox, (ST_BONE*)pBone->pFrameSibling);
	}
}

LPD3DXEFFECT cSkinnedMesh::LoadEffect(char* szFilename)
{
	LPD3DXEFFECT pEffect = NULL;

	D3DXMACRO mac[2] =
	{
		{ "MATRIX_PALETTE_SIZE_DEFAULT", "35" },
		{ NULL,                          NULL }
	};

	D3DCAPS9 caps;
	D3DXMACRO *pmac = NULL;
	g_pD3DDevice->GetDeviceCaps(&caps);
	if (caps.VertexShaderVersion > D3DVS_VERSION(1, 1))
		pmac = mac;

	DWORD dwShaderFlags = 0;

#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DXSHADER_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

#ifdef DEBUG_VS
	dwShaderFlags |= D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT;
#endif
#ifdef DEBUG_PS
	dwShaderFlags |= D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT;
#endif

	ID3DXBuffer* pBuffer = NULL;
	if (FAILED(D3DXCreateEffectFromFile(g_pD3DDevice,
		szFilename,
		pmac,
		NULL,
		dwShaderFlags,
		NULL,
		&pEffect,
		&pBuffer)))
	{
		// if creation fails, and debug information has been returned, output debug info
		if (pBuffer)
		{
			OutputDebugStringA((char*)pBuffer->GetBufferPointer());
			SAFE_RELEASE(pBuffer);
		}

		return NULL;
	}

	return pEffect;
}

void cSkinnedMesh::SetupBoneMatrixPtrs( LPD3DXFRAME pFrame )
{
	// 각 프레임의 메시 컨테이너에 있는 pSkinInfo를 이용하여 영향받는 모든 
	// 프레임의 매트릭스를 ppBoneMatrixPtrs에 연결한다.
	// pSkinInfo->GetNumBones() 으로 영향받는 본의 개수를 찾음.
	// pSkinInfo->GetBoneName(i) 로 i번 프레임의 이름을 찾음
	// D3DXFrameFind(루트 프레임, 프레임 이름) 로 프레임을 찾음.
	// 찾아서 월드매트릭스를 걸어줘라.
	if (pFrame && pFrame->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pFrame->pMeshContainer;
		LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;
		if (pSkinInfo)
		{
			DWORD dwNumBones = pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwNumBones; ++i)
			{
				LPCSTR Name = pSkinInfo->GetBoneName(i);
				ST_BONE* pInf = (ST_BONE*)D3DXFrameFind(m_pRootFrame, Name);
				pBoneMesh->ppBoneMatrixPtrs[i] = &pInf->matCombinedTransformationMatrix;
			}
		}
	}
	
	//재귀적으로 모든 프레임에 대해서 실행.
	if (pFrame && pFrame->pFrameFirstChild)
	{
		SetupBoneMatrixPtrs((ST_BONE*)pFrame->pFrameFirstChild);
	}

	if (pFrame && pFrame->pFrameSibling)
	{
		SetupBoneMatrixPtrs((ST_BONE*)pFrame->pFrameSibling);
	}
}

void cSkinnedMesh::UpdateSkinnedMesh(LPD3DXFRAME pFrame)
{
	if (pFrame && pFrame->pMeshContainer && pFrame->pMeshContainer->pSkinInfo)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pFrame->pMeshContainer;
		LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;

		DWORD dwNumBones = pSkinInfo->GetNumBones();
		for (DWORD i = 0; i < dwNumBones; ++i)
		{
			pBoneMesh->pCurrentBoneMatrices[i] = 
				pBoneMesh->pBoneOffsetMatrices[i] * *pBoneMesh->ppBoneMatrixPtrs[i];
		}

		BYTE* src = NULL;
		BYTE* dest = NULL;

		pBoneMesh->pOrigMesh->LockVertexBuffer( D3DLOCK_READONLY, (void**)&src );
		pBoneMesh->MeshData.pMesh->LockVertexBuffer( 0, (void**)&dest );

		//MeshData.pMesh을 업데이트 시켜준다.
		pSkinInfo->UpdateSkinnedMesh( pBoneMesh->pCurrentBoneMatrices, NULL, src, dest );

		pBoneMesh->MeshData.pMesh->UnlockVertexBuffer();
		pBoneMesh->pOrigMesh->UnlockVertexBuffer();
	}

	//재귀적으로 모든 프레임에 대해서 실행.
	//재귀적으로 모든 프레임에 대해서 실행.
	if (pFrame->pFrameFirstChild)
	{
		UpdateSkinnedMesh(pFrame->pFrameFirstChild);
	}

	if (pFrame->pFrameSibling)
	{
		UpdateSkinnedMesh(pFrame->pFrameSibling);
	}
}

void cSkinnedMesh::TestUpdate(ST_BONE * pBone, const D3DXMATRIXA16 & matParent)
{
	pBone->matCombinedTransformationMatrix *= matParent;

	if (pBone->pFrameSibling)
	{
		Update((ST_BONE*)pBone->pFrameSibling, matParent);
	}

	if (pBone->pFrameFirstChild)
	{
		Update((ST_BONE*)pBone->pFrameFirstChild, matParent);
	}
}

void cSkinnedMesh::AnimationChangeBlend()
{
	m_pAnimController->SetTrackWeight(0, m_fAnimationWeight);
	m_pAnimController->SetTrackWeight(1, 1 - m_fAnimationWeight);

	m_fAnimationWeight += m_fChangeMotiontime * g_pTimeManager->GetDeltaTime();

	if (m_fAnimationWeight >= 1)
	{
		m_pAnimController->SetTrackWeight(0, m_fAnimationWeight);
		m_pAnimController->SetTrackEnable(1, false);
	}
}

void cSkinnedMesh::SetAnimaionSpeed(float fAnispeed)
{
	m_pAnimController->SetTrackSpeed(0, fAnispeed);
}

void cSkinnedMesh::ShowHierarchy(const LPD3DXFRAME pFrame, int nLayer)
{
	static int n = 0;
	string strBlank("   ");

	//cout << n++;
	//for (int i = 0; i < nLayer; ++i)
	//	cout << strBlank;
	//
	//if (pFrame && pFrame->Name)
	//	cout << pFrame->Name << endl;
	//else
	//	cout << "NoName" << endl;

	if (pFrame->pFrameFirstChild)
	{
		ShowHierarchy(pFrame->pFrameFirstChild, nLayer + 1);
	}

	if (pFrame->pFrameSibling)
	{
		ShowHierarchy(pFrame->pFrameSibling, nLayer);
	}
}

void cSkinnedMesh::SaveNameMat(LPD3DXFRAME pFrame)
{
	if (pFrame == NULL)
		pFrame = m_pRootFrame;
	if (pFrame && pFrame->Name)
	{
		ST_BONE* pTempBone = (ST_BONE*)pFrame;
		m_pNameMat[pFrame->Name] = (D3DXMATRIXA16*)&pTempBone->matCombinedTransformationMatrix;
	}

	if (pFrame && pFrame->pFrameFirstChild)
	{
		SaveNameMat(pFrame->pFrameFirstChild);
	}

	if (pFrame && pFrame->pFrameSibling)
	{
		SaveNameMat(pFrame->pFrameSibling);
	}
}

D3DXMATRIXA16* cSkinnedMesh::SearchMat(string NodeName)
{
	if (m_pNameMat.find(NodeName) == m_pNameMat.end())
		return NULL;
	else
		return m_pNameMat[NodeName];

}

