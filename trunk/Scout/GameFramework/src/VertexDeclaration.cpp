#include "kXNA_Dll.h"
#include "GameFrameworkExport.h"
#include "VertexDeclaration.h"

using namespace kXNA;
VertexDeclaration::VertexDeclaration(D3D11_INPUT_ELEMENT_DESC arrInputDesc [], UINT numElements, ID3DX11Effect* pEffect, std::string strTechniqueName, ID3D11Device* pD3D11Device)
{
    ID3DX11EffectTechnique* pTestEffectTechnique;
    pTestEffectTechnique = pEffect->GetTechniqueByName( strTechniqueName.c_str());
    ID3DX11EffectPass* pTestEffectPass = pTestEffectTechnique->GetPassByIndex( 0 );
    D3DX11_PASS_SHADER_DESC passDesc;
    D3DX11_EFFECT_SHADER_DESC shaderDesc;
    pTestEffectPass->GetVertexShaderDesc( &passDesc );
    passDesc.pShaderVariable->GetShaderDesc( passDesc.ShaderIndex, &shaderDesc );
    HRESULT d3dResult = pD3D11Device->CreateInputLayout( arrInputDesc, numElements, shaderDesc.pBytecode, shaderDesc.BytecodeLength, &m_pInputLayout );
    if( FAILED( d3dResult ) )
    {
        DXTRACE_MSG( TEXT("Error creating the input layout!") );
        return;
    }
}


VertexDeclaration::~VertexDeclaration(void)
{
    if (m_pInputLayout) 
        m_pInputLayout->Release();
    m_pInputLayout = 0;
}
