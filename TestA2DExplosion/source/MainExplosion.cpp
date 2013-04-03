// engine Include
#include <A2DEngine.hpp>
using namespace Advanced2D;

A2DSprite* gpExplosion;

bool GamePreload()
{
    //display engine version in a message box
    gpEngine->SetAppTitle("SPRITE ANIMATION DEMO");
    gpEngine->SetScreenProperties(A2DEngine::ScreenProperties(800, 600, 32, false));

    return true;
}

bool GameInit(HWND hwnd) 
{
    //load sprite
    gpExplosion = new A2DSprite();
    gpExplosion->LoadSpriteImage("../Assets/explosion_30_128.tga");
    gpExplosion->SetTotalFrames(30);
    gpExplosion->SetColumns(6);
    gpExplosion->SetSize(128,128);
    gpExplosion->SetFrameTimer(40);

    return true;
}

void GameUpdate() 
{
    int cx,cy;

    //animate the explosion sprite
    gpExplosion->Animate();

    if (gpExplosion->GetCurrentFrame() == gpExplosion->GetTotalFrames() - 1)
    {
        //set a new random location
        cx = rand() % ( gpEngine->GetScreenProperties().mWidth - 128 );
        cy = rand() % ( gpEngine->GetScreenProperties().mHeight - 128 );
        gpExplosion->SetPosition(cx,cy);
    }

    //exit when escape key is pressed
    if (KEY_DOWN(VK_ESCAPE))
    {
        gpEngine->ShutDown();
    }
}

void GameEnd() 
{
    delete gpExplosion;
}

void GameRender3D()
{
    //clear the scene using a dark blue color
    gpEngine->ClearScene(D3DCOLOR_XRGB(0, 0, 80));
}

void GameRender2D()
{
    //draw the current frame of the explosion
    gpExplosion->Draw();
}
