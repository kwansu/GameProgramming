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

	// ������Ʈ �⺻ ���:
	virtual void SetPosition(const D3DXVECTOR3* pvPos);
	virtual void SetDirection(const D3DXVECTOR3* pvDir);
	virtual void SetPosition(float px, float py, float pz);
	virtual void SetRotation(float rx, float ry, float rz);
	virtual void SetScale(float ratio);
	virtual void SetScale(float sx, float sy, float sz);
	virtual void SetWorldMatirx(const D3DXMATRIXA16* pmatWorld);
	virtual void SetWorldMatirxFromParent(const D3DXMATRIXA16* pmatWorld);

	// ���� ������Ʈ�� ��ġ, ȸ���������� ��Ʈ������ �����ϴ� �Լ�
	virtual void UpdateTranslation();
	virtual void UpdateRotation();
	virtual void UpdateScaling();
	virtual void UpdateDirection();			// ������Ʈ�� ���⺤�͸� ����. ������ ���� ��������͸� *������ ȸ����ķ�* ��ȯ.
	virtual void UpdateWorld();
	virtual void UpdateTransform();			// ũ��, ȸ��, �̵���ȯ�� ��� �����ؼ� ���带 ������Ʈ�ϴ� �Լ�

	// ������Ʈ�� ���� ��Ʈ���������� D3DXVECTOR3�� ��ȯ�����ִ� �Լ�
	virtual void TransformPosition(OUT D3DXVECTOR3* pvOut);
	virtual void TransformVector(OUT D3DXVECTOR3* pvOut);

	// Get �Լ�
	virtual D3DXVECTOR3& GetPosition();

	virtual D3DXVECTOR3 GetDirection(){ return m_vDir; }
	virtual D3DXVECTOR3 GetRotYdir() { return m_vRot; }
	virtual D3DXVECTOR3 GetRightDir() { return m_vRight; }
};

