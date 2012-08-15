#include "IndexBuffer.h"
#include "GraphicsDevice.h"
#include "VertexDeclaration.h"

using namespace kXNA;
IndexBuffer::IndexBuffer(GraphicsDevice* pGraphicsDevice, int iVertexSize, DXGI_FORMAT enumFormat)
{
    m_pGraphicsDevice = pGraphicsDevice;
    m_iIndexSize = iVertexSize;
    m_enumFormat = enumFormat;
}


IndexBuffer::~IndexBuffer(void)
{
    if (m_pVertexBuffer11) 
        m_pVertexBuffer11->Release();
    m_pVertexBuffer11 = NULL;
}

ID3D11Buffer* IndexBuffer::GetData()
{
    return m_pVertexBuffer11;
}
