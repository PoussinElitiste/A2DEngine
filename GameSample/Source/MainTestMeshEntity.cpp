// external include
#include <sstream>
using namespace std::tr1;

// engine Include
#include <A2DEngine.hpp>
using namespace Advanced2D;

#define MAX 10

A2DCameraPtr gpCamera;
A2DLightPtr gpLight;

bool8 GamePreload()
{
    //display engine version in a message box
    gpEngine->setAppTitle("MESH ENTITY DEMO");
    gpEngine->setScreenProperties(A2DEngine::ScreenProperties(1024, 768, 32, false));

    return true;
}

bool8 GameInit(HWND hwnd) 
{
   //set the camera and perspective
    gpCamera = A2DCamera::create();
    A2DRenderVector cameraPosition(0.0f, 2.0f, 50.0f);
    A2DRenderVector cameraTarget(0.0f, 0.0f, 0.0f);

    gpCamera->setLocalisation(A2DCamera::A2DLocalisationInfos(cameraPosition, cameraTarget));
    gpCamera->update();

    //create a directional light
    A2DRenderVector lightPosition(0.0f,0.0f,0.0f);
    A2DRenderVector lightDirection(1.0f,0.0f,0.0f);
    gpLight = A2DLight::create(0, D3DLIGHT_DIRECTIONAL, lightPosition, lightDirection, 100);
    gpLight->setColor(D3DXCOLOR(1,0,0,0));
    gpEngine->setAmbient(D3DCOLOR_RGBA(0,0,0,0));

    //load meshes
    A2DMeshPtr pMesh; 
    A2DMesh::A2DTransformationInfos meshTrans;

    for (int n=0; n<MAX; n++) 
    {
        pMesh = A2DMesh::create();
        pMesh->load("../../Assets/cytovirus.x");
        
        meshTrans.mScale = A2DRenderVector(0.02f, 0.02f, 0.02f);

        float32 x = (float32)(rand() % 40 - 20);
        float32 y = (float32)(rand() % 40 - 20);
        float32 z = (float32)(rand() % 10 - 5);

        meshTrans.mPosition = A2DRenderVector(x, y, z);

        pMesh->setTransformation(meshTrans);

        //add mesh to entity manager
        gpEngine->addEntity(pMesh);
    }

    return true;
}

void GameKeyRelease(uint32 aKey)
{
    if (aKey == DIK_ESCAPE) 
    { gpEngine->shutDown(); }
}

void GameRender3D()
{
    //clear the scene using a dark blue color
    gpEngine->clearScene(D3DCOLOR_XRGB(0, 0, 80));
}

void GameEntityUpdate(A2DEntityPtr apEntity)
{
    if (apEntity->getRenderType() == RENDER_3D) 
    {
        //type-cast Entity to a Mesh
        A2DMeshPtr pMesh = static_pointer_cast<A2DMesh>(apEntity);

        //perform a simple rotation
        pMesh->rotate(0, 0.2f, 0);
    }
}

void GameEntityRender(A2DEntityPtr apEntity)
{
    //type-cast Entity to a Mesh
    A2DMeshPtr pMesh = static_pointer_cast<A2DMesh>(apEntity);
    //engine automatically renders each entity
    //but we can respond to each render event here
}

void GameEnd() 
{
    gpCamera.reset();
    gpLight.reset();
}

// unused Event
void GameEntityCollision(A2DEntityPtr apFirst, A2DEntityPtr apSecond){}
void GameUpdate() {}
void GameRender2D() {}
void GameKeyPress(uint32 aKey) {}
void GameMouseButton(uint32 aButton) {}
void GameMouseMotion(int32 aX,int32 aY) {}
void GameMouseMove(int32 aX,int32 aY) {}
void GameMouseWheel(uint32 wheel) {}
