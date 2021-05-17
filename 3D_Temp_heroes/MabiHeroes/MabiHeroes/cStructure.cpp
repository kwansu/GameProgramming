#include "stdafx.h"
#include "cStructure.h"
#include "cSkinnedMesh.h"


cStructure::cStructure()
	:m_pSkinnedMesh(NULL)
	, m_nIndex(0)
{

}


cStructure::~cStructure()
{
}

void cStructure::Setup()
{
	// make collision box
	ST_COLLISION_BOX_STICK coll;
	coll.pmatSticking = &m_matWorld;

	m_vecCollisionBox.push_back(coll);

	ZeroMemory(&m_mtl, sizeof(m_mtl));
	m_mtl.Diffuse = D3DXCOLOR(1, 1, 1, 1);

	//string path = "./GameData/HitBox";
	//string fullpath = this->Identify() + path;
	//if (CheckFile(fullpath.c_str()))
	//{
	//	LoadCollisionBox();
	//}
}


void cStructure::Update()
{
	UpdateTransform();
	if (m_pSkinnedMesh)
		m_pSkinnedMesh->Update(m_matWorld);

	//for (int i = 0; i < m_vecCollisionBox.size(); i++)
	//{
	//	m_vecCollisionBox[i]->
	//}

	if (g_pKeyManager->IsOnceKeyDown('C'))
	{
		SaveCollisionBox();
	}

}

void cStructure::Render()
{
	for each(const auto& box in m_vecCollisionBox)
	{
		g_pCollisionRender->RenderBox(box);
	}

	if (m_pSkinnedMesh)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		m_pSkinnedMesh->RenderInAnimateObject();
	}
}

void cStructure::RenderCollisionBox()
{
	for each(const auto& coll in m_vecCollisionBox)
		g_pCollisionRender->RenderBox(coll);
}

void cStructure::SaveData(OUT ofstream & outFile)
{
	outFile << this->m_nIndex << endl;

	outFile << this->m_vScale.x << endl;
	outFile << this->m_vScale.y << endl;
	outFile << this->m_vScale.z << endl;
	outFile << this->m_vRot.x << endl;
	outFile << this->m_vRot.y << endl;
	outFile << this->m_vRot.z << endl;
	outFile << this->m_vPos.x << endl;
	outFile << this->m_vPos.y << endl;
	outFile << this->m_vPos.z << endl;

	outFile << this->m_vecCollisionBox.size() << endl;

	for (int p = 0; p < this->m_vecCollisionBox.size(); p++)
	{
		outFile << this->m_vecCollisionBox[p].matOffset._11 << endl;
		outFile << this->m_vecCollisionBox[p].matOffset._12 << endl;
		outFile << this->m_vecCollisionBox[p].matOffset._13 << endl;
		outFile << this->m_vecCollisionBox[p].matOffset._14 << endl;
		outFile << this->m_vecCollisionBox[p].matOffset._21 << endl;
		outFile << this->m_vecCollisionBox[p].matOffset._22 << endl;
		outFile << this->m_vecCollisionBox[p].matOffset._23 << endl;
		outFile << this->m_vecCollisionBox[p].matOffset._24 << endl;
		outFile << this->m_vecCollisionBox[p].matOffset._31 << endl;
		outFile << this->m_vecCollisionBox[p].matOffset._32 << endl;
		outFile << this->m_vecCollisionBox[p].matOffset._33 << endl;
		outFile << this->m_vecCollisionBox[p].matOffset._34 << endl;
		outFile << this->m_vecCollisionBox[p].matOffset._41 << endl;
		outFile << this->m_vecCollisionBox[p].matOffset._42 << endl;
		outFile << this->m_vecCollisionBox[p].matOffset._43 << endl;
		outFile << this->m_vecCollisionBox[p].matOffset._44 << endl;
		outFile << fabs(this->m_vecCollisionBox[p].vHalfSize.x) << endl;
		outFile << fabs(this->m_vecCollisionBox[p].vHalfSize.y) << endl;
		outFile << fabs(this->m_vecCollisionBox[p].vHalfSize.z) << endl;
	}
}

