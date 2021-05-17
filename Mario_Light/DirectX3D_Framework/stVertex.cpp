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



Vertex_PN::Vertex_PN(cVec3 _pos, cVec3 _normal)
	: pos(_pos), normal(_normal)
{
}



Vertex_PNT::Vertex_PNT(cVec3 _pos, cVec3 _normal, cVec2 _texPos)
: pos(_pos), normal(_normal), texPos(_texPos)
{
}
