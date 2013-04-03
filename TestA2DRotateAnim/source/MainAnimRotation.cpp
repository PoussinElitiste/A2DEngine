// engine Include
#include <A2DEngine.hpp>
using namespace Advanced2D;

A2DSprite* gpAsteroid;

bool GamePreload()
{
    //display engine version in a message box
    gpEngine->SetAppTitle("SPRITE ANIMATE/ROTATE/SCALE DEMO");
    gpEngine->SetScreenProperties(A2DEngine::ScreenProperties(800, 600, 32, false));

    return true;
}

bool GameInit(HWND hwnd) 
{
    //load sprite
    gpAsteroid = new A2DSprite();
    gpAsteroid->LoadSpriteImage("../Assets/asteroid.tga");
    gpAsteroid->SetTotalFrames(64);
    gpAsteroid->SetColumns(8);
    gpAsteroid->SetSize(60, 60);
    gpAsteroid->SetFrameTimer(30);

    return true;
}

void GameUpdate() 
{
    static double64 scaleFactor = 0.005;

    //set position
    gpAsteroid->SetPosition(400, 300);

    //set rotation
    gpAsteroid->SetRotation( timeGetTime() / 600.0 );

    //set scale
    double64 newScale = gpAsteroid->GetScale() + scaleFactor;
    if ( newScale < 0.25 || newScale > 5 ) 
    { scaleFactor *= -1; }
    gpAsteroid->SetScale(newScale);

    //exit when escape key is pressed
    if (KEY_DOWN(VK_ESCAPE))
    {
        gpEngine->ShutDown();
    }
}

void GameEnd() 
{
    delete gpAsteroid;
}

void GameRender3D()
{
    //clear the scene using a dark blue color
    gpEngine->ClearScene(D3DCOLOR_XRGB(0, 0, 80));
}

void GameRender2D()
{
    //animate the Asteroid sprite
    gpAsteroid->Animate();

    //draw the current frame of the explosion
    gpAsteroid->Draw();
}
