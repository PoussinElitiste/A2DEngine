//------------------------
// MainTestLinearVelocity.cpp
//------------------------
// external include
#include <sstream>
using namespace std;

// engine Include
#include <A2DEngine.hpp>
using namespace Advanced2D;

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define VELOCITY 0.0001
#define ROCKETVEL 3.0
#define MAX_ROCKET 20
#define OBJECT_SHIP 100
#define OBJECT_ROCKET 200

A2DFont* gpFont;
// A2DConsole* gpConsole;
A2DSprite* gpShip;
A2DVector3 gVelocity;
A2DTexture* gpRocketImage;
A2DMath gMath;

bool8 GamePreload()
{
    //display engine version in a message box
    gpEngine->SetAppTitle("Velocity DEMO");
    gpEngine->SetScreenProperties(A2DEngine::ScreenProperties(SCREEN_WIDTH, SCREEN_HEIGHT, 32, false));

    return true;
}

bool8 GameInit(HWND hwnd) 
{
    //create the console
    //gpConsole = new A2DConsole();
    //if (!gpConsole->Init()) 
    //{
    //    gpEngine->Message("Error initializing console");
    //    return false;
    //}

    // create ship sprite
    gpShip = new A2DSprite();
    gpShip->SetObjectType(OBJECT_SHIP);
    gpShip->LoadSpriteImage("../Assets/fatship256.tga");
    gpShip->SetRotation( gMath.ToRadians(90) ); // orient to the right
    gpShip->SetPosition( 10, SCREEN_HEIGHT/2 - gpShip->Get(HEIGHT)/2 );
    gpShip->SetCollidable(false);
    gpEngine->AddEntity(gpShip);

    // load Rocket image
    gpRocketImage = new A2DTexture();
    gpRocketImage->Load("../Assets/fatrocket64.tga");

    // load the Verdana10 font
    gpFont = new A2DFont();
    if (!gpFont->LoadSpriteImage("../Assets/verdana10.tga")) 
    {
        gpEngine->Message("Error loading verdana10.tga");
        return false;
    }
    gpFont->SetColumns(16);
    gpFont->SetCharSize(20, 16);

    if (!gpFont->LoadWidthData("../Assets/verdana10.dat")) 
    {
        gpEngine->Message("Error loading verdana10.dat");
        return false;
    }

    // maximize processor
    gpEngine->SetMaximizeProcessor( !gpEngine->GetMaximizeProcessor() );

    return true;
}

//void UpdateConsole()
//{
//    ostringstream ostr;
//    int32 y = 0;
//    gpConsole->Print(gpEngine->GetVersionText(), y++);
//    ostr.str("");
//    ostr << "REFRESH : " << (float32)(1000.0f/gpEngine->GetFrameRateCore()) << " ms (" << gpEngine->GetFrameRateCore() << " fps)";
//    gpConsole->Print(ostr.str(), y++);
//    ostr.str("");
//    ostr << "Entities: " << gpEngine->GetEntityCount();
//    gpConsole->Print(ostr.str(), y++);
//}

void GameUpdate()
{
    // UpdateConsole();
}

void GameRender3D()
{
    //clear the scene using a dark blue color
    gpEngine->ClearScene(D3DCOLOR_XRGB(0, 0, 80));
}

void GameRender2D() 
{
    gpFont->Print(1, SCREEN_HEIGHT-20, "Press ~ or F12 to toggle the Console");
    gpFont->Print(1, SCREEN_HEIGHT-40, "Press SPACE to fire!!!");

    // draw console
    // if (gpConsole->IsShowing()) gpConsole->draw();
}

void GameKeyRelease(int32 aKey)
{
    if (aKey == DIK_ESCAPE) 
    { gpEngine->ShutDown(); }

    switch (aKey) 
    {
    case DIK_ESCAPE:
        { gpEngine->ShutDown(); }
        break;
    case DIK_F12:
    case DIK_GRAVE:
        //{ gpConsole->SetShowing( !gpConsole->IsShowing() ); }
        break;
    }
}

void GameEnd() 
{
    //delete gpConsole;
    delete gpFont;
    delete gpShip;
}

void GameEntityUpdate(A2DEntity* apEntity)
{
    float32 y;
    A2DSprite* pShip = nullptr, *pRocket = nullptr;
    A2DVector3 position;

    switch(apEntity->GetObjectType())
    {
    case OBJECT_SHIP:
        {
            pShip = static_cast<A2DSprite*>(apEntity);
            position = pShip->GetPosition();
            y = (float32)(position(Y) + gVelocity(Y));
            if (y < 0) 
            {
                y = 0;
                gVelocity(Y) = 0.;
            }

            if (y > SCREEN_HEIGHT-128) 
            {
                y = SCREEN_HEIGHT-128;
                gVelocity(Y) = 0.;
            }

            position(Y) = y;
            pShip->SetPosition( position );
        }
        break;
    case OBJECT_ROCKET:
        {
            pRocket = static_cast<A2DSprite*>(apEntity);
            if ( pRocket->IsAlive() && pRocket->Get(X) > SCREEN_WIDTH )
            { pRocket->SetAlive(false); } 
        }
        break;
    }
}

void Firerocket()
{
    A2DSprite* pShip = static_cast<A2DSprite*>(gpEngine->FindEntity(OBJECT_SHIP));
    if (!pShip)
    {
        gpEngine->Message("Error locating Ship in entity manager!","ERROR");
        gpEngine->ShutDown();
    }

    if(gpEngine->GetEntityCount() - 1 > MAX_ROCKET)
    {
        return;
    }

    A2DSprite* pRocket = new A2DSprite();
    pRocket->SetObjectType(OBJECT_ROCKET);
    pRocket->SetImage(gpRocketImage);
    pRocket->SetMoveTimer(1);
    pRocket->SetCollidable(false);

    float32 randRot = (float32)(rand() % 40 - 20);
    float32 angle = 90 + randRot;
    pRocket->SetRotation( gMath.ToRadians(angle) );
    float32 x = (float32)(pShip->Get(X) + pShip->Get(WIDTH));
    float32 y = (float32)(pShip->Get(Y) + pShip->Get(HEIGHT)/2 - pRocket->Get(HEIGHT)/2);
    pRocket->SetPosition(x, y);
    float32 vx = (float32)(gMath.LinearVelocityX(angle) * ROCKETVEL);
    float32 vy = (float32)(gMath.LinearVelocityY(angle) * ROCKETVEL);
    pRocket->SetVelocity(vx, vy);
    gpEngine->AddEntity(pRocket);
}

void GameKeyPress(int32 aKey) 
{
    float32 y;
    switch(aKey)
    {
        case DIK_UP:
        case DIK_W:
            {
                y = (float32)(gVelocity(Y) - VELOCITY);
                if (y < -3.0) 
                { y = -3.0; }
                gVelocity(Y) = y;
            }
            break;
        case DIK_DOWN:
        case DIK_S:
            {
                y = (float32)(gVelocity(Y) + VELOCITY);
                if (y > 3.0) 
                { y = 3.0; }
                gVelocity(Y) = y;
            }
            break;
        case DIK_SPACE:
        case DIK_LCONTROL:
            { Firerocket(); }
            break;
    }
}

// unused Event
void GameEntityRender(A2DEntity* apEntity) {}
void GameEntityCollision(A2DEntity* apFirst, A2DEntity* apSecond) {}
void GameMouseButton(int32 aButton) {}
void GameMouseMotion(int32 aX,int32 aY) {}
void GameMouseMove(int32 aX,int32 aY) {}
void GameMouseWheel(int32 wheel) {}
