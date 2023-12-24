/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	UNION管理実装
	------------------------------------
	UnionManager.cpp
	------------------------------------
	作成者	takagi

	変更履歴
	・2023/12/19 制作 takagi
	・2023/12/24 サイズ・フレーム変更 takagi

========================================== */

// =============== インクルード ===================
#include "UnionManager.h"	//自身のヘッダ
#include "CameraDef.h"		//疑似カメラ
#include "Slime_2.h"		//処理対象
#include "Slime_3.h"		//処理対象
#include "Slime_4.h"		//処理対象

#if _DEBUG
#include <Windows.h>		//メッセージボックス用
#endif

// =============== 定数定義 =====================
const std::string VS_PASS("Assets/Shader/VsUnionManager.cso");				//テクスチャのパス名
const std::string PS_PASS("Assets/Shader/PsUnionManager.cso");				//テクスチャのパス名
const std::string TEX_PASS_SLIME2("Assets/Texture/Union/Union_Green.png");	//テクスチャのパス名
const std::string TEX_PASS_SLIME3("Assets/Texture/Union/Union_Yellow.png");	//テクスチャのパス名
const std::string TEX_PASS_SLIME4("Assets/Texture/Union/Union_Red.png");	//テクスチャのパス名
const TPos3d<float> INIT_POS(640.0f, 360.0f, 0.0f);						//位置初期化
const TTriType<float> INIT_SCALE(4000.0f, 4000.0f, 0.0f);				//初期拡縮
const TTriType<float> INIT_RADIAN(0.0f);								//初期回転
const TTriType<int> FRAME_FADE_MAX(100, 60, 70);						//フェードにかけるフレーム数	x:アウト, y:ストップ, z:イン
const int FRAME_MIN(0);													//フェード時間の最小
const int FRAME_OUT_PATTERN_1_FIN(50);									//フェードアウト開始から拡縮が留まるまでのフレーム数
const int FRAME_OUT_PATTERN_2_FIN(80);									//フェードアウト開始から拡縮が留まり終わるまでのフレーム数
const float SCALE_OUT_MIN(500.0f);										//フェードアウト最小サイズ	uvの都合上、値が大きい程サイズが小さくなる
const float SCALE_IN_MIN(600.0f);										//フェードイン最小サイズ	uvの都合上、値が大きい程サイズが小さくなる
const float SCALE_OUT_STAY(10.0f);										//フェードアウト拡縮が一時収まるときのサイズ
const float SCALE_OUT_MAX(0.0f);										//フェード最大サイズ	uvの都合上、値が小さい程サイズが大きくなる
const float SCALE_IN_MAX(0.0f);											//フェード最大サイズ	uvの都合上、値が小さい程サイズが大きくなる
const float ROTATE_ACCEL_RATE(8.0f);									//角速度増加割合
const std::map<size_t, TTriType<float>>MAP_SCALE = {
	{ typeid(CSlime_2).hash_code(), {1272.0f * 0.003f, 636.0f * 0.003f, 0.0f} },	//スライム2誕生用
	{ typeid(CSlime_3).hash_code(), {1272.0f * 0.004f, 636.0f * 0.004f, 0.0f} },	//スライム3誕生用
	{ typeid(CSlime_4).hash_code(), {1272.0f * 0.005f, 636.0f * 0.005f, 0.0f} },	//スライム4誕生用
};	//UNIONの大きさ
const std::map<size_t, int>MAP_FRAME = {
	{ typeid(CSlime_2).hash_code(), 60 },	//スライム2誕生用
	{ typeid(CSlime_3).hash_code(), 90 },	//スライム3誕生用
	{ typeid(CSlime_4).hash_code(), 120 },	//スライム4誕生用
};	//UNION表示時間

// =============== グローバル変数宣言 =====================
int CUnionManager::ms_nCntUnionManager;					//自身の生成数
std::map<size_t, Texture*> CUnionManager::ms_pTexture;	//テクスチャ情報

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：生成時に行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
CUnionManager::CUnionManager()
	:m_ucFlag(0x00)		//フラグ
	,m_pCamera(nullptr)	//カメラ
{
	// =============== 静的作成 ===================
	if (0 == ms_nCntUnionManager)	//現在、他にこのクラスが作成されていない時
	{
		// =============== テクスチャリセット ===================
		if (ms_pTexture.size() > 0)	//まだコンテナに残っている時
		{
			for (auto Iterator = ms_pTexture.begin(); Iterator != ms_pTexture.end();)
			{
				if (Iterator->second)	//ヌルチェック
				{
					SAFE_DELETE(Iterator->second);	//削除
				}
				Iterator = ms_pTexture.erase(Iterator);	//イテレータ削除
			}
		}

		// =============== テクスチャ作成 ===================
		ms_pTexture.insert(std::pair<size_t, Texture*>(typeid(CSlime_2).hash_code(), new Texture));	//コンテナ格納
#if _DEBUG
		if (FAILED(ms_pTexture.at(typeid(CSlime_2).hash_code())->Create(TEX_PASS_SLIME2.c_str())))	//新規テクスチャ登録
		{
			std::string ErrorSpot = typeid(*this).name(); ErrorSpot += "->Error";					//エラー箇所
			MessageBox(nullptr, "テクスチャの読み込みに失敗しました", ErrorSpot.c_str(), MB_OK);	//エラー通知
		}
#else
		ms_pTexture.at(typeid(CSlime_2).hash_code())->Create(TEX_PASS_SLIME2.c_str());	//新規テクスチャ登録
#endif
		ms_pTexture.insert(std::pair<size_t, Texture*>(typeid(CSlime_3).hash_code(), new Texture));	//コンテナ格納
#if _DEBUG
		if (FAILED(ms_pTexture.at(typeid(CSlime_3).hash_code())->Create(TEX_PASS_SLIME3.c_str())))	//新規テクスチャ登録
		{
			std::string ErrorSpot = typeid(*this).name(); ErrorSpot += "->Error";					//エラー箇所
			MessageBox(nullptr, "テクスチャの読み込みに失敗しました", ErrorSpot.c_str(), MB_OK);	//エラー通知
		}
#else
		ms_pTexture.at(typeid(CSlime_3).hash_code())->Create(TEX_PASS_SLIME3.c_str());	//新規テクスチャ登録
#endif
		ms_pTexture.insert(std::pair<size_t, Texture*>(typeid(CSlime_4).hash_code(), new Texture));	//コンテナ格納
#if _DEBUG
		if (FAILED(ms_pTexture.at(typeid(CSlime_4).hash_code())->Create(TEX_PASS_SLIME4.c_str())))	//新規テクスチャ登録
		{
			std::string ErrorSpot = typeid(*this).name(); ErrorSpot += "->Error";					//エラー箇所
			MessageBox(nullptr, "テクスチャの読み込みに失敗しました", ErrorSpot.c_str(), MB_OK);	//エラー通知
		}
#else
		ms_pTexture.at(typeid(CSlime_4).hash_code())->Create(TEX_PASS_SLIME4.c_str());	//新規テクスチャ登録
#endif
	}
}

