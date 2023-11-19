/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	フェード実装
	------------------------------------
	Fade.cpp
	------------------------------------
	作成者	takagi

	変更履歴
	・2023/11/18 制作 takagi

========================================== */

// =============== デバッグモード ===================
#if _DEBUG
#define USE_FADE (true)	//フェード試運転
#endif

// =============== インクルード ===================
#include "Fade.h"	//自身のヘッダ
#if USE_FADE
#include "Input.h"	//キー入力用
#endif

// =============== 定数定義 =====================
const std::string TEX_PASS = "Assets/Fade.png";	//テクスチャのパス名


// =============== グローバル変数宣言 =====================
int CFade::ms_nCntFade;				//自身の生成数
VertexShader* CFade::ms_pVs;		//頂点シェーダー
PixelShader* CFade::ms_pPs;			//ピクセルシェーダー
const void* CFade::ms_pVtx;			//頂点情報
unsigned int CFade::ms_unVtxSize;	//頂点サイズ
unsigned int CFade::ms_unVtxCount;	//頂点数
const void* CFade::ms_pIdx;			//頂点のインデックス
unsigned int CFade::ms_unIdxSize;	//インデックスサイズ
unsigned int CFade::ms_unIdxCount;	//インデックス数
ID3D11Buffer* CFade::ms_pVtxBuffer;	//頂点バッファ
ID3D11Buffer* CFade::ms_pIdxBuffer;	//インデックスバッファ 

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：生成時に行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
CFade::CFade(const CCamera* pCamera)
	:m_pTexture(nullptr)	//
	, m_pCamera(pCamera)	//
	, m_nFrame(0)
	, m_bFadeOut(false)
	, m_bFadeIn(false)
	, m_bStop(false)
{
	if (0 == ms_nCntFade)	//現在、他にこのクラスが作成されていない
	{
		MakeShader();
		Make();
	}
	param[0] = DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	param[1] = DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	param[2] = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	DirectX::XMStoreFloat4x4(&matrix[0], DirectX::XMMatrixIdentity());
	DirectX::XMStoreFloat4x4(&matrix[1], DirectX::XMMatrixIdentity());
	DirectX::XMStoreFloat4x4(&matrix[2], DirectX::XMMatrixIdentity());

	ms_nCntFade++;
}

/* ========================================
	コピーコンストラクタ関数
	-------------------------------------
	内容：コピー時に行う処理
	-------------------------------------
	引数1：const CFade & Obj：コピー元の参照
	-------------------------------------
	戻値：なし
=========================================== */
CFade::CFade(const CFade & Obj)
{
}

