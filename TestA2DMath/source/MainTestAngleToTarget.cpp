//------------------------
// MainTestAngleToTarget.cpp
//------------------------
// external include
#include <sstream>
using namespace std;

// engine Include
#include <A2DEngine.hpp>
using namespace Advanced2D;

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define BULLET_VEL 3.0
#define ASTEROID_VEL 3.0
#define OBJECT_BACKGROUND 1
#define OBJECT_SHIP 10
#define OBJECT_BULLET 20
#define OBJECT_ASTEROID 30
#define OBJECT_EXPLOSION 40

A2DFont* gpFont;
// A2DConsole* gpConsole;
A2DTexture* gpBulletImage;
A2DTexture* gpAsteroidImage;
A2DTexture* gpExplosionImage;
A2DVector3 gShipPosition;
A2DVector3 gNearestAsteroid;
A2DVector3 gTargetLead;
float32 gShipAngle = 90;
float32 gNearestDistance;
A2DTimer fireTimer;
A2DMath gMath;

bool8 GamePreload()
{
    //display engine version in a message box
    gpEngine->SetAppTitle("TARGETING DEMO");
    gpEngine->SetScreenProperties(A2DEngine::ScreenProperties(SCREEN_WIDTH, SCREEN_HEIGHT, 32, false));

    return true;
}

bool8 GameInit(HWND hwnd) 
{
    //create the background
    A2DSprite* pBackground = new A2DSprite();
    pBackground->SetObjectType(OBJECT_BACKGROUND);
    if (!pBackground->LoadSpriteImage("../Assets/craters.tga")) 
    {
        gpEngine->Message("Error loading craters.tga");
        return false;
    }
    gpEngine->AddEntity( pBackground );

    //create the console
    //gpConsole = new A2DConsole();
    //if (!gpConsole->Init()) 
    //{
    //    gpEngine->Message("Error initializing console");
    //    return false;
    //}

    // create ship sprite
    A2DSprite* pShip = new A2DSprite();
    pShip->SetObjectType(OBJECT_SHIP);
    if (!pShip->LoadSpriteImage("../Assets/spaceship80.tga"))
    {
        gpEngine->Message("Error loading spaceship80.tga");
        return false;
    }
    pShip->SetRotation( gMath.ToRadians(90) ); // orient to the right
    pShip->SetPosition( 10, SCREEN_HEIGHT/2 - pShip->Get(HEIGHT)/2 );
    pShip->SetCollidable(false);
    gpEngine->AddEntity(pShip);

    //load bullet image
    gpBulletImage = new A2DTexture();
    if (!gpBulletImage->Load("../Assets/plasma.tga")) 
    {
        gpEngine->Message("Error loading plasma.tga");
        return false;
    }

    //load asteroid image
    gpAsteroidImage = new A2DTexture();
    if (!gpAsteroidImage->Load("../Assets/asteroid.tga")) 
    {
        gpEngine->Message("Error loading asteroid.tga");
        return false;
    }

    //load the explosion image
    gpExplosionImage = new A2DTexture();
    if (!gpExplosionImage->Load("../Assets/explosion_30_128.tga")) 
    {
        gpEngine->Message("Error loading explosion");
        return false;
    }

    // load the Verdana10 font
    gpFont = new A2DFont();
    if (!gpFont->LoadSpriteImage("../Assets/verdana10.tga")) 
    {
        gpEngine->Message("Error loading verdana10.tga");
        return false;
    }
    gpFont->SetColumns(16);
    gpFont->SetCharSize(20, 16);

    if (!gpFont->LoadWidthData("../Assets/verdana10.dat")) 
    {
        gpEngine->Message("Error loading verdana10.dat");
        return false;
    }

    //load sound effects
    if (!gpEngine->Audio()->Load("../Assets/fire.wav","fire")) 
    {
        gpEngine->Message("Error loading fire.wav");
        return false;
    }

    if (!gpEngine->Audio()->Load("../Assets/boom.wav","boom")) 
    {
        gpEngine->Message("Error loading boom.wav");
        return false;
    }

    // maximize processor
    gpEngine->SetMaximizeProcessor( !gpEngine->GetMaximizeProcessor() );

    return true;
}

