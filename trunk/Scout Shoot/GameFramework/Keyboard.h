#pragma once
#include "std.h"
#include "KeyboardState.h"

namespace kXNA
{
    class _kXNA Keyboard
    {
    public:
        Keyboard(void);
        ~Keyboard(void);

        bool Initialize(LPDIRECTINPUT8 dxInputObject, HWND hWnd);
        static Keyboard* GetInstance();
        static void Release();

        KeyboardState GetState();

    protected:

    private:
        static Keyboard* m_Keyboard;
        LPDIRECTINPUTDEVICE8 m_KeyboardDevice;
    };
}

