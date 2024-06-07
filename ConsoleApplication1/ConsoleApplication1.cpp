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
	Window* window = new Window(hInstance);
	window->Initialize();
	SetWindow(window);


	


	//GCRender* render = new GCRender();
	////SetRender(render);
	//render->Initialize();

	window->Run();

}

