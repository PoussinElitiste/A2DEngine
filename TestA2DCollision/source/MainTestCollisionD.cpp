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

A2DTexture* gpBallImage;
A2DFont* gpFont;
A2DConsole* gpConsole;
ostringstream gOstr;
int32 gCollisions;

bool8 GamePreload()
{
    //display engine version in a message box
    gpEngine->SetAppTitle("COLLISION D DEMO");
    gpEngine->SetScreenProperties(A2DEngine::ScreenProperties(SCREEN_WIDTH, SCREEN_HEIGHT, 32, false));

    return true;
}

bool8 GameInit(HWND hwnd) 
{
    //load background image
    A2DSprite* pBackground = new A2DSprite();
    if (!pBackground->LoadSpriteImage("../Assets/craters.tga"))
    {
        gpEngine->Message("Error loading craters.tga");
        return false;
    }
    pBackground->SetObjectType(OBJECT_BACKGROUND);
    gpEngine->AddEntity(pBackground);

    //create the console
    gpConsole = new A2DConsole();
    if (!gpConsole->Init()) 
    {
        gpEngine->Message("Error initializing console");
        return false;
    }

    //load asteroid image
    gpBallImage = new A2DTexture();
    if ( !gpBallImage->Load("../Assets/lightningball.tga") )
    {
        gpEngine->Message("Error loading lightningball.tga");
        return false;
    }

    //create asteroid sprites
    A2DSprite* pSprite;
    for (int n=0; n < MAX; ++n)
    {
        //create a new sprite
        pSprite = new A2DSprite();
        pSprite->SetObjectType(OBJECT_SPRITE);
        pSprite->SetImage(gpBallImage);
        pSprite->SetSize(128, 128);
        pSprite->SetScale( static_cast<float32>(rand() % SCALE + SCALE/4) / 100.0f );
        pSprite->SetPosition( rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT );
        pSprite->SetCollisionMethod(COLLISION_DIST);

        //set movement properties
        float32 vx = static_cast<float32>(rand()%10 - 5)/10.0f;
        float32 vy = static_cast<float32>(rand()%10 - 5)/10.0f;
        pSprite->SetVelocity( vx, vy );

        //add asteroid to the entity manager
        gpEngine->AddEntity(pSprite);
    }

    //load the Verdana10 font
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

    return true;
}

void UpdateConsole()
{
    int32 y = 0;
    gpConsole->Print(gpEngine->GetVersionText(), y++);
    y++;

    gOstr.str("");
    gOstr << "SCREEN(" << gpEngine->GetFrameRateReal() << " fps) : " << (float32)(1000.0f/gpEngine->GetFrameRateReal()) << " ms" ;
    gpConsole->Print(gOstr.str(), y++);

    gOstr.str("");
    gOstr << "CORE(" << gpEngine->GetFrameRateCore() << " fps) : " << (float32)(1000.0f/gpEngine->GetFrameRateCore()) << " ms" ;
    gpConsole->Print(gOstr.str(), y++);

    gOstr.str("");
    gOstr << "Entities: " << gpEngine->GetEntityCount();
    gpConsole->Print(gOstr.str(), y++);

    gOstr.str("");
    gOstr << "Press F2 to toggle Processor Throttling";
    gpConsole->Print(gOstr.str(), 27);
}

void GameUpdate()
{
    UpdateConsole();
    gCollisions = 0;
}

void GameRender3D()
{
    //clear the scene using a dark blue color
    gpEngine->ClearScene(D3DCOLOR_XRGB(0, 0, 80));
}

void GameRender2D() 
{
    gpFont->Print(1, SCREEN_HEIGHT-20, "Press ~ or F12 to toggle the Console");

    // draw console
    if (gpConsole->IsShowing()) 
    { gpConsole->Draw(); }
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
        { gpConsole->SetShowing( !gpConsole->IsShowing() ); }
        break;
    case DIK_F2:
        { gpEngine->SetMaximizeProcessor(!gpEngine->GetMaximizeProcessor()); }
    break;
    }
}

void GameEnd() 
{
    delete gpBallImage;
    delete gpConsole;
    delete gpFont;
}

void GameEntityUpdate(A2DEntity* apEntity)
{
    switch(apEntity->GetObjectType())
    {
    case OBJECT_SPRITE:
        {
            A2DSprite* pSpr = static_cast<A2DSprite*>(apEntity);
            float32 w = static_cast<float32>(pSpr->Get(WIDTH) * pSpr->GetScale());
            float32 h = static_cast<float32>(pSpr->Get(HEIGHT) * pSpr->GetScale());
            float32 vx = static_cast<float32>(pSpr->GetVelocity()(X));
            float32 vy = static_cast<float32>(pSpr->GetVelocity()(Y));
            if (pSpr->Get(X) < 0) 
            {
                pSpr->Set(X, 0);
                vx = fabs(vx);
            }
            else if (pSpr->Get(X) > (SCREEN_WIDTH - w)) 
            {
                pSpr->Set(X, SCREEN_WIDTH - w);
                vx = fabs(vx) * -1;
            }
            if (pSpr->Get(Y) < 0) 
            {
                pSpr->Set(Y, 0);
                vy = fabs(vy);
            }
            else if (pSpr->Get(Y) > (SCREEN_HEIGHT - h)) 
            {
                pSpr->Set(Y, (SCREEN_HEIGHT - h));
                vy = fabs(vy) * -1;
            }
            pSpr->SetVelocity(vx, vy);
        }
        break;
    }
}

void GameEntityCollision(A2DEntity* apFirst, A2DEntity* apSecond) 
{
    A2DSprite* pSrpiteA = static_cast<A2DSprite*>(apFirst);
    A2DSprite* pSrpiteB = static_cast<A2DSprite*>(apSecond);

    if ( pSrpiteA->GetObjectType() == OBJECT_SPRITE 
        && pSrpiteB->GetObjectType() == OBJECT_SPRITE)
    {
        gCollisions++;

        float32 x1 = static_cast<float32>(pSrpiteA->Get(X));
        float32 y1 = static_cast<float32>(pSrpiteA->Get(Y));
        float32 x2 = static_cast<float32>(pSrpiteB->Get(X));
        float32 y2 = static_cast<float32>(pSrpiteB->Get(Y));
        float32 vx1 = static_cast<float32>(pSrpiteA->GetVelocity()(X));
        float32 vy1 = static_cast<float32>(pSrpiteA->GetVelocity()(Y));
        float32 vx2 = static_cast<float32>(pSrpiteB->GetVelocity()(X));
        float32 vy2 = static_cast<float32>(pSrpiteB->GetVelocity()(Y));
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
        pSrpiteA->SetVelocity(vx1, vy1);
        pSrpiteB->SetVelocity(vx2, vy2);
    }
}

// unused Event
void GameEntityRender(A2DEntity* apEntity) {}
void GameKeyPress(int32 aKey) {}
void GameMouseButton(int32 aButton) {}
void GameMouseMotion(int32 aX,int32 aY) {}
void GameMouseMove(int32 aX,int32 aY) {}
void GameMouseWheel(int32 wheel) {}
