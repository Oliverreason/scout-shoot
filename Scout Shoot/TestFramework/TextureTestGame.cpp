#include "TextureTestGame.h"
#include "GameFrameworkHeader.h"

struct TextureTestGameVertexFormat
{
    XMFLOAT3 Pos;
    XMFLOAT2 Tex;
};

struct TextureTestGameCBNeverChanges
{
    XMMATRIX mView;
};

struct TextureTestGameCBChangeOnResize
{
    XMMATRIX mProjection;
};

struct TextureTestGameCBChangesEveryFrame
{
    XMMATRIX mWorld;
    XMFLOAT4 vMeshColor;
};

using namespace kXNA;
TextureTestGame::TextureTestGame( HINSTANCE hInstance, int nCmdShow)
    : GameWin( hInstance, nCmdShow, TEXT("Texture cube test game"))
{
}


TextureTestGame::~TextureTestGame(void)
{
}

void TextureTestGame::Initialize( void )
{
    GameWin::Initialize();

    //TODO Write below
    m_f4MeshColor = XMFLOAT4( 0.7f, 0.7f, 0.7f, 1.0f );
}

void TextureTestGame::LoadContent( void )
{
    GameWin::LoadContent();

    //TODO Write below
    LoadAndInitialEffect();
}

void TextureTestGame::UnloadContent( void )
{
    GameWin::UnloadContent();

    //TODO Write below
    UnLoadEffect();
}

void TextureTestGame::Draw( GameTime gameTime )
{
    GameWin::Draw(gameTime);

    //TODO Write below
    if( GetGraphicsDevice() == 0 )
        return;

    GetGraphicsDevice()->Clear(Color::DarkBlue);

    FLOAT fTotalTime = gameTime.GetTotalGameTime();

    GetGraphicsDevice()->SetVertexBuffer(m_pVertexBuffer);
    GetGraphicsDevice()->SetIndices(m_pIndexBuffer);

    // Rotate cube around the origin
    m_World = XMMatrixRotationY( fTotalTime );

    // Modify the color
    m_f4MeshColor.x = ( sinf( fTotalTime * 1.0f ) + 1.0f ) * 0.5f;
    m_f4MeshColor.y = ( cosf( fTotalTime * 3.0f ) + 1.0f ) * 0.5f;
    m_f4MeshColor.z = ( sinf( fTotalTime * 5.0f ) + 1.0f ) * 0.5f;
    TextureTestGameCBChangesEveryFrame cb;
    cb.mWorld = XMMatrixTranspose( m_World );
    cb.vMeshColor = m_f4MeshColor;
    GetGraphicsDevice()->GetDeviceContext()->UpdateSubresource(m_pCBChangesEveryFrame, 0, NULL, &cb, 0, 0);
    ID3DX11EffectConstantBuffer* pEffectCBuffer = m_pEffectTest->GetConstantBufferByName( "cbChangesEveryFrame" );
    pEffectCBuffer->SetConstantBuffer(m_pCBChangesEveryFrame);
    ID3DX11EffectSamplerVariable* pEffectSampler = m_pEffectTest->GetVariableByName( "samLinear" )->AsSampler();
    pEffectSampler->SetSampler(0, m_pSamplerLinear);

    ID3DX11EffectTechnique* pEffectTechniqueTest = m_pEffectTest->GetTechniqueByName( "TextureTestGame" );
    ID3DX11EffectPass* passCubeRender = pEffectTechniqueTest->GetPassByName( "CubeRender" );
    if( passCubeRender != 0 )
    {
        passCubeRender->Apply( 0, GetGraphicsDevice()->GetDeviceContext() );
        GetGraphicsDevice()->GetDeviceContext()->DrawIndexed(36, 0, 0);
    }

    GetGraphicsDevice()->Present();
}

void TextureTestGame::Update( GameTime gameTime )
{
    GameWin::Update(gameTime);

    //TODO Write below
}

