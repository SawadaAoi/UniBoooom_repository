/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ステージセレクト実装
	---------------------------------------
	SelectStage.cpp

	作成者
			takagi
			nieda

	変更履歴
	・2023/11/16 制作 takagi
	・2023/12/12 ステージセレクトを追加　yamamoto
	・2024/01/26 拡縮実装 takagi
	・2024/01/26 選択、決定SE追加 suzumura
	・2024/01/28 落下実装 takagi

========================================== */

// =============== インクルード ===================
#include "SelectStage.h"	//自身のヘッダ
#include "Input.h"			//入力管理
#define _USE_MATH_DEFINES	//math.hの定義使用
#include <math.h>			//M_PI使用
#include <algorithm>		//clamp使用
#include "Delete.h"			//削除マクロ

// =============== 定数定義 =======================
const TDiType<int> HISCORE_NUM_SPLIT = { 5,2 };		// ハイスコア数字画像の分割数
const TDiType<float> HISCORE_NUM_UVSCALE = { 1.0f / HISCORE_NUM_SPLIT.x ,1.0f / HISCORE_NUM_SPLIT.y };		// ハイスコア数字画像の分割数

const TTriType<float> HISCORE_BASE_POS[3] = {	// ハイスコアのステージ別の位置(背景、テキスト、スコアをまとめて)
	{220.0f, 150.0f, 0.0f},
	{600.0f, 550.0f, 0.0f},
	{1000.0f, 150.0f, 0.0f},
};

/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
CSelectStage::CSelectStage()
	: m_fSelectSize(INIT_SIZE_ARR_LET.x)	//選択しているオブジェクトの大きさ
	, m_bStickFlg(false)					//スティックの傾倒有無
	, m_pFrameCntFall(nullptr)			//手配書落下用フレームカウンタ
	, m_pFrameCntScale(nullptr)			//拡縮用フレームカウンタ
	, m_bCntUpDwn(false)					//カウントアップ・ダウン
	, m_eNextType(CScene::E_TYPE_STAGE1)	//初期の次のシーン
	, m_nButtonAlphaCnt(0)			//拡縮用フレームカウンタ
	, m_pSE{ nullptr,nullptr }
	, m_pSESpeaker{ nullptr ,nullptr }
{
	// =============== 動的確保 =====================
	for (int nIdx = 0; nIdx < static_cast<int>(E_2D_OBJECT_MAX); nIdx++)
	{
		if (m_p2dObject.find(static_cast<E_2D_OBJECT>(nIdx)) != m_p2dObject.end())	//アクセス・ヌルチェック
		{
			// =============== 中断 =====================
			continue;	//次の値の処理へ
		}
		m_p2dObject.emplace(static_cast<E_2D_OBJECT>(nIdx), new C2dPolygon());
	}
	m_pFrameCntScale = new CFrameCnt(CHANGE_SCALE_HALF_TIME, m_bCntUpDwn);	//フレーム初期化

	// =============== 初期化 =====================
	for (int nIdx = 0; nIdx < static_cast<int>(m_p2dObject.size()); nIdx++)
	{
		if (m_p2dObject.find(static_cast<E_2D_OBJECT>(nIdx)) != m_p2dObject.end() && m_p2dObject.at(static_cast<E_2D_OBJECT>(nIdx)))	//アクセス・ヌルチェック
		{
			m_p2dObject.at(static_cast<E_2D_OBJECT>(nIdx))->SetPos(INIT_MAP_POS.at(static_cast<E_2D_OBJECT>(nIdx)));					//位置セット
			m_p2dObject.at(static_cast<E_2D_OBJECT>(nIdx))->SetRotate(INIT_MAP_ROTATE.at(static_cast<E_2D_OBJECT>(nIdx)));				//回転セット
			m_p2dObject.at(static_cast<E_2D_OBJECT>(nIdx))->SetTexture(MAP_TEXTURE_FILE.at(static_cast<E_2D_OBJECT>(nIdx)).c_str());	//テクスチャセット
			m_p2dObject.at(static_cast<E_2D_OBJECT>(nIdx))->SetSize(INIT_MAP_SIZE.at(static_cast<E_2D_OBJECT>(nIdx)));					//拡縮セット
		}
	}

	//=== サウンドファイル読み込み =====
	LoadSound();	

	// データ受け継ぎ
	m_Data.Load();	//ファイルに上がっている情報を読み込む

}	


