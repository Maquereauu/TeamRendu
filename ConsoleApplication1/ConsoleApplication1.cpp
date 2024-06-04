

#include <iostream>
#include "Window.h"
#include "Render.h"
#include "Global.h"

#include "Graphics.h"

void DebugOutput(const std::string& message)
{
	OutputDebugString(L"Salut");
	OutputDebugString(L"\n");
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	Graphics* graphics = new Graphics();
	graphics->Initialize();


	DebugOutput("App started");
	Window* window = new Window(hInstance);
	SetWindow(window);
	window->Initialize();
	Render* render = new Render();
	SetRender(render);
	render->Initialize();
	window->Run();

}

