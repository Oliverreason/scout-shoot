#include "kXNA_Dll.h"
#include "GameFrameworkExport.h"
#include "GraphicsDevice.h"
#include "Color.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexDeclaration.h"

using namespace kXNA;
GraphicsDevice::GraphicsDevice(HWND hWnd)
{
    InitDevice(hWnd);
}

GraphicsDevice::~GraphicsDevice(void)
{
    CleanupDevice();
}

void GraphicsDevice::Clear(const Color color)
{
    float fClearColor[4];
    color.ToFloat4(fClearColor);

    m_pImmediateContext->ClearRenderTargetView( m_pRenderTargetView, fClearColor);
    m_pImmediateContext->ClearDepthStencilView( m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0 );
}

void GraphicsDevice::SetVertexBuffer(VertexBuffer* pVertexBuffer)
{
    unsigned int stride = pVertexBuffer->GetVertexStride();
    unsigned int offset = 0;
    GetDeviceContext()->IASetInputLayout( pVertexBuffer->GetVertexDeclaration()->GetVertexElement() );
    ID3D11Buffer* pVB11Temp = pVertexBuffer->GetData();
    GetDeviceContext()->IASetVertexBuffers( 0, 1, &(pVB11Temp), &stride, &offset );
    GetDeviceContext()->IASetPrimitiveTopology(pVertexBuffer->GetVertexTopology());
}

void kXNA::GraphicsDevice::SetIndices( IndexBuffer* pIndexBuffer )
{
    GetDeviceContext()->IASetIndexBuffer( pIndexBuffer->GetData(), pIndexBuffer->GetIndexFormat(), 0 );
}

HRESULT GraphicsDevice::InitDevice(HWND hWnd)
{
    HRESULT hr = S_OK;

    RECT rc;
    GetClientRect( hWnd, &rc );
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

    UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
    UINT numDriverTypes = ARRAYSIZE( driverTypes );

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
    UINT numFeatureLevels = ARRAYSIZE( featureLevels );

    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory( &sd, sizeof( sd ) );
    sd.BufferCount = 1;
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;

    for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
    {
        m_driverType = driverTypes[driverTypeIndex];
        hr = D3D11CreateDeviceAndSwapChain( NULL, m_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
            D3D11_SDK_VERSION, &sd, &m_pSwapChain, &m_pd3dDevice, &m_featureLevel, &m_pImmediateContext );
        if( SUCCEEDED( hr ) )
            break;
    }
    if( FAILED( hr ) )
    {
        DXTRACE_MSG( TEXT("Failed to create the Direct3D device!"));
        return hr;
    }

    // Create a render target view
    ID3D11Texture2D* pBackBuffer = NULL;
    hr = m_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );
    if( FAILED( hr ) )
    {
        DXTRACE_MSG( TEXT("Failed to get the swap chain back buffer!"));
        return hr;
    }
    hr = m_pd3dDevice->CreateRenderTargetView( pBackBuffer, NULL, &m_pRenderTargetView );
    pBackBuffer->Release();
    if( FAILED( hr ) )
    {
        DXTRACE_MSG( TEXT("Failed to create the render target view!"));
        return hr;
    }

    D3D11_TEXTURE2D_DESC depthTexDesc;
    ZeroMemory( &depthTexDesc, sizeof( depthTexDesc ) );
    depthTexDesc.Width = width;
    depthTexDesc.Height = height;
    depthTexDesc.MipLevels = 1;
    depthTexDesc.ArraySize = 1;
    depthTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthTexDesc.SampleDesc.Count = 1;
    depthTexDesc.SampleDesc.Quality = 0;
    depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
    depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthTexDesc.CPUAccessFlags = 0;
    depthTexDesc.MiscFlags = 0;
    hr = m_pd3dDevice->CreateTexture2D( &depthTexDesc, NULL, &m_pDepthTexture );
    if( FAILED( hr ) )
    {
        DXTRACE_MSG( TEXT("Failed to create the depth texture!"));
        return false;
    }
    // Create the depth stencil view
    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
    ZeroMemory( &descDSV, sizeof( descDSV ) );
    descDSV.Format = depthTexDesc.Format;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    descDSV.Texture2D.MipSlice = 0;
    hr = m_pd3dDevice->CreateDepthStencilView( m_pDepthTexture, &descDSV, &m_pDepthStencilView);
    if( FAILED( hr ) )
    {
        DXTRACE_MSG( TEXT("Failed to create the depth stencil target view!"));
        return false;
    }

    m_pImmediateContext->OMSetRenderTargets( 1, &m_pRenderTargetView, m_pDepthStencilView );

    // Setup the viewport
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)width;
    vp.Height = (FLOAT)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    m_pImmediateContext->RSSetViewports( 1, &vp );

    return S_OK;
}

void GraphicsDevice::CleanupDevice()
{
    if( m_pDepthTexture) m_pDepthTexture->Release();
    if( m_pDepthStencilView) m_pDepthStencilView->Release();
    if( m_pRenderTargetView) m_pRenderTargetView->Release();
    if( m_pSwapChain) m_pSwapChain->Release();
    if( m_pImmediateContext) m_pImmediateContext->Release();
    if( m_pd3dDevice) m_pd3dDevice->Release();

    m_pd3dDevice = NULL;
    m_pImmediateContext = NULL;
    m_pSwapChain = NULL;
    m_pRenderTargetView = NULL;
    m_pDepthTexture = NULL;
    m_pDepthStencilView = NULL;
}