/* ========================================
	デストラクタ
	----------------------------------------
	内容：破棄時に行う処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
CSelectStage::~CSelectStage()
{
	// 破棄処理
	SAFE_DELETE_POINTER_MAP(m_p2dObject);	//2dオブジェクト削除
	SAFE_DELETE(m_pFrameCntScale);			//カウンタ削除
	SAFE_DELETE(m_pFrameCntFall);			//カウンタ削除
}

/* ========================================
	更新関数
	----------------------------------------
	内容：更新処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CSelectStage::Update()
{

	// =============== 分岐 =====================
	if (!m_pFrameCntFall)	//手配書が落ちていない=選択中
	{
		Select();

		// =============== 拡縮更新 =====================
		if (m_pFrameCntScale)	//ヌルチェック
		{
			m_pFrameCntScale->Count();	//カウント進行
			m_fSelectSize = -(cosf(static_cast<float>(M_PI) * m_pFrameCntScale->GetRate()) - 1.0f) / 2.0f * (MAX_SIZE_ARR_LET - MIN_SIZE_ARR_LET) + MIN_SIZE_ARR_LET;	//イージングを使った大きさ変更
			if (m_pFrameCntScale->IsFin())	//カウント完了
			{
				m_bCntUpDwn ^= 1;													//カウントアップダウン逆転
				SAFE_DELETE(m_pFrameCntScale);											//カウンタ削除
				m_pFrameCntScale = new CFrameCnt(CHANGE_SCALE_HALF_TIME, m_bCntUpDwn);	//カウントアップ・ダウン
			}
		}

		// =============== 拡縮変更 =====================
		switch (m_eNextType)	//選択されているものを変更
		{	//TODO:アクセス・ヌルチェック
		case CScene::E_TYPE_STAGE1:	//ステージ1
			m_p2dObject.at(E_2D_OBJECT_STAGE_1_LEAVE)->SetSize({ m_fSelectSize * ASPECT_RATE_ARR_LET, m_fSelectSize, 1.0f });	//ステージ1の手配書
			m_p2dObject.at(E_2D_OBJECT_STAGE_1_REMINE)->SetSize({ m_fSelectSize * ASPECT_RATE_ARR_LET, m_fSelectSize, 1.0f });	//ステージ1の手配書
			break;	//分岐処理終了
		case CScene::E_TYPE_STAGE2:	//ステージ2
			m_p2dObject.at(E_2D_OBJECT_STAGE_2_LEAVE)->SetSize({ m_fSelectSize * ASPECT_RATE_ARR_LET, m_fSelectSize, 1.0f });	//ステージ2の手配書
			m_p2dObject.at(E_2D_OBJECT_STAGE_2_REMINE)->SetSize({ m_fSelectSize * ASPECT_RATE_ARR_LET, m_fSelectSize, 1.0f });	//ステージ2の手配書
			break;	//分岐処理終了
		case CScene::E_TYPE_STAGE3:	//ステージ3
			m_p2dObject.at(E_2D_OBJECT_STAGE_3_LEAVE)->SetSize({ m_fSelectSize * ASPECT_RATE_ARR_LET, m_fSelectSize, 1.0f });	//ステージ3の手配書
			m_p2dObject.at(E_2D_OBJECT_STAGE_3_REMINE)->SetSize({ m_fSelectSize * ASPECT_RATE_ARR_LET, m_fSelectSize, 1.0f });	//ステージ3の手配書
			break;	//分岐処理終了			
		}
	}
	else
	{	//手配書が落ちている=選択完了

		// =============== 検査 =====================
		if (m_pFrameCntFall->IsFin())	//カウント完了
		{
			// =============== フラグ操作 =====================
			m_bFinish = true;	//シーン終了

			// =============== 終了 =====================
			SAFE_DELETE(m_pFrameCntFall);	//カウンタ削除
			return;							//処理中断
		}

		// =============== カウント =====================
		m_pFrameCntFall->Count();	//カウント進行

		// =============== 変数宣言 =====================
		TTriType<float> fPos = 0.0f;	//位置
		auto EasingFunc = [this, &fPos](const TTriType<float>& fBasePos)->void {
			// =============== 変数宣言 =====================
			float fCompare = 7.5625;	//比較対象

			// =============== 初期化 =====================
			fPos = fBasePos;

			// =============== 更新 =====================
			fPos.y = (1.0f - powf(m_pFrameCntFall->GetRate(), 4.0f)) * (-m_fSelectSize / 2.0f - fBasePos.y) + fBasePos.y;	//y値更新	GetRate()は1to0
		};	//初期位置・初期サイズをもとにfPosに落下後位置を格納

		// =============== 初期化 =====================
		switch (m_eNextType)	//選択されているものを変更
		{	//TODO:アクセス・ヌルチェック
		case CScene::E_TYPE_STAGE1:	//ステージ1
			EasingFunc(INIT_MAP_POS.at(E_2D_OBJECT_STAGE_1_LEAVE));	//ステージ1の手配書			
			break;	//分岐処理終了
		case CScene::E_TYPE_STAGE2:	//ステージ2
			EasingFunc(INIT_MAP_POS.at(E_2D_OBJECT_STAGE_2_LEAVE));	//ステージ2の手配書	
			break;	//分岐処理終了
		case CScene::E_TYPE_STAGE3:	//ステージ3
			EasingFunc(INIT_MAP_POS.at(E_2D_OBJECT_STAGE_3_LEAVE));	//ステージ3の手配書	
			break;	//分岐処理終了
		}

		// =============== 落下位置更新 =====================
		switch (m_eNextType)	//選択されているものを変更
		{	//TODO:アクセス・ヌルチェック
		case CScene::E_TYPE_STAGE1:	//ステージ1
			m_p2dObject.at(E_2D_OBJECT_STAGE_1_LEAVE)->SetPos(fPos);	//ステージ1の手配書
			break;	//分岐処理終了
		case CScene::E_TYPE_STAGE2:	//ステージ2
			m_p2dObject.at(E_2D_OBJECT_STAGE_2_LEAVE)->SetPos(fPos);	//ステージ2の手配書
			break;	//分岐処理終了
		case CScene::E_TYPE_STAGE3:	//ステージ3
			m_p2dObject.at(E_2D_OBJECT_STAGE_3_LEAVE)->SetPos(fPos);	//ステージ3の手配書
			break;	//分岐処理終了
		}
	}

	m_nButtonAlphaCnt++;	//カウント進行

}

/* ========================================
	描画関数
	----------------------------------------
	内容：描画処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
	======================================== */
