// Local include
#include <A2DEngine.hpp>
#include <A2DInput.hpp>
#include <WinMain.hpp>

// External include
#include <cstdlib>
#include <ctime>
#include <list>
#include <sstream>

namespace Advanced2D
{
    A2DEngine::ScreenProperties::ScreenProperties( int32 aWidth, int32 aHeight, int32 aColorDepth, bool8 aFullScreen )
        : mWidth(aWidth)
        , mHeight(aHeight)
        , mColorDepth(aColorDepth)
        , mFullScreen(aFullScreen)
    {}

    void A2DEngine::ScreenProperties::operator()(const ScreenProperties& aScreenConfig)
    {
        mWidth = aScreenConfig.mWidth;
        mHeight = aScreenConfig.mHeight;
        mColorDepth = aScreenConfig.mColorDepth;
        mFullScreen = aScreenConfig.mFullScreen;
    }

    A2DEngine::A2DEngine()
        : mMaximizeProcesser(false)
        , mFrameCountCore(0)
        , mFrameRateCore(0)
        , mFrameCountReal(0)
        , mFrameRateReal(0)
        , mAmbientColor(D3DCOLOR_RGBA(255, 255, 255, 0))
        , mWindowHandle(0)
        , mPauseMode(false)
        , mVersionMajor(VERSION_MAJOR)
        , mVersionMinor(VERSION_MINOR)
        , mRevision(REVISION)
        , mScreenConfig(640, 480, 32, false)
        , mpBackBuffer(nullptr)
        , mpD3D(nullptr)
        , mpDevice(nullptr)
        , mpInput(nullptr)
        , mpSpriteHandler(nullptr)
    {
        srand(static_cast<uint32>(time(NULL)));

        // set default value
        SetAppTitle("Advanced2D");
    }

    A2DEngine::~A2DEngine()
    {
        if (mpDevice)
        {
            mpDevice->Release();
        }

        if (mpD3D)
        {
            mpD3D->Release();
        }
    }

    A2DString A2DEngine::GetVersionText() const
    {
        std::ostringstream stream;
        stream << "Advanced2D Engine V" << mVersionMajor << "." << mVersionMinor << "." << mRevision;
        return stream.str();
    }

    void A2DEngine::Message(const A2DString& aMessage, const A2DString& aTitle /*= "ADVANCED_2D"*/)
    {
        MessageBox(0, aMessage.c_str(), aTitle.c_str(), 0);
    }

    void A2DEngine::FatalError(const A2DString& aMessage, const A2DString& aTitle /*= "FATAL_ERROR"*/)
    {
        Message(aMessage,aTitle);
        ShutDown();
    }

    int32 A2DEngine::Init(const ScreenProperties& aScreenConfig)
    {
        //---------------------
        // initialize Direct3D
        //---------------------

        mpD3D = Direct3DCreate9(D3D_SDK_VERSION);
        if (nullptr == mpD3D) 
        { return 0; }

        // get system desktop color depth
        D3DDISPLAYMODE displayMode;
        mpD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode);

        //set configuration options for Direct3D
        D3DPRESENT_PARAMETERS D3DParameters;
        ZeroMemory(&D3DParameters, sizeof(D3DParameters));
        D3DParameters.Windowed = (!mScreenConfig.mFullScreen);
        D3DParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
        D3DParameters.EnableAutoDepthStencil = TRUE;
        D3DParameters.AutoDepthStencilFormat = D3DFMT_D16;
        D3DParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
        D3DParameters.BackBufferFormat = displayMode.Format;
        D3DParameters.BackBufferCount = 1;
        D3DParameters.BackBufferWidth = aScreenConfig.mWidth;
        D3DParameters.BackBufferHeight = aScreenConfig.mHeight;
        D3DParameters.hDeviceWindow = mWindowHandle;

        //create Direct3D device
        mpD3D->CreateDevice(
            D3DADAPTER_DEFAULT,
            D3DDEVTYPE_HAL,
            mWindowHandle,
            D3DCREATE_HARDWARE_VERTEXPROCESSING,
            &D3DParameters,
            &mpDevice);

        if ( nullptr == mpDevice ) 
        { return 0; }

        //clear the backbuffer to black
        ClearScene(D3DCOLOR_XRGB(0,0,0));