//void UpdateConsole()
//{
//    ostringstream ostr;
//    int32 y = 0;
//    gpConsole->Print(gpEngine->GetVersionText(), y++);
//    ostr.str("");
//    ostr << "REFRESH : " << (float32)(1000.0f/gpEngine->GetFrameRateCore()) << " ms (" << gpEngine->GetFrameRateCore() << " fps)";
//    gpConsole->Print(ostr.str(), y++);
//    ostr.str("");
//    ostr << "Entities: " << gpEngine->GetEntityCount();
//    gpConsole->Print(ostr.str(), y++);
//    ostr.str("");
//    ostr << "Nearest asteroid: " << gNearestAsteroid(X) << "," << gNearestAsteroid(Y);
//    gpConsole->Print(ostr.str(), y++);
//    ostr.str("");
//    ostr << "Nearest distance: " << gNearestDistance;
//    gpConsole->Print(ostr.str(), y++);
//    ostr.str("");
//    ostr << "Leading target: " << gTargetLead(X) << "," << gTargetLead(Y);
//    gpConsole->Print(ostr.str(), y++);
//    ostr.str("");
//    ostr << "Angle to target: " << gShipAngle;
//    gpConsole->Print(ostr.str(), y++);
//}

void addAsteroid()
{
    //add an asteroid
    A2DSprite* pAsteroid = new A2DSprite();
    pAsteroid->SetObjectType(OBJECT_ASTEROID);
    pAsteroid->SetVelocity(-ASTEROID_VEL, 0);
    pAsteroid->SetPosition(SCREEN_WIDTH, 50 + rand()%(SCREEN_HEIGHT-150));
    pAsteroid->SetImage(gpAsteroidImage);
    pAsteroid->SetTotalFrames(64);
    pAsteroid->SetColumns(8);
    pAsteroid->SetSize(60,60);
    pAsteroid->SetFrameTimer( rand() % 100 );
    pAsteroid->SetCurrentFrame( rand() % 64 );
    pAsteroid->SetCollidable(true);
    if (rand()%2 == 0) 
    { pAsteroid->SetAnimationDirection(-1); }
    gpEngine->AddEntity( pAsteroid );
}

void FireBullet()
{
    //get the ship from the entity manager
    A2DSprite* pShip = static_cast<A2DSprite*>(gpEngine->FindEntity(OBJECT_SHIP));
    if (!pShip)
    {
        gpEngine->Message("Error locating ship in entity manager!","ERROR");
        gpEngine->Close();
    }

    //create bullet sprite
    A2DSprite* pBullet = new A2DSprite();
    pBullet->SetObjectType(OBJECT_BULLET);
    pBullet->SetImage(gpBulletImage);
    pBullet->SetMoveTimer(1);
    pBullet->SetLifetime(5000);

    //set bullet equal to ship’s rotation angle
    float32 angle = (float32)(gMath.ToRadians(gShipAngle));
    pBullet->SetRotation( angle );

    //set bullet’s starting position
    float32 x = (float32)(pShip->Get(X) + pShip->Get(WIDTH)/2.);
    float32 y = (float32)(pShip->Get(Y) + pShip->Get(HEIGHT)/2.-8.);
    pBullet->SetPosition(x, y);

    //set bullet’s velocity
    float32 vx = (float32)(gMath.LinearVelocityX(gShipAngle) * BULLET_VEL);
    float32 vy = (float32)(gMath.LinearVelocityY(gShipAngle) * BULLET_VEL);
    pBullet->SetVelocity(vx, vy);

    //fire bullet
    gpEngine->AddEntity(pBullet);
    gpEngine->Audio()->Play("fire");
}

void TargetNearestAsteroid(A2DSprite* apAsteroid)
{
    //get asteroid’s position
    A2DVector3 target = apAsteroid->GetPosition();

    //calculate distance to target
    float32 dist = (float32)(gShipPosition.Distance2D(target));
    if (dist < gNearestDistance) 
    {
        gNearestAsteroid = target;
        gNearestDistance = dist;

        //lead the target for better accuracy
        // TODO: not supposed to modify directly value, modify throw setter
        gTargetLead(X) = apAsteroid->GetVelocity()(X) * 0.01f;
        gTargetLead(Y) = apAsteroid->GetVelocity()(Y) * 0.01f;
        gNearestAsteroid(X) += gTargetLead(X);
        gNearestAsteroid(Y) += gTargetLead(Y);
        
        //calculate angle to target
        gShipAngle = (float32)(gMath.AngleToTarget(gShipPosition, gNearestAsteroid));
        gShipAngle = 90.f + (float32)(gMath.ToDegrees( gShipAngle ));
    }
    
    //is there a target to shoot at?
    if (gNearestDistance < 1200) 
    {
        if (fireTimer.StopWatch(100)) 
        {
            FireBullet();
        }
    }
}

