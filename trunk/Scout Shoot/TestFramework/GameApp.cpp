#include "stdApp.h"

#include "SimpleTestGame.h"
#include "CubeTestGame.h"
#include "LightingTestGame.h"
#include "TextureTestGame.h"

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
    UNREFERENCED_PARAMETER( hPrevInstance );
    UNREFERENCED_PARAMETER( lpCmdLine );

    //GameWin* pGame = new SimpleTestGame(hInstance, nCmdShow);
    //pGame->Run();
    //delete pGame;

    ////GameWin* pGame = new CubeTestGame(hInstance, nCmdShow);
    ////pGame->Run();
    ////delete pGame;

    //GameWin* pGame = new LightingTestGame(hInstance, nCmdShow);
    //pGame->Run();
    //delete pGame;

    GameWin* pGame = new TextureTestGame(hInstance, nCmdShow);
    pGame->Run();
    delete pGame;

    return 0;
}