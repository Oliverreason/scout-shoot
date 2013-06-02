#include "SimpleTestGame.h"

#include "Color.h"
#include "GameTime.h"
#include "ContentManager.h"
#include "Win/GameWin.h"
#include "Win/GraphicsDevice.h"
#include "VertexDeclaration.h"

struct SimpleTestGameVertexFormat
{
    XMFLOAT3 Pos;
};

using namespace kXNA;

SimpleTestGame::SimpleTestGame( HINSTANCE hInstance, int nCmdShow)
    : GameWin( hInstance, nCmdShow, TEXT("Simple test game"))
{
}


SimpleTestGame::~SimpleTestGame(void)
{
}

void SimpleTestGame::Initialize(void)
{
    GameWin::Initialize();

    //TODO Write below
    GetGraphicsDevice()->Clear(Color::Cyan);
}

void SimpleTestGame::LoadContent(void)
{
    GameWin::LoadContent();

    //TODO Write below
    LoadAndInitialEffect();
}

void SimpleTestGame::UnloadContent(void)
{
    GameWin::UnloadContent();

    //TODO Write below
    UnLoadEffect();
}

void SimpleTestGame::Draw(GameTime gameTime)
{
    GameWin::Draw(gameTime);

    //TODO Write below
    if( GetGraphicsDevice() == 0 )
        return;

    GetGraphicsDevice()->SetVertexBuffer(m_pVertexBuffer);

    ID3DX11EffectTechnique* pEffectTechniqueTest = m_pEffectTest->GetTechniqueByName( "SimpleTestGame");
    D3DX11_TECHNIQUE_DESC techDesc;
    pEffectTechniqueTest->GetDesc( &techDesc );
    for( unsigned int p = 0; p < techDesc.Passes; p++ )
    {
        ID3DX11EffectPass* pass = pEffectTechniqueTest->GetPassByIndex( p );
        if( pass != 0 )
        {
            pass->Apply( 0, GetGraphicsDevice()->GetDeviceContext() );
            GetGraphicsDevice()->GetDeviceContext()->Draw( 3, 0 );
        }
    }

    GetGraphicsDevice()->Present();
}

void SimpleTestGame::Update(GameTime gameTime)
{
    GameWin::Update(gameTime);

    //TODO Write below
}

void SimpleTestGame::LoadAndInitialEffect()
{
    m_pEffectTest = GetContent()->LoadEffect(_T("SimpleTestGameShader.fx"));

    //Create vertex declearation
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    UINT numElements = ARRAYSIZE( layout );
    VertexDeclaration* pVertexDeclaration = new VertexDeclaration(layout, numElements, m_pEffectTest, "SimpleTestGame", GetGraphicsDevice()->GetDevice());

    // Create vertex buffer
    SimpleTestGameVertexFormat vertices[] =
    {
        XMFLOAT3( 0.0f, 0.5f, 0.5f ),
        XMFLOAT3( 0.5f, -0.5f, 0.5f ),
        XMFLOAT3( -0.5f, -0.5f, 0.5f ),
    };
    m_pVertexBuffer = new VertexBuffer(GetGraphicsDevice(), 3, pVertexDeclaration, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_pVertexBuffer->SetData(vertices);
}

void SimpleTestGame::UnLoadEffect()
{
    if (m_pEffectTest)
        m_pEffectTest->Release();

    m_pEffectTest = NULL;

    delete m_pVertexBuffer;
}