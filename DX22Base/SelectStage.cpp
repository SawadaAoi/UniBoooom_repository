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
	{ 220.0f, 150.0f, 0.0f},		// ステージ1
	{ 600.0f, 550.0f, 0.0f},		// ステージ2
	{ 1000.0f, 150.0f, 0.0f},	// ステージ3
};

const float FLASH_BUTTON_TEXT_ADJUST = 0.02f;	//「戻る」「決定」テキストの点滅間隔調整

// 手配書の揺れ関係
const float STAGE_TEX_ANIM_ANGLE = 10.0f;			// ステージ手配書画像の揺れの角度限界値
const int	CHANGE_ROTATE_HALF_TIME = 1.5f * 60;	// 揺れ半周あたりにかかる時間

// ステージセレクト処理関係
const int SELECT_MOVE_RIGHT = 1;	// 右に選択移動
const int SELECT_MOVE_LEFT = -1;	// 左に選択移動
const int SELECT_MOVE_NOT = 0;		// 入力してない

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
	: m_fChangeRotate(0.0f)					// ステージ手配書画像の傾き変動値
	, m_bStickFlg(true)						// スティックの傾倒有無
	, m_pFrameCntFall(nullptr)				// 手配書落下用フレームカウンタ
	, m_pFrameCntRotate(nullptr)				// 拡縮用フレームカウンタ
	, m_bCntUpDwn(false)					// カウントアップ・ダウン
	, m_eNextType(CScene::E_TYPE_STAGE1)	// 初期の次のシーン
	, m_nButtonAlphaCnt(0)					// 拡縮用フレームカウンタ
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
	m_pFrameCntRotate = new CFrameCnt(CHANGE_ROTATE_HALF_TIME, m_bCntUpDwn);	//フレーム初期化

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

	// 手配書画像の中心値を上にずらす(揺れのアニメーションの為)
	m_p2dObject.at(E_2D_OBJECT_STAGE_1_LEAVE)->SetOffSet(STAGE_TEXTURE_OFFSET);
	m_p2dObject.at(E_2D_OBJECT_STAGE_1_REMINE)->SetOffSet(STAGE_TEXTURE_OFFSET);
	m_p2dObject.at(E_2D_OBJECT_STAGE_2_LEAVE)->SetOffSet(STAGE_TEXTURE_OFFSET);
	m_p2dObject.at(E_2D_OBJECT_STAGE_2_REMINE)->SetOffSet(STAGE_TEXTURE_OFFSET);
	m_p2dObject.at(E_2D_OBJECT_STAGE_3_LEAVE)->SetOffSet(STAGE_TEXTURE_OFFSET);
	m_p2dObject.at(E_2D_OBJECT_STAGE_3_REMINE)->SetOffSet(STAGE_TEXTURE_OFFSET);

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
	SAFE_DELETE(m_pFrameCntRotate);			//カウンタ削除
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

	// 手配書画像落下処理が開始している場合(ステージ決定済み) 
	if (m_pFrameCntFall)
	{
		FallAnimationStageTexture();	// 手配書画像を破るアニメーション
		
	}
	else
	{	
		StageSelect();								// ステージ選択処理
		SelectStageTextureAnimation(m_eNextType);	// 選択手配書アニメーション
	}

	m_nButtonAlphaCnt++;	//「戻る」「決定」テキスト点滅

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
void CSelectStage::Draw()
{
	// =============== 描画 =====================	//TODO:アクセス・ヌルチェック
	m_p2dObject[E_2D_OBJECT_BACK_GROUND]->Draw();		//背景描画
	m_p2dObject[E_2D_OBJECT_BACK_SCENE_NAME]->Draw();	//シーン名(画面上部の枠)描画

	DrawHiscore();		// ハイスコア関連描画
	DrawStageTexture();	// ステージ手配書画像描画


	m_p2dObject[E_2D_OBJECT_BUTTON_EXPLANATION]->SetAlpha(
		fabs(cosf(m_nButtonAlphaCnt * FLASH_BUTTON_TEXT_ADJUST)));	// 「戻る」「決定」テキスト点滅
	m_p2dObject[E_2D_OBJECT_BUTTON_EXPLANATION]->Draw();			// 「戻る」「決定」テキスト描画
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
void CSelectStage::StageSelect()
{
	// ゲームコントローラー使用時
	if (GetUseVController())
	{
		TPos3d<float> fMoveInput;	// スティックの入力値を入れる変数
		fMoveInput.x = IsStickLeft().x;// コントローラーの左スティックの傾きを取得

		if (m_bStickFlg)
		{
			// スティック右
			if ( 0.0f < fMoveInput.x )
			{
				SelectStageChange(SELECT_MOVE_RIGHT);	// 遷移ステージ値を変更
				m_bStickFlg = false;					// スティック傾倒フラグオン

			}
			// スティック左
			else if (fMoveInput.x < 0.0f)
			{
				SelectStageChange(SELECT_MOVE_LEFT);	// 遷移ステージ値を変更
				m_bStickFlg = false;					// スティック傾倒フラグオン

			}
		}
		else
		{
			// スティックの傾きが一定値以下の場合
			if (fabs(fMoveInput.x) <= 0.5f )	
			{
				m_bStickFlg = true;	// スティックをニュートラルに戻したら移動可能にする
			}
		}
	}
	// キーボード使用時
	else
	{
		// 右
		if (IsKeyTrigger('D'))	SelectStageChange(SELECT_MOVE_RIGHT);	// 遷移ステージ値を変更
		// 左
		if (IsKeyTrigger('A'))	SelectStageChange(SELECT_MOVE_LEFT);	// 遷移ステージ値を変更
	}

	// 決定
	if ( (IsKeyTrigger(VK_SPACE) || IsKeyTrigger(VK_RETURN) || IsKeyTriggerController(BUTTON_B)) && !m_pFrameCntFall)
	{
		m_pFrameCntFall = new CFrameCnt(FALL_TIME_ARR_LET);	//カウンタ作成
		PlaySE(SE_DECISION);	// SEの再生 

	}

	// タイトル画面に戻る
	if ((IsKeyTrigger('B') || IsKeyTriggerController(BUTTON_A) )&& !m_pFrameCntFall)
	{
		m_eNextType = E_TYPE::E_TYPE_TITLE;
		m_bFinish = true;
	}
}



/* ========================================
	選択ステージ値変更関数
	----------------------------------------
	内容：プレイするステージを変更する
	----------------------------------------
	引数1：変更値( 定数の SELECT_MOVE_NOT / SELECT_MOVE_RIGHT / SELECT_MOVE_LEFT )
	----------------------------------------
	戻値：なし
=========================================== */
void CSelectStage::SelectStageChange(int select)
{
	// 揺れの加算値をリセットする
	SAFE_DELETE(m_pFrameCntRotate);												// カウンタ削除
	m_pFrameCntRotate = new CFrameCnt(CHANGE_ROTATE_HALF_TIME, m_bCntUpDwn);	// カウントアップ・ダウン

	ResetStageTexture(m_eNextType);	// 選択していたステージの画像描画情報をリセット
	PlaySE(SE_CHOOSE);				// SEの再生

	// カーソルが右端で右に移動する場合
	if (select == SELECT_MOVE_RIGHT && m_eNextType == CScene::E_TYPE_STAGE3)
	{
		m_eNextType = E_TYPE_STAGE1;	// 左端にループ移動
		return;
	}
	// カーソルが左端で左に移動する場合
	if (select == SELECT_MOVE_LEFT && m_eNextType == CScene::E_TYPE_STAGE1)
	{
		m_eNextType = E_TYPE_STAGE3;	// 右端にループ移動
		return;
	}

	// 選択ステージを変更
	m_eNextType = static_cast<CScene::E_TYPE>(m_eNextType + select);	

}

/* ========================================
	選択ステージ手配書画像アニメーション関数
	----------------------------------------
	内容：選択したステージの手配書画像をアニメーションさせる処理
	----------------------------------------
	引数1：ステージ番号
	----------------------------------------
	戻値：なし
=========================================== */
void CSelectStage::SelectStageTextureAnimation(CScene::E_TYPE stage)
{

	// 揺れのアニメーションに使用する値を更新
	if (m_pFrameCntRotate)	//ヌルチェック
	{
		m_pFrameCntRotate->Count();	//カウント進行

		m_fChangeRotate =	// STAGE_TEX_ANIM_ANGLE ～ -STAGE_TEX_ANIM_ANGLEの角度をセット
			(m_pFrameCntRotate->GetRate() * STAGE_TEX_ANIM_ANGLE * 2) - STAGE_TEX_ANIM_ANGLE;

		if (m_pFrameCntRotate->IsFin())	//カウント完了
		{
			m_bCntUpDwn ^= 1;															// カウントアップダウン逆転
			SAFE_DELETE(m_pFrameCntRotate);												// カウンタ削除
			m_pFrameCntRotate = new CFrameCnt(CHANGE_ROTATE_HALF_TIME, m_bCntUpDwn);	// カウントアップ・ダウン
		}
	}

	switch (stage)	// 選択しているステージ手配書画像を揺らす
	{	
	case CScene::E_TYPE_STAGE1:	//ステージ1

		m_p2dObject.at(E_2D_OBJECT_STAGE_1_LEAVE)->SetRotate({ 0.0f, 0.0f, DirectX::XMConvertToRadians(m_fChangeRotate) });
		m_p2dObject.at(E_2D_OBJECT_STAGE_1_REMINE)->SetRotate({ 0.0f, 0.0f, DirectX::XMConvertToRadians(m_fChangeRotate) });
		break;

	case CScene::E_TYPE_STAGE2:	//ステージ2

		m_p2dObject.at(E_2D_OBJECT_STAGE_2_LEAVE)->SetRotate({ 0.0f, 0.0f, DirectX::XMConvertToRadians(m_fChangeRotate) });
		m_p2dObject.at(E_2D_OBJECT_STAGE_2_REMINE)->SetRotate({ 0.0f, 0.0f, DirectX::XMConvertToRadians(m_fChangeRotate) });
		break;

	case CScene::E_TYPE_STAGE3:	//ステージ3

		m_p2dObject.at(E_2D_OBJECT_STAGE_3_LEAVE)->SetRotate({ 0.0f, 0.0f, DirectX::XMConvertToRadians(m_fChangeRotate) });
		m_p2dObject.at(E_2D_OBJECT_STAGE_3_REMINE)->SetRotate({ 0.0f, 0.0f, DirectX::XMConvertToRadians(m_fChangeRotate) });
		break;			
	}
}

/* ========================================
	ステージ画像サイズ落下アニメーション描画関数
	----------------------------------------
	内容：ステージの画像の描画情報を初期値に戻す
	----------------------------------------
	引数1：ステージ番号
	----------------------------------------
	戻値：なし
=========================================== */
void CSelectStage::FallAnimationStageTexture()
{

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
		fPos.y = fBasePos.y * m_pFrameCntFall->GetRate();	// 初期座標＊画面外までの距離割合
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

/* ========================================
	ステージ画像情報リセット描画関数
	----------------------------------------
	内容：ステージの画像の描画情報を初期値に戻す
	----------------------------------------
	引数1：ステージ番号
	----------------------------------------
	戻値：なし
=========================================== */
void CSelectStage::ResetStageTexture(CScene::E_TYPE stage)
{
	switch (stage)	// 傾きを初期値に戻す
	{
	case CScene::E_TYPE_STAGE1:
		m_p2dObject.at(E_2D_OBJECT_STAGE_1_LEAVE)->SetRotate(INIT_MAP_ROTATE.at(E_2D_OBJECT_STAGE_1_LEAVE));	
		m_p2dObject.at(E_2D_OBJECT_STAGE_1_REMINE)->SetRotate(INIT_MAP_ROTATE.at(E_2D_OBJECT_STAGE_1_REMINE));	
		break;
	case CScene::E_TYPE_STAGE2:

		m_p2dObject.at(E_2D_OBJECT_STAGE_2_LEAVE)->SetRotate(INIT_MAP_ROTATE.at(E_2D_OBJECT_STAGE_2_LEAVE));
		m_p2dObject.at(E_2D_OBJECT_STAGE_2_REMINE)->SetRotate(INIT_MAP_ROTATE.at(E_2D_OBJECT_STAGE_2_REMINE));
		break;
	case CScene::E_TYPE_STAGE3:	
		m_p2dObject.at(E_2D_OBJECT_STAGE_3_LEAVE)->SetRotate(INIT_MAP_ROTATE.at(E_2D_OBJECT_STAGE_3_LEAVE));
		m_p2dObject.at(E_2D_OBJECT_STAGE_3_REMINE)->SetRotate(INIT_MAP_ROTATE.at(E_2D_OBJECT_STAGE_3_REMINE));
		break;
	}
}

/* ========================================
	ステージ手配書描画関数
	----------------------------------------
	内容：ステージ手配書を描画する
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CSelectStage::DrawStageTexture()
{
	// 選択しているステージの手配書を一番手前に描画する
	switch (m_eNextType)
	{	//TODO:アクセス・ヌルチェック
	case CScene::E_TYPE_STAGE1:	//ステージ1
		m_p2dObject.at(E_2D_OBJECT_STAGE_2_LEAVE)->Draw();	//ステージ2の手配書描画
		m_p2dObject.at(E_2D_OBJECT_STAGE_2_REMINE)->Draw();	//ステージ2の手配書描画
		m_p2dObject.at(E_2D_OBJECT_STAGE_3_LEAVE)->Draw();	//ステージ3の手配書描画
		m_p2dObject.at(E_2D_OBJECT_STAGE_3_REMINE)->Draw();	//ステージ3の手配書描画
		m_p2dObject.at(E_2D_OBJECT_STAGE_1_LEAVE)->Draw();	//ステージ1の手配書描画
		m_p2dObject.at(E_2D_OBJECT_STAGE_1_REMINE)->Draw();	//ステージ1の手配書描画
		break;
	case CScene::E_TYPE_STAGE2:	//ステージ2
		m_p2dObject.at(E_2D_OBJECT_STAGE_1_LEAVE)->Draw();	//ステージ1の手配書描画
		m_p2dObject.at(E_2D_OBJECT_STAGE_1_REMINE)->Draw();	//ステージ1の手配書描画
		m_p2dObject.at(E_2D_OBJECT_STAGE_3_LEAVE)->Draw();	//ステージ3の手配書描画
		m_p2dObject.at(E_2D_OBJECT_STAGE_3_REMINE)->Draw();	//ステージ3の手配書描画
		m_p2dObject.at(E_2D_OBJECT_STAGE_2_LEAVE)->Draw();	//ステージ2の手配書描画
		m_p2dObject.at(E_2D_OBJECT_STAGE_2_REMINE)->Draw();	//ステージ2の手配書描画
		break;
	case CScene::E_TYPE_STAGE3:	//ステージ3
		m_p2dObject.at(E_2D_OBJECT_STAGE_1_LEAVE)->Draw();	//ステージ1の手配書描画
		m_p2dObject.at(E_2D_OBJECT_STAGE_1_REMINE)->Draw();	//ステージ1の手配書描画
		m_p2dObject.at(E_2D_OBJECT_STAGE_2_LEAVE)->Draw();	//ステージ2の手配書描画
		m_p2dObject.at(E_2D_OBJECT_STAGE_2_REMINE)->Draw();	//ステージ2の手配書描画
		m_p2dObject.at(E_2D_OBJECT_STAGE_3_LEAVE)->Draw();	//ステージ3の手配書描画
		m_p2dObject.at(E_2D_OBJECT_STAGE_3_REMINE)->Draw();	//ステージ3の手配書描画
		break;
	}
}

/* ========================================
	ハイスコア描画関数
	----------------------------------------
	内容：ハイスコアを描画する
	----------------------------------------
	引数1：無し
	----------------------------------------
	戻値：なし
=========================================== */
void CSelectStage::DrawHiscore()
{
	TTriType<float> NumBasePos;	// ハイスコア数字座標変数

	for (int i = 0; i < 3; i++)
	{
		// ハイスコア背景座標セット
		m_p2dObject.at(E_2D_OBJECT_HISCORE_BG)->SetPos({
			INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_BG).x + HISCORE_BASE_POS[i].x,
			INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_BG).y + HISCORE_BASE_POS[i].y,
			INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_BG).z ,
			});

		// ハイスコアテキスト座標セット
		m_p2dObject.at(E_2D_OBJECT_HISCORE_TEXT)->SetPos({
			INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_TEXT).x + HISCORE_BASE_POS[i].x,
			INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_TEXT).y + HISCORE_BASE_POS[i].y,
			INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_TEXT).z ,
			});

		// ハイスコア数字座標変数セット
		NumBasePos = {
			INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_NUM).x + HISCORE_BASE_POS[i].x,
			INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_NUM).y + HISCORE_BASE_POS[i].y,
			INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_NUM).z ,
		};


		m_p2dObject.at(E_2D_OBJECT_HISCORE_BG)->Draw();		// ハイスコア背景描画
		m_p2dObject.at(E_2D_OBJECT_HISCORE_TEXT)->Draw();	// ハイスコアテキスト描画
		DispNum(m_Data.nHighScore[i], 5, NumBasePos);		// ハイスコア数字描画
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

	NumStorage(&digitArray, dispNum, nDigits);	// 配列に数字を入れる

	// 桁数分描画
	for (int i = 0; i < digitArray.size(); i++)
	{
		float width = (INIT_MAP_SIZE.at(E_2D_OBJECT_HISCORE_NUM).x * 0.8f) * i;
		
		int x = digitArray[i] % HISCORE_NUM_SPLIT.x;	// 数字テクスチャの横方向位置
		int y = digitArray[i] / HISCORE_NUM_SPLIT.x;	// 数字テクスチャの縦方向位置

		m_p2dObject.at(E_2D_OBJECT_HISCORE_NUM)->SetUvScale(HISCORE_NUM_UVSCALE);	// テクスチャUV分割数
		m_p2dObject.at(E_2D_OBJECT_HISCORE_NUM)->SetUvOffset({						// テクスチャUV座標
			HISCORE_NUM_UVSCALE.x * x, 
			HISCORE_NUM_UVSCALE.y * y });

		m_p2dObject.at(E_2D_OBJECT_HISCORE_NUM)->SetPos({ pos.x - width , pos.y, pos.z });	// テクスチャ座標
		m_p2dObject.at(E_2D_OBJECT_HISCORE_NUM)->Draw();									// 描画
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