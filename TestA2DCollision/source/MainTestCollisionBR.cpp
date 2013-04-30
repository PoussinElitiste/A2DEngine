//------------------------
// MainTestCollisionBR.cpp
//------------------------
// external include
#include <sstream>

// engine Include
#include <A2DEngine.hpp>
using namespace Advanced2D;

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define OBJECT_BACKGROUND 1
#define OBJECT_SPRITE 100
#define MAX 40

A2DTexture* gpAsteroidImage;
A2DFont* gpFont;

A2DConsole* gpConsole;
std::ostringstream gOstr;
A2DTexture* gpCollisionBox;
int32 gCollisions;

bool8 GamePreload()
{
    //display engine version in a message box
    gpEngine->SetAppTitle("COLLISION BR DEMO");
    gpEngine->SetScreenProperties(A2DEngine::ScreenProperties(SCREEN_WIDTH, SCREEN_HEIGHT, 32, false));

    return true;
}

bool8 GameInit(HWND hwnd) 
{
    //load background image
    A2DSprite* pBackground = new A2DSprite();
    if (!pBackground->LoadSpriteImage("../Assets/orion.bmp"))
    {
        gpEngine->Message("Error loading orion.bmp");
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
    gpAsteroidImage = new A2DTexture();
    if ( !gpAsteroidImage->Load("../Assets/asteroid.tga") )
    {
        gpEngine->Message("Error loading asteroid.tga");
        return false;
    }

    //create asteroid sprites
    A2DSprite* pAsteroid;
    for (int n=0; n < MAX; ++n)
    {
        //create a new asteroid sprite
        pAsteroid = new A2DSprite();
        pAsteroid->SetObjectType(OBJECT_SPRITE);
        gOstr.str(""); 
        gOstr << "ASTEROID" << n;
        pAsteroid->SetName(gOstr.str());
        pAsteroid->SetImage(gpAsteroidImage);
        pAsteroid->SetScale( static_cast<float32>(rand() % 150 + 50) / 100.0f );

        // set animation properties
        pAsteroid->SetTotalFrames(64);
        pAsteroid->SetColumns(8);
        pAsteroid->SetSize(60, 60);
        pAsteroid->SetPosition( rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT );
        pAsteroid->SetFrameTimer( rand() % 90 + 10 );
        pAsteroid->SetCurrentFrame( rand() % 64 );
        if (rand()%2 == 0) 
        { pAsteroid->SetAnimationDirection(-1); }

        //set movement properties
        float32 vx = static_cast<float32>(rand()%10 - 5)/10.0f;
        float32 vy = static_cast<float32>(rand()%10 - 5)/10.0f;
        pAsteroid->SetVelocity( vx, vy );

        //collision toggle
        pAsteroid->SetCollidable(true);

        //movement timer keeps sprite consistent at any framerate
        pAsteroid->SetMoveTimer( 16 );

        //add asteroid to the entity manager
        gpEngine->AddEntity(pAsteroid);
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

    //load highlight image used to show collisions
    gpCollisionBox = new A2DTexture();
    if (!gpCollisionBox->Load("../Assets/highlight.tga")) 
    {
        gpEngine->Message("Error loading highlight.tga");
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
    gOstr << "SCREEN : " << (float32)(1000.0f/gpEngine->GetFrameRateReal()) << " ms (" << gpEngine->GetFrameRateReal() << " fps)";
    gpConsole->Print(gOstr.str(), y++);
    y++;

    gOstr.str("");
    gOstr << "CORE : " << (float32)(1000.0f/gpEngine->GetFrameRateCore()) << " ms (" << gpEngine->GetFrameRateCore() << " fps)";
    gpConsole->Print(gOstr.str(), y++);

    gOstr.str("");
    gOstr << "Processor throttling: " << gpEngine->GetMaximizeProcessor();
    gpConsole->Print(gOstr.str(), y++);
    y++;
    gOstr.str("");
    A2DEngine::ScreenProperties& screenProperties = gpEngine->GetScreenProperties();
    gOstr << "Screen: " << screenProperties.mWidth << "," << screenProperties.mHeight << "," << screenProperties.mColorDepth;
    gpConsole->Print(gOstr.str(), y++);
    y++;

    gOstr.str("");
    gOstr << "Entities: " << gpEngine->GetEntityCount();
    gpConsole->Print(gOstr.str(), y++);
    gOstr.str("");
    gOstr << "Collisions: " << gCollisions;
    gpConsole->Print(gOstr.str(), y++);
    y++;

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
    delete gpAsteroidImage;
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
            if (pSpr->Get(X) < -60) { pSpr->SetPosition(X, SCREEN_WIDTH); }
            if (pSpr->Get(X) > SCREEN_WIDTH) { pSpr->SetPosition(X, -60); }
            if (pSpr->Get(Y) < -60) { pSpr->SetPosition(Y, SCREEN_HEIGHT); }
            if (pSpr->Get(Y) > SCREEN_HEIGHT) { pSpr->SetPosition(Y, -60); }
        }
        break;
    }
}

void GameEntityCollision(A2DEntity* apFirst, A2DEntity* apSecond) 
{
    A2DSprite* pBox;
    A2DSprite* pSrpiteA = static_cast<A2DSprite*>(apFirst);
    A2DSprite* pSrpiteB = static_cast<A2DSprite*>(apSecond);
    if ( pSrpiteA->GetObjectType() == OBJECT_SPRITE 
        && pSrpiteB->GetObjectType() == OBJECT_SPRITE)
    {
        gCollisions++;

        //add first collision box
        pBox = new A2DSprite();
        pBox->SetColor(0x33DD4444);
        pBox->SetImage(gpCollisionBox);
        pBox->SetPosition( pSrpiteA->GetPosition() );
        pBox->SetScale( pSrpiteA->Get(WIDTH) * pSrpiteA->GetScale() / 100.0f );
        pBox->SetLifetime(100);
        gpEngine->AddEntity( pBox );

        //add second collision box
        pBox = new A2DSprite();
        pBox->SetColor(0x33DD4444);
        pBox->SetImage(gpCollisionBox);
        pBox->SetPosition( pSrpiteB->GetPosition() );
        pBox->SetScale( pSrpiteB->Get(WIDTH) * pSrpiteB->GetScale() / 100.0f );
        pBox->SetLifetime(100);
        gpEngine->AddEntity( pBox );
    }
}

// unused Event
void GameEntityRender(A2DEntity* apEntity) {}
void GameKeyPress(int32 aKey) {}
void GameMouseButton(int32 aButton) {}
void GameMouseMotion(int32 aX,int32 aY) {}
void GameMouseMove(int32 aX,int32 aY) {}
void GameMouseWheel(int32 wheel) {}
