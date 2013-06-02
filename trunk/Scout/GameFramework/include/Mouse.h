#pragma once
#include "std.h"
#include "MouseState.h"

namespace kXNA
{
    class _kXNA Mouse
    {
    public:
        Mouse(void);
        ~Mouse(void);

        bool Initialize(LPDIRECTINPUT8 dxInputObject, HWND hWnd);
        static Mouse* GetInstance();
        static void Release();

        MouseState GetState();
        void SetPosition(int iX, int iY);

    protected:

    private:
        static Mouse* m_Mouse;
        LPDIRECTINPUTDEVICE8 m_MouseDevice;
    };
}

