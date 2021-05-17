#pragma once

// 모든 게임 오브젝트를 포함하는 헤더
#include "cGameObject.h"

#include "cStructure.h"
//#include "cPillar.h"
//#include "cBox.h"
//#include "cStep.h"
//#include "cGrass.h"
//#include "cWall.h"
//#include "cStairs.h"
//#include "cSurface.h"
//#include "cCorridor.h"
#include "cMap.h"

#include "cCreature.h"
#include "cObj_Fiona.h"

#include "cEnemy.h"
#include "cNoll.h"
#include "cLavasat.h"
#include "cPrince.h"
#include "cWoodenElf.h"


// 구조물 타입 정의
#define CS_NUM_TYPE		1
#define CS_CLASS0		cMap

//#define CS_CLASS0		cFloor
//#define CS_CLASS1		cCeilling
//#define CS_CLASS2		cWall1
//#define CS_CLASS3		cWall2
//#define CS_CLASS4		cWall3
//#define CS_CLASS5		cWall4
//#define CS_CLASS6		cWall5
//#define CS_CLASS7		cWall6
//#define CS_CLASS8		cWall7
//#define CS_CLASS9		cWall8
//#define CS_CLASS10		cWall9
//#define CS_CLASS11		cWall10
//#define CS_CLASS12		cWall11
//#define CS_CLASS13		cWall12
//#define CS_CLASS14		cCorridor1
//#define CS_CLASS15		cCorridor2
//#define CS_CLASS16		cCorridor3
//#define CS_CLASS17		cCorridor4
//#define CS_CLASS18		cCorridor5
//#define CS_CLASS19		cLongHall
//#define CS_CLASS20		cPillar1
//#define CS_CLASS21		cPillar2
//#define CS_CLASS22		cPillar3
//#define CS_CLASS23		cPillar4
//#define CS_CLASS24		cPillar5
//#define CS_CLASS25		cPillar6
//#define CS_CLASS26		cPillar7
//#define CS_CLASS27		cPillar8
//#define CS_CLASS28		cStairs1
//#define CS_CLASS29		cStairs2
//#define CS_CLASS30		cStairs3
//#define CS_CLASS31		cStairs4
//#define CS_CLASS32		cStairs5
//#define CS_CLASS33		cStairs6
//#define CS_CLASS34		cStairsC
//#define CS_CLASS35		cGrass








//00_FLOOR");
//01_CEILLING");
//02_WALL1");
//03_WALL2");
//04_WALL3");
//05_WALL4");
//06_WALL5");
//07_WALL6");
//08_WALL7");
//09_WALL8");
//10_WALL9");
//11_WALL10");
//12_WALL11");
//13_WALL12");
//14_CORRIDOR1");
//15_CORRIDOR2");
//16_CORRIDOR3");
//17_CORRIDOR4");
//18_CORRIDOR5");
//19_LONGHALL");

//20_PILLAR1");
//21_PILLAR2");
//22_PILLAR3");
//23_PILLAR4");
//24_PILLAR5");
//25_PILLAR6");
//26_PILLAR7");
//27_PILLAR8");

//28_STAIRS1");
//29_STAIRS2");
//30_STAIRS3");
//31_STAIRS4");
//32_STAIRS5");
//33_STAIRS6");
//34_STAIRSC");
//35_GRASS");

//
//cStructure* structure;
//for (int i = 0; i < m_vecpStructure.size(); i++)
//{
//	if (strcmp(m_szToken, m_vecpStructure[i]->Identify().c_str()) == 0)
//		;
//}
//
//ST_COLLISION_BOX_STICK* coll = &structure->m_vecCollisionBox.back();



#define CREATE_STRUCTURE(index)	new (CS_CLASS##index)

enum STRUCTURE_TYPE
{
	STRUCTURE_MAP
};





































