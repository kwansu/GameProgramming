#pragma once

class cGrid
{
private:
	vector<Vertex_PC>	m_aVertex;
	cMatrixA			m_matInterval;
	int					m_nLine;

public:
	cGrid();
	~cGrid();
	void Setup();
	void Render();
	// 격자 사이 간격
	void SetInterval(float fInterval);
};

