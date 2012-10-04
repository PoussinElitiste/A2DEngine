#ifndef INC_ADVANCED2D_A2DENGINE_HPP
#define INC_ADVANCED2D_A2DENGINE_HPP

// external include
#include <iostream>
#include <windows.h>
#include <d3D9.h>
#include <d3Dx9.h>
#include <DxErr.h>

// local include
#include "A2DTimer.hpp"
#include "A2DString.hpp"
#include "A2DTypes.hpp"

#define VERSION_MAJOR 1
#define VERSION_MINOR 0
#define REVISION 0

extern Advanced2D::bool8 gGameOver;

extern Advanced2D::bool8 GamePreload();
extern Advanced2D::bool8 GameInit(HWND);
extern void GameUpdate();
extern void GameEnd();
extern void GameRender3D();

namespace Advanced2D
{
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
        };

        A2DEngine();
        virtual ~A2DEngine();

        int32 Init(const ScreenProperties& aScreenConfig);
        void Close();
        void Update();
        void Message(const A2DString& aMessage, const A2DString& aTitle = "ADVANCED_2D");
        void FatalError(const A2DString& aMessage, const A2DString& aTitle = "FATAL_ERROR");
        void ShutDown();
        void ClearScene(D3DCOLOR aColor);
        void SetDefaultMaterial();
        void SetAmbient(D3DCOLOR aColorValue);
        int32 RenderStart();
        int32 RenderStop();
        int32 Release();

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

        // Accessor Second order
        A2DString GetVersionText() const;

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
        D3DCOLOR mAmbientColor;
        bool8 mMaximizeProcesser;

        A2DTimer mCoreTimer;
        long32 mFrameCountCore;
        long32 mFrameRateCore;

        A2DTimer mRealTimer;
        long32 mFrameCountReal;
        long32 mFrameRateReal;
    }; //class

}; // namespace

// define global A2DEngine object(visible everywhere!)
extern Advanced2D::A2DEngine* gpEngine;
#endif // INC_ADVANCED2D_A2DENGINE_HPP