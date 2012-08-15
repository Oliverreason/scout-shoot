#pragma once
#include "GameFrameworkHeader.h"

using namespace kXNA;

class kXNA::GameTime;

class TextureTestGame : public GameWin
{
public:
    TextureTestGame( HINSTANCE hInstance, int nCmdShow);
    virtual ~TextureTestGame(void);

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

    ID3DX11Effect* m_pEffectTest;
    ID3D11Buffer* m_pCBNeverChanges;
    ID3D11Buffer* m_pCBChangeOnResize;
    ID3D11Buffer* m_pCBChangesEveryFrame;
    ID3D11SamplerState* m_pSamplerLinear;
    XMFLOAT4 m_f4MeshColor;
};

