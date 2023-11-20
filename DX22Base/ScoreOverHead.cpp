/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	スコア管理用cpp
	---------------------------------------
	ScoreManager.cpp

	作成者	山本凱翔

	変更履歴
	・2023/11/18　作成

========================================== */

// =============== インクルード ===================
#include "ScoreOverHead.h"
#include "Sprite.h"
/* ========================================
	関数：コンストラクタ
	-------------------------------------
	内容：実行時に行う処理
	-------------------------------------
	引数1：爆発の位置,スコア
	-------------------------------------
	戻値：なし
=========================================== */
CScoreOverHead::CScoreOverHead(TPos3d<float> fPos, int nScore, float posY)
	: m_pScoreTexture(nullptr)
	, m_Transform(fPos, { 0.0f, 0.0f, 0.0f }, 0.0f)
	, digits{}
	, digitArray{}
	, ArraySize(0)
{
	m_pScoreTexture = new Texture();

	if (FAILED(m_pScoreTexture->Create("Assets/Texture/numbers_v1/number.png")))
	{
		MessageBox(NULL, "数字読み込み", "Error", MB_OK);
	}
	m_Transform.fPos.y += posY;
	//slimeのレベルによって爆発の大きさ変わるからslimeのとこで高さ調整する必要あり？
	//m_Transform.fPos.y

	// 数字を各桁ごとに配列に格納
	digitArray = digitsToArray(nScore);
	ArraySize = digitArray.size();
}

CScoreOverHead::~CScoreOverHead()
{
	digits.clear();
	digitArray.clear();
}

void CScoreOverHead::Update()	//
{
}

void CScoreOverHead::Draw()
{
	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMFLOAT4X4 inv;//逆行列の格納先
	inv = m_pCamera->GetViewMatrix();

	//カメラの行列はGPUに渡す際に転置されているため、逆行列のために一度元に戻す
	DirectX::XMMATRIX matInv = DirectX::XMLoadFloat4x4(&inv);
	matInv = DirectX::XMMatrixTranspose(matInv);


	//移動成分は逆行列で打ち消す必要が無いので0を設定して移動を無視する
	DirectX::XMStoreFloat4x4(&inv, matInv);
	inv._41 = inv._42 = inv._43 = 0.0f;

	matInv = DirectX::XMLoadFloat4x4(&inv);
	matInv = DirectX::XMMatrixInverse(nullptr, matInv);

	
	for (int i = 0; i <= ArraySize; i++)
	{

		float width = 20.0f*i;


		DirectX::XMMATRIX world = matInv * DirectX::XMMatrixTranslation(m_Transform.fPos.x+width, m_Transform.fPos.y, m_Transform.fPos.z);
		DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));
		Sprite::SetSize(DirectX::XMFLOAT2(20.0f, -20.0f));
		int y = digitArray[i] % 5;	//ここ名前募集します
		int x= digitArray[i] / 5;	//配列に入ってる数字の場所を計算してます
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.2f*y, 0.5f*x));//0.2と0.5はtimeと同じなのであとでゲームパラメータに追加して変えます
		Sprite::SetUVScale(DirectX::XMFLOAT2(0.2f, 0.5f));

		Sprite::SetWorld(mat[0]);
		Sprite::SetTexture(m_pScoreTexture);
		Sprite::Draw();
		
	}


}

std::vector<int> CScoreOverHead::digitsToArray(int score)
{
	while (score > 0) {
		digits.push_back(score % 10);
		score /= 10;
	}
	// １の位から入っているので反転する
	std::reverse(digits.begin(), digits.end());
	return digits;
}
