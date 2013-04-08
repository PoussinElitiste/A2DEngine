// engine Include
#include <A2DEngine.hpp>
using namespace Advanced2D;


A2DSample* gpWobble;

bool8 GamePreload()
{
    //display engine version in a message box
    gpEngine->SetAppTitle("AUDIO TEST");
    gpEngine->SetScreenProperties(A2DEngine::ScreenProperties(640, 480, 32, false));

    return true;
}

bool8 GameInit(HWND hwnd) 
{
    // create bug by trigger mouse Button event
    // TODO: use engine message to display command
    // gpEngine->Message("Press mouse buttons to hear sound clips!");
    A2DAudio* pAudio = gpEngine->Audio(); 

    //load sample into audio manager
    if (!pAudio->Load("../Assets/gong.ogg", "gong")) 
    {
        gpEngine->Message("Error loading gong.ogg");
        return false;
    }

    //load sample into audio manager
    if (!pAudio->Load("../Assets/explosion.wav", "explosion")) 
    {
        gpEngine->Message("Error loading explosion.wav");
        return false;
    }

    //load independent sample
    gpWobble = new A2DSample();
    gpWobble = pAudio->Load("../Assets/wobble.wav");
    if (!gpWobble) 
    {
        gpEngine->Message("Error loading wobble.wav");
        return false;
    }

    return true;
}

void GameKeyRelease(int32 aKey)
{
    if (aKey == DIK_ESCAPE) 
    { gpEngine->ShutDown(); }
}

void GameMouseButton(int32 aButton)
{
    A2DAudio* pAudio = gpEngine->Audio();

    switch(aButton) 
    {
    case 0:
        //play gong sample stored in audio manager
        if(!pAudio->IsPlaying("gong"))
        {
            pAudio->Play("gong");
        }
        break;

    case 1:
        //play explosion sample stored in audio manager
        if(!pAudio->IsPlaying("explosion"))
        {
           pAudio->Play("explosion");
        }
        break;

    case 2:
        //play woggle sample stored independently
        if(!pAudio->IsPlaying(gpWobble))
        {
           pAudio->Play(gpWobble);
        }
        break;
    }
}

void GameRender3D()
{
    gpEngine->ClearScene(D3DCOLOR_XRGB(100,0,0));
}

void GameEnd()
{
    gpEngine->Audio()->StopAll();
    delete gpWobble;
}

// unused Event
void GameUpdate() {}
void GameKeyPress(int32 aKey) {}
void GameMouseWheel(int32 wheel) {}
void GameRender2D() {}
void GameMouseMotion(int32 aX,int32 aY) {}
void GameMouseMove(int32 aX,int32 aY) {}