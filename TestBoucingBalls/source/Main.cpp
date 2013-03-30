// engine Include
#include <A2DEngine.hpp>
using namespace Advanced2D;

// external include
#include <vector>
using std::vector;

//we need this keyboard macro to detect Escape key
#define KEY_DOWN(keyState) ((GetAsyncKeyState(keyState) & 0x8000)?1:0)

A2DCamera* gpCamera;

//define the number of spheres
#define SPHERES 10

//create the entity vector and iterator
typedef std::vector<A2DMesh*>::iterator meshIterator;
std::vector<A2DMesh*> gBalls;

bool GamePreload()
{
    //display engine version in a message box
    gpEngine->SetAppTitle("BOUNCING BALLS");
    gpEngine->SetScreenProperties(A2DEngine::ScreenProperties(1024, 768, 32, false));

    return true;
}

bool GameInit(HWND hwnd) 
{
    srand(time(NULL));

    // Set Camera perspective
    gpCamera = new A2DCamera();
    A2DVector3 position(0.f, 2.f, 10.f);
    A2DVector3 target(0.f, 0.f, 0.f);
    gpCamera->SetLocalisation(A2DCamera::A2DLocalisationInfos(position, target));
    gpCamera->Update();

    // create ball meshes
    A2DMesh* pBall;
    for(int32 i = 0; i < SPHERES; ++i)
    {
        pBall = new A2DMesh();
        pBall->Load("../../asset/ball.x");
        
        float32 vX = static_cast<float>(rand()%8+1)/1000.f;
        float32 vY = static_cast<float>(rand()%8+1)/1000.f;
        float32 vZ = static_cast<float>(rand()%8+1)/1000.f;
        A2DMesh::A2DTransformationInfos transfo;
        transfo.mPosition = A2DVector3();
        transfo.mScale = A2DVector3(0.3f, 0.3f, 0.3f);
        transfo.mVelocity = A2DVector3(vX, vY, vZ);
        transfo.mRotate = A2DVector3(0.1f, 0.2f, 0.01f);
        pBall->SetTransformation(transfo);

        gBalls.push_back(pBall);
    }

    return true;
}

void GameUpdate() 
{
    for(meshIterator it = gBalls.begin(); it != gBalls.end(); ++it)
    {
        (*it)->Update();
        (*it)->LimitBoundary(-5, 5, 4, -4, 4, -4);
    }
    
    //escape key will terminate the program
    if (KEY_DOWN(VK_ESCAPE)) gpEngine->Close();
}

void GameEnd() 
{
    for(meshIterator it = gBalls.begin(); it != gBalls.end(); ++it)
    {
        delete *it;
    }

    gBalls.clear();

    if(gpCamera)
    { delete gpCamera; }
}

void GameRender3D()
{
    static DWORD start = 0;

    // clear the scene using a dark blue color
    gpEngine->ClearScene(D3DCOLOR_RGBA(30,30,100, 0));

    //return to the origin
    gpEngine->SetIdentity();

    // draw entities
    for(meshIterator it = gBalls.begin(); it != gBalls.end(); ++it)
    {
        //remember, every entity must be moved individually!
        (*it)->Tranform();
        (*it)->Draw();
    }
}
