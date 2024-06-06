//#include <iostream>
#include "Window.h"
#include "Render.h"
#include "Global.h"
#include "Graphics.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"

//void DebugOutput(const std::string& message)
//{
//	OutputDebugString(L"Salut");
//	OutputDebugString(L"\n");
//}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{


	/*DebugOutput("App started");*/
	Window* window = new Window(hInstance);
	window->Initialize();
	SetWindow(window);


	GCGraphics* graphics = new GCGraphics();
	graphics->Initialize();


	graphics->m_pRender->ResetCommandList();

	GCMesh* mesh = graphics->CreateMesh();
	GCShader* shader1 = graphics->CreateShader(STEnum::color, L"color");
	GCShader* shader2 = graphics->CreateShader(STEnum::texture, L"texture");

	GCMaterial* material1 = graphics->CreateMaterial();
	material1->AddTexture("ahah", graphics);

	//graphics->CreateTexture("ahah");


	graphics->m_pRender->CloseCommandList();
	graphics->m_pRender->ExecuteCommandList();


	//GCRender* render = new GCRender();
	////SetRender(render);
	//render->Initialize();

	window->Run(graphics->m_pRender);

}