        //create pointer to the back buffer
        mpDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &mpBackBuffer);

        //use ambient lighting and z-buffering
        mpDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
        mpDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        SetAmbient(mAmbientColor);

        //initialize 2D renderer
        HRESULT result = D3DXCreateSprite(mpDevice, &mpSpriteHandler);

        if (result != D3D_OK) 
        { return 0; }

        //call game initialization extern function
        if (!GameInit(GetWindowHandle()))
        { return 0; }

        //set a default material
        SetDefaultMaterial();

        //------------------------
        // initialize DirectInput
        //------------------------

        mpInput = new A2DInput(GetWindowHandle());

        return 1;
    }

    void A2DEngine::SetDefaultMaterial()
    {
        D3DMATERIAL9 material;
        memset(&material, 0, sizeof(material));
        material.Diffuse.r = 1.0f;
        material.Diffuse.g = 1.0f;
        material.Diffuse.b = 1.0f;
        material.Diffuse.a = 1.0f;
        mpDevice->SetMaterial(&material);
    }

    void A2DEngine::ClearScene(A2DColor aColor)
    {
        mpDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, aColor, 1.0f, 0);
    }

    void A2DEngine::SetIdentity()
    {
        D3DXMATRIX mat;
        D3DXMatrixIdentity(&mat);
        
        mpDevice->SetTransform(D3DTS_WORLD, &mat);
    }

    void A2DEngine::SetAmbient(A2DColor aColorValue)
    {
        mAmbientColor = aColorValue;
        mpDevice->SetRenderState(D3DRS_AMBIENT, mAmbientColor);
    }

    int32 A2DEngine::RenderStart()
    {
        if (nullptr == mpDevice)
        { return 0; }

        if ( mpDevice->BeginScene() != D3D_OK )
        { return 0; }

        return 1;
    }

    int32 A2DEngine::RenderStop()
    {
        if ( nullptr == mpDevice )
        { return 0; }

        if ( mpDevice->EndScene() != D3D_OK )
        { return 0; }

        if ( mpDevice->Present(NULL, NULL, NULL, NULL) != D3D_OK )
        { return 0; }

        return 1;
    }

    int32 A2DEngine::Render2DStart()
    {
        if ( mpSpriteHandler->Begin(D3DXSPRITE_ALPHABLEND) != D3D_OK )
        { return 0; }
        else
        { return 1; }
    }

    int32 A2DEngine::Render2DStop()
    {
        mpSpriteHandler->End();
        return 1;
    }

    void A2DEngine::ShutDown()
    {
        gGameOver = true;
    }

    void A2DEngine::Update()
    {
        static A2DTimer timedUpdate;

        // Calculate core framerate
        ++mFrameCountCore;
        if (mCoreTimer.StopWatch(999)) 
        {
            mFrameRateCore = mFrameCountCore;
            mFrameCountCore = 0;
        }

        //-------
        // Input
        //-------
        mpInput->Update();
        UpdateKeyboard();
        UpdateMouse();

        //-------
        // Game
        //-------
        // Fast update with no timing
        GameUpdate();

        //--------
        // Render
        //--------
        // Update with 60fps timing
        if ( !timedUpdate.StopWatch(14) ) 
        {
            if ( !GetMaximizeProcessor() )
            {
                Sleep(1);
            }
        }
        else 
        {
            // Calculate real framerate
            ++mFrameCountReal;
            if (mRealTimer.StopWatch(999)) 
            {
                mFrameRateReal = mFrameCountReal;
                mFrameCountReal = 0;
            }

            //return to the origin
            SetIdentity();

            // Begin rendering
            RenderStart();

            // Allow game to 3D render
            GameRender3D();

            // Allow game to 2D render
            Render2DStart();
            GameRender2D();
            Render2DStop();

            // Done rendering
            RenderStop();
        }
    }

    void A2DEngine::UpdateMouse()
    {
        static int32 oldPosX = 0;
        static int32 oldPosY = 0;

        int32 deltaX = mpInput->GetDeltaX();
        int32 deltaY = mpInput->GetDeltaY();

        //check mouse buttons 1-3
        for (int32 n=0; n<4; ++n) 
        {
            if (mpInput->GetMouseButton(n))
            { GameMouseButton(n); }
        }

        //check mouse position
        if (mpInput->GetPosX() != oldPosX || mpInput->GetPosY() != oldPosY) 
        {
            GameMouseMove( mpInput->GetPosX(), mpInput->GetPosY() );
            oldPosX = mpInput->GetPosX();
            oldPosY = mpInput->GetPosY();
        }

        //check mouse motion
        if (deltaX != 0 || deltaY ) 
        { GameMouseMotion(deltaX, deltaY); }

        //check mouse wheel
        int32 wheel = mpInput->GetDeltaWheel();
        if (wheel != 0)
        { GameMouseWheel(wheel); }
    }

    void A2DEngine::UpdateKeyboard()
    {
        static char oldKeys[256];
        for (int32 n=0; n<255; ++n)
        {
            //check for key press
            if (mpInput->GetKeyState(n) & 0x80) 
            {
                GameKeyPress(n);
                oldKeys[n] = mpInput->GetKeyState(n);
            }//check for release
            else if (oldKeys[n] & 0x80) 
            {
                GameKeyRelease(n);
                oldKeys[n] = mpInput->GetKeyState(n);
            }
        }
    }

    void A2DEngine::Close()
    {
        GameEnd();
    }
}; // namespace