void GameUpdate()
{
    // UpdateConsole();
}

void GameRender3D()
{
    //clear the scene using a dark blue color
    gpEngine->ClearScene(D3DCOLOR_XRGB(0, 0, 80));
}

void GameRender2D() 
{
    gpFont->Print(1, SCREEN_HEIGHT-20, "Press ~ or F12 to toggle the Console");
    gpFont->Print(1, SCREEN_HEIGHT-40, "Press SPACE to launch an asteroid!!!");

    // draw console
    // if (gpConsole->IsShowing()) gpConsole->draw();

    gNearestDistance = 999999;
}

void GameEnd() 
{
    //delete gpConsole;
    delete gpFont;
    delete gpBulletImage;
    delete gpAsteroidImage;
    delete gpExplosionImage;
}

void GameEntityUpdate(A2DEntity* apEntity)
{
    A2DSprite* pShip = nullptr, *pBullet = nullptr, *pAsteroid = nullptr;
    A2DVector3 position;

    switch(apEntity->GetObjectType())
    {
    case OBJECT_SHIP:
        {
            pShip = static_cast<A2DSprite*>(apEntity);
            gShipPosition = pShip->GetPosition();
            pShip->SetRotation( gMath.ToRadians(gShipAngle) );
        }
        break;
    case OBJECT_BULLET:
        {
            pBullet = static_cast<A2DSprite*>(apEntity);
            if ( pBullet->IsAlive() && pBullet->Get(X) > SCREEN_WIDTH )
            { pBullet->SetAlive(false); } 
        }
        break;
    case OBJECT_ASTEROID:
        {
            pAsteroid = static_cast<A2DSprite*>(apEntity);
            if (pAsteroid->Get(X) < -64)
            { pAsteroid->Set(X, SCREEN_WIDTH); }
            TargetNearestAsteroid(pAsteroid);
        }
        break;  
    }
}

void GameEntityCollision(A2DEntity* apFirst, A2DEntity* apSecond) 
{
    if (apFirst->GetObjectType() == OBJECT_ASTEROID)
    {
        A2DSprite* pAsteroid = static_cast<A2DSprite*>(apFirst);
        if (apSecond->GetObjectType() == OBJECT_BULLET)
        {
            //create an explosion
            A2DSprite* pExplosion = new A2DSprite();
            pExplosion->SetObjectType(OBJECT_EXPLOSION);
            pExplosion->SetImage(gpExplosionImage);
            pExplosion->SetColumns(6);
            pExplosion->SetCollidable(false);
            pExplosion->SetSize(128, 128);
            float32 x = (float32)(pAsteroid->GetPosition()(X));
            float32 y = (float32)(pAsteroid->GetPosition()(Y));
            pExplosion->SetPosition(x-32, y-32);
            pExplosion->SetTotalFrames(30);
            pExplosion->SetFrameTimer(40);
            pExplosion->SetLifetime(1000);
            gpEngine->AddEntity( pExplosion );

            //remove the asteroid
            apSecond->SetAlive(false);
            
            //remove the bullet
            apFirst->SetAlive(false);

            //play explosion sound
            gpEngine->Audio()->Play("boom");
        }
    }
}

void GameKeyPress(int32 aKey) 
{
    switch(aKey)
    {
        case DIK_SPACE:
        { addAsteroid(); }
        break;
    }
}

void GameKeyRelease(int32 aKey)
{
    switch (aKey) 
    {
    case DIK_ESCAPE:
        { gpEngine->ShutDown(); }
        break;
    case DIK_F12:
    case DIK_GRAVE:
        //{ gpConsole->SetShowing( !gpConsole->IsShowing() ); }
        break;
    }
}

// unused Event
void GameEntityRender(A2DEntity* apEntity) {}
void GameMouseButton(int32 aButton) {}
void GameMouseMotion(int32 aX,int32 aY) {}
void GameMouseMove(int32 aX,int32 aY) {}
void GameMouseWheel(int32 wheel) {}
