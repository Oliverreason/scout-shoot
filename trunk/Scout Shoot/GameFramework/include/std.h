#pragma once
#include <tchar.h>

#include <vector>
#include <string>
#include <algorithm>

#ifdef _UNICODE
typedef std::wstring tstring;
typedef wchar_t tchar;
#else
typedef std::string tstring;
typedef char tchar;
#endif

#include <windows.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <xnamath.h>
#include <DxErr.h>
#include <D3Dcompiler.h>
#include <d3dx11effect.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
