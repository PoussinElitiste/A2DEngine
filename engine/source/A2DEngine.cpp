// Local include
#include <A2DEngine.hpp>
#include <A2DInput.hpp>
#include <WinMain.hpp>

// External include
#include <cstdlib>
#include <ctime>
#include <sstream>

namespace Advanced2D
{
   A2DEngine::ScreenProperties::ScreenProperties( int32 aWidth, int32 aHeight, int32 aColorDepth, bool8 aFullScreen )
      : mWidth(aWidth)
      , mHeight(aHeight)
      , mColorDepth(aColorDepth)
      , mFullScreen(aFullScreen)
   {}

   void A2DEngine::ScreenProperties::operator()(const ScreenProperties &aScreenConfig)
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
      , mpAudio(nullptr)
   {
      srand(static_cast<uint32>(time(NULL)));

      // set default value
      setAppTitle("Advanced2D");
   }

   A2DEngine::~A2DEngine()
   {
      if (mpAudio)
      {
         mpAudio->stopAll();
      }

      if (mpDevice)
      {
         mpDevice->Release();
      }

      if (mpD3D)
      {
         mpD3D->Release();
      }
   }

   A2DString A2DEngine::getVersionText() const
   {
      std::ostringstream stream;
      stream << "Advanced2D Engine V" << mVersionMajor << "." << mVersionMinor << "." << mRevision;
      return stream.str();
   }

   void A2DEngine::message(const A2DString &aMessage, const A2DString &aTitle /*= "ADVANCED_2D"*/)
{
      MessageBox(0, aMessage.c_str(), aTitle.c_str(), 0);
   }

   void A2DEngine::fatalError(const A2DString &aMessage, const A2DString &aTitle /*= "FATAL_ERROR"*/)
{
      message(aMessage,aTitle);
      shutDown();
   }

   int32 A2DEngine::init(const ScreenProperties &aScreenConfig)
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

      //clear the back buffer to black
      clearScene(D3DCOLOR_XRGB(0,0,0));