void CSelectStage::Draw() //const
{
	// =============== 描画 =====================	//TODO:アクセス・ヌルチェック


	m_p2dObject[E_2D_OBJECT_BACK_GROUND]->Draw();		//背景描画

	HiscoreDraw();	// ハイスコア関連

	switch (m_eNextType)	//選択されているものを変更
	{	//TODO:アクセス・ヌルチェック
	case CScene::E_TYPE_STAGE1:	//ステージ1
		m_p2dObject.at(E_2D_OBJECT_STAGE_2_LEAVE)->Draw();	//ステージ2の手配書描画
		m_p2dObject.at(E_2D_OBJECT_STAGE_2_REMINE)->Draw();	//ステージ2の手配書描画
		m_p2dObject.at(E_2D_OBJECT_STAGE_3_LEAVE)->Draw();	//ステージ3の手配書描画
		m_p2dObject.at(E_2D_OBJECT_STAGE_3_REMINE)->Draw();	//ステージ3の手配書描画
		m_p2dObject.at(E_2D_OBJECT_STAGE_1_LEAVE)->Draw();	//ステージ1の手配書描画
		m_p2dObject.at(E_2D_OBJECT_STAGE_1_REMINE)->Draw();	//ステージ1の手配書描画
		break;	//分岐処理終了
	case CScene::E_TYPE_STAGE2:	//ステージ2
		m_p2dObject.at(E_2D_OBJECT_STAGE_1_LEAVE)->Draw();	//ステージ1の手配書描画
		m_p2dObject.at(E_2D_OBJECT_STAGE_1_REMINE)->Draw();	//ステージ1の手配書描画
		m_p2dObject.at(E_2D_OBJECT_STAGE_3_LEAVE)->Draw();	//ステージ3の手配書描画
		m_p2dObject.at(E_2D_OBJECT_STAGE_3_REMINE)->Draw();	//ステージ3の手配書描画
		m_p2dObject.at(E_2D_OBJECT_STAGE_2_LEAVE)->Draw();	//ステージ2の手配書描画
		m_p2dObject.at(E_2D_OBJECT_STAGE_2_REMINE)->Draw();	//ステージ2の手配書描画
		break;	//分岐処理終了
	case CScene::E_TYPE_STAGE3:	//ステージ3
		m_p2dObject.at(E_2D_OBJECT_STAGE_1_LEAVE)->Draw();	//ステージ1の手配書描画
		m_p2dObject.at(E_2D_OBJECT_STAGE_1_REMINE)->Draw();	//ステージ1の手配書描画
		m_p2dObject.at(E_2D_OBJECT_STAGE_2_LEAVE)->Draw();	//ステージ2の手配書描画
		m_p2dObject.at(E_2D_OBJECT_STAGE_2_REMINE)->Draw();	//ステージ2の手配書描画
		m_p2dObject.at(E_2D_OBJECT_STAGE_3_LEAVE)->Draw();	//ステージ3の手配書描画
		m_p2dObject.at(E_2D_OBJECT_STAGE_3_REMINE)->Draw();	//ステージ3の手配書描画
		break;	//分岐処理終了
	}
	m_p2dObject[E_2D_OBJECT_BACK_SCENE_NAME]->Draw();	//シーン名描画

	// 「タイトルへ戻る」関連
	m_p2dObject[E_2D_OBJECT_TO_TITLE_TEXT]->Draw();		// タイトルへテキスト

	m_p2dObject[E_2D_OBJECT_TO_TITLE_BUTTON]->SetAlpha(fabs(cosf(m_nButtonAlphaCnt * 0.03f)));

	m_p2dObject[E_2D_OBJECT_TO_TITLE_BUTTON]->Draw();	// Aボタンテキスト
}
/* ========================================
	ステージを選択する関数
	----------------------------------------
	内容：ステージを選択する
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
	======================================== */
