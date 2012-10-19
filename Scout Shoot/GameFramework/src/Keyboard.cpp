#include "kXNA_Dll.h"
#include "GameFrameworkExport.h"
#include "Keyboard.h"
#include "KeyboardState.h"

using namespace kXNA;
Keyboard* Keyboard::m_Keyboard;

Keyboard::Keyboard(void)
{
}


Keyboard::~Keyboard(void)
{
    if( m_KeyboardDevice )
    { 
        m_KeyboardDevice->Unacquire();
        m_KeyboardDevice->Release();
    }
    m_KeyboardDevice = NULL;
}

Keyboard* Keyboard::GetInstance()
{
    if (m_Keyboard == 0)
    {
        m_Keyboard = new Keyboard();
    }
    return m_Keyboard;
}

void Keyboard::Release()
{
    if (m_Keyboard)
    {
        delete m_Keyboard;
    }
    m_Keyboard = NULL;
}

bool Keyboard::Initialize(LPDIRECTINPUT8 dxInputObject, HWND hWnd)
{
    HRESULT result = dxInputObject->CreateDevice( GUID_SysKeyboard, &m_KeyboardDevice, 0);
    if(FAILED( result ))
        return false;

    result = m_KeyboardDevice->SetDataFormat( &c_dfDIKeyboard);
    if(FAILED( result ))
        return false;

    result = m_KeyboardDevice->SetCooperativeLevel( hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    if(FAILED( result ))
        return false;

    result = m_KeyboardDevice->Acquire();
    if(FAILED( result ))
        return false;

    return true;
}

KeyboardState Keyboard::GetState()
{
    KeyboardState keyboardState(m_KeyboardDevice);

    return keyboardState;
}