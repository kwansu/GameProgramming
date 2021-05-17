#include "StdAfx.h"
#include "cAllocateHierarchy.h"
#include "cMtlTex.h"

cAllocateHierarchy::cAllocateHierarchy(void)
	: m_vMax(-FLT_MAX, -FLT_MAX, -FLT_MAX)
	, m_vMin(FLT_MAX, FLT_MAX, FLT_MAX)
	, m_dwMaxPaletteSize(0)
	, m_dwDefaultPaletteSize(0)
	, m_isGereric(true)
{
}


cAllocateHierarchy::~cAllocateHierarchy(void)
{
}

STDMETHODIMP cAllocateHierarchy::CreateFrame( THIS_ LPCSTR Name,
	LPD3DXFRAME *ppNewFrame )
{
	ST_BONE* pBone = new ST_BONE;
	
	// TODO : 이름을 잘 저장해주세요. 물론 해제도.
	pBone->Name = NULL;
	if (Name)
	{
		int nLen = strlen(Name) + 1;
		pBone->Name = new char[nLen];
		strcpy(pBone->Name, Name);
	}

	pBone->pFrameFirstChild = NULL;
	pBone->pFrameSibling = NULL;
	pBone->pMeshContainer = NULL;

	D3DXMatrixIdentity(&pBone->TransformationMatrix);
	D3DXMatrixIdentity(&pBone->matCombinedTransformationMatrix);

	*ppNewFrame = pBone;

	return S_OK;
}

