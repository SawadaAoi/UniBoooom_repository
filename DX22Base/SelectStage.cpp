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

========================================== */

// =============== インクルード ===================
#include "SelectStage.h"	//自身のヘッダ
#include "Input.h"
#include "GameParameter.h"
#define _USE_MATH_DEFINES	//math.hの定義使用
#include <math.h>			//M_PI使用
#include <algorithm>		//clamp使用
#include "Delete.h"			//削除マクロ

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
	:m_bStickFlg(false)					//スティックの傾倒有無
	,m_pFrameCnt(nullptr)				//フレームカウンタ
	,m_bCntUpDwn(false)					//カウントアップ・ダウン
	,m_eNextType(CScene::E_TYPE_STAGE1)	//初期の次のシーン
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
	m_pFrameCnt = new CFrameCnt(CHANGE_SCALE_HALF_TIME, m_bCntUpDwn);	//フレーム初期化

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
	Select();

	// =============== 変数宣言 =====================
	float fSize = INIT_SIZE_ARR_LET.x;	//大きさ

	// =============== 拡縮更新 =====================
	if (m_pFrameCnt)	//ヌルチェック
	{
		m_pFrameCnt->Count();	//カウント進行
		fSize = -(cosf(static_cast<float>(M_PI) * m_pFrameCnt->GetRate()) - 1.0f) / 2.0f * (MAX_SIZE_ARR_LET - MIN_SIZE_ARR_LET) + MIN_SIZE_ARR_LET;	//イージングを使った大きさ変更
		if (m_pFrameCnt->IsFin())	//カウント完了
		{
			m_bCntUpDwn ^= 1;													//カウントアップダウン逆転
			SAFE_DELETE(m_pFrameCnt);											//カウンタ削除
			m_pFrameCnt = new CFrameCnt(CHANGE_SCALE_HALF_TIME, m_bCntUpDwn);	//カウントアップ・ダウン
		}
	}

	// =============== 拡縮変更 =====================
	switch (m_eNextType)	//選択されているものを変更
	{	//TODO:アクセス・ヌルチェック
	case CScene::E_TYPE_STAGE1:	//ステージ1
		m_p2dObject.at(E_2D_OBJECT_STAGE_1_LEAVE)->SetSize({ fSize * ASPECT_RATE_ARR_LET, fSize, 1.0f });	//ステージ1の手配書
		m_p2dObject.at(E_2D_OBJECT_STAGE_1_REMINE)->SetSize({ fSize * ASPECT_RATE_ARR_LET, fSize, 1.0f });	//ステージ1の手配書
		break;	//分岐処理終了
	case CScene::E_TYPE_STAGE2:	//ステージ2
		m_p2dObject.at(E_2D_OBJECT_STAGE_2_LEAVE)->SetSize({ fSize * ASPECT_RATE_ARR_LET, fSize, 1.0f });	//ステージ2の手配書
		m_p2dObject.at(E_2D_OBJECT_STAGE_2_REMINE)->SetSize({ fSize * ASPECT_RATE_ARR_LET, fSize, 1.0f });	//ステージ2の手配書
		break;	//分岐処理終了
	case CScene::E_TYPE_STAGE3:	//ステージ3
		m_p2dObject.at(E_2D_OBJECT_STAGE_3_LEAVE)->SetSize({ fSize * ASPECT_RATE_ARR_LET, fSize, 1.0f });	//ステージ3の手配書
		m_p2dObject.at(E_2D_OBJECT_STAGE_3_REMINE)->SetSize({ fSize * ASPECT_RATE_ARR_LET, fSize, 1.0f });	//ステージ3の手配書
		break;	//分岐処理終了
	}
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
	//!memo(見たら消してー)：constが邪魔になったら外してね(.hの方も)
void CSelectStage::Draw() //const
{
	// =============== 描画 =====================	//TODO:アクセス・ヌルチェック
	m_p2dObject[E_2D_OBJECT_BACK_GROUND]->Draw();		//背景描画
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

	//for (auto Iterator = m_p2dObject.begin(); Iterator != m_p2dObject.end(); Iterator++)
	//{
	//	if (Iterator->second)	//ヌルチェック
	//	{
	//		Iterator->second->Draw();	//描画	//順番の都合で不採用
	//	}
	//}
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
				}
				m_bStickFlg = true;	//スティック傾倒中
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
				}
				m_bStickFlg = true;	//スティック傾倒中
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
		}
	}

	if (IsKeyTrigger(VK_SPACE) || IsKeyTriggerController(BUTTON_B))
	{
		m_bFinish = true;	// タイトルシーン終了フラグON
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