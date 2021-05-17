#pragma once
class cObject
{
protected:
	cVec3		m_vPos;
	cVec3		m_vLook, m_vUp, m_vRight;
	float		m_fAngleX, m_fAngleY;		//각 축회전 degree값. 축으로 양의 방향이 0도 기준.
	cMatrixA	m_matWolrd, m_matScale;
	cMatrixA	m_matTrl, m_matRot;

public:
	cObject();
	~cObject();

	// 오브젝트 인터페이스
	virtual void Setup() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	void SetPosition(const cVec3* pvPos);
	void SetPosition(float px, float py, float pz);
	void SetRotation(float rx, float ry, float rz);
	void SetScale(float sx, float sy, float sz);
	void SetWorldMatirx(const cMatrixA* pmatWorld);

	// 현재 오브젝트의 위치, 회전값등으로 메트릭스를 변경하는 함수
	void UpdateTranslation();
	void UpdateRotation();
	void UpdateWorld();
	void UpdateDirection();			//오브젝트의 방향벡터를 구함. 월드의 양의 축단위벡터를 *현재의 회전행렬로* 변환.

	// 오브젝트의 현재 메트릭스값으로 cVec3를 변환시켜주는 함수
	void TransformPosition(cVec3* pvOut);
	void TransformVector(cVec3* pvOut);
	cVec3* GetPosition();
};

