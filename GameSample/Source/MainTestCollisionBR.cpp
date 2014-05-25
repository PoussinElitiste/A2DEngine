//------------------------
// MainTestCollisionBR.cpp
//------------------------
// external include
#include <sstream>
using namespace std::tr1;

// engine Include
#include <A2DEngine.hpp>
using namespace Advanced2D;

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define OBJECT_BACKGROUND 1
#define OBJECT_SPRITE 100
#define MAX 40

A2DTexturePtr gpAsteroidImage;
A2DFontPtr gpFont;

A2DConsolePtr gpConsole;
std::ostringstream gOstr;
A2DTexturePtr gpCollisionBox;
int32 gCollisions;

bool8 GamePreload()
{
    //display engine version in a message box
    gpEngine->setAppTitle("COLLISION BR DEMO");
    gpEngine->setScreenProperties(A2DEngine::ScreenProperties(SCREEN_WIDTH, SCREEN_HEIGHT, 32, false));

    return true;
}

bool8 GameInit(HWND hwnd) 
{
    //load background image
    A2DSpritePtr pBackground = A2DSprite::create();
    if (!pBackground->loadSpriteImage("../Assets/orion.bmp"))
    {
        gpEngine->message("Error loading orion.bmp");
        return false;
    }
    pBackground->setObjectType(OBJECT_BACKGROUND);
    gpEngine->addEntity(pBackground);

    //create the console
    gpConsole = A2DConsole::create();
    if (!gpConsole->init()) 
    {
        gpEngine->message("Error initializing console");
        return false;
    }

    //load asteroid image
    gpAsteroidImage = A2DTexture::create();
    if ( !gpAsteroidImage->load("../Assets/asteroid.tga") )
    {
        gpEngine->message("Error loading asteroid.tga");
        return false;
    }

    //create asteroid sprites
    A2DSpritePtr pAsteroid;
    for (int n=0; n < MAX; ++n)
    {
        //create a new asteroid sprite
        pAsteroid = A2DSprite::create();
        pAsteroid->setObjectType(OBJECT_SPRITE);
        gOstr.str(""); 
        gOstr << "ASTEROID" << n;
        pAsteroid->setName(gOstr.str());
        pAsteroid->setImage(gpAsteroidImage);
        pAsteroid->setScale( static_cast<float32>(rand() % 150 + 50) / 100.0f );

        // set animation properties
        pAsteroid->setTotalFrames(64);
        pAsteroid->setColumns(8);
        pAsteroid->setSize(60, 60);
        pAsteroid->setPosition( rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT );
        pAsteroid->setFrameTimer( rand() % 90 + 10 );
        pAsteroid->setCurrentFrame( rand() % 64 );
        if (rand()%2 == 0) 
        { pAsteroid->setAnimationDirection(-1); }

        //set movement properties
        float32 vx = static_cast<float32>(rand()%10 - 5)/10.0f;
        float32 vy = static_cast<float32>(rand()%10 - 5)/10.0f;
        pAsteroid->setVelocity( vx, vy );

        //collision toggle
        pAsteroid->setCollidable(true);

        //movement timer keeps sprite consistent at any framerate
        pAsteroid->setMoveTimer( 16 );

        //add asteroid to the entity manager
        gpEngine->addEntity(pAsteroid);
    }

    //load the Verdana10 font
    gpFont = A2DFont::create();
    if (!gpFont->loadSpriteImage("../Assets/verdana10.tga")) 
    {
        gpEngine->message("Error loading verdana10.tga");
        return false;
    }
    gpFont->setColumns(16);
    gpFont->setCharSize(20, 16);

    if (!gpFont->loadWidthData("../Assets/verdana10.dat")) 
    {
        gpEngine->message("Error loading verdana10.dat");
        return false;
    }

    //load highlight image used to show collisions
    gpCollisionBox = A2DTexture::create();
    if (!gpCollisionBox->load("../Assets/highlight.tga")) 
    {
        gpEngine->message("Error loading highlight.tga");
        return false;
    }

    return true;
}

