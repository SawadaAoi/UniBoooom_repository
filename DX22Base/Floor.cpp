/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	Floor用cpp
	------------------------------------
	Floor.cpp
	------------------------------------
	作成者
		yamashita
	変更履歴
	・2023/11/16 h,作成 yamashita
	・2023/11/16 コンストラクタに頂点シェーダーとモデルの読み込みを追加 yamashita
	・2023/11/16 カメラのセット関数を作成 yamashita
	・2023/11/22 床の自動生成機能を追加 yamashita
	・2023/12/07 ゲームパラメータから一部定数移動 takagi
	・2023/12/15 ステージ別に床のモデルを設定できるように修正 Sawada
	・2023/12/15 コンストラクタの引数にステージ番号を追加 yamashita

========================================== */
#include "Floor.h"
#include "DirectWrite.h"
// =============== 定数定義 =====================
const TDiType<float> FLOOR_OFFSET[3] = {	//下の配列番号の｢-2｣は調整用
	{47.7f * FLOOR_SCALE[CFloor::Stage1].x,47.7f * FLOOR_SCALE[CFloor::Stage1].x},
	{47.7f * FLOOR_SCALE[CFloor::Stage2].x,47.8f * FLOOR_SCALE[CFloor::Stage2].x},
	{47.7f * FLOOR_SCALE[CFloor::Stage3].x,47.7f * FLOOR_SCALE[CFloor::Stage3].x} };
#if MODE_GAME_PARAMETER
#else
const float STAGE1_FLOOR_SCALE_X = 1.1f;
const float STAGE1_FLOOR_SCALE_Z = 1.1f;
#endif

/* ========================================
   関数：コンストラクタ
   ----------------------------------------
   内容：生成時に行う処理
   ----------------------------------------
   引数1：プレイヤーの座標ポインタ
   引数2：ステージ番号 
   ----------------------------------------
   戻値：なし
======================================== */
CFloor::CFloor(TPos3d<float>* pPlayerPos, StageKinds stageKind)
	:m_pModel(nullptr)
	,m_pVS(nullptr)
	,m_pCamera(nullptr)
	,m_pPlayerFloor{0,0,0}
	,m_pPlayePos(pPlayerPos)
	,m_stage(stageKind)
{
	//頂点シェーダ読み込み
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}
	SetFloorModel();	//ステージ毎のモデルを読み込み

	//床の位置情報を入れる
	TTriType<float> pos;
	for (int i = 0; i < FLOOR_NUM; i++)
	{
		//X座標
		switch (i % 3)
		{
		case(0):	pos.x = -(FLOOR_OFFSET[(int)m_stage].x);
			break;
		case(1):	pos.x = 0.0f;
			break;
		case(2):	pos.x = FLOOR_OFFSET[(int)m_stage].x;
			break;
		}

		//Z座標
		switch (i / 3)
		{
		case(0):	pos.z = -(FLOOR_OFFSET[(int)m_stage].y);
			break;
		case(1):	pos.z = 0.0f;
			break;
		case(2):	pos.z = FLOOR_OFFSET[(int)m_stage].y;
			break;
		}

		m_Transform[i].fPos		= { pos.x, -0.1f, pos.z };					//ポジションの初期化
		m_Transform[i].fScale	= { FLOOR_SCALE[(int)m_stage].x, 1.0f, FLOOR_SCALE[(int)m_stage].y };	//スケールの初期化
		m_Transform[i].fRadian	= { 0.0f, 0.0f, 0.0f };						//回転角を初期化
	}	
}

/* ========================================
   関数：デストラクタ
   ----------------------------------------
   内容：終了時に行う処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
======================================== */
CFloor::~CFloor()
{
	SAFE_DELETE(m_pModel);
	SAFE_DELETE(m_pVS);
}

/* ========================================
	アップデート関数
   ----------------------------------------
   内容：毎フレーム行う処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
======================================== */
void CFloor::Update()
{
	calculationPosition();
}

/* ========================================
   描画関数
   ----------------------------------------
   内容：オブジェクトの描画
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
======================================== */
void CFloor::Draw()
{
	DirectX::XMFLOAT4X4 mat[3];

	for (int i = 0; i < FLOOR_NUM; i++)
	{
		mat[0] = m_Transform[i].GetWorldMatrixSRT();
		mat[1] = m_pCamera->GetViewMatrix();
		mat[2] = m_pCamera->GetProjectionMatrix();

		//-- 行列をシェーダーへ設定
		m_pVS->WriteBuffer(0, mat);

		//-- モデル表示
		if (m_pModel) {
			m_pModel->Draw();
		}
	}
}