/* ========================================
	デストラクタ関数
	-------------------------------------
	内容：破棄時に行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
CFade::~CFade()
{
	ms_nCntFade--;
	SAFE_DELETE(ms_pPs);
}

void CFade::Update()
{
}

void CFade::Draw()
{
	if (IsKeyTrigger('7'))
	{
		m_bFadeOut = true;
		m_nFrame = 150;
	}

	if (m_nFrame <= 0 && m_bFadeOut)
	{
		m_bFadeOut = false;
		m_nFrame = 60;
		m_bStop = true;
	}
	if (m_nFrame <= 0 && m_bFadeIn)
	{
		m_bFadeIn = false;
	}

	if (m_nFrame <= 0 && m_bStop)
	{
		m_bStop = false;
		m_nFrame = 150;
		m_bFadeIn = true;
	}

	if (!m_pTexture || !m_bFadeOut && !m_bFadeIn && !m_bStop)
	{
		return;
	}

	float rad;
	rad = 3.1f * 3.0f / 180.0f * (float)m_nFrame;

	if (m_bFadeIn)
	{
		rad *= -1.0f;
	}

	float size;
	int nTemp = 150 - m_nFrame;
	//size = A_3 * (float)(m_nFrame * m_nFrame * m_nFrame) + B_3 * (float)(m_nFrame * m_nFrame) + C_3 * (float)(m_nFrame) + D_3;
	if (nTemp <= 50)
	{
		if (m_bFadeIn)
		{
			size = 1000.0f - (1000.0f - 15.0f) * (float)nTemp / 50.0f;
		}
		if (m_bFadeOut)
		{
			size = 0.0f + (100.0f - 0.0f) * (float)nTemp / 50.0f;
		}
	}
	else
	{
		if (nTemp <= 100)
		{
			if (m_bFadeIn)
			{
				size = 30.0f + (100.0f - 30.0f) * (float)(nTemp - 50) / 50.0f;
			}
			if (m_bFadeOut)
			{
				size = 100.0f - (100.0f - 15.0f) * (float)(nTemp - 50) / 50.0f;
			}
		}
		else
		{
			if (nTemp < 150)
			{
				if (m_bFadeIn)
				{
					size = 100.0f - (100.0f - 0.0f) * (float)(nTemp - 100) / 50.0f;
				}
				if (m_bFadeOut)
				{
					size = 15.0f + (1000.0f - 15.0f) * (float)(nTemp - 100) / 50.0f;
				}
			}
			else
			{
				if (nTemp < 150)
				{
					size = 1000.0f;
				}
			}
		}
		
	}
	m_nFrame--;

	if (m_bStop)
	{
		size = 500.0f;
	}

	//size *= 1.06f;
	//param[1].x = -size / 2.0f;
	//param[1].y = -size / 2.0f;
	param[1].z = size;
	param[1].w = size;

	
	DirectX::XMMATRIX world =
		DirectX::XMMatrixScaling(80.0f, 80.0f, 0.0f) * DirectX::XMMatrixRotationZ(rad) * DirectX::XMMatrixTranslation(640.0f, 360.0f, 0.0f);

	DirectX::XMStoreFloat4x4(&matrix[0], DirectX::XMMatrixTranspose(world));
	matrix[2] = m_pCamera->GetProjectionMatrix(CCamera::E_DRAW_TYPE_2D);

	//ms_pVs->WriteBuffer();
	ms_pVs->WriteBuffer(0, matrix);
	ms_pVs->WriteBuffer(1, param);
	ms_pVs->Bind();
	ms_pPs->SetTexture(0, m_pTexture);
	ms_pPs->Bind();

	ID3D11DeviceContext* pContext = GetContext();
		UINT offset = 0;

	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pContext->IASetVertexBuffers(0, 1, &ms_pVtxBuffer, &ms_unVtxSize, &offset);

	// 描画
	if (ms_unIdxCount > 0)
	{
		DXGI_FORMAT format;
		switch (ms_unIdxSize)
		{
		case 4: format = DXGI_FORMAT_R32_UINT; break;
		case 2: format = DXGI_FORMAT_R16_UINT; break;
		}
		pContext->IASetIndexBuffer(ms_pIdxBuffer, format, 0);
		pContext->DrawIndexed(ms_unIdxCount, 0, 0);
	}
	else
	{
		// 頂点バッファのみで描画
		pContext->Draw(ms_unVtxCount, 0);
	}

}

/* ========================================
	シェーダー作成関数
	-------------------------------------
	内容：シェーダーをコンパイル・登録
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CFade::MakeShader()
{
	// =============== コード記述 ===================
//	const char* pcVs = R"EOT(
//struct VS_IN {
//	float3 pos : POSITION0;
//	float3 normal : NORMAL0;
//	float2 uv : TEXCOORD0;
//};
//struct VS_OUT {
//	float4 pos : SV_POSITION;
//	float3 normal : NORMAL0;
//	float2 uv : TEXCOORD0;
//};
//cbuffer Matrix : register(b0) {
//	float4x4 world;
//	float4x4 view;
//	float4x4 proj;
//};
//VS_OUT main(VS_IN vin) {
//	VS_OUT vout;
//	//vout.pos = float4(vin.pos, 1.0f);
//	//vout.pos.z += 0.5f;
//	//vout.pos.y -= 0.8f;
//	vout.pos = mul(vout.pos, world);
//	vout.pos = mul(vout.pos, view);
//	vout.pos = mul(vout.pos, proj);
//	vout.normal = vin.normal;
//	vout.uv = vin.uv;
//	return vout;
//})EOT";
//	const char* pcPs = R"EOT(
//struct PS_IN {
//	float4 pos : SV_POSITION;
//	float3 normal : NORMAL0;
//	float2 uv : TEXCOORD0;
//};
//Texture2D tex : register(t0);
//SamplerState samp : register(s0);
//float4 main(PS_IN pin) : SV_TARGET
//{
//	return tex.Sample(samp, pin.uv);
//})EOT";

	ms_pVs = new VertexShader();
	ms_pVs->Load("Assets/Shader/VsFade.cso");
	ms_pPs = new PixelShader();
	ms_pPs->Load("Assets/Shader/PsFade.cso");
}

void CFade::Make()
{
	Vertex aVtx[] = {
		{{-10.5f, 10.5f, -0.0f}, {0.0f, 0.0f}},
		{{ 10.5f, 10.5f, -0.0f}, {1.0f, 0.0f}},
		{{-10.5f,-10.5f, -0.0f}, {0.0f, 1.0f}},
		{{ 10.5f,-10.5f, -0.0f}, {1.0f, 1.0f}},
	};	//頂点情報
	int aIdx[] = {
		0, 1, 2, 2, 1, 3
	};


	ms_pVtx = aVtx;					//頂点情報
	ms_unVtxSize = sizeof(Vertex);	//頂点型サイズ
	ms_unVtxCount = _countof(aVtx);	//頂点数
//	bool isWrite;				
	ms_pIdx = aIdx;
	ms_unIdxSize = sizeof(int);
	ms_unIdxCount = _countof(aIdx);


	CreateVtxBuffer();
	CreateIdxBuffer();
}

void CFade::CreateVtxBuffer()
{
	//＞バッファ情報設定
	D3D11_BUFFER_DESC BufDesc;
	ZeroMemory(&BufDesc, sizeof(BufDesc));	//中身を全て0で初期化
	BufDesc.ByteWidth = ms_unVtxSize * ms_unVtxCount;	//バッファの大きさ
	BufDesc.Usage = D3D11_USAGE_DEFAULT;			//メモリ上での管理方法
	BufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	//GPU上での利用方法

	//＞バッファ初期データ設定
	D3D11_SUBRESOURCE_DATA SubResource;
	ZeroMemory(&SubResource, sizeof(SubResource));
	SubResource.pSysMem = ms_pVtx;				//バッファに入れ込むデータ

	//＞頂点バッファの作成
	HRESULT hr;
	hr = GetDevice()->CreateBuffer(&BufDesc, &SubResource, &ms_pVtxBuffer);
	if (FAILED(hr))
	{
		ms_pVtxBuffer = nullptr;
	}
}

void CFade::CreateIdxBuffer()
{
	// インデックスサイズの確認
	switch (ms_unIdxSize)
	{
	default:
		//todo:error
		return;
	case 2:
	case 4:
		break;
	}

	// バッファの情報を設定
	D3D11_BUFFER_DESC bufDesc = {};
	bufDesc.ByteWidth = ms_unIdxSize * ms_unIdxCount;
	bufDesc.Usage = D3D11_USAGE_DEFAULT;
	bufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	// バッファの初期データ
	D3D11_SUBRESOURCE_DATA subResource = {};
	subResource.pSysMem = ms_pIdx;

	// インデックスバッファ生成
	ID3D11Device* pDevice = GetDevice();
	pDevice->CreateBuffer(&bufDesc, &subResource, &ms_pIdxBuffer);
}


/* ========================================
	テクスチャセッタ関数
	-------------------------------------
	内容：引数をもとにテクスチャー作成
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CFade::SetTexture()
{
	if (m_pTexture)
	{
		SAFE_DELETE(m_pTexture);
	}
	m_pTexture = new Texture;
	m_pTexture->Create(TEX_PASS.c_str());
}