STDMETHODIMP cAllocateHierarchy::CreateMeshContainer( 
	THIS_ LPCSTR Name, 
	CONST D3DXMESHDATA *pMeshData, 
	CONST D3DXMATERIAL *pMaterials, 
	CONST D3DXEFFECTINSTANCE *pEffectInstances, 
	DWORD NumMaterials,
	CONST DWORD *pAdjacency, 
	LPD3DXSKININFO pSkinInfo, 
	LPD3DXMESHCONTAINER *ppNewMeshContainer )
{
	ST_BONE_MESH* pBoneMesh = new ST_BONE_MESH;
	
	pBoneMesh->Name = NULL;

	if (Name)
	{
		pBoneMesh->Name = new char[strlen(Name) + 1];
		strcpy_s(pBoneMesh->Name, strlen(Name) + 1, Name);
	}

	if (pMeshData && pMeshData->Type == D3DXMESHTYPE_MESH)
	{
		D3DXVECTOR3 vMin(0, 0, 0), vMax(0, 0, 0);

		LPVOID pV = NULL;
		pMeshData->pMesh->LockVertexBuffer(0, &pV);
		D3DXComputeBoundingBox((D3DXVECTOR3*)pV,
			pMeshData->pMesh->GetNumVertices(),
			D3DXGetFVFVertexSize(pMeshData->pMesh->GetFVF()),
			&vMin,
			&vMax);
		D3DXVec3Minimize(&m_vMin, &m_vMin, &vMin);
		D3DXVec3Maximize(&m_vMax, &m_vMax, &vMax);
		pMeshData->pMesh->UnlockVertexBuffer();

		HRESULT uR = pMeshData->pMesh->CloneMeshFVF(
			pMeshData->pMesh->GetOptions(),
			pMeshData->pMesh->GetFVF(),
			g_pD3DDevice,
			&pBoneMesh->pOrigMesh);

		if (uR == D3DERR_INVALIDCALL)
		{
			pBoneMesh->MeshData.pMesh = NULL;
			pBoneMesh->pOrigMesh = NULL;
		}
		else
		{
			pMeshData->pMesh->AddRef();
			pBoneMesh->MeshData.pMesh = pMeshData->pMesh;
		}
	}
	else if (pMeshData)
	{
		assert(false, "처리하지 않은 종류의 매쉬가 있습니다.");
	}

	if(pMaterials)
	{
		pBoneMesh->vecMtlTex.resize(NumMaterials);
		pBoneMesh->vecNormalMap.resize(NumMaterials);
		for(DWORD i = 0; i < NumMaterials; ++i)
		{
			pBoneMesh->vecMtlTex[i] = new cMtlTex;
			pBoneMesh->vecMtlTex[i]->m_stMtl = pMaterials[i].MatD3D;

			if (pMaterials[i].pTextureFilename)
			{
				std::string sFullPath = m_sFolder + std::string(pMaterials[i].pTextureFilename);
				LPDIRECT3DTEXTURE9 pTexture = g_pTextureManager->GetTexture(sFullPath);
				pBoneMesh->vecMtlTex[i]->SetTexture(pTexture);

				int lenght = sFullPath.size();
				sFullPath.insert(lenght - 4, "_normal");
				pBoneMesh->vecNormalMap[i] = g_pTextureManager->GetTexture(sFullPath);
			}
		}
	}
	
	pBoneMesh->pEffects = NULL;
	
	if (pAdjacency)
	{
		DWORD dwNumFaces = pMeshData->pMesh->GetNumFaces();
		pBoneMesh->pAdjacency = new DWORD[3 * dwNumFaces];
		memcpy(pBoneMesh->pAdjacency, pAdjacency, 3 * sizeof(DWORD) * dwNumFaces);
	}
	
	if (pSkinInfo)
	{
		if(m_isGereric)
		{
			pBoneMesh->pSkinInfo = pSkinInfo;
			pSkinInfo->AddRef();

			int nBone = pSkinInfo->GetNumBones();

			pBoneMesh->ppBoneMatrixPtrs = new D3DXMATRIX*[nBone];
			pBoneMesh->pBoneOffsetMatrices = new D3DXMATRIX[nBone];
			pBoneMesh->pCurrentBoneMatrices = new D3DXMATRIX[nBone];

			for (int i = 0; i < nBone; ++i)
			{
				pBoneMesh->pBoneOffsetMatrices[i] = *(pSkinInfo->GetBoneOffsetMatrix(i));
			}
		}
		else
		{
			pBoneMesh->pSkinInfo = pSkinInfo;
			pSkinInfo->AddRef();

			int nBone = pSkinInfo->GetNumBones();

			pBoneMesh->ppBoneMatrixPtrs = new D3DXMATRIX*[nBone];
			pBoneMesh->pBoneOffsetMatrices = new D3DXMATRIX[nBone];

			for (int i = 0; i < nBone; ++i)
			{
				pBoneMesh->ppBoneMatrixPtrs[i] = NULL;
				pBoneMesh->pBoneOffsetMatrices[i] = *(pSkinInfo->GetBoneOffsetMatrix(i));
			}

			// ConvertToIndexedBlendedMesh 함수에 팔렛트 엔트리 개수를 넘겨야하기 때문에 
			// 멤버변수로 세팅하고 외부에서 적용해주도록 설정.
			// 메쉬에 영향을 주는 팔레트의 개수는 
			// m_dwDefaultPaletteSize와 pSkinInfo->GetNumBones()보다 클 수 없다.
			// m_dwDefaultPaletteSize는 쉐이더에 정의되어있다.
			pBoneMesh->dwNumPaletteEntries = min(m_dwDefaultPaletteSize, pSkinInfo->GetNumBones());

			// 최대 팔레트 사이즈 업데이트
			if (m_dwMaxPaletteSize < pBoneMesh->dwNumPaletteEntries)
			{
				m_dwMaxPaletteSize = pBoneMesh->dwNumPaletteEntries;
			}

			// blend weights와 인덱스를 이용해 pWorkingMesh 생성.
			pBoneMesh->pSkinInfo->ConvertToIndexedBlendedMesh(
				pBoneMesh->pOrigMesh,
				D3DXMESH_MANAGED | D3DXMESHOPT_VERTEXCACHE,
				pBoneMesh->dwNumPaletteEntries,
				pBoneMesh->pAdjacency,
				NULL,
				NULL,
				NULL,
				&pBoneMesh->dwMaxNumFaceInfls,
				&pBoneMesh->dwNumAttrGroups,
				&pBoneMesh->pBufBoneCombos,
				&pBoneMesh->pWorkingMesh);

			// 기존 메쉬의 FVF가 버텍스 블랜딩 정보를 전달 할 수 없는 경우 FVF를 변경한다
			DWORD dwOldFVF = pBoneMesh->pWorkingMesh->GetFVF();
			DWORD dwNewFVF =
				(dwOldFVF & D3DFVF_POSITION_MASK) |
				D3DFVF_NORMAL |
				D3DFVF_TEX1 |
				D3DFVF_LASTBETA_UBYTE4;

			if (dwNewFVF != dwOldFVF)
			{
				// 메쉬를 복사하면서 FVF를 변경한다.
				LPD3DXMESH pMesh = NULL;

				pBoneMesh->pWorkingMesh->CloneMeshFVF(
					pBoneMesh->pWorkingMesh->GetOptions(),
					dwNewFVF,
					g_pD3DDevice,
					&pMesh);

				// 기존 메쉬를 대체
				SAFE_RELEASE(pBoneMesh->pWorkingMesh);
				pBoneMesh->pWorkingMesh = pMesh;

				// 새로 생성한 메쉬에는 노멀 정보가 있으므로
				// 기존 메쉬 FVF에 노멀 정보가 없으면 새로 계산해줘야함.
				if (!(dwOldFVF & D3DFVF_NORMAL))
				{
					D3DXComputeNormals(pBoneMesh->pWorkingMesh, NULL);
				}
			}

			// Interpret the UBYTE4 as a D3DCOLOR.
			// The GeForce3 doesn't support the UBYTE4 decl type.  So, we convert any
			// blend indices to a D3DCOLOR semantic, and later in the shader convert
			// it back using the D3DCOLORtoUBYTE4() intrinsic.  Note that we don't
			// convert any data, just the declaration.
			D3DVERTEXELEMENT9 pDecl[MAX_FVF_DECL_SIZE];
			D3DVERTEXELEMENT9 * pDeclCur;
			pBoneMesh->pWorkingMesh->GetDeclaration(pDecl);

			pDeclCur = pDecl;
			while (pDeclCur->Stream != 0xff)
			{
				if ((pDeclCur->Usage == D3DDECLUSAGE_BLENDINDICES) &&
					(pDeclCur->UsageIndex == 0))
					pDeclCur->Type = D3DDECLTYPE_D3DCOLOR;
				pDeclCur++;
			}

			pBoneMesh->pWorkingMesh->UpdateSemantics(pDecl);
		}

		////////////////////////////////////////////////////
		//pBoneMesh->pSkinInfo = pSkinInfo;
		//pSkinInfo->AddRef();

		//int nBone = pSkinInfo->GetNumBones();

		//pBoneMesh->ppBoneMatrixPtrs = new D3DXMATRIX*[nBone];
		//pBoneMesh->pBoneOffsetMatrices = new D3DXMATRIX[nBone];

		//for (int i = 0; i < nBone; ++i)
		//{
		//	pBoneMesh->ppBoneMatrixPtrs[i] = NULL;
		//	pBoneMesh->pBoneOffsetMatrices[i] = *(pSkinInfo->GetBoneOffsetMatrix(i));
		//}

		//// ConvertToIndexedBlendedMesh 함수에 팔렛트 엔트리 개수를 넘겨야하기 때문에 
		//// 멤버변수로 세팅하고 외부에서 적용해주도록 설정.
		//// 메쉬에 영향을 주는 팔레트의 개수는 
		//// m_dwDefaultPaletteSize와 pSkinInfo->GetNumBones()보다 클 수 없다.
		//// m_dwDefaultPaletteSize는 쉐이더에 정의되어있다.
		//pBoneMesh->dwNumPaletteEntries = min(m_dwDefaultPaletteSize, pSkinInfo->GetNumBones());

		//// 최대 팔레트 사이즈 업데이트
		//if (m_dwMaxPaletteSize < pBoneMesh->dwNumPaletteEntries)
		//{
		//	m_dwMaxPaletteSize = pBoneMesh->dwNumPaletteEntries;
		//}

		//// blend weights와 인덱스를 이용해 pWorkingMesh 생성.
		//pBoneMesh->pSkinInfo->ConvertToIndexedBlendedMesh(
		//	pBoneMesh->pOrigMesh,
		//	D3DXMESH_MANAGED | D3DXMESHOPT_VERTEXCACHE,
		//	pBoneMesh->dwNumPaletteEntries,
		//	pBoneMesh->pAdjacency,
		//	NULL,
		//	NULL,
		//	NULL,
		//	&pBoneMesh->dwMaxNumFaceInfls,
		//	&pBoneMesh->dwNumAttrGroups,
		//	&pBoneMesh->pBufBoneCombos,
		//	&pBoneMesh->pWorkingMesh);

		//// 기존 메쉬의 FVF가 버텍스 블랜딩 정보를 전달 할 수 없는 경우 FVF를 변경한다
		////DWORD dwOldFVF = pBoneMesh->pWorkingMesh->GetFVF();
		////DWORD dwNewFVF =
		////	(dwOldFVF & D3DFVF_POSITION_MASK) |
		////	D3DFVF_NORMAL |
		////	D3DFVF_TEX1 |
		////	D3DFVF_LASTBETA_UBYTE4;

		////if (dwNewFVF != dwOldFVF)
		////{
		////	// 메쉬를 복사하면서 FVF를 변경한다.
		////	LPD3DXMESH pMesh = NULL;

		////	pBoneMesh->pWorkingMesh->CloneMeshFVF(
		////		pBoneMesh->pWorkingMesh->GetOptions(),
		////		dwNewFVF,
		////		g_pD3DDevice,
		////		&pMesh);

		////	// 기존 메쉬를 대체
		////	SAFE_RELEASE(pBoneMesh->pWorkingMesh);
		////	pBoneMesh->pWorkingMesh = pMesh;

		////	// 새로 생성한 메쉬에는 노멀 정보가 있으므로
		////	// 기존 메쉬 FVF에 노멀 정보가 없으면 새로 계산해줘야함.
		////	if (!(dwOldFVF & D3DFVF_NORMAL))
		////	{
		////		D3DXComputeNormals(pBoneMesh->pWorkingMesh, NULL);
		////	}
		////}

		//// Interpret the UBYTE4 as a D3DCOLOR.
		//// The GeForce3 doesn't support the UBYTE4 decl type.  So, we convert any
		//// blend indices to a D3DCOLOR semantic, and later in the shader convert
		//// it back using the D3DCOLORtoUBYTE4() intrinsic.  Note that we don't
		//// convert any data, just the declaration.
		//D3DVERTEXELEMENT9 pDecl[MAX_FVF_DECL_SIZE];
		//D3DVERTEXELEMENT9 * pDeclCur;
		//pBoneMesh->pWorkingMesh->GetDeclaration(pDecl);

		//pDeclCur = pDecl;
		//while (pDeclCur->Stream != 0xff)
		//{
		//	if ((pDeclCur->Usage == D3DDECLUSAGE_BLENDINDICES) &&
		//		(pDeclCur->UsageIndex == 0))
		//		pDeclCur->Type = D3DDECLTYPE_D3DCOLOR;
		//	pDeclCur++;
		//}

		//pBoneMesh->pWorkingMesh->UpdateSemantics(pDecl);
	}
	else
	{
		pBoneMesh->pSkinInfo = NULL;
		pBoneMesh->ppBoneMatrixPtrs = NULL;
		pBoneMesh->pBoneOffsetMatrices = NULL;
	}

	*ppNewMeshContainer = pBoneMesh;

	return S_OK;
}

