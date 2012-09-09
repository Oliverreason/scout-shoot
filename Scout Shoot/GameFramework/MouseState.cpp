#include "kXNA_Dll.h"
#include "GameFrameworkExport.h"
#include "MouseState.h"

using namespace kXNA;
MouseState::MouseState(const LPDIRECTINPUTDEVICE8& mouseDevice)
{
    ZeroMemory(&m_mouseState, sizeof(m_mouseState));

    HRESULT hr;
    while (true)
    {
        if ( SUCCEEDED( hr = mouseDevice->GetDeviceState(sizeof(m_mouseState), (LPVOID)&m_mouseState)) )
            break;

        if ( hr != DIERR_INPUTLOST || hr != DIERR_NOTACQUIRED)
            break;//failed

        if ( FAILED(mouseDevice->Acquire()) )
            break;//failed
    }
}


MouseState::~MouseState(void)
{

}

bool MouseState::IsLeftButtonPressed()
{
    return m_mouseState.rgbButtons[0] & 0x80;
}

bool MouseState::IsMiddleButtonPressed()
{
    return m_mouseState.rgbButtons[2] & 0x80;
}

bool MouseState::IsRightButtonPressed()
{
    return m_mouseState.rgbButtons[1] & 0x80;
}

bool MouseState::IsXButton1Pressed()
{
    return m_mouseState.rgbButtons[3] & 0x80;
}

bool MouseState::IsXButton2Pressed()
{
    return false;
}

int MouseState::GetX()
{
    return m_mouseState.lX;
}

int MouseState::GetY()
{
    return m_mouseState.lY;
}