#pragma once

namespace kXNA
{
    class GameTime;

    class GameComponent
    {
    public:
        GameComponent(void);
        ~GameComponent(void);

        virtual void Initialize();
        virtual void Update(GameTime gameTime);

        inline bool GetEnabled() const { return m_bEnabled;}
        inline void SetEnabled(bool bEnabled) { m_bEnabled = bEnabled; }

    private:
        bool m_bEnabled;
    };
}