#pragma once
#include "std.h"

namespace kXNA
{
    class _kXNA MouseState
    {
    public:
        MouseState(const LPDIRECTINPUTDEVICE8& mouseDevice);
        ~MouseState(void);

        bool IsLeftButtonPressed();
        bool IsMiddleButtonPressed();
        bool IsRightButtonPressed();
        bool IsXButton1Pressed();
        bool IsXButton2Pressed();

        int GetScrollWheelValue();
        int GetX();
        int GetY();

    private:
        DIMOUSESTATE m_mouseState;
    };
}

