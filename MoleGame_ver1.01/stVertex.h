#pragma once

struct stVertex_PC
{
	cVec3	pos;
	xColor	color;

	stVertex_PC();
	stVertex_PC(cVec3 _pos, xColor _color);
};


struct stVertex_PT
{
	cVec3	pos;
	cVec2	texPos;

	stVertex_PT(cVec3 _pos);
	stVertex_PT(cVec3 _pos, cVec2 _texPos);
};