STDMETHODIMP cAllocateHierarchy::DestroyFrame( THIS_ LPD3DXFRAME pFrameToFree )
{
	// TODO : 해제 잘 합시다.
	ST_BONE* pBone = (ST_BONE*)pFrameToFree;

	if(pBone->Name)
		delete [] pBone->Name;

	return S_OK;
}

STDMETHODIMP cAllocateHierarchy::DestroyMeshContainer( THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree )
{
	// TODO : 해제 잘 합시다.

	ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pMeshContainerToFree;
	//for each(auto p in pBoneMesh->vecMtlTex)
	//{
	//	SAFE_RELEASE(p);
	//}

	while(pBoneMesh)
	{
		pBoneMesh->MeshData.pMesh->Release();

		
		if(pBoneMesh->ppBoneMatrixPtrs)
			delete [] pBoneMesh->ppBoneMatrixPtrs;
		if(pBoneMesh->pBoneOffsetMatrices)
			delete [] pBoneMesh->pBoneOffsetMatrices;

		pBoneMesh->pSkinInfo->Release();
		pBoneMesh->pOrigMesh->Release(); 

		pBoneMesh = (ST_BONE_MESH*)pBoneMesh->pNextMeshContainer;
	}

	return S_OK;
}

ST_SPHERE cAllocateHierarchy::GetBoundSphere()
{
	ST_SPHERE stColl;

	D3DXVECTOR3 vDir = m_vMax - m_vMin;

	stColl.fRadius = D3DXVec3Length(&vDir) * 0.5f;
	stColl.vOffset = m_vMin + vDir * 0.5f;

	return stColl;
}

DWORD cAllocateHierarchy::GetMaxPalettSize()
{
	return m_dwMaxPaletteSize;
}

void cAllocateHierarchy::SetPalettSize(DWORD nSize)
{
	m_dwDefaultPaletteSize = nSize;
}
