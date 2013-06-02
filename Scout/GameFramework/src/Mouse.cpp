#include "kXNA_Dll.h"
#include "GameFrameworkExport.h"
#include "Mouse.h"
#include "MouseState.h"

using namespace kXNA;
Mouse* Mouse::m_Mouse;

Mouse::Mouse(void)
{
}


Mouse::~Mouse(void)
{
    if( m_MouseDevice )
    { 
        m_MouseDevice->Unacquire();
        m_MouseDevice->Release();
    }
    m_MouseDevice = NULL;
}

Mouse* Mouse::GetInstance()
{
    if (m_Mouse == 0)
    {
        m_Mouse = new Mouse();
    }
    return m_Mouse;
}

void Mouse::Release()
{
    if (m_Mouse)
    {
        delete m_Mouse;
    }
    m_Mouse = NULL;
}

bool Mouse::Initialize(LPDIRECTINPUT8 dxInputObject, HWND hWnd)
{
    HRESULT result = dxInputObject->CreateDevice( GUID_SysMouse, &m_MouseDevice, 0);
    if(FAILED( result ))
        return false;

    result = m_MouseDevice->SetDataFormat( &c_dfDIMouse);
    if(FAILED( result ))
        return false;

    result = m_MouseDevice->SetCooperativeLevel( hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    if(FAILED( result ))
        return false;

    result = m_MouseDevice->Acquire();
    if(FAILED( result ))
        return false;

    return true;
}

MouseState Mouse::GetState()
{
    MouseState mouseState(m_MouseDevice);

    return mouseState;
}

void Mouse::SetPosition(int iX, int iY)
{

}