// engine Include
#include <A2DEngine.hpp>
using namespace Advanced2D;

A2DCamera* gpCamera;
A2DMesh* gpMesh;

bool GamePreload()
{
    //display engine version in a message box
    gpEngine->SetAppTitle( "CUBE DEMO");
    gpEngine->SetScreenProperties(A2DEngine::ScreenProperties(1024, 768, 32, false));

    return true;
}

bool GameInit(HWND hwnd) 
{
    // create cube
    gpMesh = new A2DMesh();
    gpMesh->CreateCube(2.f, 2.f, 2.f);

    // Set Camera perspective
    gpCamera = new A2DCamera();
    A2DVector3 position(0.f, 2.f, 6.f);
    A2DVector3 target(0.f, 0.f, 0.f);
    gpCamera->SetLocalisation(A2DCamera::A2DLocalisationInfos(position, target));
    gpCamera->Update();

    //set the ambient color
    gpEngine->SetAmbient(D3DCOLOR_XRGB(40,40,255));

    return true;
}

void GameUpdate() {}

void GameEnd() 
{
    delete gpCamera;
    delete gpMesh;
}

void GameRender3D()
{
    //clear the scene using a dark blue color
    gpEngine->ClearScene(D3DCOLOR_RGBA(30,30,100, 0));

    //return to the origin
    gpEngine->SetIdentity();

    //rotate and draw the cube
    gpMesh->Rotate(2.0f, 0.0f, 0.0f);
    gpMesh->Tranform();
    gpMesh->Draw();
}
