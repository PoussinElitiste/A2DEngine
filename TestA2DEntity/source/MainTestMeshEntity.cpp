// external include
#include <sstream>

// engine Include
#include <A2DMesh.hpp>
#include <A2DCamera.hpp>
#include <A2DLight.hpp>

using namespace Advanced2D;

#define MAX 10

A2DCamera* gpCamera;
A2DLight* gpLight;

bool8 GamePreload()
{
    //display engine version in a message box
    gpEngine->SetAppTitle("MESH ENTITY DEMO");
    gpEngine->SetScreenProperties(A2DEngine::ScreenProperties(1024, 768, 32, false));

    return true;
}

bool8 GameInit(HWND hwnd) 
{
   //set the camera and perspective
    gpCamera = new A2DCamera();
    A2DRenderVector cameraPosition(0.0f, 2.0f, 50.0f);
    A2DRenderVector cameraTarget(0.0f, 0.0f, 0.0f);

    gpCamera->SetLocalisation(A2DCamera::A2DLocalisationInfos(cameraPosition, cameraTarget));
    gpCamera->Update();

    //create a directional light
    A2DRenderVector lightPosition(0.0f,0.0f,0.0f);
    A2DRenderVector lightDirection(1.0f,0.0f,0.0f);
    gpLight = new A2DLight(0, D3DLIGHT_DIRECTIONAL, lightPosition, lightDirection, 100);
    gpLight->SetColor(D3DXCOLOR(1,0,0,0));
    gpEngine->SetAmbient(D3DCOLOR_RGBA(0,0,0,0));

    //load meshes
    A2DMesh* pMesh;
    A2DMesh::A2DTransformationInfos meshTrans;

    for (int n=0; n<MAX; n++) 
    {
        pMesh = new A2DMesh();
        pMesh->Load("../Assets/cytovirus.x");
        
        meshTrans.mScale = A2DRenderVector(0.02f, 0.02f, 0.02f);

        float32 x = (float32)(rand() % 40 - 20);
        float32 y = (float32)(rand() % 40 - 20);
        float32 z = (float32)(rand() % 10 - 5);

        meshTrans.mPosition = A2DRenderVector(x, y, z);

        pMesh->SetTransformation(meshTrans);

        //add mesh to entity manager
        gpEngine->AddEntity(pMesh);
    }

    return true;
}

void GameKeyRelease(int32 aKey)
{
    if (aKey == DIK_ESCAPE) 
    { gpEngine->ShutDown(); }
}

void GameRender3D()
{
    //clear the scene using a dark blue color
    gpEngine->ClearScene(D3DCOLOR_XRGB(0, 0, 80));
}

void GameEntityUpdate(A2DEntity* apEntity)
{
    if (apEntity->GetRenderType() == RENDER_3D) 
    {
        //type-cast Entity to a Mesh
        A2DMesh* pMesh = static_cast<A2DMesh*>(apEntity);

        //perform a simple rotation
        pMesh->Rotate(0, 0.2f, 0);
    }
}

void GameEntityRender(A2DEntity* apEntity)
{
    //type-cast Entity to a Mesh
    A2DMesh* pMesh = static_cast<A2DMesh*>(apEntity);
    //engine automatically renders each entity
    //but we can respond to each render event here
}

void GameEnd() 
{
    delete gpCamera;
    delete gpLight;
}

// unused Event
void GameUpdate() {}
void GameRender2D() {}
void GameKeyPress(int32 aKey) {}
void GameMouseButton(int32 aButton) {}
void GameMouseMotion(int32 aX,int32 aY) {}
void GameMouseMove(int32 aX,int32 aY) {}
void GameMouseWheel(int32 wheel) {}
