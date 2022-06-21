///////////////////////////////////////
// Polygon.cpp
//-------------------------------------
// 2020/07/17	作成
//		07/26	アニメ処理実装
//		07/30	アニメ処理修正
//		08/03	Set関数の相対指定追加
//
///////////////////////////////////////

//--- インクルード部
#include "Polygon.h"
#include <string.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3dcompiler.lib")

//--- 定数
const unsigned char VTX_NUM = 4; // 頂点数
// 頂点シェーダ
const char VSCode[] = "\
struct VS_IN {\
	float3 pos : POSITION0;\
	float4 color : COLOR0;\
	float2 uv : TEXCOORD0;\
};\
struct VS_OUT {\
	float4 pos : SV_POSITION;\
	float4 color : TEXCOORD0;\
	float2 uv : TEXCOORD1;\
};\
cbuffer ConstantBuffer : register(b0) {\
	float4x4 WVP;\
};\
VS_OUT main(VS_IN VIN) {\
	VS_OUT VOUT;\
	VOUT.pos = mul(float4(VIN.pos, 1), WVP);\
	VOUT.color = VIN.color;\
	VOUT.uv = VIN.uv;\
	return VOUT;\
}";
// ピクセルシェーダ
const char PSCode[] = "\
struct PS_IN {\
	float4 pos : SV_POSITION;\
	float4 color : TEXCOORD0;\
	float2 uv : TEXCOORD1;\
};\
Texture2D tex : register(t0);\
SamplerState samp : register(s0);\
float4 main(PS_IN PIN) : SV_Target {\
	return tex.Sample(samp, PIN.uv) * PIN.color;\
}";

//--- 構造体
struct Vertex
{
	float x, y, z;		// 座標
	float r, g, b, a;	// カラー
	float u, v;			// UV
};

//--- グローバル変数
Vertex						g_vertex[VTX_NUM];	// 頂点データ
ID3D11Buffer				*g_pBuffer;			// 頂点バッファ
ID3D11ShaderResourceView	*g_pWhiteTexture;	// 空テクスチャ

//--- コンストラクタ
CPolygon::CPolygon()
{
	// ステータスの初期化
	m_Texture.LoadTexture(NULL);			// テクスチャ
	m_Position	= { -100.0f, -100.0f };		// 位置
	m_Size		= { 1.0f, 1.0f };			// 大きさ
	m_Split		= { 1, 1 };					// 分割数
	m_Color		= { 1.0f,1.0f,1.0f,1.0f };	// 色
	m_TexCoord	= { 0.0f,0.0f };			// UV座標
	m_fRadian	= 0.0f;						// 角度
	m_bShow = true;							// 表示
	strcpy(m_szName, "default");			// 名前

}

//--- デストラクタ
CPolygon::~CPolygon()
{
	// テクスチャの解放
	m_Texture.UnLoadTexture();
}

