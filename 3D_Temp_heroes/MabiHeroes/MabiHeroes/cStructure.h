#pragma once
#include "cGameObject.h"
#include <sys/stat.h>



class cEditScene;
class cSkinnedMesh;
class cGroup;
class cFrame;

class cStructure :
	public cGameObject
{
	friend class cWorld;
	friend class cEditScene;

protected:
	vector<ST_COLLISION_BOX_STICK>	m_vecCollisionBox;
	cSkinnedMesh*					m_pSkinnedMesh;
	string							m_ID;
	D3DMATERIAL9					m_mtl;
	int								m_nIndex;

public:
	cStructure();
	virtual ~cStructure();

	// cGameObject overrid
	virtual void Setup()	override;
	virtual void Update()	override;
	virtual void Render()	override;


	void RenderCollisionBox();

	// 각 구조물의 저장 방식설정
	virtual void SaveData(OUT ofstream& outFile);
	void	SaveCollisionBox();
	void	LoadCollisionBox();
	void	CreateCollisionBox(D3DXMATRIXA16* mat);
	void	CreateCollisionBox2(D3DXMATRIXA16* mat, D3DXMATRIXA16* offset);

	void	CloneCollisionBox(D3DXMATRIXA16* mat, D3DXMATRIXA16* offset, D3DXVECTOR3 half);

	void	Save(int num);
	string	Identify() { return m_ID; }

	inline bool CheckFile(const std::string& name)
	{
		struct stat buffer;
		return (stat(name.c_str(), &buffer) == 0);
	}
};