/* ========================================
	コピーコンストラクタ関数
	-------------------------------------
	内容：コピー時に行う処理
	-------------------------------------
	引数1：const CUnionManager & Obj：コピー元の参照
	-------------------------------------
	戻値：なし
=========================================== */
//CUnionManager::CUnionManager(const CUnionManager & Obj)
//{
//}

/* ========================================
	デストラクタ関数
	-------------------------------------
	内容：破棄時に行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
CUnionManager::~CUnionManager()
{
	// =============== 終了 ===================
	ms_nCntUnionManager--;				//自身の数カウント
	for (auto Iterator = m_pUnion.end(); Iterator != m_pUnion.begin();)
	{
		if (*--Iterator)	//ヌルチェック
		{
			SAFE_DELETE(*Iterator);	//削除
		}
		Iterator = m_pUnion.erase(Iterator);	//イテレータ削除
	}
	if (ms_nCntUnionManager == 0)
	{
		for (auto Iterator = ms_pTexture.begin(); Iterator != ms_pTexture.end();)
		{
			if (Iterator->second)	//ヌルチェック
			{
				SAFE_DELETE(Iterator->second);	//削除
			}
			Iterator = ms_pTexture.erase(Iterator);	//イテレータ削除
		}
	}
}

/* ========================================
	更新関数
	-------------------------------------
	内容：更新処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CUnionManager::Update()
{
	// =============== 削除 ===================
	for (auto Iterator = m_pUnion.begin(); Iterator != m_pUnion.end();)
	{
		if (*Iterator)	//ヌルチェック
		{
			(*Iterator)->Update();	//更新
			if ((*Iterator)->IsFin())	//役目を終えたもの
			{
				SAFE_DELETE(*Iterator);					//削除
				Iterator = m_pUnion.erase(Iterator);	//イテレータ削除
			}
			else
			{
				Iterator++;	//イテレータ調整
			}
		}
	}
}

/* ========================================
	描画関数
	-------------------------------------
	内容：描画処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CUnionManager::Draw()
{
	// =============== 描画 ===================
	for (auto Iterator = m_pUnion.begin(); Iterator != m_pUnion.end(); Iterator++)
	{
		if (*Iterator)	//ヌルチェック
		{
			(*Iterator)->Draw();	//描画
		}
	}
}

/* ========================================
	カメラセット関数
	-------------------------------------
	内容：カメラの登録
	-------------------------------------
	引数1：CCamera * pCamera：カメラ
	-------------------------------------
	戻値：なし
=========================================== */
void CUnionManager::SetCamera(CCamera * pCamera)
{
	// =============== 初期化 ===================
	m_pCamera = pCamera;	//カメラ初期化
}

/* ========================================
	UNION生成関数
	-------------------------------------
	内容：引数のクラスにあわせてUNIONを生成
	-------------------------------------
	引数1：const size_t & HashTypeId：型のハッシュコード
	引数2：const TPos3d<float> & fPos：型のハッシュコード
	-------------------------------------
	戻値：なし
=========================================== */
void CUnionManager::MakeUnion(const size_t & HashTypeId, const TPos3d<float> & fPos)
{
	// =============== 検査 ===================
	if (ms_pTexture.find(HashTypeId) == ms_pTexture.end() || MAP_SCALE.find(HashTypeId) == MAP_SCALE.end())
	{
		// =============== 終了 ===================
		return;	//処理中断
	}
	
	// =============== 変数宣言 ===================
	CUnion* Temp = new CUnion(MAP_FRAME.at(HashTypeId));	//登録したい情報

	// =============== 情報登録 ===================
	Temp->SetTexture(ms_pTexture.at(HashTypeId));	//テクスチャ登録
	Temp->SetPos(fPos);								//位置登録
	Temp->SetSize(MAP_SCALE.at(HashTypeId));		//大きさ登録
	Temp->SetCamera(m_pCamera);						//カメラセッタ

	// =============== コンテナ登録 ===================
	m_pUnion.push_back(Temp);	//UNION追加
}