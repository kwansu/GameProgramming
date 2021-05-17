#pragma once

#include "cMtlTex.h"

struct ST_BONE : public D3DXFRAME
{
	D3DXMATRIXA16 matCombinedTransformationMatrix;
};

struct ST_BONE_MESH : public D3DXMESHCONTAINER
{
	std::vector<cMtlTex*>	vecMtlTex;
	vector<LPDIRECT3DTEXTURE9> vecNormalMap;

	LPD3DXMESH				pWorkingMesh;
	LPD3DXMESH				pOrigMesh;				// 원본 메쉬 CloneMeshFVF로 복사
	D3DXMATRIX**			ppBoneMatrixPtrs;		// 이 메쉬에 영향을 주는 프레임'들'의 월드매트릭스 포인터 배열
	D3DXMATRIX*				pBoneOffsetMatrices;	// 원본 메쉬를 로컬스페이스로 보내는 매트릭스들.
	D3DXMATRIX*				pCurrentBoneMatrices;	// 각 본의 계산된 월드매트릭스

	DWORD					dwNumPaletteEntries;
	DWORD					dwMaxNumFaceInfls;
	DWORD					dwNumAttrGroups;
	LPD3DXBUFFER			pBufBoneCombos;
};


class cAllocateHierarchy : public ID3DXAllocateHierarchy
{
protected:
	string			m_sFolder;
	D3DXVECTOR3		m_vMax;
	D3DXVECTOR3		m_vMin;
	DWORD			m_dwDefaultPaletteSize;
	DWORD			m_dwMaxPaletteSize;

public:
	bool			m_isGereric;

public:
	cAllocateHierarchy(void);
	~cAllocateHierarchy(void);
	
	string GetFolder() { return m_sFolder; }
	void SetFolder(string st) { m_sFolder = st; }

public:
	STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, 
		LPD3DXFRAME *ppNewFrame) override;

	STDMETHOD(CreateMeshContainer)(THIS_ 
		LPCSTR Name, 
		CONST D3DXMESHDATA *pMeshData, 
		CONST D3DXMATERIAL *pMaterials, 
		CONST D3DXEFFECTINSTANCE *pEffectInstances, 
		DWORD NumMaterials, 
		CONST DWORD *pAdjacency, 
		LPD3DXSKININFO pSkinInfo, 
		LPD3DXMESHCONTAINER *ppNewMeshContainer) override;

	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree) override; 

	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree) override;

	ST_SPHERE GetBoundSphere();
	DWORD GetMaxPalettSize();
	void SetPalettSize(DWORD nSize);
};

