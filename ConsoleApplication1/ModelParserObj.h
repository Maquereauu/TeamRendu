#pragma once
#include "header.h"
#include "PrimitiveFactory.h"
#include "Render.h"

struct Geometry;

struct ObjInfo {
	std::vector<std::vector<float>> coords;
	std::vector<uint16_t> faces;
};

class ModelParserObj
{
public:
	ModelParserObj();
	~ModelParserObj();
	void ParseObj();
	Geometry* BuildObj();

protected:
	ObjInfo m_ParsedObj;
};

