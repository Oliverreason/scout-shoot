#pragma once
#include "std.h"

namespace kXNA
{
    class GraphicsDevice;
    class VertexDeclaration;

    class VertexBuffer
    {
    public:
        VertexBuffer(GraphicsDevice* pGraphicsDevice, int iVertexSize, VertexDeclaration* pVertexDeclaration, D3D_PRIMITIVE_TOPOLOGY enumVertexTopology);
        ~VertexBuffer(void);

        template<typename VertexType> 
        void SetData( VertexType pData [] );

        ID3D11Buffer* GetData();

        inline GraphicsDevice* GetGraphicsDevice() const { return m_pGraphicsDevice;}
        inline VertexDeclaration* GetVertexDeclaration() const { return m_pVertexDeclaration;}
        inline int GetVertexCount() const { return m_iVertexSize;}
        inline int GetVertexStride() const { return m_iVertexStride;}
        inline D3D_PRIMITIVE_TOPOLOGY GetVertexTopology() const { return m_enumVertexTopology;}

    private:
        GraphicsDevice* m_pGraphicsDevice;
        VertexDeclaration* m_pVertexDeclaration;
        int m_iVertexSize;
        int m_iVertexStride;

        D3D_PRIMITIVE_TOPOLOGY m_enumVertexTopology;
        ID3D11Buffer* m_pVertexBuffer11;
    };

    template<typename VertexType> 
    void VertexBuffer::SetData( VertexType pData [] )
    {
        m_iVertexStride = sizeof(VertexType);

        D3D11_BUFFER_DESC bd;
        ZeroMemory( &bd, sizeof(bd) );
        bd.Usage = D3D11_USAGE_DEFAULT;
        bd.ByteWidth = m_iVertexStride * m_iVertexSize;
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bd.CPUAccessFlags = 0;
        D3D11_SUBRESOURCE_DATA InitData;
        ZeroMemory( &InitData, sizeof(InitData) );
        InitData.pSysMem = pData;
        HRESULT d3dResult = GetGraphicsDevice()->GetDevice()->CreateBuffer( &bd, &InitData, &m_pVertexBuffer11 );
        if( FAILED( d3dResult ) )
        {
            DXTRACE_MSG( TEXT("Failed to create vertex buffer!") );
            return;
        }
    }
}