void cStructure::SaveCollisionBox()
{
	string name = this->Identify();
	for (int i = 0; i < m_vecCollisionBox.size(); i++)
	{
		string hbname = "Hitbox";
		char buffer[33];
		hbname = hbname + itoa(i, buffer, 10);
		g_pIniData->AddData(hbname.c_str(), "matOffset_41", m_vecCollisionBox[i].matOffset._41);
		g_pIniData->AddData(hbname.c_str(), "matOffset_42", m_vecCollisionBox[i].matOffset._42);
		g_pIniData->AddData(hbname.c_str(), "matOffset_43", m_vecCollisionBox[i].matOffset._43);
		g_pIniData->AddData(hbname.c_str(), "matOffset_44", m_vecCollisionBox[i].matOffset._44);

		g_pIniData->AddData(hbname.c_str(), "vHalfSize.x", m_vecCollisionBox[i].vHalfSize.x);
		g_pIniData->AddData(hbname.c_str(), "vHalfSize.y", m_vecCollisionBox[i].vHalfSize.y);
		g_pIniData->AddData(hbname.c_str(), "vHalfSize.z", m_vecCollisionBox[i].vHalfSize.z);
	}


	string path = "./GameData/HitBox";
	string fullpath = this->Identify() + path;
	g_pIniData->IniSave(fullpath.c_str());
}

void cStructure::CreateCollisionBox(D3DXMATRIXA16* mat)
{
	ST_COLLISION_BOX_STICK coll;
	coll.pmatSticking = mat;

	m_vecCollisionBox.push_back(coll);
}
void cStructure::CreateCollisionBox2(D3DXMATRIXA16* mat, D3DXMATRIXA16* offset)
{
	ST_COLLISION_BOX_STICK coll;
	coll.pmatSticking = mat;
	coll.matOffset = *offset;

	m_vecCollisionBox.push_back(coll);
}

void cStructure::CloneCollisionBox(D3DXMATRIXA16* mat, D3DXMATRIXA16* offset, D3DXVECTOR3 half)
{
	ST_COLLISION_BOX_STICK coll;
	coll.pmatSticking = mat;
	
	coll.matOffset = *offset;

	coll.vHalfSize.x = half.x;
	coll.vHalfSize.y = half.y;
	coll.vHalfSize.z = half.z;

	m_vecCollisionBox.push_back(coll);
}

void cStructure::LoadCollisionBox()
{
	//string path = "./GameData/HitBox";
	//string fullpath = this->Identify() + path;

	//fopen_s(&m_fp, fullpath.c_str(), "r");

	//while (true)
	//{//
	//	ns_SKS::GetToken(m_fp, m_szToken);


	//	if (m_szToken == NULL)
	//		break;


	//	if (m_szToken[0] == '[')
	//	{//
	//		if (m_szToken[1] == 'H' && m_szToken[2] == 'B')
	//		{

	//		}
	//		else
	//		{
	//		}
	//	}
	//}//while
	//fclose(m_fp);
}