void TextureTestGame::LoadAndInitialEffect()
{
    m_pEffectTest = GetContent()->LoadEffect(_T("TextureTestGameShader.fx"));

    //Create vertex declearation
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    VertexDeclaration* pVertexDeclaration = new VertexDeclaration(layout, ARRAYSIZE( layout ), m_pEffectTest, "TextureTestGame", GetGraphicsDevice()->GetDevice());

    // Create vertex buffer
    TextureTestGameVertexFormat vertices[] =
    {
        { XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },
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

    // Create the constant buffers
    D3D11_BUFFER_DESC bd;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(TextureTestGameCBNeverChanges);
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = 0;
    HRESULT hr = GetGraphicsDevice()->GetDevice()->CreateBuffer( &bd, NULL, &m_pCBNeverChanges );
    if( FAILED( hr ) )
        return;
    bd.ByteWidth = sizeof(TextureTestGameCBChangeOnResize);
    hr = GetGraphicsDevice()->GetDevice()->CreateBuffer( &bd, NULL, &m_pCBChangeOnResize );
    if( FAILED( hr ) )
        return;
    bd.ByteWidth = sizeof(TextureTestGameCBChangesEveryFrame);
    hr = GetGraphicsDevice()->GetDevice()->CreateBuffer( &bd, NULL, &m_pCBChangesEveryFrame );
    if( FAILED( hr ) )
        return;

    // Create the sample state
    D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory( &sampDesc, sizeof(sampDesc) );
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
    hr = GetGraphicsDevice()->GetDevice()->CreateSamplerState( &sampDesc, &m_pSamplerLinear );
    if( FAILED( hr ) )
        return;

    // Initialize the world matrix
    m_World = XMMatrixIdentity();
    // Initialize the view matrix
    XMVECTOR Eye = XMVectorSet( 0.0f, 3.0f, -6.0f, 0.0f );
    XMVECTOR At = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
    XMVECTOR Up = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
    XMMATRIX matView = XMMatrixLookAtLH( Eye, At, Up );
    TextureTestGameCBNeverChanges cbNeverChanges;
    cbNeverChanges.mView = XMMatrixTranspose( matView );
    GetGraphicsDevice()->GetDeviceContext()->UpdateSubresource( m_pCBNeverChanges, 0, NULL, &cbNeverChanges, 0, 0 );
    ID3DX11EffectConstantBuffer* pEffectCBuffer = m_pEffectTest->GetConstantBufferByName( "cbNeverChanges" );
    pEffectCBuffer->SetConstantBuffer(m_pCBNeverChanges);
    // Initialize the projection matrix
    RECT rc;
    GetClientRect( GetWindow(), &rc );
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;
    XMMATRIX matProjection = XMMatrixPerspectiveFovLH( XM_PIDIV4, width / (FLOAT)height, 0.01f, 100.0f );
    TextureTestGameCBChangeOnResize cbChangesOnResize;
    cbChangesOnResize.mProjection = XMMatrixTranspose( matProjection );
    GetGraphicsDevice()->GetDeviceContext()->UpdateSubresource( m_pCBChangeOnResize, 0, NULL, &cbChangesOnResize, 0, 0 );
    pEffectCBuffer = m_pEffectTest->GetConstantBufferByName( "cbChangeOnResize" );
    pEffectCBuffer->SetConstantBuffer(m_pCBChangeOnResize);
}

void TextureTestGame::UnLoadEffect()
{
    if (m_pEffectTest)
        m_pEffectTest->Release();//有Buffer未释放，尚未查找到原因
    if (m_pCBNeverChanges)
        m_pCBNeverChanges->Release();
    if (m_pCBChangeOnResize)
        m_pCBChangeOnResize->Release();
    if (m_pCBChangesEveryFrame)
        m_pCBChangesEveryFrame->Release();

    m_pEffectTest = NULL;
    m_pCBNeverChanges = NULL;
    m_pCBChangeOnResize = NULL;
    m_pCBChangesEveryFrame = NULL;

    delete m_pVertexBuffer;
    delete m_pIndexBuffer;
}
