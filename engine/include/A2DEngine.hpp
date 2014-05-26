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
#include <A2DList.hpp>
#include <A2DTypes.hpp>
#include <A2DTemplate.hpp>

// core include
#include <A2DAudio.hpp>
#include <A2DCamera.hpp>
#include <A2DConsole.hpp>
#include <A2DEntity.hpp>
#include <A2DFont.hpp>
#include <A2DInput.hpp>
#include <A2DMesh.hpp>
#include <A2DLight.hpp>
#include <A2DParticleEmitter.hpp>
#include <A2DRectangle.hpp>
#include <A2DSample.hpp>
#include <A2DSprite.hpp>
#include <A2DTexture.hpp>
#include <A2DTimer.hpp>
#include <A2DVector3.hpp>
#include <A2DMath.hpp>

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
extern void GameEntityUpdate(A2DEntityPtr apEntity);
extern void GameEntityRender(A2DEntityPtr apEntity);

// Input
extern void GameKeyPress( uint32 aKey );
extern void GameKeyRelease( uint32 aKey );
extern void GameMouseButton( uint32 aButton );
extern void GameMouseWheel( uint32 aWheel );
extern void GameMouseMotion( int32 aX, int32 aY );
extern void GameMouseMove( int32 aX, int32 aY );

// Physic
extern void GameEntityCollision(A2DEntityPtr apFirst, A2DEntityPtr apSecond);

namespace Advanced2D
{
   typedef D3DCOLOR A2DColor;

   class A2DInput;

   class A2DEngine
   {
      typedef A2DList<A2DEntityPtr>             EntityList;
      typedef A2DList<A2DEntityPtr>::iterator   EntityListIt;
   public:
      class ScreenProperties
      {
      public:
         ScreenProperties( int32 aWidth, int32 mHeight, int32 mColorDepth, bool8 mFullScreen);

         void operator()(const ScreenProperties &aScreenConfig);

         int32 mWidth;
         int32 mHeight;
         int32 mColorDepth;
         bool8 mFullScreen;
      }; // ScreenProperties

   private:
      int32 mVersionMajor, mVersionMinor, mRevision;

      HWND mWindowHandle;

      LPDIRECT3D9          mpD3D;
      LPDIRECT3DDEVICE9    mpDevice;
      LPDIRECT3DSURFACE9   mpBackBuffer;
      LPD3DXSPRITE         mpSpriteHandler;

      A2DString   mAppTitle;

      ScreenProperties mScreenConfig;

      bool8    mPauseMode;
      A2DColor mAmbientColor;
      bool8    mMaximizeProcesser;

      A2DTimer mCoreTimer;
      long32   mFrameCountCore;
      long32   mFrameRateCore;

      A2DTimer mRealTimer;
      long32   mFrameCountReal;
      long32   mFrameRateReal;

      A2DInputPtr mpInput;
      A2DAudioPtr mpAudio;
      EntityList  mpEntities;

   public:
      A2DEngine();
      virtual ~A2DEngine();

   public:
      void update();
      void updateKeyboard();
      void updateMouse();

      // Debug
      A2DString getVersionText() const;
      void message(const A2DString &aMessage, const A2DString &aTitle = "ADVANCED_2D");
      void fatalError(const A2DString &aMessage, const A2DString &aTitle = "FATAL_ERROR");

      // Service
      int32 init(const ScreenProperties &aScreenConfig);
      void close();
      void shutDown();
      void clearScene(A2DColor aColor);
      int32 release();

      void setIdentity(); // reset scene Position
      void setDefaultMaterial();
      void setAmbient(A2DColor aColorValue);

      // Render
      int32 renderStart();
      int32 renderStop();
      int32 render2DStart();
      int32 render2DStop();

      // entities
      void addEntity(A2DEntityPtr apEntity);
      A2DEntityPtr findEntity(int32 aObjectType);
      A2DEntityPtr findEntity(A2DString aName);
      int32 getEntityCount() const;
      void updateEntities();
      void draw3DEntities();
      void draw2DEntities();
      void buryEntities();

      // Physic
      bool8 collision(A2DSpritePtr apSprite1, A2DSpritePtr apSprite2);
      bool8 collisionBR(A2DSpritePtr apSprite1, A2DSpritePtr apSprite2);
      bool8 collisionD(A2DSpritePtr apSprite1, A2DSpritePtr apSprite2);
      void testForCollisions();

   // accessors / mutator First order
   public:
      bool8 isPaused() const { return mPauseMode; }
      void setPaused(bool8 aValue) { mPauseMode = aValue; }

      LPDIRECT3DDEVICE9 getDevice() const { return mpDevice; }
      LPDIRECT3DSURFACE9 getBackBuffer() const { return mpBackBuffer; }
      LPD3DXSPRITE getSpriteHandle() const { return mpSpriteHandler; }

      HWND getWindowHandle() const { return mWindowHandle; }
      void setWindowHandle( HWND aHwnd ) { mWindowHandle = aHwnd; }
        
      const A2DString& getAppTitle() const { return mAppTitle; }
      void setAppTitle( const A2DString& aNewTitle ) { mAppTitle = aNewTitle; }

      int32 getVersionMajor() const { return mVersionMajor; }
      int32 getVersionMinor() const { return mVersionMinor; }
      int32 getRevision() const { return mRevision; }

      long32 getFrameRateCore() const { return mFrameCountCore; } 
      long32 getFrameRateReal() const { return mFrameCountReal; } 

      ScreenProperties &getScreenProperties() { return mScreenConfig; }
      void setScreenProperties( const ScreenProperties &aNewProperties) { mScreenConfig = aNewProperties; }

      bool8 getMaximizeProcessor() const { return mMaximizeProcesser; }
      void setMaximizeProcessor(bool8 aValue) { mMaximizeProcesser = aValue; }

      A2DAudioPtr getAudio() { return mpAudio; }
   }; //class
}; // namespace

// define global A2DEngine object(visible everywhere!)
extern Advanced2D::A2DEngine *gpEngine;
#endif // INC_ADVANCED2D_A2DENGINE_HPP