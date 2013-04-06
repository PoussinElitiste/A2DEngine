#ifndef INC_ADVANCED2D_A2DINPUT_HPP
#define INC_ADVANCED2D_A2DINPUT_HPP

// compatibility to prevent warning
#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif

// external include
#include <dinput.h>

// local include 
#include <A2DEngine.hpp>

namespace Advanced2D
{
    class A2DInput
    {
    public:
        A2DInput( HWND aWindow );
        virtual ~A2DInput();

    private:
        HWND mWindow;
        IDirectInput8* mpDi;
        IDirectInputDevice8* mpKeyboard;

        char8 mKeyState[256];
        IDirectInputDevice8* mpMouse;
        DIMOUSESTATE mMouseState;
        POINT mPosition;

    public:
        bool GetMouseButton( char aButton );
        char GetKeyState(int aKey) { return mKeyState[aKey]; }
        long GetPosX() { return mPosition.x; }
        long GetPosY() { return mPosition.y; }
        long GetDeltaX() { return mMouseState.lX; }
        long GetDeltaY() { return mMouseState.lY; }
        long GetDeltaWheel() { return mMouseState.lZ; }

    public:
        void Update();
    }; // class 
} // namespace

#endif // INC_ADVANCED2D_A2DINPUT_HPP