//--- ポリゴン全体の初期化
HRESULT InitPolygon(UINT width, UINT height)
{
	HRESULT hr = E_FAIL;
	ID3D11Device *pDevice = GetDevice();
	ID3D11DeviceContext *pContext = GetContext();

	// 初期設定
	ZeroMemory(g_vertex, sizeof(g_vertex));
	g_vertex[1].u = 1.0f;
	g_vertex[2].v = 1.0f;
	g_vertex[3].u = g_vertex[3].v = 1;

	// カメラ行列
	DirectX::XMMATRIX cameraMat =
		DirectX::XMMatrixOrthographicOffCenterLH(0, static_cast<float>(width), static_cast<float>(height), 0, -1, 1);
	cameraMat = DirectX::XMMatrixTranspose(cameraMat);
	DirectX::XMFLOAT4X4 f4x4;
	DirectX::XMStoreFloat4x4(&f4x4, cameraMat);


	//頂点バッファ作成
	D3D11_BUFFER_DESC vtxBufDesc;
	ZeroMemory(&vtxBufDesc, sizeof(vtxBufDesc));
	vtxBufDesc.ByteWidth = sizeof(Vertex) * VTX_NUM;
	vtxBufDesc.Usage = D3D11_USAGE_DYNAMIC;
	vtxBufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vtxBufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA vtxSubResource;
	ZeroMemory(&vtxSubResource, sizeof(vtxSubResource));
	vtxSubResource.pSysMem = g_vertex;

	hr = pDevice->CreateBuffer(&vtxBufDesc, &vtxSubResource, &g_pBuffer);
	if (FAILED(hr)) { return hr; }

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	pContext->IASetVertexBuffers(0, 1, &g_pBuffer, &stride, &offset);
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);


	// シェーダコンパイル
	ID3DBlob *VSobj;
	ID3DBlob *PSobj;
	ID3DBlob *error;
	hr = D3DCompile(VSCode, sizeof(VSCode), NULL, NULL, NULL, "main", "vs_5_0", 0, 0, &VSobj, &error);
	if (FAILED(hr)) { return hr; }
	hr = D3DCompile(PSCode, sizeof(PSCode), NULL, NULL, NULL, "main", "ps_5_0", 0, 0, &PSobj, &error);
	if (FAILED(hr)) { return hr; }

	//頂点レイアウト作成
	ID3D11InputLayout *pInputLayout;
	static const D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,							 D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	hr = pDevice->CreateInputLayout(layout, _countof(layout), VSobj->GetBufferPointer(), VSobj->GetBufferSize(), &pInputLayout);
	if (FAILED(hr)) { return hr; }
	pContext->IASetInputLayout(pInputLayout);
	SAFE_RELEASE(pInputLayout);

	//頂点シェーダー生成
	ID3D11VertexShader *pVertexShader;
	hr = pDevice->CreateVertexShader(VSobj->GetBufferPointer(), VSobj->GetBufferSize(), NULL, &pVertexShader);
	if (FAILED(hr)) { return hr; }
	pContext->VSSetShader(pVertexShader, NULL, 0);
	SAFE_RELEASE(pVertexShader);
	SAFE_RELEASE(VSobj);

	D3D11_BUFFER_DESC shaderBufDesc;
	ZeroMemory(&shaderBufDesc, sizeof(shaderBufDesc));
	shaderBufDesc.ByteWidth = sizeof(f4x4);
	shaderBufDesc.Usage = D3D11_USAGE_DEFAULT;
	shaderBufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	D3D11_SUBRESOURCE_DATA shaderSubResource;
	ZeroMemory(&shaderSubResource, sizeof(shaderSubResource));
	shaderSubResource.pSysMem = &f4x4;

	ID3D11Buffer *pShaderBuffer;
	hr = pDevice->CreateBuffer(&shaderBufDesc, &shaderSubResource, &pShaderBuffer);
	if (FAILED(hr)) { return hr; }
	pContext->VSSetConstantBuffers(0, 1, &pShaderBuffer);
	SAFE_RELEASE(pShaderBuffer);

	//ピクセルシェーダー生成
	ID3D11PixelShader  *pPixelShader;
	hr = pDevice->CreatePixelShader(PSobj->GetBufferPointer(), PSobj->GetBufferSize(), NULL, &pPixelShader);
	if (FAILED(hr)) { return hr; }
	pContext->PSSetShader(pPixelShader, NULL, 0);
	SAFE_RELEASE(pPixelShader);
	SAFE_RELEASE(PSobj);

	// 白色テクスチャ生成
	D3D11_TEXTURE2D_DESC texDesc;
	ZeroMemory(&texDesc, sizeof(D3D11_TEXTURE2D_DESC));
	texDesc.Width = 1;
	texDesc.Height = 1;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	texDesc.SampleDesc.Count = 1;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	BYTE color[] = { 0xff, 0xff, 0xff, 0xff };
	D3D11_SUBRESOURCE_DATA texSubResource;
	ZeroMemory(&texSubResource, sizeof(texSubResource));
	texSubResource.SysMemPitch = sizeof(color);
	texSubResource.pSysMem = color;

	ID3D11Texture2D *pTex = NULL;
	hr = pDevice->CreateTexture2D(&texDesc, &texSubResource, &pTex);
	if (FAILED(hr)) { return hr; }

	D3D11_SHADER_RESOURCE_VIEW_DESC shaderViewDesc;
	ZeroMemory(&shaderViewDesc, sizeof(shaderViewDesc));
	shaderViewDesc.Format = texDesc.Format;
	shaderViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderViewDesc.Texture2D.MipLevels = texDesc.MipLevels;

	hr = pDevice->CreateShaderResourceView(pTex, &shaderViewDesc, &g_pWhiteTexture);
	if (FAILED(hr)) { return hr; }
	pContext->PSSetShaderResources(0, 1, &g_pWhiteTexture);
	SAFE_RELEASE(pTex);

	return hr;
}

//--- ポリゴン全体の終了
void UninitPolygon()
{
	SAFE_RELEASE(g_pBuffer);
}

//--- 更新
void CPolygon::Update()
{

}

