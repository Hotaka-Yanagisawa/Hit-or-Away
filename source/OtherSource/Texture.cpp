//////////////////////////////////////////////
// Texture.h
//--------------------------------------------
// 2020/07/17	作成
//		09/03	クラス化
//
//////////////////////////////////////////////

//--- インクルード部
#include "Texture.h"
#include "DirectXTex/DirectXTex.h"
#include "DirectXTex/WICTextureLoader.h"

#ifdef _X86_
#ifdef _DEBUG
#pragma comment(lib, "DirectXTex/Win32/Debug/DirectXTex.lib")
#pragma comment(lib, "DirectXTex/Win32/Debug/WICTextureLoader.lib")
#else
#pragma comment(lib, "DirectXTex/Win32/Release/DirectXTex.lib")
#pragma comment(lib, "DirectXTex/Win32/Release/WICTextureLoader.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment(lib, "DirectXTex/x64/Debug/DirectXTex.lib")
#pragma comment(lib, "DirectXTex/x64/Debug/WICTextureLoader.lib")
#else
#pragma comment(lib, "DirectXTex/x64/Release/DirectXTex.lib")
#pragma comment(lib, "DirectXTex/x64/Release/WICTextureLoader.lib")
#endif
#endif

//--- コンストラクタ
CTexture::CTexture()
{
	m_pTexture = NULL;
}

//--- デストラクタ
CTexture::~CTexture()
{
	// テクスチャの解放
	UnLoadTexture();
}

//--- 画像読み込み
HRESULT CTexture::LoadTexture(const char *pszFileName)
{
	wchar_t wPath[MAX_PATH];
	size_t wLen = 0;
	MultiByteToWideChar(0, 0, pszFileName, -1, wPath, MAX_PATH);
	DirectX::TexMetadata mdata;
	GetMetadataFromTGAFile(wPath, mdata);
	DirectX::ScratchImage image;
	LoadFromTGAFile(wPath, &mdata, image);

	ID3D11Device *pDevice = GetDevice();
	ID3D11DeviceContext *pContext = GetContext();

	HRESULT hr = CreateShaderResourceView(pDevice, image.GetImages(), image.GetImageCount(), mdata, &m_pTexture);
	if (FAILED(hr))
	{
		ID3D11Resource *tex = NULL;
		hr = DirectX::CreateWICTextureFromFile(pDevice, pContext, wPath, &tex, &m_pTexture);
	}

	return hr;
}

//--- テクスチャ解放
void CTexture::UnLoadTexture()
{
	SAFE_RELEASE(m_pTexture);
}
