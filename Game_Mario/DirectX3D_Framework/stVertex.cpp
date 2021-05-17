#include "stdafx.h"
#include "stVertex.h"


Vertex_PC::Vertex_PC()
	: pos(0, 0, 0), color(D3DCOLOR_XRGB(0, 0, 0))
{
}


Vertex_PC::Vertex_PC(cVec3 _pos, xColor _color)
	: pos(_pos), color(_color)
{
}



Vertex_PT::Vertex_PT()
	: pos(0, 0, 0), texPos(0, 0)
{
}


Vertex_PT::Vertex_PT(cVec3 _pos, cVec2 _texPos)
	: pos(_pos), texPos(_texPos)
{
}