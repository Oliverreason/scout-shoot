#pragma once
#include "std.h"

namespace kXNA
{
    class GraphicsDevice;

    class _kXNA ContentManager
    {
    public:
        ContentManager(GraphicsDevice* pGraphicsDevice);
        ~ContentManager(void);

        ID3DX11Effect* LoadEffect(const tstring strEffectFileName);

    private:
        bool ContentManager::CompileD3DShader( const tstring strFilePath, char* entry, char* shaderModel, ID3DBlob** buffer);

        GraphicsDevice* m_pGraphicsDevice;
    };
}