#include "kXNA_Dll.h"
#include "GameFrameworkExport.h"
#include "ContentManager.h"
#include "GraphicsDevice.h"

using namespace kXNA;
ContentManager::ContentManager(GraphicsDevice* pGraphicsDevice)
{
    m_pGraphicsDevice = pGraphicsDevice;
}


ContentManager::~ContentManager(void)
{
}

ID3DX11Effect* ContentManager::LoadEffect(const tstring strEffectFileName)
{
    ID3DBlob* buffer = 0;

    bool compileResult = CompileD3DShader( strEffectFileName, 0, "fx_5_0", &buffer );

    if( compileResult == false )
    {
        DXTRACE_MSG( _T("Error compiling the effect shader!"));
        buffer->Release();
    }

    HRESULT d3dResult;

    ID3DX11Effect* effect = NULL;
    d3dResult = D3DX11CreateEffectFromMemory( buffer->GetBufferPointer( ),
        buffer->GetBufferSize( ), 0, m_pGraphicsDevice->GetDevice(), &effect );
    
    if( FAILED( d3dResult ) )
    {
        DXTRACE_MSG( TEXT("Error creating the effect shader!"));
        if( buffer )
            buffer->Release( );
    }

    if( buffer )
        buffer->Release( );

    return effect;
}

bool ContentManager::CompileD3DShader( const tstring strFilePath, char* entry, char* shaderModel, ID3DBlob** buffer )
{
    DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined( DEBUG ) || defined( _DEBUG )
    shaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* errorBuffer = 0;
    HRESULT result;

    result = D3DX11CompileFromFile( strFilePath.c_str(), 0, 0, entry, shaderModel,
        shaderFlags, 0, 0, buffer, &errorBuffer, 0 );

    if( FAILED( result ) )
    {
        if( errorBuffer != 0 )
        {
            OutputDebugStringA( ( char* )errorBuffer->GetBufferPointer( ) );
            errorBuffer->Release( );
        }

        return false;
    }
    
    if( errorBuffer != 0 )
        errorBuffer->Release( );

    return true;
}