void cStructure::Save(int num)
{
	//// world mat
	//string Structure = "ST";
	//char buffer[66];
	//string number = itoa(num, buffer, sizeof(buffer));
	//string name = dash + Structure + dash + this->Identify() + space + sharp + number + dash;

	//g_pIniData->AddData(name.c_str(), "m_matWorld._11", m_matWorld._11);
	//g_pIniData->AddData(name.c_str(), "m_matWorld._12", m_matWorld._12);
	//g_pIniData->AddData(name.c_str(), "m_matWorld._13", m_matWorld._13);
	//g_pIniData->AddData(name.c_str(), "m_matWorld._14", m_matWorld._14);

	//g_pIniData->AddData(name.c_str(), "m_matWorld._21", m_matWorld._21);
	//g_pIniData->AddData(name.c_str(), "m_matWorld._22", m_matWorld._22);
	//g_pIniData->AddData(name.c_str(), "m_matWorld._23", m_matWorld._23);
	//g_pIniData->AddData(name.c_str(), "m_matWorld._24", m_matWorld._24);

	//g_pIniData->AddData(name.c_str(), "m_matWorld._31", m_matWorld._31);
	//g_pIniData->AddData(name.c_str(), "m_matWorld._32", m_matWorld._32);
	//g_pIniData->AddData(name.c_str(), "m_matWorld._33", m_matWorld._33);
	//g_pIniData->AddData(name.c_str(), "m_matWorld._34", m_matWorld._34);

	//g_pIniData->AddData(name.c_str(), "m_matWorld._41", m_matWorld._41);
	//g_pIniData->AddData(name.c_str(), "m_matWorld._42", m_matWorld._42);
	//g_pIniData->AddData(name.c_str(), "m_matWorld._43", m_matWorld._43);
	//g_pIniData->AddData(name.c_str(), "m_matWorld._44", m_matWorld._44);

	//g_pIniData->AddData(name.c_str(), "_", 0);
	//// hit box

	//g_pIniData->IniSave("./GameData/MapData");

	//vector<string> vecName;

	//for (int p = 0; p < m_vecCollisionBox.size(); p++)
	//{
	//	string hitBox = "HB";
	//	string numb;
	//	char buff[66];
	//	numb = itoa(p, buff, sizeof(buff));

	//	string hitBoxName = dash + hitBox + dash + this->Identify() + space + sharp + numb + dash;
	//	vecName.push_back(hitBoxName);

	//	g_pIniData->AddData(vecName[p].c_str(), "matOffset._11", m_vecCollisionBox[p].matOffset._11
	//	g_pIniData->AddData(vecName[p].c_str(), "matOffset._12", m_vecCollisionBox[p].matOffset._12
	//	g_pIniData->AddData(vecName[p].c_str(), "matOffset._13", m_vecCollisionBox[p].matOffset._13
	//	g_pIniData->AddData(vecName[p].c_str(), "matOffset._14", m_vecCollisionBox[p].matOffset._14

	//	g_pIniData->AddData(vecName[p].c_str(), "matOffset._21", m_vecCollisionBox[p].matOffset._21
	//	g_pIniData->AddData(vecName[p].c_str(), "matOffset._22", m_vecCollisionBox[p].matOffset._22
	//	g_pIniData->AddData(vecName[p].c_str(), "matOffset._23", m_vecCollisionBox[p].matOffset._23
	//	g_pIniData->AddData(vecName[p].c_str(), "matOffset._24", m_vecCollisionBox[p].matOffset._24

	//	g_pIniData->AddData(vecName[p].c_str(), "matOffset._31", m_vecCollisionBox[p].matOffset._31
	//	g_pIniData->AddData(vecName[p].c_str(), "matOffset._32", m_vecCollisionBox[p].matOffset._32
	//	g_pIniData->AddData(vecName[p].c_str(), "matOffset._33", m_vecCollisionBox[p].matOffset._33
	//	g_pIniData->AddData(vecName[p].c_str(), "matOffset._34", m_vecCollisionBox[p].matOffset._34

	//	g_pIniData->AddData(vecName[p].c_str(), "matOffset._41", m_vecCollisionBox[p].matOffset._41
	//	g_pIniData->AddData(vecName[p].c_str(), "matOffset._42", m_vecCollisionBox[p].matOffset._42
	//	g_pIniData->AddData(vecName[p].c_str(), "matOffset._43", m_vecCollisionBox[p].matOffset._43
	//	g_pIniData->AddData(vecName[p].c_str(), "matOffset._44", m_vecCollisionBox[p].matOffset._44

	//	g_pIniData->AddData(vecName[p].c_str(), "vHalfSize.x",	 m_vecCollisionBox[p].vHalfSize.x
	//	g_pIniData->AddData(vecName[p].c_str(), "vHalfSize.y",	 m_vecCollisionBox[p].vHalfSize.y
	//	g_pIniData->AddData(vecName[p].c_str(), "vHalfSize.z",	 m_vecCollisionBox[p].vHalfSize.z

	//	g_pIniData->AddData(vecName[p].c_str(), "_", 0);


	//}
	//g_pIniData->IniSave("./GameData/MapData");

}
