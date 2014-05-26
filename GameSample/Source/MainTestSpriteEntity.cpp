// external include
#include <sstream>
using namespace std::tr1;

// engine Include
#include <A2DEngine.hpp>
using namespace Advanced2D;

#define OBJECT_SPRITE 100
#define MAX 100

A2DTexturePtr gpImage;

bool8 GamePreload()
{
    //display engine version in a message box
    gpEngine->setAppTitle("SPRITE ENTITY DEMO");
    gpEngine->setScreenProperties(A2DEngine::ScreenProperties(1024, 768, 32, false));

    return true;
}

bool8 GameInit(HWND hwnd) 
{
    //load sprite
    A2DSpritePtr pAsteroid;
    gpImage = A2DTexture::create();
    gpImage->load("../../Assets/asteroid.tga");
    for (int32 n=0; n < MAX; ++n) 
    {
        //create a new asteroid sprite
        pAsteroid = A2DSprite::create();
        pAsteroid->setObjectType(OBJECT_SPRITE);
        pAsteroid->setImage(gpImage);
        pAsteroid->setTotalFrames(64);
        pAsteroid->setColumns(8);
        pAsteroid->setSize(60,60);
        pAsteroid->setPosition( rand() % 950, rand() % 700 );
        pAsteroid->setFrameTimer( rand() % 100 );
        pAsteroid->setCurrentFrame( rand() % 64 );

        if ( rand()%2 == 0) 
        { pAsteroid->setAnimationDirection(-1); }

        //add sprite to the entity manager
        gpEngine->addEntity(pAsteroid);  
    }

    std::ostringstream stream;
    stream << "Entities: " << gpEngine->getEntityCount();
    // BUG!! trigger key release -> need to fix it!!
    //gpEngine->Message(stream.str());

    return true;
}

void GameKeyRelease(int32 aKey)
{
    if (aKey == DIK_ESCAPE) 
    { gpEngine->shutDown(); }
}

void GameEntityUpdate(A2DEntityPtr apEntity)
{
    //type-cast Entity to a Sprite
    A2DSpritePtr sprite = static_pointer_cast<A2DSprite>(apEntity);

    //this is where you can update sprite properties
}

void GameEntityRender(A2DEntityPtr apEntity)
{
    //engine automatically renders each entity
    //but we can respond to each render event here
}

void GameEnd() 
{
    gpImage.reset();
}

void GameRender3D()
{
    //clear the scene using a dark blue color
    gpEngine->clearScene(D3DCOLOR_XRGB(0, 0, 80));
}

// unused Event
void GameEntityCollision(A2DEntityPtr apFirst, A2DEntityPtr apSecond){}
void GameUpdate() {}
void GameRender2D() {}
void GameKeyPress(uint32 aKey) {}
void GameKeyRelease(uint32 aKey) {}
void GameMouseButton(uint32 aButton) {}
void GameMouseMotion(int32 aX,int32 aY) {}
void GameMouseMove(int32 aX,int32 aY) {}
void GameMouseWheel(uint32 wheel) {}
