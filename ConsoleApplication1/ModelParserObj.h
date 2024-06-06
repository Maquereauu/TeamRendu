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
	void Initialize(GCRender* pRender, std::string fileName);
	void ParseObj();
	GCGEOMETRYTEXTURE* BuildObjWithTextures();
	GCGEOMETRY* BuildObj();

private:
	ObjInfo m_ParsedObj;
	GCRender* m_pRender;
	std::string m_fileName;
};