/* ========================================
	ポジション算出関数
   ----------------------------------------
   内容：プレイヤーの座標から床の表示座標をわりだす
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
======================================== */
void CFloor::calculationPosition()
{
	int offsetX = (int)m_pPlayePos->x;	//プレイヤーの中心からのX座標のずれ
	int offsetZ = (int)m_pPlayePos->z;	//プレイヤーの中心からのZ座標のずれ
	if (offsetX >= 0) { offsetX += int(FLOOR_OFFSET[(int)m_stage].x / 2.0f); }	//座標がプラスなら加算
	else { offsetX -= int(FLOOR_OFFSET[(int)m_stage].x / 2.0f); }					//座標がマイナスなら減算
	if (offsetZ >= 0) { offsetZ += int(FLOOR_OFFSET[(int)m_stage].y / 2.0f); }	//座標がプラスなら加算
	else { offsetZ -= int(FLOOR_OFFSET[(int)m_stage].y / 2.0f); }				//座標がマイナスなら減算

	//プレイヤーが床の大きさで何枚目分の所にいるか
	m_pPlayerFloor.x = int(offsetX / FLOOR_OFFSET[(int)m_stage].x);
	m_pPlayerFloor.z = int(offsetZ / FLOOR_OFFSET[(int)m_stage].x);


	//床を表示する座標を確定
	TTriType<float> pos;
	TTriType<float> centerPos = { m_pPlayerFloor.x * FLOOR_OFFSET[(int)m_stage].x,
		0.0f,m_pPlayerFloor.z * FLOOR_OFFSET[(int)m_stage].y };
	for (int i = 0; i < FLOOR_NUM; i++)
	{
		//X座標
		switch (i % 3)
		{
		case(0):	pos.x = centerPos.x - (FLOOR_OFFSET[(int)m_stage].x);
			break;
		case(1):	pos.x = centerPos.x;
			break;
		case(2):	pos.x = centerPos.x + FLOOR_OFFSET[(int)m_stage].x;
			break;
		}

		//Z座標
		switch (i / 3)
		{
		case(0):	pos.z = centerPos.z - (FLOOR_OFFSET[(int)m_stage].y);
			break;
		case(1):	pos.z = centerPos.z;
			break;
		case(2):	pos.z = centerPos.z + FLOOR_OFFSET[(int)m_stage].y;
			break;
		}

		m_Transform[i].fPos = { pos.x, -0.1f, pos.z };	//座標を確定
	}
}

/* ========================================
   カメラセット関数
   ----------------------------------------
   内容：他のオブジェクトと同じカメラをセットする
   ----------------------------------------
   引数：カメラのポインタ
   ----------------------------------------
   戻値：なし
======================================== */
void CFloor::SetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;
}

/* ========================================
   床モデルセット関数
   ----------------------------------------
   内容：ステージ毎に違う見た目の床モデルをセットする
   ----------------------------------------
   引数1：ステージの種類
   ----------------------------------------
   戻値：なし
======================================== */
void CFloor::SetFloorModel()
{
	//床のモデル読み込み
	m_pModel = new Model;
	switch (m_stage)
	{
	case CFloor::Stage1:
		if (!m_pModel->Load("Assets/Model/floor/Stage1/floor_grass.fbx", 1.0f, Model::XFlip)) {		//倍率と反転は省略可
			MessageBox(NULL, "floor", "Error", MB_OK);	//ここでエラーメッセージ表示
		}
		break;
	case CFloor::Stage2:
		if (!m_pModel->Load("Assets/Model/floor/Stage2/floor_cave.fbx", 1.0f, Model::XFlip)) {		//倍率と反転は省略可
			MessageBox(NULL, "floor", "Error", MB_OK);	//ここでエラーメッセージ表示
		}
		break;
	case CFloor::Stage3:
		if (!m_pModel->Load("Assets/Model/floor/Stage3/floor_StainedGlass.FBX", 1.0f, Model::XFlip)) {		//倍率と反転は省略可
			MessageBox(NULL, "floor", "Error", MB_OK);	//ここでエラーメッセージ表示
		}
		break;
	}

	m_pModel->SetVertexShader(m_pVS);
}
