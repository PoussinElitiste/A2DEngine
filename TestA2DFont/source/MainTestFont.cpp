// external include
#include <sstream>

// engine Include
#include <A2DEngine.hpp>
using namespace Advanced2D;

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define OBJECT_BACKGROUND 1
#define OBJECT_SPRITE 100
#define MAX 50

A2DSprite* gpPanel;
A2DTexture* gpAsteroidImage;
A2DFont* gpSystem12;
A2DFont* gpNonprop;
A2DFont* gpVerdana10;

bool8 GamePreload()
{
    //display engine version in a message box
    gpEngine->SetAppTitle("FONT DEMO");
    gpEngine->SetScreenProperties(A2DEngine::ScreenProperties(SCREEN_WIDTH, SCREEN_HEIGHT, 32, false));

    return true;
}

bool8 GameInit(HWND hwnd) 
{
    //load background image
    A2DSprite* pBackground = new A2DSprite();
    pBackground->LoadSpriteImage("../Assets/orion.bmp");
    pBackground->SetObjectType(999);
    gpEngine->AddEntity(pBackground);

    //load asteroid image
    gpAsteroidImage = new A2DTexture();
    gpAsteroidImage->Load("../Assets/asteroid.tga");

    //create asteroid sprites
    A2DSprite* pAsteroid;
    for (int n=0; n < MAX; ++n)
    {
        //create a new asteroid sprite
        pAsteroid = new A2DSprite();
        pAsteroid->SetObjectType(OBJECT_SPRITE);
        pAsteroid->SetImage(gpAsteroidImage);
        pAsteroid->SetTotalFrames(64);
        pAsteroid->SetColumns(8);
        pAsteroid->SetSize(60,60);
        pAsteroid->SetPosition( rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT );
        pAsteroid->SetFrameTimer( rand() % 100 );
        pAsteroid->SetCurrentFrame( rand() % 64 );
        if (rand()%2 == 0) 
        { pAsteroid->SetAnimationDirection(-1); }
        pAsteroid->SetVelocity( static_cast<float32>(rand()%10)/10.0f, static_cast<float32>(rand()%10)/10.0f );

        //add asteroid to the entity manager
        gpEngine->AddEntity(pAsteroid);
    }

    //load the panel
    gpPanel = new A2DSprite();
    gpPanel->LoadSpriteImage("../Assets/panel.tga");
    float32 scale = SCREEN_WIDTH / 640.0f;
    gpPanel->SetScale(scale);
    gpPanel->SetColor(0xBBFFFFFF);

    //load the System12 font
    gpSystem12 = new A2DFont();
    if (!gpSystem12->LoadSpriteImage("../Assets/system12.tga")) 
    {
        gpEngine->Message("Error loading system12.tga");
        return false;
    }
    gpSystem12->SetColumns(16);
    gpSystem12->SetCharSize(14,16);

    if (!gpSystem12->LoadWidthData("../Assets/system12.dat")) 
    {
        gpEngine->Message("Error loading system12.dat");
        return false;
    }

    //load System12 without proportional data
    gpNonprop = new A2DFont();
    gpNonprop->LoadSpriteImage("../Assets/system12.tga");
    gpNonprop->SetColumns(16);
    gpNonprop->SetCharSize(14,16);

    //load the Verdana12 font
    gpVerdana10 = new A2DFont();
    if (!gpVerdana10->LoadSpriteImage("../Assets/verdana10.tga")) 
    {
        gpEngine->Message("Error loading verdana10.tga");
        return false;
    }
    gpVerdana10->SetColumns(16);
    gpVerdana10->SetCharSize(20,16);

    if (!gpVerdana10->LoadWidthData("../Assets/verdana10.dat")) 
    {
        gpEngine->Message("Error loading verdana10.dat");
        return false;
    }

    return true;
}

void GameKeyRelease(int32 aKey)
{
    if (aKey == DIK_ESCAPE) 
    { gpEngine->ShutDown(); }
}

void GameEntityUpdate(A2DEntity* apEntity)
{
    switch(apEntity->GetObjectType())
    {
        case OBJECT_SPRITE:
        {        
            A2DSprite* pSpr = static_cast<A2DSprite*>(apEntity);
            if (pSpr->Get(X) < -60) 
            { pSpr->SetPosition(X, SCREEN_WIDTH); }
            if (pSpr->Get(X) > SCREEN_WIDTH) 
            { pSpr->SetPosition(X, -60); }
            if (pSpr->Get(Y) < -60) 
            { pSpr->SetPosition(Y, SCREEN_HEIGHT); }
            if (pSpr->Get(Y) > SCREEN_HEIGHT) 
            { pSpr->SetPosition(Y, -60); }
        }
        break;
    }
}

void GameEnd() 
{
    delete gpPanel;
    delete gpAsteroidImage;
    delete gpSystem12;
    delete gpNonprop;
    delete gpVerdana10;
}

void GameRender3D()
{
    //clear the scene using a dark blue color
    gpEngine->ClearScene(D3DCOLOR_XRGB(0, 0, 80));
}

void GameRender2D() 
{
    std::ostringstream os;
    A2DString str;
    gpPanel->Draw();
    gpNonprop->Print(1,1, "This is the SYSTEM 12 font WITHOUT proportional data", 0xFF111111);
    gpNonprop->Print(1,20, "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 0xFF111111);
    gpNonprop->Print(1,40, "abcdefghijklmnopqrstuvwxyz!@#$%^&*()_+{}|:<>?", 0xFF111111);

    gpSystem12->SetScale(1.0f);
    gpSystem12->Print(1,80, "This is the SYSTEM 12 font WITH proportional data", 0xFF111111);
    gpSystem12->Print(1,100, "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 0xFF111111);
    gpSystem12->Print(1,120, "abcdefghijklmnopqrstuvwxyz!@#$%^&*()_+{}|:<>?", 0xFF111111);

    for (float32 s=0.5f; s<2.0f; s+=0.25f) 
    {
        gpVerdana10->SetScale( s );
        int32 x = (int32)(s * 20);
        int32 y = (int32)(100 + s * 120);
        os.str("");
        os << "VERDANA 10 font scaled at " << s*100 << "%";
        gpVerdana10->Print(x,y, os.str(), 0xFF111111);
    }

    gpVerdana10->SetScale( 1.5f );
    gpVerdana10->Print(600, 140, gpEngine->GetVersionText(), 0xFF991111);
    os.str("");
    os << "SCREEN : " << static_cast<float32>(1000.0f/gpEngine->GetFrameRateReal()) << " ms";
    gpVerdana10->Print(600, 180, os.str(), 0xFF119911);
    os.str("");
    os << "CORE : " << static_cast<float32>(1000.0f/gpEngine->GetFrameRateCore()) << " ms";
    gpVerdana10->Print(600, 220, os.str(), 0xFF119911);
}

// unused Event
void GameUpdate() {}
void GameEntityRender(A2DEntity* apEntity) {}
void GameKeyPress(int32 aKey) {}
void GameMouseButton(int32 aButton) {}
void GameMouseMotion(int32 aX,int32 aY) {}
void GameMouseMove(int32 aX,int32 aY) {}
void GameMouseWheel(int32 wheel) {}
void GameEntityCollision(A2DEntity* apFirst, A2DEntity* apSecond) {}
