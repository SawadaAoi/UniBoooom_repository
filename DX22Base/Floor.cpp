#include "Floor.h"

CFloor::CFloor()
	:m_pModel(nullptr)
	,m_pVS(nullptr)
	,m_pCamera(nullptr)
{
	//頂点シェーダ読み込み
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}
	//床のモデル読み込み
	m_pModel = new Model;
	if (!m_pModel->Load("Assets/Model/floor/floor_1.1.FBX", 0.1f, Model::XFlip)) {		//倍率と反転は省略可
		MessageBox(NULL, "slime_blue", "Error", MB_OK);	//ここでエラーメッセージ表示
	}
	m_pModel->SetVertexShader(m_pVS);

	// レンダーターゲット、深度バッファの設定
	RenderTarget* pRTV = GetDefaultRTV();	//デフォルトで使用しているRenderTargetViewの取得
	DepthStencil* pDSV = GetDefaultDSV();	//デフォルトで使用しているDepthStencilViewの取得
	SetRenderTargets(1, &pRTV, pDSV);		//DSVがnullだと2D表示になる

	m_Transform.fPos = { 0.0f, 0.0f, 0.0f };
	m_Transform.fScale = { 1.0f, 1.0f, 1.0f };
	m_Transform.fRadian = { 0.0f, 0.0f, 0.0f };
}

CFloor::~CFloor()
{
	SAFE_DELETE(m_pModel);
	SAFE_DELETE(m_pVS);
}

void CFloor::Update()
{
}

void CFloor::Draw()
{
	DirectX::XMFLOAT4X4 mat[3];

	mat[0] = m_Transform.GetWorldMatrixSRT();
	mat[1] = m_pCamera->GetViewMatrix();
	mat[2] = m_pCamera->GetProjectionMatrix();

	//-- モデル表示
	if (m_pModel) {
		m_pModel->Draw();
	}
}

void CFloor::SetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;
}
