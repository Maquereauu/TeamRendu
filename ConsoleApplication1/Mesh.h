#pragma once
#include "PrimitiveFactory.h"
class Mesh
{
public: 
	Mesh();
	~Mesh();
	void CreateBoxGeometry();
	void CreateBoxGeometryTex();
	GCGEOMETRY* m_boxGeometry;
	GCGEOMETRYTEXTURE* m_boxGeometryTex;
};

