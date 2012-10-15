// external include
#include <iostream>

// Engine include
#include <A2DEngine.hpp>

bool GamePreload()
{
    //display engine version in a message box
    gpEngine->Message(gpEngine->GetVersionText(), "TEST A2D ENGINE !!");

    //return fail to terminate the engine
    return false;
}

bool GameInit(HWND hwnd) { return 0;}
void GameUpdate() {}
void GameEnd() {}
void GameRender3D() {}