#pragma once
#include "std.h"

namespace kXNA
{
    class GraphicsDevice;
    class VertexDeclaration;

    class IndexBuffer
    {
    public:
        IndexBuffer(GraphicsDevice* pGraphicsDevice, int iVertexSize, DXGI_FORMAT enumFormat);
        ~IndexBuffer(void);

        template<typename IndexType> 
        void SetData( IndexType pData [] );

        ID3D11Buffer* GetData();

        inline GraphicsDevice* GetGraphicsDevice() const { return m_pGraphicsDevice;}
        inline int GetVertexCount() const { return m_iIndexSize;}
        inline DXGI_FORMAT GetIndexFormat() const { return m_enumFormat;}

    private:
        GraphicsDevice* m_pGraphicsDevice;
        int m_iIndexSize;

        DXGI_FORMAT m_enumFormat;
        ID3D11Buffer* m_pVertexBuffer11;
    };

    template<typename IndexType> 
    void IndexBuffer::SetData( IndexType pData [] )
    {
        D3D11_BUFFER_DESC bd;
        ZeroMemory( &bd, sizeof(bd) );
        bd.Usage = D3D11_USAGE_DEFAULT;
        bd.ByteWidth = sizeof(IndexType) * m_iIndexSize;
        bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
        bd.CPUAccessFlags = 0;
        D3D11_SUBRESOURCE_DATA InitData;
        ZeroMemory( &InitData, sizeof(InitData) );
        InitData.pSysMem = pData;
        HRESULT d3dResult = GetGraphicsDevice()->GetDevice()->CreateBuffer( &bd, &InitData, &m_pVertexBuffer11 );
        if( FAILED( d3dResult ) )
        {
            DXTRACE_MSG( TEXT("Failed to create index buffer!") );
            return;
        }
    }
}