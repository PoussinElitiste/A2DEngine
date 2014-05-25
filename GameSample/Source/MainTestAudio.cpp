// engine Include
#include <A2DEngine.hpp>
using namespace Advanced2D;


A2DSamplePtr gpWobble;

bool8 GamePreload()
{
    //display engine version in a message box
    gpEngine->setAppTitle("AUDIO TEST");
    gpEngine->setScreenProperties(A2DEngine::ScreenProperties(640, 480, 32, false));

    return true;
}

bool8 GameInit(HWND hwnd)
{
    // create bug by trigger mouse Button event
    // TODO: use engine message to display command
    // gpEngine->Message("Press mouse buttons to hear sound clips!");
    A2DAudioPtr pAudio = gpEngine->getAudio(); 

    //load sample into audio manager
    if (!pAudio->load("../../Assets/gong.ogg", "gong")) 
    {
        gpEngine->message("Error loading gong.ogg");
        return false;
    }

    //load sample into audio manager
    if (!pAudio->load("../../Assets/explosion.wav", "explosion")) 
    {
        gpEngine->message("Error loading explosion.wav");
        return false;
    }

    //load independent sample
    gpWobble = A2DSample::create();
    gpWobble = pAudio->load("../../Assets/wobble.wav");
    if (!gpWobble) 
    {
        gpEngine->message("Error loading wobble.wav");
        return false;
    }

    return true;
}

void GameKeyRelease(uint32 aKey)
{
    if (aKey == DIK_ESCAPE) 
    { gpEngine->shutDown(); }
}

void GameMouseButton(uint32 aButton)
{
    A2DAudioPtr pAudio = gpEngine->getAudio();

    switch(aButton) 
    {
    case 0:
        //play gong sample stored in audio manager
        if(!pAudio->isPlaying("gong"))
        {
            pAudio->play("gong");
        }
        break;

    case 1:
        //play explosion sample stored in audio manager
        if(!pAudio->isPlaying("explosion"))
        {
           pAudio->play("explosion");
        }
        break;

    case 2:
        //play woggle sample stored independently
        if(!pAudio->isPlaying(gpWobble))
        {
           pAudio->play(gpWobble);
        }
        break;
    }
}

void GameRender3D()
{
    gpEngine->clearScene(D3DCOLOR_XRGB(100,0,0));
}

void GameEnd()
{
    gpEngine->getAudio()->stopAll();
}

// unused Event
void GameEntityRender(A2DEntityPtr apEntity){}
void GameEntityCollision(A2DEntityPtr apFirst, A2DEntityPtr apSecond){}
void GameEntityUpdate(A2DEntityPtr apEntity){}
void GameUpdate() {}
void GameKeyPress(uint32 aKey) {}
void GameMouseWheel(uint32 wheel) {}
void GameRender2D() {}
void GameMouseMotion(int32 aX,int32 aY) {}
void GameMouseMove(int32 aX,int32 aY) {}