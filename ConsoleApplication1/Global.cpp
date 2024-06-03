#include "Global.h"

Window* g_pWindow = nullptr;

void SetWindow(Window* pWindow)
{
	g_pWindow = pWindow;
}

Window* GetWindow()
{
	return g_pWindow;
}

Render* g_pRender = nullptr;

void SetRender(Render* pRender)
{
	g_pRender = pRender;
}

Render* GetRender()
{
	return g_pRender;
}
