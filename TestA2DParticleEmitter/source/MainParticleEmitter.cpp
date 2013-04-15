// engine Include
#include <A2DEngine.hpp>
using namespace Advanced2D;

A2DParticleEmitter* pPartA;
A2DParticleEmitter* pPartB;
A2DParticleEmitter* pPartC;
A2DParticleEmitter* pPartD;
A2DParticleEmitter* pPartE;

bool8 GamePreload()
{
    //display engine version in a message box
    gpEngine->SetAppTitle("PARTICLE DEMO");
    gpEngine->SetScreenProperties(A2DEngine::ScreenProperties(1024, 768, 32, false));

    return true;
}

bool8 GameInit(HWND hwnd) 
{
    gpEngine->SetMaximizeProcessor(true);

    //Create Particule
    pPartA = new A2DParticleEmitter();
    pPartA->LoadSpriteImage("../../Assets/particle16.tga");
    pPartA->SetPosition(100, 300);
    pPartA->SetDirection(0);
    pPartA->SetMax(500);
    pPartA->SetAlphaRange(100, 255);
    pPartA->SetSpread(30);
    pPartA->SetVelocity(2.0);
    pPartA->SetLength(250);

    pPartB = new A2DParticleEmitter();
    pPartB->LoadSpriteImage("../../Assets/particle16.tga");
    pPartB->SetPosition(300, 100);
    pPartB->SetDirection(180);
    pPartB->SetScale(0.6);
    pPartB->SetMax(500);
    pPartB->SetAlphaRange(0, 100);
    pPartB->SetColorRange(200, 0, 0, 255, 10, 10);
    pPartB->SetVelocity(2.0);
    pPartB->SetSpread(40);
    pPartB->SetLength(200);

    pPartC = new A2DParticleEmitter();
    pPartC->LoadSpriteImage("../../Assets/particle16.tga");
    pPartC->SetPosition(250, 525);
    pPartC->SetDirection(0);
    pPartC->SetScale(0.5);
    pPartC->SetMax(2000);
    pPartC->SetAlphaRange(100, 150);
    pPartC->SetColorRange(0, 0, 200, 10, 10, 255);
    pPartC->SetVelocity(0.2);
    pPartC->SetSpread(5);
    pPartC->SetLength(180);

    pPartD = new A2DParticleEmitter();
    pPartD->LoadSpriteImage("../../Assets/particle16.tga");
    pPartD->SetPosition(750, 650);
    pPartD->SetScale(0.75);
    pPartD->SetMax(10);
    pPartD->SetAlphaRange(50, 100);
    pPartD->SetColorRange(210, 50, 0, 255, 255, 1);
    pPartD->SetVelocity(2.0);
    pPartD->SetDirection(0);
    pPartD->SetSpread(40);
    pPartD->SetLength(100);

    pPartE = new A2DParticleEmitter();
    pPartE->LoadSpriteImage("../../Assets/particle16.tga");
    pPartE->SetPosition(730, 575);
    pPartE->SetScale(4.0f);
    pPartE->SetMax(1000);
    pPartE->SetAlphaRange(1, 20);
    pPartE->SetColorRange(250, 250, 250, 255, 255, 255);
    pPartE->SetVelocity(2.0);
    pPartE->SetDirection(0);
    pPartE->SetSpread(80);
    pPartE->SetLength(800);

    return true;
}

void GameUpdate() 
{
    //move particles
    pPartA->Update();
    pPartB->Update();

    //update the circular emitter
    double64 dir = pPartC->GetDirection() + 0.2;
    pPartC->SetDirection(dir);
    pPartC->Update();

    //update the rotating emitter
    static double64 unit = 3.1415926535 / 36000.0;
    static double64 angle = 0.0;
    static double64 radius = 150.0;

    angle += unit;
    if (angle > 360.0) 
    { angle = 360.0 - angle; }

    double64 x = 750.0 + cos(angle) * radius;
    double64 y = 500.0 + sin(angle) * radius;

    pPartD->SetPosition(x, y);
    pPartD->Update();

    //update smoke emitter
    pPartE->SetPosition(x, y);
    pPartE->Update();

    //exit when escape key is pressed
    if (KEY_DOWN(VK_ESCAPE))
    {
        gpEngine->ShutDown();
    }
}

void GameEnd() 
{
    delete pPartA;
    delete pPartB;
    delete pPartC;
    delete pPartD;
    delete pPartE;
}

void GameRender3D()
{
    //clear the scene using a dark blue color
    gpEngine->ClearScene(D3DCOLOR_XRGB(0, 0, 0));
}

void GameRender2D()
{   
    pPartA->Draw();
    pPartB->Draw();
    pPartC->Draw();
    pPartD->Draw();
    pPartE->Draw();
}

// unused Event
void GameKeyPress( int32 aKey ) {}
void GameKeyRelease( int32 aKey ) {}
void GameMouseButton( int32 aButton ) {}
void GameMouseMotion( int32 aX, int32 aY ) {}
void GameMouseMove( int32 aX, int32 aY ) {}
void GameMouseWheel( int32 aWheel ) {}