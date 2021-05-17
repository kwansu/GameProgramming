#pragma once
#include "cEnemy.h"

namespace ns_SKEL_ARCHER
{
#define fTURN_SPEED				110
#define fRUN_SPEED				90
#define fTURN_MAX_ANGLE			50
#define fATTACK_MAX_ANGLE		35
#define fTRACE_ANGLE_SPEED		50

#define fHP_MAX					1200
}

class cSkelArcher : public cEnemy
{
public:
	cSkelArcher();
	~cSkelArcher();

	// creature override
	virtual void SetupCreature()	override;
	virtual void UpdateCreature()	override;
};

enum SkelArcher_Animation
{
	/*  0 걷기			*/		ANI_WALK,
	/*  1 공격준비		*/		ANI_WAIT,
	/*  2 아이들			*/		ANI_UNARMEDWAIT,
	/*  3 활쏘기			*/		ANI_THROUGHARROWSTART,
	/*  4 ???			*/		ANI_THROUGHARROWSHOT,
	/*  5 발사루프		*/		ANI_THROUGHARROWLOOP,
	/*  6 말하기			*/		ANI_TALK,
	/*  7 스턴상태		*/		ANI_STUN,
	/*  8 옆걷기(우)		*/		ANI_SIDEWALK02,
	/*  9 옆걷기(좌)		*/		ANI_SIDEWALK01,
	/* 10 뛰기			*/		ANI_RUN,
	/* 11 웃기			*/		ANI_LAUGH,
	/* 12 날라가기		*/		ANI_KNOCKBACKSTART,
	/* 13 쓰러져있기		*/		ANI_KNOCKBACKLOOP,
	/* 14 일어나기		*/		ANI_KNOCKBACKEND,
	/* 15 맞기			*/		ANI_FLINCH,
	/* 16 헥헥데기		*/		ANI_DYINGWAIT,
	/* 17 굴며날라가기	*/		ANI_DOWNSTART,
	/* 18 쓰러져있기		*/		ANI_DOWNLOOP,
	/* 19 일어나기		*/		ANI_DOWNEND,
	/* 20 죽어있음		*/		ANI_DEATHWAIT,
	/* 21 죽고있음		*/		ANI_DEATH,
	/* 22 쎄게활장전		*/		ANI_CHARGEARROWSTART,
	/* 23 쎄게활쏘기		*/		ANI_CHARGEARROWSHOT,
	/* 24 쎄게활루프		*/		ANI_CHARGEARROWLOOP,
	/* 25 뒤로대쉬		*/		ANI_BACKDASH,
	/* 26 돌아서장전		*/		ANI_ARROWSHOWERSTART,
	/* 27 돌아서쏨		*/		ANI_ARROWSHOWERSHOT,
	/* 28 돌아서쏨루프	*/		ANI_ARROWSHOWERLOOP,
	/* 29 빨리활쏘기		*/		ANI_ARROWSHOT,
	/* 30 화남			*/		ANI_ANGRY,
	/* 31 네이놈			*/		ANI_AGGROCHANGE,
};