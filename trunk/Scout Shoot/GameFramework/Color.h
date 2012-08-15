#pragma once
#include "std.h"

namespace kXNA
{
    struct Color
    {
    public:
        Color(void);
        Color(FLOAT fColorRed, FLOAT fColorBlue, FLOAT fColorGreen);
        Color(FLOAT fColorRed, FLOAT fColorBlue, FLOAT fColorGreen, FLOAT fColorAlpha);
        ~Color(void);

        inline FLOAT GetA() const { return m_fColorAlpha; }
        inline void SetA(FLOAT fColorAlpha) { m_fColorAlpha = fColorAlpha; }
        inline FLOAT GetB() const { return m_fColorBlue; }
        inline void SetB(FLOAT fColorBlue) { m_fColorBlue = fColorBlue; }
        inline FLOAT GetG() const { return m_fColorGreen; }
        inline void SetG(FLOAT fColorGreen) { m_fColorGreen = fColorGreen; }
        inline FLOAT GetR() const { return m_fColorRed; }
        inline void SetR(FLOAT fColorRed) { m_fColorRed = fColorRed; }

        void ToFloat4(FLOAT* ColorRGBA) const;

        static const Color White;
        static const Color Black;
        static const Color Red;
        static const Color Green;
        static const Color Blue;
        static const Color DarkBlue;
        static const Color Yellow;
        static const Color Cyan;
        static const Color Magenta;

    private:
        FLOAT m_fColorRed;
        FLOAT m_fColorGreen;
        FLOAT m_fColorBlue;
        FLOAT m_fColorAlpha;
    };
}