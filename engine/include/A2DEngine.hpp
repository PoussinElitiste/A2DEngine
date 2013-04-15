#ifndef INC_ADVANCED2D_A2DENGINE_HPP
#define INC_ADVANCED2D_A2DENGINE_HPP

// external include
#include <d3D9.h>
#include <d3Dx9.h>
#include <DxErr.h>
#include <fmod.hpp>
#include <iostream>
#include <windows.h>

// local Include
#include <A2DString.hpp>
#include <A2DArray.hpp>
#include <A2DTypes.hpp>
#include <A2DTemplate.hpp>

// core include
#include <A2DAudio.hpp>
#include <A2DCamera.hpp>
#include <A2DInput.hpp>
#include <A2DMesh.hpp>
#include <A2DLight.hpp>
#include <A2DParticleEmitter.hpp>
#include <A2DSample.hpp>
#include <A2DSprite.hpp>
#include <A2DTexture.hpp>
#include <A2DTimer.hpp>
#include <A2DVector3.hpp>

#define VERSION_MAJOR 1
#define VERSION_MINOR 0
#define REVISION 0

// macro to read the key states(deprecated)
// TODO: replace by A2DInput
#define KEY_DOWN(vk) ((GetAsyncKeyState(vk) & 0x8000)?1:0)

//------------
// Engine API
//------------
using namespace Advanced2D;

// Game
extern bool8 gGameOver;
extern bool8 GamePreload();
extern bool8 GameInit(HWND);
extern void GameUpdate();
extern void GameEnd();
extern void GameRender3D();
extern void GameRender2D();

// Input
extern void GameKeyPress( int32 aKey );
extern void GameKeyRelease( int32 aKey );
extern void GameMouseButton( int32 aButton );
extern void GameMouseMotion( int32 aX, int32 aY );
extern void GameMouseMove( int32 aX, int32 aY );
extern void GameMouseWheel( int32 aWheel );

namespace Advanced2D
{
    typedef D3DCOLOR A2DColor;

    class A2DInput;

    class A2DEngine
    {
    public:
        class ScreenProperties
        {
        public:
            ScreenProperties( int32 aWidth, int32 mHeight, int32 mColorDepth, bool8 mFullScreen);

            void operator()(const ScreenProperties& aScreenConfig);

            int32 mWidth;
            int32 mHeight;
            int32 mColorDepth;
            bool8 mFullScreen;
        }; // ScreenProperties

    private:
        int32 mVersionMajor, mVersionMinor, mRevision;

        HWND mWindowHandle;

        LPDIRECT3D9 mpD3D;
        LPDIRECT3DDEVICE9 mpDevice;
        LPDIRECT3DSURFACE9 mpBackBuffer;
        LPD3DXSPRITE mpSpriteHandler;

        A2DString mAppTitle;

        ScreenProperties mScreenConfig;

        bool8 mPauseMode;
        A2DColor mAmbientColor;
        bool8 mMaximizeProcesser;

        A2DTimer mCoreTimer;
        long32 mFrameCountCore;
        long32 mFrameRateCore;

        A2DTimer mRealTimer;
        long32 mFrameCountReal;
        long32 mFrameRateReal;

        A2DInput* mpInput;

        A2DAudio* mpAudio;

    public:
        A2DEngine();
        virtual ~A2DEngine();

    public:
        int32 Init(const ScreenProperties& aScreenConfig);
        void Close();
        void Update();
        void UpdateKeyboard();
        void UpdateMouse();
        void Message(const A2DString& aMessage, const A2DString& aTitle = "ADVANCED_2D");
        void FatalError(const A2DString& aMessage, const A2DString& aTitle = "FATAL_ERROR");
        void ShutDown();
        void ClearScene(A2DColor aColor);
        void SetIdentity(); // reset scene Position
        void SetDefaultMaterial();
        void SetAmbient(A2DColor aColorValue);
        int32 RenderStart();
        int32 RenderStop();
        int32 Render2DStart();
        int32 Render2DStop();
        int32 Release();

    public:
        // accessor/mutator First order
        bool8 IsPaused() const { return mPauseMode; }
        void SetPaused(bool8 aValue) { mPauseMode = aValue; }

        LPDIRECT3DDEVICE9 GetDevice() const { return mpDevice; }
        LPDIRECT3DSURFACE9 GetBackBuffer() const { return mpBackBuffer; }
        LPD3DXSPRITE GetSpriteHandle() const { return mpSpriteHandler; }

        HWND GetWindowHandle() const { return mWindowHandle; }
        void SetWindowHandle( HWND aHwnd ) { mWindowHandle = aHwnd; }
        
        const A2DString& GetAppTitle() const { return mAppTitle; }
        void SetAppTitle( const A2DString& aNewTitle ) { mAppTitle = aNewTitle; }

        int32 GetVersionMajor() const { return mVersionMajor; }
        int32 GetVersionMinor() const { return mVersionMinor; }
        int32 GetRevision() const { return mRevision; }

        long32 GetFrameRateCore() const { return mFrameCountCore; } 
        long32 GetFrameRateReal() const { return mFrameCountReal; } 

        ScreenProperties& GetScreenProperties() { return mScreenConfig; }
        void SetScreenProperties( const ScreenProperties& aNewProperties) { mScreenConfig = aNewProperties; }

        bool8 GetMaximizeProcessor() const { return mMaximizeProcesser; }
        void SetMaximizeProcessor(bool8 aValue) { mMaximizeProcesser = aValue; }

        A2DString GetVersionText() const;

        A2DAudio* Audio() { return mpAudio; }
    }; //class

}; // namespace

// define global A2DEngine object(visible everywhere!)
extern Advanced2D::A2DEngine* gpEngine;
#endif // INC_ADVANCED2D_A2DENGINE_HPP