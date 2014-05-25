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
        bool getMouseButton( char8 aButton );
        char getKeyState(int32 aKey) { return mKeyState[aKey]; }
        long getPosX() { return mPosition.x; }
        long getPosY() { return mPosition.y; }
        long getDeltaX() { return mMouseState.lX; }
        long getDeltaY() { return mMouseState.lY; }
        long getDeltaWheel() { return mMouseState.lZ; }

    public:
        void Update();
    }; // class 
} // namespace

#endif // INC_ADVANCED2D_A2DINPUT_HPP