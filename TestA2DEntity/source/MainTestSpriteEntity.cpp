// external include
#include <sstream>

// engine Include
#include <A2DEngine.hpp>
using namespace Advanced2D;

#define OBJECT_SPRITE 100
#define MAX 10000

A2DTexture* gpImage;

bool8 GamePreload()
{
    //display engine version in a message box
    gpEngine->SetAppTitle("SPRITE ENTITY DEMO");
    gpEngine->SetScreenProperties(A2DEngine::ScreenProperties(1024, 768, 32, false));

    return true;
}

bool8 GameInit(HWND hwnd) 
{
    //load sprite
    A2DSprite* pAsteroid;
    gpImage = new A2DTexture();
    gpImage->Load("../Assets/asteroid.tga");
    for (int32 n=0; n < MAX; ++n) 
    {
        //create a new asteroid sprite
        pAsteroid = new A2DSprite();
        pAsteroid->SetObjectType(OBJECT_SPRITE);
        pAsteroid->SetImage(gpImage);
        pAsteroid->SetTotalFrames(64);
        pAsteroid->SetColumns(8);
        pAsteroid->SetSize(60,60);
        pAsteroid->SetPosition( rand() % 950, rand() % 700 );
        pAsteroid->SetFrameTimer( rand() % 100 );
        pAsteroid->SetCurrentFrame( rand() % 64 );

        if ( rand()%2 == 0) 
        { pAsteroid->SetAnimationDirection(-1); }

        //add sprite to the entity manager
        gpEngine->AddEntity(pAsteroid);  
    }

    std::ostringstream stream;
    stream << "Entities: " << gpEngine->GetEntityCount();
    // BUG!! trigger key release -> need to fix it!!
    //gpEngine->Message(stream.str());

    return true;
}

void GameKeyRelease(int32 aKey)
{
    if (aKey == DIK_ESCAPE) 
    { gpEngine->ShutDown(); }
}

void GameEntityUpdate(A2DEntity* apEntity)
{
    //type-cast Entity to a Sprite
    A2DSprite* sprite = static_cast<A2DSprite*>(apEntity);

    //this is where you can update sprite properties
}

void GameEntityRender(A2DEntity* apEntity)
{
    //engine automatically renders each entity
    //but we can respond to each render event here
}

void GameEnd() 
{
    delete gpImage;
}

void GameRender3D()
{
    //clear the scene using a dark blue color
    gpEngine->ClearScene(D3DCOLOR_XRGB(0, 0, 80));
}

// unused Event
void GameUpdate() {}
void GameRender2D() {}
void GameKeyPress(int32 aKey) {}
void GameMouseButton(int32 aButton) {}
void GameMouseMotion(int32 aX,int32 aY) {}
void GameMouseMove(int32 aX,int32 aY) {}
void GameMouseWheel(int32 wheel) {}
