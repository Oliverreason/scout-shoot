#include "LightingTestGame.h"

#include "Color.h"
#include "GameTime.h"
#include "ContentManager.h"
#include "Win/GameWin.h"
#include "Win/GraphicsDevice.h"
#include "VertexDeclaration.h"

struct LightingTestGameVertexFormat
{
    XMFLOAT3 Pos;
    XMFLOAT3 Normal;
};

struct LightingTestGameConstantBuffer
{
    XMMATRIX mWorld;
    XMMATRIX mView;
    XMMATRIX mProjection;
    XMFLOAT4 vLightDir[2];
    XMFLOAT4 vLightColor[2];
};

using namespace kXNA;
LightingTestGame::LightingTestGame( HINSTANCE hInstance, int nCmdShow)
    : GameWin( hInstance, nCmdShow, TEXT("Lighting cube test game"))
{
}


LightingTestGame::~LightingTestGame(void)
{
}

void LightingTestGame::Initialize( void )
{
    GameWin::Initialize();

    //TODO Write below
    GetGraphicsDevice()->Clear(Color::DarkBlue);
}

void LightingTestGame::LoadContent( void )
{
    GameWin::LoadContent();

    //TODO Write below
    LoadAndInitialEffect();
}

void LightingTestGame::UnloadContent( void )
{
    GameWin::UnloadContent();

    //TODO Write below
    UnLoadEffect();
}

void LightingTestGame::Draw( GameTime gameTime )
{
    GameWin::Draw(gameTime);

    //TODO Write below
    if( GetGraphicsDevice() == 0 )
        return;

    GetGraphicsDevice()->Clear(Color::DarkBlue);

    FLOAT fTotalTime = gameTime.GetTotalGameTime();

    GetGraphicsDevice()->SetVertexBuffer(m_pVertexBuffer);
    GetGraphicsDevice()->SetIndices(m_pIndexBuffer);

    // Setup our lighting parameters
    XMFLOAT4 vLightDirs[2] =
    {
        XMFLOAT4( -0.577f, 0.577f, -0.577f, 1.0f ),
        XMFLOAT4( 0.0f, 0.0f, -1.0f, 1.0f ),
    };
    XMFLOAT4 vLightColors[2] =
    {
        XMFLOAT4( 0.5f, 0.5f, 0.5f, 1.0f ),
        XMFLOAT4( 0.5f, 0.0f, 0.0f, 1.0f )
    };

    // Rotate the second light around the origin
    XMMATRIX mRotate = XMMatrixRotationY( -2.0f * fTotalTime );
    XMVECTOR vLightDir = XMLoadFloat4( &vLightDirs[1] );
    vLightDir = XMVector3Transform( vLightDir, mRotate );
    XMStoreFloat4( &vLightDirs[1], vLightDir );

    m_World = XMMatrixRotationY( fTotalTime );
    LightingTestGameConstantBuffer cb1;
    cb1.mWorld = XMMatrixTranspose( m_World );
    cb1.mView = XMMatrixTranspose( m_View );
    cb1.mProjection = XMMatrixTranspose( m_Projection );
    cb1.vLightDir[0] = vLightDirs[0];
    cb1.vLightDir[1] = vLightDirs[1];
    cb1.vLightColor[0] = vLightColors[0];
    cb1.vLightColor[1] = vLightColors[1];
    GetGraphicsDevice()->GetDeviceContext()->UpdateSubresource(m_pConstantBuffer, 0, NULL, &cb1, 0, 0);
    ID3DX11EffectConstantBuffer* pEffectCBuffer = m_pEffectTest->GetConstantBufferByName( "LightingCBuffer" );
    pEffectCBuffer->SetConstantBuffer(m_pConstantBuffer);

    ID3DX11EffectTechnique* pEffectTechniqueTest = m_pEffectTest->GetTechniqueByName( "LightingTestGame" );
    ID3DX11EffectPass* passCubeRender = pEffectTechniqueTest->GetPassByName( "CubeRender" );
    if( passCubeRender != 0 )
    {
        passCubeRender->Apply( 0, GetGraphicsDevice()->GetDeviceContext() );
        GetGraphicsDevice()->GetDeviceContext()->DrawIndexed(36, 0, 0);
    }

    GetGraphicsDevice()->Present();
}

