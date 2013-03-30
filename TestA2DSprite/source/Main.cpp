// engine Include
#include <A2DEngine.hpp>
using namespace Advanced2D;

A2DSprite* gpSprite;

bool GamePreload()
{
    //display engine version in a message box
    gpEngine->SetAppTitle("SPRITE COLOR KEY DEMO");
    gpEngine->SetScreenProperties(A2DEngine::ScreenProperties(640, 480, 32, false));

    return true;
}

bool GameInit(HWND hwnd) 
{
    //load sprite
    gpSprite = new A2DSprite();
    //gpSprite->LoadSpriteImage("../Assets/fatship_colorkeyed.bmp");
    gpSprite->LoadSpriteImage("../Assets/fatship_alpha.tga");

    return true;
}

void GameUpdate() 
{
    //exit when escape key is pressed
    if (KEY_DOWN(VK_ESCAPE))
    {
        gpEngine->ShutDown();
    }
}

void GameEnd() 
{
    delete gpSprite;
}

void GameRender3D()
{
    //clear the scene using a dark blue color
    gpEngine->ClearScene(D3DCOLOR_XRGB(0, 0, 80));

    //return to the origin
    gpEngine->SetIdentity();
}

void GameRender2D()
{
    //calculate center of screen
    int cx = gpEngine->GetScreenProperties().mWidth / 2;
    int cy = gpEngine->GetScreenProperties().mHeight / 2;

    //calculate center of sprite
    int sx = gpSprite->Get(WIDTH) / 2;
    int sy = gpSprite->Get(HEIGHT) / 2;

    //draw sprite centered
    gpSprite->SetPosition( cx-sx, cy-sy);
    gpSprite->Draw();
}
