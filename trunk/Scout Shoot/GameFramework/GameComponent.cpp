#include "kXNA_Dll.h"
#include "GameFrameworkExport.h"
#include "GameComponent.h"
#include "GameTime.h"
#include "GameWin.h"

using namespace kXNA;
GameComponent::GameComponent(GameWin* pGame)
{
    m_pGame = pGame;
}


GameComponent::~GameComponent(void)
{
}

void GameComponent::Initialize()
{
}

void GameComponent::Update(GameTime gameTime)
{
}

void GameComponent::Finalize()
{
}