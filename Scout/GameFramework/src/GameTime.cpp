#include "kXNA_Dll.h"
#include "GameFrameworkExport.h"
#include "GameTime.h"

using namespace kXNA;
GameTime::GameTime(void)
{
}

GameTime::GameTime(FLOAT fTotalTime, FLOAT fElapsedLastUpdateTime)
{
    m_fTotalTime = fTotalTime;
    m_fElapsedLastUpdateTime = fElapsedLastUpdateTime;
}

GameTime::~GameTime(void)
{
}
