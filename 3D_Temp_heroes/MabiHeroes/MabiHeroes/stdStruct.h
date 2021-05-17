#pragma once
struct ST_PCT_VERTEX
{
	D3DXVECTOR3 p;
	D3DCOLOR	c;
	D3DXVECTOR2 t;
	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 };
};
struct ST_PC_VERTEX
{
	D3DXVECTOR3 p;
	D3DCOLOR	c;

	ST_PC_VERTEX()
		: p(0, 0, 0)
		, c(D3DCOLOR_XRGB(255, 255, 255))
	{

	}
	ST_PC_VERTEX(D3DXVECTOR3 _p, D3DCOLOR _c)
		: p(_p)
		, c(_c)
	{
	}

	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE, };
};


struct ST_PN_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3	n;

	ST_PN_VERTEX()
		: p(0, 0, 0)
		, n(0, 0, 0)
	{

	}
	ST_PN_VERTEX(D3DXVECTOR3 _p, D3DXVECTOR3 _n)
		: p(_p)
		, n(_n)
	{
	}

	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL, };
};


struct ST_PNT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3	n;
	D3DXVECTOR2	t;

	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1, };
};


struct ST_PT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR2 t;

	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1, };
};


struct ST_RHWC_VERTEX
{
	D3DXVECTOR4 p;
	D3DCOLOR	c;

	enum { FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE, };
};


struct ST_POS_SAMPLE
{
	int				nKeyFrame;
	D3DXVECTOR3		p;
};


struct ST_ROT_SAMPLE
{
	int				nKeyFrame;
	D3DXQUATERNION	q;
};


struct ST_SIZEF
{
	float fWidth;
	float fHeight;

	ST_SIZEF()
		: fWidth(0)
		, fHeight(0) {}

	ST_SIZEF(float w, float h)
		: fWidth(w)
		, fHeight(h) {}
};


struct ST_RAY
{
	D3DXVECTOR3 vOri;
	D3DXVECTOR3 vDir;
};


struct ST_PLANE
{
	D3DXVECTOR3 vOther;
	D3DXVECTOR3 vNormal;
};


struct ST_SPHERE
{
	D3DXVECTOR3 vOffset;
	float		fRadius;
	
	ST_SPHERE()
		: vOffset(0, 0, 0)
		, fRadius(1) {}
};


struct ST_COLLISION_SPHERE
{
	D3DXVECTOR3 vCenter;
	float		fRadius;

	ST_COLLISION_SPHERE()
		: vCenter(0, 0, 0)
		, fRadius(1) {}
};


// 오브젝트의 본에 붙일 충돌체
struct ST_COLLISION_BOX_STICK
{
	D3DXMATRIXA16*	pmatSticking;
	D3DXMATRIXA16	matOffset;
	D3DXVECTOR3		vHalfSize;


	ST_COLLISION_BOX_STICK()
		: vHalfSize(2, 2, 2)
	{
		D3DXMatrixIdentity(&matOffset);
	}
	void SetMatOffset(D3DXMATRIXA16* mat)
	{
		matOffset = *mat;
	}
	void SetHalfSize(D3DXVECTOR3 vec)
	{
		vHalfSize = vec;
	}
};


struct ST_MISILE
{
	bool					isActive;
	float					fActiveTime;
	D3DXMATRIXA16			matWorld;
	D3DXVECTOR3				vDir;
	ST_COLLISION_BOX_STICK	stAttackBox;
	D3DXVECTOR3				vPos;

	ST_MISILE()
		: vDir(0, 0, 1)
		, isActive(false)
		, fActiveTime(0)
	{
		D3DXMatrixIdentity(&matWorld);
		stAttackBox.pmatSticking = &matWorld;
	}

	inline void Update()
	{
		matWorld._41 += vDir.x;
		matWorld._42 += vDir.y;
		matWorld._43 += vDir.z;
		vPos.x = matWorld._41;
		vPos.y = matWorld._42;
		vPos.z = matWorld._43;

		fActiveTime -= g_fDeltaTime;

		if (fActiveTime < 0)
		{
			isActive = false;

		}
	}
};
