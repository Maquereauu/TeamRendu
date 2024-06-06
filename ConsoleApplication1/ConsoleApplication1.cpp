//#include <iostream>
#include "Window.h"
#include "Render.h"
#include "Global.h"
#include "Graphics.h"
#include "Mesh.h"
#include "Texture.h"

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

	graphics->CreateMesh();
	graphics->CreateShader(STEnum::color, L"color");
	graphics->CreateShader(STEnum::texture, L"texture");
	graphics->CreateTexture();


	for (int i = 0; i < graphics->GetTexturesTemplates().size(); i++)
		graphics->GetTexturesTemplates()[i]->Initialize(graphics->m_pRender, "ahah");
	//tex->Initialize(graphicsManager->m_pRender, "ahah");

	graphics->m_pRender->CloseCommandList();
	graphics->m_pRender->ExecuteCommandList();


	//GCRender* render = new GCRender();
	////SetRender(render);
	//render->Initialize();

	window->Run(graphics->m_pRender);

}

