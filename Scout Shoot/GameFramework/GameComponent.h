#pragma once

namespace kXNA
{
    class GameTime;
    class GameWin;

    class _kXNA GameComponent
    {
    public:
        GameComponent(GameWin* pGame);
        virtual ~GameComponent(void);

        virtual void Initialize();
        virtual void Update(GameTime gameTime);

        inline bool GetEnabled() const { return m_bEnabled;}
        inline void SetEnabled(const bool& bEnabled) { m_bEnabled = bEnabled; }
        inline GameWin* GetGame() const { return m_pGame;}
        inline void SetGame(GameWin* game) { m_pGame = game; }
        inline int GetUpdateOrder() const { return m_iUpdateOrder;}
        inline void SetUpdateOrder(const int& iUpdateOrder) { m_iUpdateOrder = iUpdateOrder; }

    protected:
        virtual void Finalize();

    private:
        bool m_bEnabled;
        GameWin* m_pGame;
        int m_iUpdateOrder;
    };
}