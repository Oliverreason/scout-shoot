#pragma once
#include "GameFrameworkHeader.h"

using namespace kXNA;

class kXNA::GameTime;

class SimpleTestGame : public GameWin
{
public:
    SimpleTestGame( HINSTANCE hInstance, int nCmdShow);
    ~SimpleTestGame(void);

protected:
    virtual void Initialize(void);
    virtual void LoadContent(void);
    virtual void UnloadContent(void);
    virtual void Draw(GameTime gameTime);
    virtual void Update(GameTime gameTime);

private:
    void LoadAndInitialEffect();
    void UnLoadEffect();

    ID3DX11Effect* m_pEffectTest;
    VertexBuffer* m_pVertexBuffer;
};