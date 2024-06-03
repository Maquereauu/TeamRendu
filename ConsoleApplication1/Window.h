#pragma once
//#include "header.h"
#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif
#include "d3dUtil.h"
#include "Timer.h"

// Link necessary d3d12 libraries.

class Window
{


public:

    Window(HINSTANCE hInstance);
    Window(const Window& rhs) = delete;
    Window& operator=(const Window& rhs) = delete;
    ~Window();
    static Window* GetApp();

    HINSTANCE AppInst()const;
    HWND      MainWnd()const;
    float     AspectRatio()const;

    bool Get4xMsaaState()const;
    void Set4xMsaaState(bool value);

    int Run();

    virtual bool Initialize();
    virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    DXGI_FORMAT mDepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
    DXGI_FORMAT mBackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
    bool      m4xMsaaState = false;    // 4X MSAA enabled
    UINT      m4xMsaaQuality = 0;      // quality level of 4X MSAA
private:
    void Update(const Timer& gt);
    void Draw(const Timer& gt);

    virtual void OnResize() { }

private:

    bool InitMainWindow();

    void CalculateFrameStats();

    void LogAdapters();
    void LogAdapterOutputs(IDXGIAdapter* adapter);
    void LogOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format);

private:

    static Window* mApp;

    HINSTANCE mhAppInst = nullptr; // application instance handle
    HWND      mhMainWnd = nullptr; // main window handle
    bool      mAppPaused = false;  // is the application paused?
    bool      mMinimized = false;  // is the application minimized?
    bool      mMaximized = false;  // is the application maximized?
    bool      mResizing = false;   // are the resize bars being dragged?
    bool      mFullscreenState = false;// fullscreen enabled

    // Set true to use 4X MSAA (§4.1.8).  The default is false.

    // Used to keep track of the “delta-time” and game time (§4.4).
    Timer mTimer;
    IDXGIFactory4* mdxgiFactory;
    // Derived class should set these in derived constructor to customize starting values.
    std::wstring mMainWndCaption = L"Noeil";
    int mClientWidth = 1920;
    int mClientHeight = 1080;
};