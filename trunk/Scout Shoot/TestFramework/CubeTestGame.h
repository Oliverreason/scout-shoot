#pragma once
#include "stdApp.h"

#include "Win/GameWin.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"

using namespace kXNA;

class kXNA::GameTime;

class CubeTestGame : public GameWin
{
public:
    CubeTestGame( HINSTANCE hInstance, int nCmdShow);
    virtual ~CubeTestGame(void);

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
    IndexBuffer* m_pIndexBuffer;

    XMMATRIX m_World;
    XMMATRIX m_View;
    XMMATRIX m_Projection;
};