void CSelectStage::Select()
{
	// ゲームコントローラー
	if (GetUseVController())
	{
		TPos3d<float> fMoveInput;	// スティックの入力値を入れる変数
		fMoveInput.x = IsStickLeft().x;// コントローラーの左スティックの傾きを取得

		// 左スティックを倒している
		if (!m_bStickFlg)
		{
			// スティック左
			if (fMoveInput.x < 0.0f)
			{
				if (m_eNextType != CScene::E_TYPE_STAGE1)	//候補の最低値でないとき
				{	//TODO:アクセス・ヌルチェック
					//TODO:段数減らす
					switch (m_eNextType)	//新しく選択されたものを変更
					{
						case CScene::E_TYPE_STAGE1:	//ステージ1
							m_p2dObject.at(E_2D_OBJECT_STAGE_1_LEAVE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_1_LEAVE));	//ステージ1の手配書
							m_p2dObject.at(E_2D_OBJECT_STAGE_1_REMINE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_1_REMINE));	//ステージ1の手配書
							break;	//分岐処理終了
						case CScene::E_TYPE_STAGE2:	//ステージ1
							m_p2dObject.at(E_2D_OBJECT_STAGE_2_LEAVE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_2_LEAVE));	//ステージ2の手配書
							m_p2dObject.at(E_2D_OBJECT_STAGE_2_REMINE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_2_REMINE));	//ステージ2の手配書
							break;	//分岐処理終了
						case CScene::E_TYPE_STAGE3:	//ステージ1
							m_p2dObject.at(E_2D_OBJECT_STAGE_3_LEAVE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_3_LEAVE));	//ステージ3の手配書
							m_p2dObject.at(E_2D_OBJECT_STAGE_3_REMINE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_3_REMINE));	//ステージ3の手配書
							break;	//分岐処理終了
					}
					m_eNextType = static_cast<CScene::E_TYPE>(m_eNextType - 1);	//次のシーン番号を選択

				//===== SEの再生 =======
					PlaySE(SE_CHOOSE);
				}

			}
			// スティック右
			else if ( 0.0f < fMoveInput.x )
			{
				if (m_eNextType != CScene::E_TYPE_STAGE3)	//候補の最大値でないとき
				{	//TODO:アクセス・ヌルチェック
					//TODO:段数減らす
					switch (m_eNextType)	//新しく選択されたものを変更
					{
					case CScene::E_TYPE_STAGE1:	//ステージ1
						m_p2dObject.at(E_2D_OBJECT_STAGE_1_LEAVE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_1_LEAVE));	//ステージ1の手配書
						m_p2dObject.at(E_2D_OBJECT_STAGE_1_REMINE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_1_REMINE));	//ステージ1の手配書
						break;	//分岐処理終了
					case CScene::E_TYPE_STAGE2:	//ステージ1
						m_p2dObject.at(E_2D_OBJECT_STAGE_2_LEAVE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_2_LEAVE));	//ステージ2の手配書
						m_p2dObject.at(E_2D_OBJECT_STAGE_2_REMINE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_2_REMINE));	//ステージ2の手配書
						break;	//分岐処理終了
					case CScene::E_TYPE_STAGE3:	//ステージ1
						m_p2dObject.at(E_2D_OBJECT_STAGE_3_LEAVE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_3_LEAVE));	//ステージ3の手配書
						m_p2dObject.at(E_2D_OBJECT_STAGE_3_REMINE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_3_REMINE));	//ステージ3の手配書
						break;	//分岐処理終了
					}
					m_eNextType = static_cast<CScene::E_TYPE>(m_eNextType + 1);	//次のシーン番号を選択

				//===== SEの再生 =======
					PlaySE(SE_CHOOSE);
				}

			}
		}
		// 左スティックがニュートラル
		else
		{
			if (fabs(fMoveInput.x) <= 0.5f )
			{
				m_bStickFlg = false;
			}
		}
	}
	else
	{
		//キーボード入力
		if (IsKeyTrigger('A'))
		{
			if (m_eNextType != CScene::E_TYPE_STAGE1)	//候補の最低値でないとき
			{	//TODO:アクセス・ヌルチェック
				//TODO:段数減らす
				switch (m_eNextType)	//新しく選択されたものを変更
				{
				case CScene::E_TYPE_STAGE1:	//ステージ1
					m_p2dObject.at(E_2D_OBJECT_STAGE_1_LEAVE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_1_LEAVE));	//ステージ1の手配書
					m_p2dObject.at(E_2D_OBJECT_STAGE_1_REMINE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_1_REMINE));	//ステージ1の手配書
					break;	//分岐処理終了
				case CScene::E_TYPE_STAGE2:	//ステージ1
					m_p2dObject.at(E_2D_OBJECT_STAGE_2_LEAVE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_2_LEAVE));	//ステージ2の手配書
					m_p2dObject.at(E_2D_OBJECT_STAGE_2_REMINE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_2_REMINE));	//ステージ2の手配書
					break;	//分岐処理終了
				case CScene::E_TYPE_STAGE3:	//ステージ1
					m_p2dObject.at(E_2D_OBJECT_STAGE_3_LEAVE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_3_LEAVE));	//ステージ3の手配書
					m_p2dObject.at(E_2D_OBJECT_STAGE_3_REMINE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_3_REMINE));	//ステージ3の手配書
					break;	//分岐処理終了
				}
				m_eNextType = static_cast<CScene::E_TYPE>(m_eNextType - 1);	//次のシーン番号を選択
			}
			m_bStickFlg = true;	//スティック傾倒中

				//===== SEの再生 =======
			PlaySE(SE_CHOOSE);
		}
		if (IsKeyTrigger('D'))
		{
			if (m_eNextType != CScene::E_TYPE_STAGE3)	//候補の最大値でないとき
			{	//TODO:アクセス・ヌルチェック
				//TODO:段数減らす
				switch (m_eNextType)	//新しく選択されたものを変更
				{
				case CScene::E_TYPE_STAGE1:	//ステージ1
					m_p2dObject.at(E_2D_OBJECT_STAGE_1_LEAVE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_1_LEAVE));	//ステージ1の手配書
					m_p2dObject.at(E_2D_OBJECT_STAGE_1_REMINE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_1_REMINE));	//ステージ1の手配書
					break;	//分岐処理終了
				case CScene::E_TYPE_STAGE2:	//ステージ1
					m_p2dObject.at(E_2D_OBJECT_STAGE_2_LEAVE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_2_LEAVE));	//ステージ2の手配書
					m_p2dObject.at(E_2D_OBJECT_STAGE_2_REMINE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_2_REMINE));	//ステージ2の手配書
					break;	//分岐処理終了
				case CScene::E_TYPE_STAGE3:	//ステージ1
					m_p2dObject.at(E_2D_OBJECT_STAGE_3_LEAVE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_3_LEAVE));	//ステージ3の手配書
					m_p2dObject.at(E_2D_OBJECT_STAGE_3_REMINE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_3_REMINE));	//ステージ3の手配書
					break;	//分岐処理終了
				}
				m_eNextType = static_cast<CScene::E_TYPE>(m_eNextType + 1);	//次のシーン番号を選択
			}
			m_bStickFlg = true;	//スティック傾倒中

			//===== SEの再生 =======
			PlaySE(SE_CHOOSE);
		}
	}

	if (IsKeyTrigger(VK_SPACE) || IsKeyTriggerController(BUTTON_B) && m_pFrameCntFall)
	{
		m_pFrameCntFall = new CFrameCnt(FALL_TIME_ARR_LET);	//カウンタ作成
		//===== SEの再生 =======
		PlaySE(SE_DECISION);
	}

	if (IsKeyTrigger('B') || IsKeyTriggerController(BUTTON_A) && m_pFrameCntFall)
	{
		m_eNextType = E_TYPE::E_TYPE_TITLE;
		m_bFinish = true;
	}
}

