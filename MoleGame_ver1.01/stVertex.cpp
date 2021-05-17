#include "stdafx.h"
#include "stVertex.h"


stVertex_PC::stVertex_PC()
	: pos(0, 0, 0), color(D3DCOLOR_XRGB(255, 255, 255))
{
}


stVertex_PC::stVertex_PC(cVec3 _pos, xColor _color)
	: pos(_pos), color(_color)
{
}




stVertex_PT::stVertex_PT(cVec3 _pos)
	: pos(_pos), texPos(0, 0)
{
}


stVertex_PT::stVertex_PT(cVec3 _pos, cVec2 _texPos)
	: pos(_pos), texPos(_texPos)
{
}

