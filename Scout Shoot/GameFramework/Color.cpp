#include "Color.h"

using namespace kXNA;
Color::Color(void)
    : m_fColorRed(0.0f), m_fColorBlue(0.0f), m_fColorGreen(0.0f), m_fColorAlpha(1.0f)
{
}

Color::Color(FLOAT fColorRed, FLOAT fColorBlue, FLOAT fColorGreen)
    : m_fColorRed(fColorRed), m_fColorBlue(fColorBlue), m_fColorGreen(fColorGreen), m_fColorAlpha(1.0f)
{
}

Color::Color(FLOAT fColorRed, FLOAT fColorBlue, FLOAT fColorGreen, FLOAT fColorAlpha)
    : m_fColorRed(fColorRed), m_fColorBlue(fColorBlue), m_fColorGreen(fColorGreen), m_fColorAlpha(fColorAlpha)
{
}

Color::~Color(void)
{
}

void Color::ToFloat4(FLOAT* ColorRGBA) const
{
    ColorRGBA[0] = m_fColorRed;
    ColorRGBA[1] = m_fColorGreen;
    ColorRGBA[2] = m_fColorBlue;
    ColorRGBA[3] = m_fColorAlpha;
}

const Color Color::White = Color( 1.0f, 1.0f, 1.0f);
const Color Color::Black = Color( 0, 0, 0);
const Color Color::Red = Color( 1.0f, 0, 0);
const Color Color::Blue = Color( 0, 1.0f, 0);
const Color Color::DarkBlue = Color( 0, 0.3f, 0.125f);
const Color Color::Green = Color( 0, 0, 1.0f);
const Color Color::Yellow = Color( 1.0f, 1.0f, 0);
const Color Color::Cyan = Color( 0, 1.0f, 1.0f);
const Color Color::Magenta = Color( 1.0f, 0, 1.0f);