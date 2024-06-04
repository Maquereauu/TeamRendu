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

GCRender* g_pRender = nullptr;

void SetRender(GCRender* pRender)
{
	g_pRender = pRender;
}

GCRender* GetRender()
{
	return g_pRender;
}
