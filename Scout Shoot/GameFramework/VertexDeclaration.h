#pragma once
#include "std.h"

namespace kXNA
{
    class VertexDeclaration
    {
    public:
        VertexDeclaration(D3D11_INPUT_ELEMENT_DESC arrInputDesc [], UINT numElements, ID3DX11Effect* pEffect, std::string strTechniqueName, ID3D11Device* pD3D11Device);
        ~VertexDeclaration(void);

        inline ID3D11InputLayout* GetVertexElement() const { return m_pInputLayout;}
        inline int GetVertexStride() const { return m_iVertexStride;}

    private:
        ID3D11InputLayout* m_pInputLayout;
        int m_iVertexStride;
    };
}