/* ========================================
	種類ゲッタ
	----------------------------------------
	内容：自身がステージセレクトであることを示す
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：自身の種類
=========================================== */
CSelectStage::E_TYPE CSelectStage::GetType() const
{
	// =============== 提供 ===================
	return CSelectStage::E_TYPE_SELECT_STAGE;	//自身の種類
}

/* ========================================
	次シーンゲッタ
	----------------------------------------
	内容：遷移したいシーンが何かを示す
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：遷移先シーンの種類
=========================================== */
CSelectStage::E_TYPE CSelectStage::GetNext() const
{
	// =============== 提供 ===================
	return m_eNextType;	//遷移先シーンの種類
}

/* ========================================
   セレクトステージ用SE読み込み関数
   ----------------------------------------
   内容：セレクトステージ用のSEのファイルを読み込む
   ----------------------------------------
   引数：無し
   ----------------------------------------
   戻値：無し
======================================== */
void CSelectStage::LoadSound()
{
	//SEの読み込み
	for (int i = 0; i < SE_MAX; i++)
	{
		m_pSE[i] = CSound::LoadSound(m_sSEFile[i].c_str());
		if (!m_pSE[i])
		{
			MessageBox(NULL, m_sSEFile[i].c_str(), "Error", MB_OK);	//ここでエラーメッセージ表示
		}
	}
}

