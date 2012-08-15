#pragma once
#include "std.h"

namespace kXNA
{
    class GameTime
    {
    public:
        GameTime(void);
        GameTime(FLOAT fTotalTime, FLOAT fElapsedLastUpdateTime);
        ~GameTime(void);

        inline FLOAT GetTotalGameTime() const { return m_fTotalTime;}
        inline FLOAT GetElapsedGameTime() const { return m_fElapsedLastUpdateTime;}

    private:
        FLOAT m_fTotalTime;
        FLOAT m_fElapsedLastUpdateTime;
    };
}