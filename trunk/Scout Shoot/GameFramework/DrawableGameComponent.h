#pragma once
#include "GameComponent.h"

namespace kXNA
{
    class GameTime;
    class GameWin;
    class GraphicsDevice;

    class _kXNA DrawableGameComponent :
        public GameComponent 
    {
    public:
        DrawableGameComponent(GameWin* pGame);
        virtual ~DrawableGameComponent(void);

        virtual void Draw(GameTime gameTime);

        inline int GetDrawOrder() const { return m_iDrawOrder;}
        inline void SetDrawOrder(const int& iDrawOrder) { m_iDrawOrder = iDrawOrder; }
        inline GraphicsDevice* GetGraphicsDevice() const { return m_pGraphicsDevice;}
        inline void SetGraphicsDevice(GraphicsDevice* graphicsDevice) { m_pGraphicsDevice = graphicsDevice; }
        inline bool GetVisible() const { return m_bVisible;}
        inline void SetVisible(const bool& bVisible) { m_bVisible = bVisible; }

    protected:
        virtual void LoadContent();
        virtual void UnloadContent();

    private:
        int m_iDrawOrder;
        GraphicsDevice* m_pGraphicsDevice;
        bool m_bVisible;
    };
}