//--- 描画
void CPolygon::Draw()
{
	// 表示しない
	if (!m_bShow) return;

	//--- 極座標を求める
	// 中心からの距離
	float halfW = m_Size.x * 0.5f;
	float halfH = m_Size.y * 0.5f;
	// 中心から四隅への距離
	float length = sqrtf(halfW * halfW + halfH * halfH);
	// 四隅に向かう角度
	float radian[] =
	{
		atan2f(-halfH, -halfW),	// 左上への角度
		atan2f(-halfH,  halfW),	// 右上への角度
		atan2f(halfH, -halfW),	// 左下への角度
		atan2f(halfH,  halfW),	// 右下への角度
	};

	//--- ステータスの設定
	for (int i = 0; i < 4; i++)
	{
		// 極座標から絶対座標へ変換
		float x = cosf(radian[i] + m_fRadian) * length;
		float y = sinf(radian[i] + m_fRadian) * length;
		// 座標の設定
		g_vertex[i].x = m_Position.x + x;
		g_vertex[i].y = m_Position.y + y;
		// 色の設定
		g_vertex[i].r = m_Color.r;
		g_vertex[i].g = m_Color.g;
		g_vertex[i].b = m_Color.b;
		g_vertex[i].a = m_Color.a;
	}
	// テクスチャの設定
	ID3D11DeviceContext *pContext = GetContext();
	pContext->PSSetShaderResources(0, 1, m_Texture.m_pTexture == NULL ? &g_pWhiteTexture : &m_Texture.m_pTexture);
	// UVの設定
	float w = 1.0f / m_Split.x;
	float h = 1.0f / m_Split.y;
	g_vertex[0].u = m_TexCoord.x		* w; g_vertex[0].v = m_TexCoord.y		* h;
	g_vertex[1].u = (m_TexCoord.x + 1)	* w; g_vertex[1].v = m_TexCoord.y		* h;
	g_vertex[2].u = m_TexCoord.x		* w; g_vertex[2].v = (m_TexCoord.y + 1)	* h;
	g_vertex[3].u = (m_TexCoord.x + 1)	* w; g_vertex[3].v = (m_TexCoord.y + 1)	* h;

	//--- ポリゴン描画
	HRESULT hr = E_FAIL;
	D3D11_MAPPED_SUBRESOURCE mapResource;
	// データ描き込み
	hr = pContext->Map(g_pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResource);
	if (SUCCEEDED(hr))
	{
		memcpy_s(mapResource.pData, sizeof(g_vertex), g_vertex, sizeof(g_vertex));
	}
	pContext->Unmap(g_pBuffer, 0);
	// 描画
	pContext->Draw(VTX_NUM, 0);
}

//--- 座標設定
void CPolygon::SetPos(float PosX, float PosY, bool Rela)
{
	if(!Rela)
		m_Position = { PosX, PosY };
	else
	{
		m_Position.x += PosX;
		m_Position.y += PosY;
	}
}

//--- 大きさ設定
void CPolygon::SetSize(float SizeX, float SizeY, bool Rela)
{
	if (!Rela)
		m_Size = { SizeX, SizeY };
	else
	{
		m_Size.x += SizeX;
		m_Size.y += SizeY;
	}
}

//--- 色設定
void CPolygon::SetColor(float r, float g, float b, float a, bool Rela)
{
	if (!Rela)
	{
		// 0 ～ 1の間に補正
		if (r < 0.0f) r = 0.0f;	if (r > 1.0f) r = 1.0f;	// 赤
		if (g < 0.0f) g = 0.0f;	if (g > 1.0f) g = 1.0f;	// 緑
		if (b < 0.0f) b = 0.0f;	if (b > 1.0f) b = 1.0f;	// 青
		if (a < 0.0f) a = 0.0f;	if (a > 1.0f) a = 1.0f;	// 透明度
		m_Color = { r, g, b, a };
	}
	else
	{
		m_Color.r += r;
		m_Color.g += g;
		m_Color.b += b;
		m_Color.a += a;
	}
}

//--- 角度設定
void CPolygon::SetAngle(float Angle, bool Rela)
{
	// 0.0 ～ 360.0度に補正
	Angle = (int)Angle * 10 % (360 * 10) / 10.0f;

	// ラジアンを度数に置き換える
	float PI = 3.141592f;
	if (!Rela)
		m_fRadian = Angle * PI / 180.0f;
	else
		m_fRadian += Angle * PI / 180.0f;
}

//--- 名前設定
void CPolygon::SetName(const char* Name)
{
	strcpy(m_szName, Name);
}

//--- 画像読み込み
void CPolygon::SetImage(const char* FileName)
{
	m_Texture.LoadTexture(FileName);
}

//--- テクスチャの設定
void CPolygon::SetTexture(ID3D11ShaderResourceView* pTexture)
{
	m_Texture.m_pTexture = pTexture;
}

//--- 分割数設定
void CPolygon::SetSplit(float w, float h)
{
	m_Split = { w, h };
}

//--- UV座標設定
void CPolygon::SetUV(float u, float v)
{
	// 値を格納
	m_TexCoord = { u ,v };
}

//--- 座標取得
VECTOR2<> CPolygon::GetPos()
{
	return m_Position;
}

//--- 大きさ取得
VECTOR2<> CPolygon::GetSize()
{
	return m_Size;
}

//--- 名前取得
char* CPolygon::GetName()
{
	char temp[10];
	strcpy(temp, m_szName);
	return temp;
}

