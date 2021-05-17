#pragma once
class cObject
{
protected:
	cVec3		m_vPos;
	cVec3		m_vLook, m_vUp, m_vRight;
	float		m_fAngleX, m_fAngleY;		//�� ��ȸ�� degree��. ������ ���� ������ 0�� ����.
	cMatrixA	m_matWolrd, m_matScale;
	cMatrixA	m_matTrl, m_matRot;

public:
	cObject();
	~cObject();

	// ������Ʈ �������̽�
	virtual void Setup() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	void SetPosition(const cVec3* pvPos);
	void SetPosition(float px, float py, float pz);
	void SetRotation(float rx, float ry, float rz);
	void SetScale(float sx, float sy, float sz);
	void SetWorldMatirx(const cMatrixA* pmatWorld);

	// ���� ������Ʈ�� ��ġ, ȸ���������� ��Ʈ������ �����ϴ� �Լ�
	void UpdateTranslation();
	void UpdateRotation();
	void UpdateWorld();
	void UpdateDirection();			//������Ʈ�� ���⺤�͸� ����. ������ ���� ��������͸� *������ ȸ����ķ�* ��ȯ.

	// ������Ʈ�� ���� ��Ʈ���������� cVec3�� ��ȯ�����ִ� �Լ�
	void TransformPosition(cVec3* pvOut);
	void TransformVector(cVec3* pvOut);
	cVec3* GetPosition();
};

