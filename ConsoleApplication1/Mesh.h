#pragma once
#include "PrimitiveFactory.h"
class Mesh
{
public: 
	Mesh();
	~Mesh();
	void CreateBoxGeometry();
	GCGEOMETRY* m_boxGeometry;
};