/* ========================================
	SEの再生関数
	----------------------------------------
	内容：SEの再生
	----------------------------------------
	引数1：SEの種類(enum)
	引数2：音量
	----------------------------------------
	戻値：なし
======================================== */
void CSelectStage::PlaySE(SE se, float volume)
{
	m_pSESpeaker[se] = CSound::PlaySound(m_pSE[se]);	//SE再生
	m_pSESpeaker[se]->SetVolume(volume);				//音量の設定
}

void CSelectStage::HiscoreParamSet()
{
}

void CSelectStage::HiscoreDraw()
{
	for (int i = 0; i < 3; i++)
	{
		m_p2dObject.at(E_2D_OBJECT_HISCORE_BG)->SetPos({
		INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_BG).x + HISCORE_BASE_POS[i].x,
		INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_BG).y + HISCORE_BASE_POS[i].y,
		INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_BG).z ,
			});
		m_p2dObject.at(E_2D_OBJECT_HISCORE_TEXT)->SetPos({
			INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_TEXT).x + HISCORE_BASE_POS[i].x,
			INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_TEXT).y + HISCORE_BASE_POS[i].y,
			INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_TEXT).z ,
			});

		m_p2dObject.at(E_2D_OBJECT_HISCORE_BG)->Draw();
		m_p2dObject.at(E_2D_OBJECT_HISCORE_TEXT)->Draw();

		TTriType<float> NumBasePos = {
			INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_NUM).x + HISCORE_BASE_POS[i].x,
			INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_NUM).y + HISCORE_BASE_POS[i].y,
			INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_NUM).z ,
		};

		DispNum(m_Data.nHighScore[i], 5, NumBasePos);
	}

	
}



