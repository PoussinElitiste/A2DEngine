// engine Include
#include <A2DEngine.hpp>
using namespace Advanced2D;

// external include
#include <dinput.h>

A2DParticleEmitter* gpParticle;
A2DSprite* gpCursor;

bool8 GamePreload()
{
    //display engine version in a message box
    gpEngine->SetAppTitle("INPUT DEMO");
    gpEngine->SetScreenProperties(A2DEngine::ScreenProperties(1024, 768, 32, false));

    return true;
}

bool8 GameInit(HWND hwnd) 
{
    //load sprite
    gpParticle = new A2DParticleEmitter();
    gpParticle->LoadSpriteImage("../Assets/particle16.tga");
    gpParticle->SetMax(0);
    gpParticle->SetAlphaRange(50,200);
    gpParticle->SetDirection(0);
    gpParticle->SetSpread(270);
    gpParticle->SetScale(1.5f);
    gpParticle->SetLength(2000);

    //load cursor
    gpCursor = new A2DSprite();
    gpCursor->LoadSpriteImage("../Assets/particle16.tga");

    return true;
}

void GameUpdate() 
{
    gpParticle->Update();
}

void GameKeyPress(int32 aKey) { }
void GameKeyRelease(int32 aKey)
{
    if (aKey == DIK_ESCAPE) 
    { gpEngine->ShutDown(); }
}

void GameMouseButton(int32 aButton)
{
    switch(aButton) 
    {
    case 0: //button 1
        gpParticle->SetVelocity( (rand() % 10 - 5) / 500.0f );
        gpParticle->Add();
        break;
    }
}

void GameMouseMotion(int32 aX,int32 aY) 
{ }

void GameMouseMove(int32 aX,int32 aY)
{
    float32 fx = (float32)aX;
    float32 fy = (float32)aY;

    gpCursor->SetPosition(fx, fy);
    gpParticle->SetPosition(fx, fy);
}

void GameMouseWheel(int32 wheel) 
{ }

void GameRender3D()
{
    gpEngine->ClearScene(D3DCOLOR_XRGB(0,0,0));
}

void GameRender2D()
{
    gpParticle->Draw();
    gpCursor->Draw();
}

void GameEnd()
{
    delete gpParticle;
    delete gpCursor;
}
