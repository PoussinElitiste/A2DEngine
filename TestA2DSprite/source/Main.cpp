// engine Include
#include <A2DEngine.hpp>
using namespace Advanced2D;

A2DSprite* gpShip;

bool GamePreload()
{
    //display engine version in a message box
    gpEngine->SetAppTitle("SPRITE ROTATION AND SCALING DEMO");
    gpEngine->SetScreenProperties(A2DEngine::ScreenProperties(800, 600, 32, false));

    return true;
}

bool GameInit(HWND hwnd) 
{
    //load sprite
    gpShip = new A2DSprite();
    //gpShip->LoadSpriteImage("../Assets/fatship_colorkeyed.bmp");
    //gpShip->LoadSpriteImage("../Assets/fatship_alpha.tga");
    gpShip->LoadSpriteImage("../Assets/fatship.tga");

    return true;
}

void GameUpdate() 
{
    static double64 scaleFactor = 0.001;

    //set position
    gpShip->SetPosition(400, 300);

    //set rotation
    gpShip->SetRotation( timeGetTime() / 600.0 );

    //set scale
    double64 newScale = gpShip->GetScale() + scaleFactor;
    if ( newScale < 0.01 || newScale > 1.5 ) 
    { scaleFactor *= -1; }
    gpShip->SetScale(newScale);

    //exit when escape key is pressed
    if (KEY_DOWN(VK_ESCAPE))
    {
        gpEngine->ShutDown();
    }
}

void GameEnd() 
{
    delete gpShip;
}

void GameRender3D()
{
    //clear the scene using a dark blue color
    gpEngine->ClearScene(D3DCOLOR_XRGB(0, 0, 80));
}

void GameRender2D()
{
    ////calculate center of screen
    //int cx = gpEngine->GetScreenProperties().mWidth / 2;
    //int cy = gpEngine->GetScreenProperties().mHeight / 2;

    ////calculate center of sprite
    //int sx = gpShip->Get(WIDTH) / 2;
    //int sy = gpShip->Get(HEIGHT) / 2;

    ////draw sprite centered
    //gpShip->SetPosition( cx-sx, cy-sy);
    gpShip->Draw();
}
