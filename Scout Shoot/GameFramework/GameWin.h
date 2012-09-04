#pragma once
#include "std.h"

namespace kXNA
{
    class GameComponent;
    class ContentManager;
    class GraphicsDevice;
    class GameTime;
    class Keyboard;
    class KeyboardState;

    class _kXNA GameWin
    {
    public:
        GameWin( HINSTANCE hInstance, int nCmdShow, const tchar charArrWinTitle []);
        virtual ~GameWin(void);

        void Run(void);

        inline std::vector<GameComponent*> GetComponents() const { return m_vecGameComponent; }
        inline void SetComponents(std::vector<GameComponent*> vecGameComponent) { m_vecGameComponent = vecGameComponent; }
        inline ContentManager* GetContent() const { return m_pContent; }
        inline void SetContent(ContentManager* pContentManager) { m_pContent = pContentManager; }
        inline GraphicsDevice* GetGraphicsDevice() const { return m_pGraphicsDevice; }
        inline void SetGraphicsDevice(GraphicsDevice* pGraphicsDevice) { m_pGraphicsDevice = pGraphicsDevice; }

        inline HWND GetWindow() const { return m_hWnd;}

    protected:
        virtual void Initialize(void);
        virtual void LoadContent(void);
        virtual void UnloadContent(void);
        virtual void Finalize(void);
        virtual void Draw(GameTime gameTime);
        virtual void Update(GameTime gameTime);

    private:
        std::vector<GameComponent*> m_vecGameComponent;
        ContentManager* m_pContent;
        GraphicsDevice* m_pGraphicsDevice;

        tstring m_strWinTitle;
        HINSTANCE m_hInst;
        int m_nCmdWinShow;
        HWND m_hWnd;

        LPDIRECTINPUT8 m_dxInputObject;

        DWORD m_dwTimeStart;
        DWORD m_dwTimeLastUpdate;

        HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow, const tchar strWinTitle []);
        HRESULT InitDevice();
        void Render();
    };
}