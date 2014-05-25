// Local include
#include <A2DEngine.hpp>

namespace Advanced2D
{
   A2DInput::A2DInput( HWND aHwnd )
   {
      //save window handle
      mWindow = aHwnd;

      //create DirectInput object
      DirectInput8Create( GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&mpDi, NULL );

      //initialize keyboard
      mpDi->CreateDevice(GUID_SysKeyboard, &mpKeyboard, NULL);
      mpKeyboard->SetDataFormat( &c_dfDIKeyboard );
      mpKeyboard->SetCooperativeLevel( mWindow, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
      mpKeyboard->Acquire();

      //initialize mouse
      mpDi->CreateDevice( GUID_SysMouse, &mpMouse, NULL );
      mpMouse->SetDataFormat( &c_dfDIMouse );
      mpMouse->SetCooperativeLevel( mWindow, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
      mpMouse->Acquire();
   }

   A2DInput::~A2DInput()
   {
      mpDi->Release();
      mpKeyboard->Release();
      mpMouse->Release();
   }

   A2DInputPtr A2DInput::create(HWND aWindow)
   {
      return A2DInputPtr(new A2DInput(aWindow));
   }

   void A2DInput::Update()
   {
      //poll state of the keyboard
      mpKeyboard->Poll();
      if (!SUCCEEDED(mpKeyboard->GetDeviceState(256, (LPVOID)&mKeyState)))
      {
         //keyboard device lost, try to re-acquire
         mpKeyboard->Acquire();
      }

      //poll state of the mouse
      mpMouse->Poll();
      if (!SUCCEEDED(mpMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mMouseState)))
      {
         //mouse device lose, try to re-acquire
         mpMouse->Acquire();
      }

      //get mouse position on screen
      GetCursorPos(&mPosition);
      ScreenToClient(mWindow, &mPosition);
   }

   bool8 A2DInput::getMouseButton( char8 aButton )
   {
      return (mMouseState.rgbButtons[aButton] & 0x80) != 0;
   }
}; // namespace