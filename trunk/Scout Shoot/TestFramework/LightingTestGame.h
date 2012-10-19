#pragma once
#include "stdApp.h"

#include "Win/GameWin.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"

using namespace kXNA;

class kXNA::GameTime;

class LightingTestGame : public GameWin
{
public:
    LightingTestGame( HINSTANCE hInstance, int nCmdShow);
    virtual ~LightingTestGame(void);

protected:
    virtual void Initialize(void);
    virtual void LoadContent(void);
    virtual void UnloadContent(void);
    virtual void Draw(GameTime gameTime);
    virtual void Update(GameTime gameTime);

private:
    void LoadAndInitialEffect();
    void UnLoadEffect();

    VertexBuffer* m_pVertexBuffer;
    IndexBuffer* m_pIndexBuffer;

    XMMATRIX m_World;
    XMMATRIX m_View;
    XMMATRIX m_Projection;

    ID3DX11Effect* m_pEffectTest;
    ID3D11Buffer* m_pConstantBuffer;
};

