#include "kXNA_Dll.h"
#include "GameFrameworkExport.h"
#include "KeyboardState.h"

using namespace kXNA;
KeyboardState::KeyboardState(const LPDIRECTINPUTDEVICE8& keyboardDevice)
{
    ZeroMemory(m_KeyboardKeys, sizeof(m_KeyboardKeys));
    HRESULT hr;
    while (true)
    {
        if ( SUCCEEDED( hr = keyboardDevice->GetDeviceState(sizeof(m_KeyboardKeys), (LPVOID)&m_KeyboardKeys)) )
            break;

        if ( hr != DIERR_INPUTLOST || hr != DIERR_NOTACQUIRED)
            break;//failed

        if ( FAILED(keyboardDevice->Acquire()) )
            break;//failed
    }
}


KeyboardState::~KeyboardState(void)
{

}

bool KeyboardState::IsKeyDown(Keys key)
{
    return m_KeyboardKeys[key] & 0x80;
}

bool KeyboardState::IsKeyUp(Keys key)
{
    return !(m_KeyboardKeys[key] & 0x80);
}

bool KeyboardState::GetItem(Keys key)
{
    return (m_KeyboardKeys[key] & 0x80);
}