void LightingTestGame::Update( GameTime gameTime )
{
    GameWin::Update(gameTime);

    //TODO Write below
}

void LightingTestGame::LoadAndInitialEffect()
{
    m_pEffectTest = GetContent()->LoadEffect(_T("LightingTestGameShader.fx"));

    //Create vertex declearation
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    UINT numElements = ARRAYSIZE( layout );
    VertexDeclaration* pVertexDeclaration = new VertexDeclaration(layout, numElements, m_pEffectTest, "LightingTestGame", GetGraphicsDevice()->GetDevice());

    // Create vertex buffer
    LightingTestGameVertexFormat vertices[] =
    {
        { XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT3( 0.0f, 1.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT3( 0.0f, 1.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, 1.0f, 0.0f ) },
        { XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, 1.0f, 0.0f ) },

        { XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT3( 0.0f, -1.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT3( 0.0f, -1.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT3( 0.0f, -1.0f, 0.0f ) },
        { XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT3( 0.0f, -1.0f, 0.0f ) },

        { XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT3( -1.0f, 0.0f, 0.0f ) },
        { XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT3( -1.0f, 0.0f, 0.0f ) },
        { XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT3( -1.0f, 0.0f, 0.0f ) },
        { XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT3( -1.0f, 0.0f, 0.0f ) },

        { XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT3( 1.0f, 0.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT3( 1.0f, 0.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT3( 1.0f, 0.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT3( 1.0f, 0.0f, 0.0f ) },

        { XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT3( 0.0f, 0.0f, -1.0f ) },
        { XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT3( 0.0f, 0.0f, -1.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT3( 0.0f, 0.0f, -1.0f ) },
        { XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT3( 0.0f, 0.0f, -1.0f ) },

        { XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT3( 0.0f, 0.0f, 1.0f ) },
        { XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT3( 0.0f, 0.0f, 1.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, 0.0f, 1.0f ) },
        { XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, 0.0f, 1.0f ) },
    };
    m_pVertexBuffer = new VertexBuffer(GetGraphicsDevice(), ARRAYSIZE( vertices ), pVertexDeclaration, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_pVertexBuffer->SetData(vertices);

    // Create index buffer
    WORD indices[] =
    {
        3,1,0,        2,1,3,
        6,4,5,        7,4,6,
        11,9,8,        10,9,11,
        14,12,13,        15,12,14,
        19,17,16,        18,17,19,
        22,20,21,        23,20,22
    };
    m_pIndexBuffer = new IndexBuffer(GetGraphicsDevice(), ARRAYSIZE( indices ), DXGI_FORMAT_R16_UINT);
    m_pIndexBuffer->SetData(indices);

    // Initialize the world matrix
    m_World = XMMatrixIdentity();
    // Initialize the view matrix
    XMVECTOR Eye = XMVectorSet( 0.0f, 4.0f, -10.0f, 0.0f );
    XMVECTOR At = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
    XMVECTOR Up = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
    m_View = XMMatrixLookAtLH( Eye, At, Up );
    // Initialize the projection matrix
    RECT rc;
    GetClientRect( GetWindow(), &rc );
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;
    m_Projection = XMMatrixPerspectiveFovLH( XM_PIDIV4, width / (FLOAT)height, 0.01f, 100.0f );

    // Create the constant buffer
    D3D11_BUFFER_DESC bd;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(LightingTestGameConstantBuffer);
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;
    bd.StructureByteStride = 0;
    HRESULT hr = GetGraphicsDevice()->GetDevice()->CreateBuffer( &bd, NULL, &m_pConstantBuffer );
    if( FAILED( hr ) )
        return;
}

void LightingTestGame::UnLoadEffect()
{
    if (m_pEffectTest)
        m_pEffectTest->Release();//有Buffer未释放，尚未查找到原因
    if (m_pConstantBuffer)
        m_pConstantBuffer->Release();

    m_pEffectTest = NULL;
    m_pConstantBuffer = NULL;

    delete m_pVertexBuffer;
    delete m_pIndexBuffer;
}
