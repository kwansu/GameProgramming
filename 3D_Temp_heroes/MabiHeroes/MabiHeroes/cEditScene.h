#pragma once
#include "cGameNode.h"
#include "stdObjects.h"
#include "cLocalEditor.h"


class cEditScene :
	public cGameNode
{
private:
	enum eEditMode
	{
		SELECT_OBJECT,
		SELECT_COLLBOX,
		COLLOCATE_STRUCTURE,
		TRANSFORM_ROTATION,
		TRANSFORM_POSITION,
		TRANSFORM_SIZE
	};

private:
	cCamera*					m_pCamera;
	cGrid*						m_pGrid;
	cLocalEditor*				m_pLocalEditor;

	vector<cCreature*>			m_vecpCreature;
	vector<cStructure*>			m_vecpStructure;
	vector<string>				m_vecpStructureName;

	ST_RAY						m_rayMouse;
	ST_RAY						m_rayPickRay;
	ST_PLANE					m_pnPickPlane;
	D3DXVECTOR3					m_vPickOffset;
	D3DXVECTOR3					m_vPickOffset2;
	cCreature*					m_pPickedObject;
	cStructure*					m_pPickedStructure;
	cStructure*					m_pLastPickedStructure;
	ST_COLLISION_BOX_STICK*		m_pPickedHitBox;
	ST_COLLISION_BOX_STICK*		m_pLastPickedHitBox;
	FILE*						m_fp;
	char						m_szToken[1024];
	char						m_szPrevToken[1024];
	int							m_hbIndex;

	D3DXVECTOR3					m_vTransformDir;
	eEditMode					m_eCurrentMode;
	bool						m_isDrag;
	bool						m_isRotateMode;
	bool						m_isDebugRender;
	int							m_nStructureIndex;

	ST_COLLISION_BOX_STICK		colltemp;

public:
	cEditScene();
	~cEditScene();

	// cGameNode override
	void Setup()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

private:
	// 조작
	void PickObject();
	bool SelectTransAixs();
	void SelectStructure(int nIndex);
	void DeleteObject();
	void DragObject();
	void ObjectTranslate();
	void ObjectRotation();
	void ObjectScaling();
	bool RayPickPointFromPlane(OUT D3DXVECTOR3& vPickPos);

	// 세이브 로드
	void SaveData();
	void LoadData();
	void SaveCreatureData(const cCreature* pCreature, OUT ofstream& outFile);
	void LoadStructures();
	//char* GetToken();

	bool IsPickCreature(cCreature* pCreature);
	bool IsPickHitBox(const ST_COLLISION_BOX_STICK& stHitBox);

	void UpdateRotation(OUT D3DXMATRIXA16& matR);
};

