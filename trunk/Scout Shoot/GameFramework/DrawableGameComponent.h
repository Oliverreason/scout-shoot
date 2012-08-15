#pragma once
#include "GameComponent.h"

namespace kXNA
{
    class GameTime;

    class DrawableGameComponent :
        public GameComponent 
    {
    public:
        DrawableGameComponent(void);
        ~DrawableGameComponent(void);

        virtual void Draw(GameTime gameTime);
    };
}