/* ========================================
	数字描画関数
	----------------------------------------
	内容：数字を描画する
	----------------------------------------
	引数1：描画する数字
	引数2：桁数
	引数3：位置
	引数4：大きさ
	引数5：数字間の大きさ
	----------------------------------------
	戻値：なし
=========================================== */
void CSelectStage::DispNum(int dispNum, int nDigits, TTriType<float> pos)
{

	std::vector<int> digitArray;
	DirectX::XMFLOAT4X4 mat;
	int Num = dispNum;


	NumStorage(&digitArray, dispNum, nDigits);

	for (int i = 0; i < digitArray.size(); i++)
	{
		float width = (INIT_MAP_SIZE.at(E_2D_OBJECT_HISCORE_NUM).x * 0.8f) * i;
		
		int x = digitArray[i] % HISCORE_NUM_SPLIT.x;	//ここ名前募集します
		int y = digitArray[i] / HISCORE_NUM_SPLIT.x;	//配列に入ってる数字の場所を計算してます

		m_p2dObject.at(E_2D_OBJECT_HISCORE_NUM)->SetUvScale(HISCORE_NUM_UVSCALE);
		m_p2dObject.at(E_2D_OBJECT_HISCORE_NUM)->SetUvOffset({ HISCORE_NUM_UVSCALE.x * x, HISCORE_NUM_UVSCALE.y * y });

		m_p2dObject.at(E_2D_OBJECT_HISCORE_NUM)->SetPos({ pos.x - width , pos.y, pos.z });
		m_p2dObject.at(E_2D_OBJECT_HISCORE_NUM)->Draw();
	}
}


/* ========================================
	数字桁格納処理
	----------------------------------------
	内容：配列に数字を桁ごとに格納する
	----------------------------------------
	引数1：桁格納配列
	引数1：格納する数字
	引数1：桁数
	----------------------------------------
	戻値：無し
=========================================== */
void CSelectStage::NumStorage(std::vector<int>* digitArray, int nNumber, int nDigits)
{
	// 数字桁配列をリセット
	(*digitArray).clear();

	// 表示する数字が0以上の場合
	if (0 < nNumber)
	{
		// nNumberを全て格納するまで繰り返す
		while (0 != nNumber)
		{
			(*digitArray).push_back(nNumber % 10);	// nNumberの下1桁を格納する
			nNumber /= 10;							// nNumberを1桁スライドさせる

		}

	}

	// 指定桁数まで0埋めする
	while ((*digitArray).size() < nDigits)
	{
		(*digitArray).push_back(0);
	}
}