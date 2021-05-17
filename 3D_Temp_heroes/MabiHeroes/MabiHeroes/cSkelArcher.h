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
	/*  0 �ȱ�			*/		ANI_WALK,
	/*  1 �����غ�		*/		ANI_WAIT,
	/*  2 ���̵�			*/		ANI_UNARMEDWAIT,
	/*  3 Ȱ���			*/		ANI_THROUGHARROWSTART,
	/*  4 ???			*/		ANI_THROUGHARROWSHOT,
	/*  5 �߻����		*/		ANI_THROUGHARROWLOOP,
	/*  6 ���ϱ�			*/		ANI_TALK,
	/*  7 ���ϻ���		*/		ANI_STUN,
	/*  8 ���ȱ�(��)		*/		ANI_SIDEWALK02,
	/*  9 ���ȱ�(��)		*/		ANI_SIDEWALK01,
	/* 10 �ٱ�			*/		ANI_RUN,
	/* 11 ����			*/		ANI_LAUGH,
	/* 12 ���󰡱�		*/		ANI_KNOCKBACKSTART,
	/* 13 �������ֱ�		*/		ANI_KNOCKBACKLOOP,
	/* 14 �Ͼ��		*/		ANI_KNOCKBACKEND,
	/* 15 �±�			*/		ANI_FLINCH,
	/* 16 ������		*/		ANI_DYINGWAIT,
	/* 17 ���糯�󰡱�	*/		ANI_DOWNSTART,
	/* 18 �������ֱ�		*/		ANI_DOWNLOOP,
	/* 19 �Ͼ��		*/		ANI_DOWNEND,
	/* 20 �׾�����		*/		ANI_DEATHWAIT,
	/* 21 �װ�����		*/		ANI_DEATH,
	/* 22 ���Ȱ����		*/		ANI_CHARGEARROWSTART,
	/* 23 ���Ȱ���		*/		ANI_CHARGEARROWSHOT,
	/* 24 ���Ȱ����		*/		ANI_CHARGEARROWLOOP,
	/* 25 �ڷδ뽬		*/		ANI_BACKDASH,
	/* 26 ���Ƽ�����		*/		ANI_ARROWSHOWERSTART,
	/* 27 ���Ƽ���		*/		ANI_ARROWSHOWERSHOT,
	/* 28 ���Ƽ�������	*/		ANI_ARROWSHOWERLOOP,
	/* 29 ����Ȱ���		*/		ANI_ARROWSHOT,
	/* 30 ȭ��			*/		ANI_ANGRY,
	/* 31 ���̳�			*/		ANI_AGGROCHANGE,
};