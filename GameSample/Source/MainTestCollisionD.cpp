//------------------------
// MainTestCollisionD.cpp
//------------------------

// external include
#include <sstream>
#include <iomanip>
using namespace std;

// engine Include
#include <A2DEngine.hpp>
using namespace Advanced2D;

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define OBJECT_BACKGROUND 1
#define OBJECT_SPRITE 100
#define MAX 50
#define SCALE 70

A2DTexturePtr  gpBallImage;
A2DFontPtr     gpFont;
A2DConsolePtr  gpConsole;
ostringstream  gOstr;
int32          gCollisions;

bool8 GamePreload()
{
    //display engine version in a message box
    gpEngine->setAppTitle("COLLISION D DEMO");
    gpEngine->setScreenProperties(A2DEngine::ScreenProperties(SCREEN_WIDTH, SCREEN_HEIGHT, 32, false));

    return true;
}

bool8 GameInit(HWND hwnd) 
{
    //load background image
    A2DSpritePtr pBackground = A2DSprite::create();
    if (!pBackground->loadSpriteImage("../Assets/craters.tga"))
    {
        gpEngine->message("Error loading craters.tga");
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
    gpBallImage = A2DTexture::create();
    if ( !gpBallImage->load("../Assets/lightningball.tga") )
    {
        gpEngine->message("Error loading lightningball.tga");
        return false;
    }

    //create asteroid sprites
    A2DSpritePtr pSprite;
    for (int n=0; n < MAX; ++n)
    {
        //create a new sprite
        pSprite = A2DSprite::create();
        pSprite->setObjectType(OBJECT_SPRITE);
        pSprite->setImage(gpBallImage);
        pSprite->setSize(128, 128);
        pSprite->setScale( static_cast<float32>(rand() % SCALE + SCALE/4) / 100.0f );
        pSprite->setPosition( rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT );
        pSprite->setCollisionMethod(COLLISION_DIST);

        //set movement properties
        float32 vx = static_cast<float32>(rand()%10 - 5)/10.0f;
        float32 vy = static_cast<float32>(rand()%10 - 5)/10.0f;
        pSprite->setVelocity( vx, vy );

        //add asteroid to the entity manager
        gpEngine->addEntity(pSprite);
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

    return true;
}

void UpdateConsole()
{
    int32 y = 0;
    gpConsole->print(gpEngine->getVersionText(), y++);
    y++;

    gOstr.str("");
    gOstr << "SCREEN(" << gpEngine->getFrameRateReal() << " fps) : " << (float32)(1000.0f/gpEngine->getFrameRateReal()) << " ms" ;
    gpConsole->print(gOstr.str(), y++);

    gOstr.str("");
    gOstr << "CORE(" << gpEngine->getFrameRateCore() << " fps) : " << (float32)(1000.0f/gpEngine->getFrameRateCore()) << " ms" ;
    gpConsole->print(gOstr.str(), y++);

    gOstr.str("");
    gOstr << "Entities: " << gpEngine->getEntityCount();
    gpConsole->print(gOstr.str(), y++);

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
    //delete gpBallImage;
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
            float32 w = static_cast<float32>(pSpr->get(WIDTH) * pSpr->getScale());
            float32 h = static_cast<float32>(pSpr->get(HEIGHT) * pSpr->getScale());
            float32 vx = static_cast<float32>(pSpr->getVelocity()(X));
            float32 vy = static_cast<float32>(pSpr->getVelocity()(Y));
            if (pSpr->get(X) < 0) 
            {
                pSpr->set(X, 0);
                vx = fabs(vx);
            }
            else if (pSpr->get(X) > (SCREEN_WIDTH - w)) 
            {
                pSpr->set(X, SCREEN_WIDTH - w);
                vx = fabs(vx) * -1;
            }
            if (pSpr->get(Y) < 0) 
            {
                pSpr->set(Y, 0);
                vy = fabs(vy);
            }
            else if (pSpr->get(Y) > (SCREEN_HEIGHT - h)) 
            {
                pSpr->set(Y, (SCREEN_HEIGHT - h));
                vy = fabs(vy) * -1;
            }
            pSpr->setVelocity(vx, vy);
        }
        break;
    }
}

void GameEntityCollision(A2DEntityPtr apFirst, A2DEntityPtr apSecond) 
{
    A2DSpritePtr pSrpiteA = static_pointer_cast<A2DSprite>(apFirst);
    A2DSpritePtr pSrpiteB = static_pointer_cast<A2DSprite>(apSecond);

    if ( pSrpiteA->getObjectType() == OBJECT_SPRITE 
        && pSrpiteB->getObjectType() == OBJECT_SPRITE)
    {
        gCollisions++;

        float32 x1 = static_cast<float32>(pSrpiteA->get(X));
        float32 y1 = static_cast<float32>(pSrpiteA->get(Y));
        float32 x2 = static_cast<float32>(pSrpiteB->get(X));
        float32 y2 = static_cast<float32>(pSrpiteB->get(Y));
        float32 vx1 = static_cast<float32>(pSrpiteA->getVelocity()(X));
        float32 vy1 = static_cast<float32>(pSrpiteA->getVelocity()(Y));
        float32 vx2 = static_cast<float32>(pSrpiteB->getVelocity()(X));
        float32 vy2 = static_cast<float32>(pSrpiteB->getVelocity()(Y));
        if (x1 < x2) 
        {
            vx1 = fabs(vx1) * -1;
            vx2 = fabs(vx1);
        }
        else if (x1 > x2) 
        {
            vx1 = fabs(vx1);
            vx2 = fabs(vx2) * -1;
        }
        if (y1 < y2) 
        {
            vy1 = fabs(vy1) * -1;
            vy2 = fabs(vy2);
        }
        else 
        {
            vy1 = fabs(vy1);
            vy2 = fabs(vy2) * -1;
        }
        pSrpiteA->setVelocity(vx1, vy1);
        pSrpiteB->setVelocity(vx2, vy2);
    }
}

// unused Event
void GameEntityRender(A2DEntityPtr apEntity) {}
void GameKeyPress(uint32 aKey) {}
void GameMouseButton(uint32 aButton) {}
void GameMouseMotion(int32 aX,int32 aY) {}
void GameMouseMove(int32 aX,int32 aY) {}
void GameMouseWheel(uint32 wheel) {}
