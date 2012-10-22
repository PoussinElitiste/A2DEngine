// engine Include
#include <A2DEngine.hpp>
using namespace Advanced2D;

// external include
#include <vector>
using std::vector;

//we need this keyboard macro to detect Escape key
#define KEY_DOWN(keyState) ((GetAsyncKeyState(keyState) & 0x8000)?1:0)

A2DCamera*  gpCamera;
A2DLight*   gpLight;
A2DMesh*    gpMesh;

bool GamePreload()
{
    //display engine version in a message box
    gpEngine->SetAppTitle( "BOUNCING BALLS");
    gpEngine->SetScreenProperties(A2DEngine::ScreenProperties(1024, 768, 32, false));

    return true;
}

bool GameInit(HWND hwnd) 
{
    srand(static_cast<uint32>(time(NULL)));

    // Set Camera perspective
    gpCamera = new A2DCamera();
    A2DRenderVector position(0.f, 2.f, 10.f);
    A2DRenderVector target(0.f, 0.f, 0.f);
    gpCamera->SetLocalisation(A2DCamera::A2DLocalisationInfos(position, target));
    gpCamera->Update();

    // load the mesh
    gpMesh = new A2DMesh();
    //gpMesh->CreateCube(1.f, 1.f, 1.f);
    gpMesh->Load("../../asset/ball.x");
    A2DMesh::A2DTransformationInfos transfo;
    //transfo.mScale = A2DRenderVector(2.f, 2.f, 2.f);
    gpMesh->SetTransformation(transfo);

    // create a directional light
    //A2DRenderVector pos(10.f, 0.f, 0.f);
    //A2DRenderVector dir(0.f, 0.f, 0.f);
    //gpLight = new A2DLight(0, D3DLIGHT_DIRECTIONAL, pos, dir, 100.f);

    // create a spot light
    A2DRenderVector pos(-10.f, -20.f, 0.f);
    A2DRenderVector dir(0.f, 2.f, 0.f);
    gpLight = new A2DLight(0, D3DLIGHT_SPOT, pos, dir, 1000.f);

    // create a point light
    //A2DRenderVector pos(0.f, -20.f, 0.f);
    //A2DRenderVector dir(0.f, 0.f, 0.f);
    //gpLight = new A2DLight(0, D3DLIGHT_POINT, pos, dir, 20.f);

    // set a low ambient level
    gpEngine->SetAmbient(D3DCOLOR_XRGB(20, 20, 20));

    return true;
}

void GameUpdate() 
{
    //rotate the cytovirus mesh
    gpMesh->Rotate(-0.1f, 0.0f, 0.05f);
    
    //escape key will terminate the program
    if (KEY_DOWN(VK_ESCAPE)) { gpEngine->Close(); }
}

void GameEnd() 
{
    delete gpCamera;
    delete gpLight;
    delete gpMesh;
}

void GameRender3D()
{
    static DWORD start = 0;

    // clear the scene using a dark blue color
    gpEngine->ClearScene(D3DCOLOR_XRGB(0,0,80));
    gpEngine->SetIdentity();

    gpMesh->Tranform();
    gpMesh->Draw();
}

void GameRender2D()
{

}
