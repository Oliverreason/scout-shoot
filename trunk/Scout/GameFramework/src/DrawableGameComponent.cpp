#include "kXNA_Dll.h"
#include "GameFrameworkExport.h"
#include "DrawableGameComponent.h"
#include "Win/GameWin.h"
#include "GameTime.h"

using namespace kXNA;
DrawableGameComponent::DrawableGameComponent(GameWin* pGame)
    : GameComponent(pGame)
{
}


DrawableGameComponent::~DrawableGameComponent(void)
{
}

void DrawableGameComponent::Draw(GameTime gameTime)
{
}

void DrawableGameComponent::LoadContent()
{
}

void DrawableGameComponent::UnloadContent()
{
}