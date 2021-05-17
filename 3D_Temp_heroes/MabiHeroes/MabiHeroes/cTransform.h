#pragma once
class cTransform
{
protected:
	D3DXVECTOR3		m_vPos;
	D3DXVECTOR3		m_vDir;
	D3DXVECTOR3		m_vRight;
	D3DXVECTOR3		m_vRot;
	D3DXVECTOR3		m_vScale;
	

	D3DXMATRIXA16	m_matWorld;
	D3DXMATRIXA16	m_matS, m_matR, m_matT;

public:
	cTransform();
	virtual ~cTransform();

	// 오브젝트 기본 기능:
	virtual void SetPosition(const D3DXVECTOR3* pvPos);
	virtual void SetDirection(const D3DXVECTOR3* pvDir);
	virtual void SetPosition(float px, float py, float pz);
	virtual void SetRotation(float rx, float ry, float rz);
	virtual void SetScale(float ratio);
	virtual void SetScale(float sx, float sy, float sz);
	virtual void SetWorldMatirx(const D3DXMATRIXA16* pmatWorld);
	virtual void SetWorldMatirxFromParent(const D3DXMATRIXA16* pmatWorld);

	// 현재 오브젝트의 위치, 회전값등으로 메트릭스를 변경하는 함수
	virtual void UpdateTranslation();
	virtual void UpdateRotation();
	virtual void UpdateScaling();
	virtual void UpdateDirection();			// 오브젝트의 방향벡터를 구함. 월드의 양의 축단위벡터를 *현재의 회전행렬로* 변환.
	virtual void UpdateWorld();
	virtual void UpdateTransform();			// 크기, 회전, 이동변환을 모두 실행해서 월드를 업데이트하는 함수

	// 오브젝트의 현재 메트릭스값으로 D3DXVECTOR3를 변환시켜주는 함수
	virtual void TransformPosition(OUT D3DXVECTOR3* pvOut);
	virtual void TransformVector(OUT D3DXVECTOR3* pvOut);

	// Get 함수
	virtual D3DXVECTOR3& GetPosition();

	virtual D3DXVECTOR3 GetDirection(){ return m_vDir; }
	virtual D3DXVECTOR3 GetRotYdir() { return m_vRot; }
	virtual D3DXVECTOR3 GetRightDir() { return m_vRight; }
};