      //create pointer to the back buffer
      mpDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &mpBackBuffer);

      //use ambient lighting and z-buffering
      mpDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
      mpDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
      setAmbient(mAmbientColor);

      //initialize 2D renderer
      HRESULT result = D3DXCreateSprite(mpDevice, &mpSpriteHandler);

      if (result != D3D_OK) 
      { return 0; }

      //set a default material
      setDefaultMaterial();

      //------------------------
      // initialize DirectInput
      //------------------------
      mpInput = A2DInput::create(getWindowHandle());

      //------------------------
      // initialize Audio
      //------------------------
      mpAudio = A2DAudio::create();
      if (!mpAudio->init()) 
      { return 0; }

      //call game initialization extern function
      if (!GameInit(getWindowHandle()))
      { return 0; }

      return 1;
   }

   void A2DEngine::setDefaultMaterial()
   {
      D3DMATERIAL9 material;
      memset(&material, 0, sizeof(material));
      material.Diffuse.r = 1.0f;
      material.Diffuse.g = 1.0f;
      material.Diffuse.b = 1.0f;
      material.Diffuse.a = 1.0f;
      mpDevice->SetMaterial(&material);
   }

   void A2DEngine::clearScene(A2DColor aColor)
   {
      mpDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, aColor, 1.0f, 0);
   }

   void A2DEngine::setIdentity()
   {
      D3DXMATRIX mat;
      D3DXMatrixIdentity(&mat);
        
      mpDevice->SetTransform(D3DTS_WORLD, &mat);
   }

   void A2DEngine::setAmbient(A2DColor aColorValue)
   {
      mAmbientColor = aColorValue;
      mpDevice->SetRenderState(D3DRS_AMBIENT, mAmbientColor);
   }

   int32 A2DEngine::renderStart()
   {
      if (nullptr == mpDevice)
      { return 0; }

      if ( mpDevice->BeginScene() != D3D_OK )
      { return 0; }

      return 1;
   }

   int32 A2DEngine::renderStop()
   {
      if ( nullptr == mpDevice )
      { return 0; }

      if ( mpDevice->EndScene() != D3D_OK )
      { return 0; }

      if ( mpDevice->Present(NULL, NULL, NULL, NULL) != D3D_OK )
      { return 0; }

      return 1;
   }

   int32 A2DEngine::render2DStart()
   {
      if ( mpSpriteHandler->Begin(D3DXSPRITE_ALPHABLEND) != D3D_OK )
      { return 0; }
      else
      { return 1; }
   }

   int32 A2DEngine::render2DStop()
   {
      mpSpriteHandler->End();
      return 1;
   }

   void A2DEngine::shutDown()
   {
      gGameOver = true;
   }

   void A2DEngine::update()
   {
      static A2DTimer timedupdate;

      // Calculate core framerate
      ++mFrameCountCore;
      if (mCoreTimer.StopWatch(999)) 
      {
         mFrameRateCore = mFrameCountCore;
         mFrameCountCore = 0;
      }

      //-------
      // Game
      //-------
      // Fast update with no timing
      GameUpdate();

      //update entities
      if (!mPauseMode) 
      {
         updateEntities();
      }

      //--------
      // Physic
      //--------
      //perform global collision testing
      if (!mPauseMode /*&& mCollisionTimer.stopwatch(50)*/) 
      {
         testForCollisions();
      }

      //--------
      // Timer
      //--------
      // Update with 60fps timing
      if ( !timedupdate.StopWatch(14) ) 
      {
         if ( !getMaximizeProcessor() )
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

         //-------
         // Input
         //-------
         mpInput->Update();
         updateKeyboard();
         updateMouse();

         //--------
         // Audio
         //--------
         mpAudio->update();

         //--------
         // Render
         //--------
         //return to the origin
         setIdentity();

         // Allow game to 3D render
         renderStart();
         {
               // call render 3D callback
               GameRender3D();

               //render 3D entities
               if (!mPauseMode) { draw3DEntities(); }

               // Allow game to 2D render
               render2DStart();
               {
                  //render 2D entities
                  if (!mPauseMode) { draw2DEntities(); } 

                  // call render 2D callback after render enties(like Font)
                  GameRender2D();
               }
               render2DStop();
         }
         renderStop();
      }

      //remove dead entities from the list
      buryEntities();
   }

   void A2DEngine::addEntity(A2DEntityPtr apEntity)
   {
      static int id = 0;
      apEntity->setID(id);
      mpEntities.push_back(apEntity);
      ++id;
   }

   A2DEntityPtr A2DEngine::findEntity(int32 aObjectType)
   {
      EntityListIt iter = mpEntities.begin();
      while (iter != mpEntities.end())
      {
         if ((*iter)->isAlive() == true && (*iter)->getObjectType() == aObjectType)
         { return *iter; }
         else
         { ++iter; }
      }

      return nullptr;
   }

   A2DEntityPtr A2DEngine::findEntity(A2DString aName)
   {
      EntityListIt iter = mpEntities.begin();
      while (iter != mpEntities.end())
      {
         if ( (*iter)->isAlive() == true && (*iter)->getName() == aName )
         { return *iter; }
         else
         { ++iter; }
      }

      return nullptr;
   }

   int32 A2DEngine::getEntityCount() const 
   {
      return mpEntities.size();
   }

   void A2DEngine::updateEntities()
   {
      EntityListIt iter;
      A2DEntityPtr pEntity;
        
      iter = mpEntities.begin();
      while (iter != mpEntities.end())
      {
         //point local sprite to object in the list
         pEntity = *iter;

         //is this entity alive?
         if ( pEntity->isAlive() ) 
         {
               // move/animate entity
               pEntity->move();
               pEntity->animate();

               // tell game that this entity has been updated
               GameEntityUpdate( pEntity );

               // see if this entity will auto-expire
               if ( pEntity->getLifetime() > 0)
               {
                  if ( pEntity->lifetimeExpired() ) 
                  {
                     pEntity->setAlive(false);
                  }
               }
         }
         ++iter;
      }
   }

   void A2DEngine::draw3DEntities()
   {
      A2DEntityPtr pEntity;
      EntityListIt iter = mpEntities.begin();
      while (iter != mpEntities.end())
      {
         //temporary pointer
         pEntity = *iter;
            
         //is this a 3D entity?
         if ( pEntity->getRenderType() == RENDER_3D ) 
         {
               //is this entity in use?
               if ( pEntity->isAlive() && pEntity->isVisible() ) 
               {
                  pEntity->draw();
                  GameEntityRender( pEntity );
               }
         }
         ++iter;
      }
   }

   void A2DEngine::draw2DEntities()
   {
      A2DEntityPtr pEntity;
      EntityListIt iter = mpEntities.begin();
      while (iter != mpEntities.end()) 
      {
         //temporary pointer
         pEntity = *iter;
         //is this a 2D entity?
         if ( pEntity->getRenderType() == RENDER_2D ) 
         {
               //is this entity in use?
               if ( pEntity->isAlive() && pEntity->isVisible() ) 
               {
                  pEntity->draw();
                  GameEntityRender( pEntity );
               }
         }
         ++iter;
      }
   }

   void A2DEngine::buryEntities()
   {
      EntityListIt iter = mpEntities.begin();
      while (iter != mpEntities.end()) 
      {
         if ( (*iter)->isAlive() == false ) 
         {
               iter = mpEntities.erase( iter );
         }
         else 
         { ++iter; }
      }
   }

   void A2DEngine::testForCollisions()
   {
      EntityListIt first = mpEntities.begin();

      // TEMPORARY! TODO: implement 3D collision
      if ( (*first)->getRenderType() != RENDER_2D )
      {
         //we only care about sprite collisions
         return;
      }

      EntityListIt second;
      A2DSpritePtr pSprite1;
      A2DSpritePtr pSprite2;

      while (first != mpEntities.end() )
      {
         if ( (*first)->getRenderType() == RENDER_2D )
         {
               //point local sprite to sprite contained in the list
               pSprite1 = std::tr1::static_pointer_cast<A2DSprite>(*first);

               //if this entity is alive and visible...
               if ( pSprite1->isAlive() && pSprite1->isVisible() && pSprite1->isCollidable() )
               {
                  //test all other entities for collision
                  second = mpEntities.begin();
                  while ( second != mpEntities.end() )
                  {
                     //point local sprite to sprite contained in the list
                     pSprite2 = std::tr1::static_pointer_cast<A2DSprite>(*second);

                     //if other entity is active and not same as first entity...
                     if ( pSprite2->isAlive() && pSprite2->isVisible() 
                           && pSprite2->isCollidable() && pSprite1 != pSprite2 )
                     {
                           //test for collision
                           if ( collision(pSprite1, pSprite2 ) ) 
                           {
                              //notify game of collision
                              GameEntityCollision( pSprite1, pSprite2 );
                           }
                     }

                     //go to the next sprite in the list
                     ++second;
                  }
               }

               // go to the next sprite in the list
               ++first;
         }// render2d
      } // while
   }

   bool8 A2DEngine::collision(A2DSpritePtr apSprite1, A2DSpritePtr apSprite2)
   {
      switch (apSprite1->getCollisionMethod()) 
      {
         case COLLISION_RECT:
               {
                  return collisionBR(apSprite1, apSprite2);
               }
               break;
         case COLLISION_DIST:
               {
                  return collisionD(apSprite1, apSprite2);
               }
               break;
         case COLLISION_NONE:
         default:
         break;
      }

      return false;
   }

   // Bounding Rectangle
   bool8 A2DEngine::collisionBR(A2DSpritePtr apSprite1, A2DSpritePtr apSprite2)
   {
      bool8 result = false;
      A2DRectangle rectA(
         apSprite1->get(X),
         apSprite1->get(Y),
         apSprite1->get(X) + apSprite1->get(WIDTH) * apSprite1->getScale(),
         apSprite1->get(Y) + apSprite1->get(HEIGHT) * apSprite1->getScale());

      A2DRectangle rectB(
         apSprite2->get(X),
         apSprite2->get(Y),
         apSprite2->get(X) + apSprite2->get(WIDTH) * apSprite2->getScale(),
         apSprite2->get(Y) + apSprite2->get(HEIGHT) * apSprite2->getScale());

      //are any of sprite b’s corners intersecting sprite a?
      result = ( 
         rectA.isInside( rectB.getLeft(), rectB.getTop() )
         || rectA.isInside( rectB.getRight(), rectB.getTop() ) 
         || rectA.isInside( rectB.getLeft(), rectB.getBottom() ) 
         || rectA.isInside( rectB.getRight(), rectB.getBottom() )
         );

      return result;
   }


   bool8 A2DEngine::collisionD(A2DSpritePtr apSprite1, A2DSpritePtr apSprite2)
   {
      double64 radius1, radius2;

      //calculate radius 1
      if ( apSprite1->get(WIDTH) > apSprite1->get(HEIGHT) )
      {
         radius1 = (apSprite1->get(WIDTH) * apSprite1->getScale()) / 2.;
      }
      else
      {
         radius1 = (apSprite1->get(HEIGHT) * apSprite1->getScale()) / 2.;
      }

      //point = center of sprite 1
      double64 x1 = apSprite1->get(X) + radius1;
      double64 y1 = apSprite1->get(Y) + radius1;
      A2DVector3 vector1(x1, y1, 0.0);

      //calculate radius 2
      if ( apSprite2->get(WIDTH) > apSprite2->get(HEIGHT) )
      {
         radius2 = (apSprite2->get(WIDTH) * apSprite2->getScale()) / 2.;
      }
      else
      {
         radius2 = (apSprite2->get(HEIGHT) * apSprite2->getScale()) / 2.;
      }

      //point = center of sprite 2
      double64 x2 = apSprite2->get(X) + radius2;
      double64 y2 = apSprite2->get(Y) + radius2;
      A2DVector3 vector2(x2, y2, 0.0);

      //calculate distance
      double64 dist = vector1.distance2D( vector2 );

      //return distance comparison
      return (dist < radius1 + radius2);
   }

   void A2DEngine::updateMouse()
   {
      static int32 oldPosX = 0;
      static int32 oldPosY = 0;

      int32 deltaX = mpInput->getDeltaX();
      int32 deltaY = mpInput->getDeltaY();

      //check mouse buttons 1-3
      for (int32 n=0; n<4; ++n) 
      {
         if (mpInput->getMouseButton(n))
         { GameMouseButton(n); }
      }

      //check mouse position
      if (mpInput->getPosX() != oldPosX || mpInput->getPosY() != oldPosY) 
      {
         GameMouseMove( mpInput->getPosX(), mpInput->getPosY() );
         oldPosX = mpInput->getPosX();
         oldPosY = mpInput->getPosY();
      }

      //check mouse motion
      if (deltaX != 0 || deltaY ) 
      { GameMouseMotion(deltaX, deltaY); }

      //check mouse wheel
      int32 wheel = mpInput->getDeltaWheel();
      if (wheel != 0)
      { GameMouseWheel(wheel); }
   }

   void A2DEngine::updateKeyboard()
   {
      static char oldKeys[256];
      for (int32 n=0; n<255; ++n)
      {
         //check for key press
         if (mpInput->getKeyState(n) & 0x80) 
         {
               GameKeyPress(n);
               oldKeys[n] = mpInput->getKeyState(n);
         }//check for release
         else if (oldKeys[n] & 0x80) 
         {
               GameKeyRelease(n);
               oldKeys[n] = mpInput->getKeyState(n);
         }
      }
   }

   void A2DEngine::close()
   {
      GameEnd();
   }
}; // namespace