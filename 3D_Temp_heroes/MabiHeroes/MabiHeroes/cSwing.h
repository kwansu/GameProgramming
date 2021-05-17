#pragma once

#define SWING_ALPHA_DECRESE 5
struct stSwingRect
{
	vector<ST_PCT_VERTEX>	stRectSwing;
	int						stfAlpha;
	bool					stbLife;
	float					stfDeleteTime;
	string					stCreatureName;

	bool					stIsWhite;

};
struct stSwting
{
	D3DXVECTOR3 stUpVec, stDownVec;
	int			stLastAddRect;

	stSwting() {}
	stSwting(D3DXVECTOR3 vecUp, D3DXVECTOR3 vecDown)
	{
		stUpVec = vecUp;
		stDownVec = vecDown;
	}
};

class cSwing
{
private:
	map<string, vector<stSwting>>						m_mapSwing;
	map<string, vector<stSwingRect>>					m_mapSwingRect;			// 실직적으로 그릴것 만 담음.
	map<string, vector<stSwingRect>>::iterator			m_mapiSwingRect;
	
	


public:
	cSwing();
	~cSwing();


	void AddSwing(string CreatureName, D3DXVECTOR3 vecUp, D3DXVECTOR3 vecDown, bool isWhite = false);
	void Update();
	void Reder();
};

