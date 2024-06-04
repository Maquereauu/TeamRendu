#pragma once
#include "PrimitiveFactory.h"
class Mesh
{
public: 
	Mesh();
	~Mesh();
	void CreateBoxGeometry();
	Geometry* m_boxGeometry;
};