void UpdateConsole()
{
    int32 y = 0;
    gpConsole->print(gpEngine->getVersionText(), y++);
    y++;

    gOstr.str("");
    gOstr << "SCREEN : " << (float32)(1000.0f/gpEngine->getFrameRateReal()) << " ms (" << gpEngine->getFrameRateReal() << " fps)";
    gpConsole->print(gOstr.str(), y++);
    y++;

    gOstr.str("");
    gOstr << "CORE : " << (float32)(1000.0f/gpEngine->getFrameRateCore()) << " ms (" << gpEngine->getFrameRateCore() << " fps)";
    gpConsole->print(gOstr.str(), y++);

    gOstr.str("");
    gOstr << "Processor throttling: " << gpEngine->getMaximizeProcessor();
    gpConsole->print(gOstr.str(), y++);
    y++;
    gOstr.str("");
    A2DEngine::ScreenProperties& screenProperties = gpEngine->getScreenProperties();
    gOstr << "Screen: " << screenProperties.mWidth << "," << screenProperties.mHeight << "," << screenProperties.mColorDepth;
    gpConsole->print(gOstr.str(), y++);
    y++;

    gOstr.str("");
    gOstr << "Entities: " << gpEngine->getEntityCount();
    gpConsole->print(gOstr.str(), y++);
    gOstr.str("");
    gOstr << "Collisions: " << gCollisions;
    gpConsole->print(gOstr.str(), y++);
    y++;

    gOstr.str("");
    gOstr << "Press F2 to toggle Processor Throttling";
    gpConsole->print(gOstr.str(), 27);
}

void GameUpdate()
{
    UpdateConsole();
    gCollisions = 0;
}

void GameRender3D()
{
    //clear the scene using a dark blue color
    gpEngine->clearScene(D3DCOLOR_XRGB(0, 0, 80));
}

void GameRender2D() 
{
    gpFont->print(1, SCREEN_HEIGHT-20, "Press ~ or F12 to toggle the Console");

    // draw console
    if (gpConsole->isShowing()) 
    { gpConsole->draw(); }
}

void GameKeyRelease(uint32 aKey)
{
    if (aKey == DIK_ESCAPE) 
    { gpEngine->shutDown(); }

    switch (aKey) 
    {
    case DIK_ESCAPE:
        { gpEngine->shutDown(); }
        break;
    case DIK_F12:
    case DIK_GRAVE:
        { gpConsole->setShowing( !gpConsole->isShowing() ); }
        break;
    case DIK_F2:
        { gpEngine->setMaximizeProcessor(!gpEngine->getMaximizeProcessor()); }
    break;
    }
}

void GameEnd() 
{
    //delete gpAsteroidImage;
    //delete gpConsole;
    //delete gpFont;
}

void GameEntityUpdate(A2DEntityPtr apEntity)
{
    switch(apEntity->getObjectType())
    {
    case OBJECT_SPRITE:
        {
            A2DSpritePtr pSpr = static_pointer_cast<A2DSprite>(apEntity);
            if (pSpr->get(X) < -60) { pSpr->setPosition(X, SCREEN_WIDTH); }
            if (pSpr->get(X) > SCREEN_WIDTH) { pSpr->setPosition(X, -60); }
            if (pSpr->get(Y) < -60) { pSpr->setPosition(Y, SCREEN_HEIGHT); }
            if (pSpr->get(Y) > SCREEN_HEIGHT) { pSpr->setPosition(Y, -60); }
        }
        break;
    }
}

void GameEntityCollision(A2DEntityPtr apFirst, A2DEntityPtr apSecond) 
{
    A2DSpritePtr pBox;
    A2DSpritePtr pSrpiteA = static_pointer_cast<A2DSprite>(apFirst);
    A2DSpritePtr pSrpiteB = static_pointer_cast<A2DSprite>(apSecond);
    if ( pSrpiteA->getObjectType() == OBJECT_SPRITE 
        && pSrpiteB->getObjectType() == OBJECT_SPRITE)
    {
        gCollisions++;

        //add first collision box
        pBox = A2DSprite::create();
        pBox->setColor(0x33DD4444);
        pBox->setImage(gpCollisionBox);
        pBox->setPosition( pSrpiteA->getPosition() );
        pBox->setScale( pSrpiteA->get(WIDTH) * pSrpiteA->getScale() / 100.0f );
        pBox->setLifetime(100);
        gpEngine->addEntity( pBox );

        //add second collision box
        pBox = A2DSprite::create();
        pBox->setColor(0x33DD4444);
        pBox->setImage(gpCollisionBox);
        pBox->setPosition( pSrpiteB->getPosition() );
        pBox->setScale( pSrpiteB->get(WIDTH) * pSrpiteB->getScale() / 100.0f );
        pBox->setLifetime(100);
        gpEngine->addEntity( pBox );
    }
}

// unused Event
void GameEntityRender(A2DEntityPtr apEntity) {}
void GameKeyPress(uint32 aKey) {}
void GameMouseButton(uint32 aButton) {}
void GameMouseMotion(int32 aX,int32 aY) {}
void GameMouseMove(int32 aX,int32 aY) {}
void GameMouseWheel(uint32 wheel) {}
