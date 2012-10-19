#include "kXNA_Dll.h"
#include "GameFrameworkExport.h"
#include "VertexBuffer.h"
#include "Win/GraphicsDevice.h"
#include "VertexDeclaration.h"

using namespace kXNA;
VertexBuffer::VertexBuffer(GraphicsDevice* pGraphicsDevice, int iVertexSize, VertexDeclaration* pVertexDeclaration, D3D_PRIMITIVE_TOPOLOGY enumVertexTopology)
{
    m_pGraphicsDevice = pGraphicsDevice;
    m_iVertexSize = iVertexSize;
    m_pVertexDeclaration = pVertexDeclaration;
    m_enumVertexTopology = enumVertexTopology;
}


VertexBuffer::~VertexBuffer(void)
{
    if (m_pVertexBuffer11) 
        m_pVertexBuffer11->Release();
    m_pVertexBuffer11 = NULL;

    delete m_pVertexDeclaration;
}

ID3D11Buffer* VertexBuffer::GetData()
{
    return m_pVertexBuffer11;
}
