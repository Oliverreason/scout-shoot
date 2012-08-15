#pragma once
#include "std.h"

namespace kXNA
{
    struct Color;
    class VertexBuffer;
    class IndexBuffer;

    class GraphicsDevice
    {
        friend class ContentManager;
    public:
        GraphicsDevice(HWND hWnd);
        ~GraphicsDevice(void);

        void Clear(Color color);
        void SetVertexBuffer(VertexBuffer* pVertexBuffer);
        void SetIndices(IndexBuffer* pIndexBuffer);

        inline ID3D11Device* GetDevice() const { return m_pd3dDevice; }
        inline ID3D11DeviceContext* GetDeviceContext() const { return m_pImmediateContext; }
        inline ID3D11RenderTargetView* GetRenderTarget() const { return m_pRenderTargetView; }
        inline IDXGISwapChain* GetSwapChain() const { return m_pSwapChain; }

        inline void Present() const { m_pSwapChain->Present(0, 0); }

    private:
        HINSTANCE m_hInstance;
        int m_nCmdWinShow;
        HWND m_hWnd;

        D3D_DRIVER_TYPE m_driverType;
        D3D_FEATURE_LEVEL m_featureLevel;
        ID3D11Device* m_pd3dDevice;
        ID3D11DeviceContext* m_pImmediateContext;
        IDXGISwapChain* m_pSwapChain;
        ID3D11RenderTargetView* m_pRenderTargetView;
        ID3D11Texture2D* m_pDepthTexture;
        ID3D11DepthStencilView* m_pDepthStencilView;

        HRESULT InitDevice(HWND hWnd);
        void CleanupDevice();
    };
}