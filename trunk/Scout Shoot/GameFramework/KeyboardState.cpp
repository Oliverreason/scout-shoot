#include "kXNA_Dll.h"
#include "GameFrameworkExport.h"
#include "KeyboardState.h"

using namespace kXNA;
KeyboardState::KeyboardState(const LPDIRECTINPUTDEVICE8& keyboardDevice)
{
    ZeroMemory(m_KeyboardKeys, sizeof(m_KeyboardKeys));

    keyboardDevice->GetDeviceState(sizeof(m_KeyboardKeys), (LPVOID)&m_KeyboardKeys);
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