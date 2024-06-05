//#include <iostream>
#include "Window.h"
#include "Render.h"
#include "Global.h"


//void DebugOutput(const std::string& message)
//{
//	OutputDebugString(L"Salut");
//	OutputDebugString(L"\n");
//}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{


	/*DebugOutput("App started");*/
	Window* window = new Window(hInstance);
	SetWindow(window);
	window->Initialize();
	GCRender* render = new GCRender();
	SetRender(render);
	render->Initialize();
	window->Run();

}

