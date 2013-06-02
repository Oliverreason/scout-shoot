#include "CameraInputGame.h"

#include "Color.h"
#include "GameTime.h"
#include "ContentManager.h"
#include "Win/GameWin.h"
#include "Win/GraphicsDevice.h"
#include "VertexDeclaration.h"


struct CubeTestGameVertexFormat
{
    XMFLOAT3 Pos;
    XMFLOAT4 Color;
};

using namespace kXNA;
CameraInputGame::CameraInputGame( HINSTANCE hInstance, int nCmdShow)
    : GameWin( hInstance, nCmdShow, TEXT("Cube test game"))
{
}


CameraInputGame::~CameraInputGame(void)
{
}

void CameraInputGame::Initialize( void )
{
    GameWin::Initialize();

    //TODO Write below
    GetGraphicsDevice()->Clear(Color::DarkBlue);
}

void CameraInputGame::LoadContent( void )
{
    GameWin::LoadContent();

    //TODO Write below
    LoadAndInitialEffect();
}

void CameraInputGame::UnloadContent( void )
{
    GameWin::UnloadContent();

    //TODO Write below
    UnLoadEffect();
}

void CameraInputGame::Draw( GameTime gameTime )
{
    GameWin::Draw(gameTime);

    //TODO Write below
    if( GetGraphicsDevice() == 0 )
        return;

    GetGraphicsDevice()->Clear(Color::DarkBlue);

    FLOAT fTotalTime = gameTime.GetTotalGameTime();

    GetGraphicsDevice()->SetVertexBuffer(m_pVertexBuffer);
    GetGraphicsDevice()->SetIndices(m_pIndexBuffer);

    //ID3DX11EffectMatrixVariable* viewMatrix;
    //viewMatrix = m_pEffectTest->GetVariableByName( "View" )->AsMatrix( );
    //viewMatrix->SetMatrix( ( float* )&m_View );
    //ID3DX11EffectMatrixVariable* projMatrix;
    //projMatrix = m_pEffectTest->GetVariableByName( "Projection" )->AsMatrix( );
    //projMatrix->SetMatrix( ( float* )&m_Projection );

    m_World = XMMatrixRotationY( fTotalTime );
    ID3DX11EffectMatrixVariable* worldMatrix;
    worldMatrix = m_pEffectTest->GetVariableByName( "World" )->AsMatrix( );
    worldMatrix->SetMatrix( ( float* )&m_World );
    ID3DX11EffectTechnique* pEffectTechniqueTest = m_pEffectTest->GetTechniqueByName( "CubeTestGame");
    D3DX11_TECHNIQUE_DESC techDesc;
    pEffectTechniqueTest->GetDesc( &techDesc );
    for( unsigned int p = 0; p < techDesc.Passes; p++ )
    {
        ID3DX11EffectPass* pass = pEffectTechniqueTest->GetPassByIndex( p );
        if( pass != 0 )
        {
            pass->Apply( 0, GetGraphicsDevice()->GetDeviceContext() );
            GetGraphicsDevice()->GetDeviceContext()->DrawIndexed(36, 0, 0);
        }
    }

    XMMATRIX mSpin = XMMatrixRotationZ( -fTotalTime );
    XMMATRIX mOrbit = XMMatrixRotationY( -fTotalTime * 2.0f );
    XMMATRIX mTranslate = XMMatrixTranslation( -4.0f, 0.0f, 0.0f );
    XMMATRIX mScale = XMMatrixScaling( 0.3f, 0.3f, 0.3f );
    XMMATRIX matOrbitWorld = mScale * mSpin * mTranslate * mOrbit;
    worldMatrix = m_pEffectTest->GetVariableByName( "World" )->AsMatrix( );
    worldMatrix->SetMatrix( ( float* )&matOrbitWorld );
    pEffectTechniqueTest = m_pEffectTest->GetTechniqueByName( "CubeTestGame");
    pEffectTechniqueTest->GetDesc( &techDesc );
    for( unsigned int p = 0; p < techDesc.Passes; p++ )
    {
        ID3DX11EffectPass* pass = pEffectTechniqueTest->GetPassByIndex( p );
        if( pass != 0 )
        {
            pass->Apply( 0, GetGraphicsDevice()->GetDeviceContext() );
            GetGraphicsDevice()->GetDeviceContext()->DrawIndexed(36, 0, 0);
        }
    }

    GetGraphicsDevice()->Present();
}

void CameraInputGame::Update( GameTime gameTime )
{
    GameWin::Update(gameTime);

    //TODO Write below
}

void CameraInputGame::LoadAndInitialEffect()
{
    m_pEffectTest = GetContent()->LoadEffect(_T("CubeTestGameShader.fx"));

    //Create vertex declearation
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    UINT numElements = ARRAYSIZE( layout );
    VertexDeclaration* pVertexDeclaration = new VertexDeclaration(layout, numElements, m_pEffectTest, "CubeTestGame", GetGraphicsDevice()->GetDevice());

    // Create vertex buffer
    CubeTestGameVertexFormat vertices[] =
    {
        { XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT4( 0.0f, 1.0f, 0.0f, 1.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT4( 0.0f, 1.0f, 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT4( 1.0f, 0.0f, 0.0f, 1.0f ) },
        { XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT4( 1.0f, 0.0f, 1.0f, 1.0f ) },
        { XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT4( 1.0f, 1.0f, 0.0f, 1.0f ) },
        { XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT4( 1.0f, 1.0f, 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT4( 0.0f, 0.0f, 0.0f, 1.0f ) },
    };
    m_pVertexBuffer = new VertexBuffer(GetGraphicsDevice(), 8, pVertexDeclaration, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_pVertexBuffer->SetData(vertices);

    // Create index buffer
    WORD indices[] =
    {
        3,1,0,        2,1,3,
        0,5,4,        1,5,0,
        3,4,7,        0,4,3,
        1,6,5,        2,6,1,
        2,7,6,        3,7,2,
        6,4,5,        7,4,6,
    };
    m_pIndexBuffer = new IndexBuffer(GetGraphicsDevice(), 36, DXGI_FORMAT_R16_UINT);
    m_pIndexBuffer->SetData(indices);

    // Initialize the world matrix
    m_World = XMMatrixIdentity();
    // Initialize the view matrix
    XMVECTOR Eye = XMVectorSet( 0.0f, 1.0f, -5.0f, 0.0f );
    XMVECTOR At = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
    XMVECTOR Up = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
    //m_View = XMMatrixLookAtLH( Eye, At, Up );
    // Initialize the projection matrix
    RECT rc;
    GetClientRect( GetWindow(), &rc );
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;
    //m_Projection = XMMatrixPerspectiveFovLH( XM_PIDIV2, width / (FLOAT)height, 0.01f, 100.0f );
}

void CameraInputGame::UnLoadEffect()
{
    if (m_pEffectTest)
        m_pEffectTest->Release();

    m_pEffectTest = NULL;

    delete m_pVertexBuffer;
    delete m_pIndexBuffer;
}
