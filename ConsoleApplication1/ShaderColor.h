#pragma once
#include "Shader.h"
class GCShaderColor : public GCShader
{
public:

	virtual void Initialize(GCRender* pRender) override;


	virtual void CompileShader() override;



};

