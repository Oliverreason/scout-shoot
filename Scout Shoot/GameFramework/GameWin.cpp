#include "kXNA_Dll.h"
#include "GameFrameworkExport.h"
#include "GameWin.h"
#include "GameTime.h"
#include "ContentManager.h"
#include "GameComponent.h"
#include "DrawableGameComponent.h"
#include "GraphicsDevice.h"
#include "Keyboard.h"
#include "Mouse.h"

LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch( message )
    {
    case WM_PAINT:
        hdc = BeginPaint( hWnd, &ps );
        EndPaint( hWnd, &ps );
        break;

    case WM_DESTROY:
        PostQuitMessage( 0 );
        break;
    case WM_KEYDOWN:
        switch(wParam)
        {
        case VK_ESCAPE:
            {
                HWND hDesk;
                //RECT rc;
                //hDesk = GetDesktopWindow();
                //GetWindowRect( hDesk, &rc);
                RECT rc = { 0, 0, 1024, 768 };
                SetWindowLong( hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
                SetWindowPos( hWnd, HWND_TOPMOST, 0, 0, rc.right, rc.bottom, SWP_SHOWWINDOW);
            }
            break;
        }
    default:
        return DefWindowProc( hWnd, message, wParam, lParam );
    }

    return 0;
}

using namespace kXNA;
GameWin::GameWin(HINSTANCE hInstance, int nCmdShow, const tchar charArrWinTitle []) 
    : m_strWinTitle(tstring(charArrWinTitle))
     , m_hInst(hInstance)
     , m_nCmdWinShow(nCmdShow)
{
    m_dwTimeStart = 0;
    m_dwTimeLastUpdate = 0;
}

GameWin::~GameWin(void)
{
    delete m_pContent;
    delete m_pGraphicsDevice;
}

void GameWin::Run(void)
{
    Initialize();
    // Main message loop
    MSG msg = {0};
    while( WM_QUIT != msg.message )
    {
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
            Render();
        }
    }
    Finalize();
    return;//(int) msg.wParam;
}

void GameWin::Initialize(void)
{
    if( FAILED( InitWindow( m_hInst, m_nCmdWinShow, m_strWinTitle.c_str()) || FAILED( InitDevice())))
        return;

    if(FAILED( DirectInput8Create( m_hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_dxInputObject, 0 )))
        return;

    Keyboard::GetInstance()->Initialize(m_dxInputObject, m_hWnd);
    Mouse::GetInstance()->Initialize(m_dxInputObject, m_hWnd);

    m_pContent = new ContentManager( GetGraphicsDevice());

    if (GetComponents().size() > 0)
    {
        for (std::vector<GameComponent*>::iterator iter = GetComponents().begin(); iter != GetComponents().end(); ++iter)
        {
            (*iter)->Initialize();
        }
    }

    LoadContent();
}

void GameWin::LoadContent(void)
{
}

void GameWin::UnloadContent(void)
{
}

void GameWin::Finalize(void)
{
    if(m_dxInputObject) 
        m_dxInputObject->Release( );
    m_dxInputObject = 0;

    if (GetComponents().size() > 0)
    {
        for (std::vector<GameComponent*>::iterator iter = GetComponents().begin(); iter != GetComponents().end(); ++iter)
        {
            delete (*iter);
        }
    }

    UnloadContent();
}

void GameWin::Draw(GameTime gameTime)
{
    if (GetComponents().size() > 0)
    {
        for (std::vector<GameComponent*>::iterator iter = GetComponents().begin(); iter != GetComponents().end(); ++iter)
        {
            if ( (*iter)->GetEnabled())
            {
                DrawableGameComponent* pDGComponent = dynamic_cast<DrawableGameComponent*>(*iter);
                if (pDGComponent != NULL)
                {
                    pDGComponent->Update(gameTime);
                }
            }
        }
    }
}

void GameWin::Update(GameTime gameTime)
{
    if (GetComponents().size() > 0)
    {
        for (std::vector<GameComponent*>::iterator iter = GetComponents().begin(); iter != GetComponents().end(); ++iter)
        {
            if ( (*iter)->GetEnabled())
            {
                (*iter)->Update(gameTime);
            }
        }
    }

    Draw(gameTime);
}

HRESULT GameWin::InitWindow( HINSTANCE hInstance, int nCmdShow, const tchar strWinTitle [] )
{
    // Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof( WNDCLASSEX );
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon( hInstance, ( LPCTSTR )IDI_APPLICATION );
    wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
    wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = strWinTitle;
    wcex.hIconSm = LoadIcon( wcex.hInstance, ( LPCTSTR )IDI_APPLICATION );
    if( !RegisterClassEx( &wcex ) )
        return E_FAIL;

    // Create window
    m_hInst = hInstance;
    RECT rc = { 0, 0, 1024, 768 };
    AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
    //UINT width = GetSystemMetrics(SM_CXSCREEN);
    //UINT height = GetSystemMetrics(SM_CYSCREEN);
    m_hWnd = CreateWindow( strWinTitle, strWinTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top,
        //0, 0, width, height,
        NULL, NULL, hInstance,
        NULL );
    if( !m_hWnd )
        return E_FAIL;

    HWND hDesk;
    hDesk = GetDesktopWindow();
    GetWindowRect( hDesk, &rc);
    SetWindowLong( m_hWnd, GWL_STYLE, WS_BORDER);
    SetWindowPos( m_hWnd, HWND_TOPMOST, 0, 0, rc.right, rc.bottom, SWP_SHOWWINDOW);

    ShowWindow( m_hWnd, nCmdShow );
    UpdateWindow(m_hWnd);

    return S_OK;
}

HRESULT GameWin::InitDevice()
{
    m_pGraphicsDevice = new GraphicsDevice(m_hWnd);
    return S_OK;
}

void GameWin::Render()
{
    // Update our time
    DWORD dwTimeCur = GetTickCount();
    if( m_dwTimeStart == 0)
    {
        m_dwTimeStart = dwTimeCur;
        m_dwTimeLastUpdate = dwTimeCur;
    }
    float fTotalTime = ( dwTimeCur - m_dwTimeStart ) / 1000.0f;
    float fElapsedLastUpdateTime = ( dwTimeCur - m_dwTimeLastUpdate ) / 1000.0f;
    m_dwTimeLastUpdate = dwTimeCur;
    GameTime gameTime (fTotalTime, fElapsedLastUpdateTime);

    Update(gameTime);
}