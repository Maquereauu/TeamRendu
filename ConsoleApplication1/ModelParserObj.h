#pragma once
#include "header.h"
#include "PrimitiveFactory.h"
#include "Render.h"

struct Geometry;

struct ObjInfo {
	std::vector<std::vector<float>> coords;
	std::vector<std::vector<uint16_t>> facesInfos;
	std::vector<std::vector<float>> uvs; 
};

class ModelParserObj
{
public:
	ModelParserObj();
	~ModelParserObj();
	void ParseObj();
	GeometryTexture* BuildObj();

protected:
	ObjInfo m_ParsedObj;
};

