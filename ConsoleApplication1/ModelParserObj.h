#pragma once
#include "header.h"
#include "PrimitiveFactory.h"

struct Geometry;

struct ObjInfo {
	std::vector<std::vector<float>> vertices;
	std::vector<std::vector<std::vector<int>>> indices;
};

class ModelParserObj
{
public:
	ModelParserObj();
	~ModelParserObj();
	ObjInfo ParseObj();
	Geometry BuildObj();
};

