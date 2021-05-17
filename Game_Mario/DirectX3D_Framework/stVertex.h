#pragma once


struct Vertex_PC
{
	cVec3	pos;
	xColor	color;

	Vertex_PC();
	Vertex_PC(cVec3 _pos, xColor _color = D3DCOLOR_XRGB(0, 0, 0));
	enum  { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
};



struct Vertex_PT
{
	cVec3	pos;
	cVec2	texPos;

	Vertex_PT();
	Vertex_PT(cVec3 _pos, cVec2 _texPos = cVec2(0, 0));
	enum  { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
};

