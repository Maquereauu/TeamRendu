#pragma once
#include "header.h"
#include "PrimitiveFactory.h"
#include "Render.h"

struct GCGEOMETRYTEXTURE;

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
	GCGEOMETRYTEXTURE* BuildObj();

protected:
	ObjInfo m_ParsedObj;
	GCRender* m_pRender;
};

