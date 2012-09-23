// external include
#include <sstream>

// Local include
#include "WinMain.hpp"
#include "A2DEngine.hpp"
#include "A2DTimer.hpp"
using namespace Advanced2D;

//macro to read the key states
#define KEY_DOWN(vk) ((GetAsyncKeyState(vk) & 0x8000)?1:0)

HINSTANCE gHInstance;
HWND gHWnd;
int gnCmdShow;

//declare global engine object
Advanced2D::A2DEngine* gpEngine;
bool gGameOver;

//window event callback function
LRESULT WINAPI WinProc( HWND aHWnd, UINT aMsg, WPARAM aWParam, LPARAM aLParam )
{
    switch( aMsg )
    {
    case WM_QUIT:
    case WM_CLOSE:
    case WM_DESTROY:
        {
            gGameOver = true;
        }
        break;
    }

    return DefWindowProc( aHWnd, aMsg, aWParam, aLParam );
}

// Entry Call
int WINAPI WinMain(HINSTANCE aHInstance, HINSTANCE aHPrevInstance, LPSTR aLPCmdLine, int anCmdShow)
{
    MSG msg;
    srand((unsigned int)time(NULL));
    gHInstance = aHInstance;
    gnCmdShow = anCmdShow;
    DWORD dwStyle, dwExStyle;
    RECT windowRect;
    
    // Create engine object first!

    gpEngine = new A2DEngine();
    //let main program have a crack at things before window is created
    if (!GamePreload()) 
    {
        MessageBox(gHWnd, "[WinMain] Error in game preload!", "Error", MB_OK);
        return 0;
    }

    //get window caption string from engine
    char title[255];
    sprintf(title, "%s", gpEngine->GetAppTitle().c_str());

    //set window dimensions
    A2DEngine::ScreenProperties& rScreenProperties = gpEngine->GetScreenProperties();
    windowRect.left = static_cast<long>(0);
    windowRect.right = static_cast<long>(rScreenProperties.mWidth);
    windowRect.top = static_cast<long>(0);
    windowRect.bottom = static_cast<long>(rScreenProperties.mHeight);

    //create the window class structure
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);
    //fill the struct with info
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = (WNDPROC)WinProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = aHInstance;
    wc.hIcon = NULL;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = title;
    wc.hIconSm = NULL;

    //set up the window with the class info
    RegisterClassEx(&wc);

    //set up the screen in windowed or fullscreen mode?
    if (rScreenProperties.mFullScreen)
    {
        DEVMODE dm;
        memset(&dm, 0, sizeof(dm));
        dm.dmSize = sizeof(dm);
        dm.dmPelsWidth = rScreenProperties.mWidth;
        dm.dmPelsHeight = rScreenProperties.mHeight;
        dm.dmBitsPerPel = rScreenProperties.mColorDepth;
        dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

        if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) 
        {
            MessageBox(NULL, "[WinMain] Display mode failed", NULL, MB_OK);
            rScreenProperties.mFullScreen = false;
        }

        dwStyle = WS_POPUP;
        dwExStyle = WS_EX_APPWINDOW;
        ShowCursor(FALSE);
    }
    else 
    {
        dwStyle = WS_OVERLAPPEDWINDOW;
        dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
    }

    //adjust window to true requested size
    AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

    //create the program window
    gHWnd = CreateWindowEx( 
                0,
                title, //window class
                title, //title bar
                dwStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                0, 0, //x,y coordinate
                windowRect.right - windowRect.left, //width of the window
                windowRect.bottom - windowRect.top, //height of the window
                0, //parent window
                0, //menu
                gHInstance, //application instance
                0
            ); //window parameters

    //was there an error creating the window?
    if (!gHWnd) 
    {
        MessageBox(gHWnd, "[WinMain] Error creating program window!", "Error", MB_OK);
        return 0;
    }

    //display the window
    ShowWindow(gHWnd, gnCmdShow);
    UpdateWindow(gHWnd);

    //initialize the engine
    gpEngine->SetWindowHandle(gHWnd);
    if ( !gpEngine->Init(gpEngine->GetScreenProperties()) )
    {
        MessageBox(gHWnd, "[WinMain] Error initializing the engine", "Error", MB_OK);
        return 0;
    }

    // main message loop
    gGameOver = false;
    while (!gGameOver)
    {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        gpEngine->Update();
    }

    if (rScreenProperties.mFullScreen) 
    {
        ShowCursor(TRUE);
    }

    gpEngine->Close();
    delete gpEngine;

    return 1;
} // WinMain