#pragma once
#include "header.h"
#include "PrimitiveFactory.h"
#include "Render.h"

class GCMesh;
class GCGeometry;
class GCGeometryColor;
class GCGeometryTexture;

struct GCVERTEX;
struct GCVERTEXTEXTURE;

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

	GCGeometryColor* BuildObjColor();
	GCGeometryTexture* BuildObjTexture();


private:
	ObjInfo m_ParsedObj;
	GCRender* m_pRender;
	std::string m_fileName;
};

