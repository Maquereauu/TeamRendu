#pragma once
#include "PrimitiveFactory.h"
#include "ModelParserObj.h"

class PrimitiveFactory;

class ModelParserObj;

class Mesh
{
public: 
	Mesh();
	~Mesh();
	void CreateBoxGeometry();
	void CreateObjGeometry();
	Geometry* GetBoxGeometry();

protected :
	Geometry* m_boxGeometry;
	GeometryTexture* m_GeoTextures;
};

