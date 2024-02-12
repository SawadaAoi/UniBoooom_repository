/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	シーン管理実装
	---------------------------------------
	SceneManager.cpp

	作成者	takagi

	変更履歴
	・2023/10/24 仮制作 takagi
	・2023/11/05 現段階のコーディング規約適用 takagi
	・2023/11/07 コメント修正 takagi
	・2023/11/16 シーン遷移の流れを実装 takagi
	・2023/11/17 過去シーンに戻る処理を追加・キー入力でシーンを切り替えられるデバッグモード追加 takagi
	・2023/11/23 フェード・ヒットストップ機能追加 takagi
	・2023/11/27 フェード本実装 takagi
	・2023/11/29 ヒットストップの仕様変更に対応 takagi
	・2023/12/01 フェードの仕様変更 takagi 
	・2023/12/12 最初のシーンをタイトルに変更
	・2023/12/14 BGMの管理をScene毎から移動 yamashita
	・2023/12/14 BGM用の定数定義 yamashita
	・2023/12/14 BGMをフェードするように変更 yamashita
	・2023/12/15 アプリ終了実装 takagi 

========================================== */

// =============== デバッグモード ===================
#if _DEBUG
#define KEY_CHANGE_SCENE (true)	//キー入力でシーンを変える
#endif

// =============== インクルード ===================
#include "SceneManager.h"	//自身のヘッダ
//#include "Prot.h"			//インスタンス候補
#include "Title.h"			//インスタンス候補
#include "SelectStage.h"	//インスタンス候補
#include "Stage1.h"			//インスタンス候補
#include "Stage2.h"			//インスタンス候補
#include "Stage3.h"			//インスタンス候補
#include "Result.h"			//インスタンス候補
#include "HitStop.h"		//ヒットストップ

#if _DEBUG
#include <Windows.h>		//メッセージボックス用
#endif

#if KEY_CHANGE_SCENE
#include <string>			//文字列操作
#include "Input.h"			//キー入力
#endif

// =============== 定数定義 ===================
const std::string BGM_FILE[CScene::E_TYPE_MAX] = {	//各ステージのBGMのファイル
	"Assets/Sound/BGM/Title_Select.mp3",	//タイトル
	"Assets/Sound/BGM/Title_Select.mp3",	//ステージセレクト
	"Assets/Sound/BGM/Stage1.mp3",	//Stage1
	"Assets/Sound/BGM/Stage2.mp3",	//Stage2
	"Assets/Sound/BGM/Stage3.mp3",	//Stage3
	"Assets/Sound/BGM/Result.mp3" };	//リザルト

/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
CSceneManager::CSceneManager()
	: m_pScene(nullptr)						//シーン
	, m_ePastScene(CScene::E_TYPE_NONE)		//前のシーン
	, m_eNextScene(CScene::E_TYPE_TITLE)	//シーン遷移先
	, m_bFinish(false)						//シーン管理を開始
	, m_pFade(nullptr)						//フェード
	, m_bStartFadeOut(false)
	, m_bFinFadeOut(false)
	, m_pBGM{nullptr,nullptr,nullptr,nullptr,nullptr,nullptr}
	, m_pBGMSpeaker(nullptr)
{
	// =============== サウンド読み込み ===================
	LoadSound();
	// =============== 動的確保 ===================
	if (!m_pScene)	//ヌルチェック
	{
		ChangeScene();	//最初に始めるシーン作成
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
CSceneManager::~CSceneManager()
{
	// =============== 終了 ===================
	if (m_pScene)	//ヌルチェック
	{
		SAFE_DELETE(m_pScene);	//解放
	}
	if (m_pFade)	//ヌルチェック
	{
		SAFE_DELETE(m_pFade);	//解放
	}
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
void CSceneManager::Update()
{
#if KEY_CHANGE_SCENE
	for (int nIdx = 0; nIdx < CScene::E_TYPE_MAX; nIdx++)
	{
		if (nIdx < 10)	//キー入力できる範囲
		{
			//Shift入力中に数字を押すとその数字のシーンに移る
			if (IsKeyPress(VK_SHIFT) & IsKeyTrigger(*std::to_string(nIdx).c_str()))
			{
				m_eNextScene = static_cast<CScene::E_TYPE>(nIdx);	//移動先シーン登録
				delete m_pScene;									//メモリ解放
				m_pScene = nullptr;									//空アドレス代入
				ChangeScene();										//シーン変更
			}
		}
	}
#endif

	// =============== ヒットストップ ===================
	CHitStop::Update();	//ヒットストップ更新

	// =============== シーン切換 ===================
	if (m_pFade)	//ヌルチェック
	{
		if (!m_pFade->IsFade())	//フェード検査
		{
			if (m_bStartFadeOut)
			{
				ChangeScene();
				m_bStartFadeOut = false;
			}
		}
	}

	// =============== 更新 ===================
	if (m_pScene)	//ヌルチェック
	{
		if (m_pScene->IsFin())	//シーン終了検査
		{
			// =============== フェード ===================
			if (m_pFade)	//ヌルチェック
			{
				if (!m_pFade->IsFadeOut())
				{
					m_pFade->Start();		//フェード開始
					m_bStartFadeOut = true;
				}
			}
		}
		else
		{
			// =============== フェード ===================
			if (m_pFade)	//ヌルチェック
			{
				if (!m_pFade->IsFade())
				{
					m_pScene->Update();	//シーン更新
				}
			}
		}
	}

	// =============== フェード系 ===================
	if (m_pFade)	//ヌルチェック
	{
		m_pFade->Update();	//フェード更新
	}

	// =============== サウンド ===================
	SoundUpdate();
}

/* ========================================
	描画関数
	----------------------------------------
	内容：描画処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CSceneManager::Draw()
{
	// =============== 描画 ===================
	if (m_pScene)	//ヌルチェック
	{
		m_pScene->Draw();	//シーン描画
	}

	// =============== フェード系 ===================
	if (m_pFade)	//ヌルチェック
	{
		m_pFade->Draw();	//フェード更新
	}
}

/* ========================================
	終了確認関数
	----------------------------------------
	内容：シーン管理をやめるかどうかのフラグを返す
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：true:シーン管理をやめたい / false:シーン管理を続けたい
=========================================== */
bool CSceneManager::IsFin() const
{
	// =============== 提供 =====================
	return m_bFinish;	//終了要求フラグ
}

/* ========================================
	シーン変更関数
	----------------------------------------
	内容：現在シーン削除→次シーン推移
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CSceneManager::ChangeScene()
{	
	// =============== 事前準備 =====================
	if (m_pScene)	//ヌルチェック
	{
		m_eNextScene = m_pScene->GetNext();	// 遷移先取得
	}

	// =============== 遷移先検査 =====================
	if (CScene::E_TYPE_NONE == m_eNextScene || CScene::E_TYPE_MAX == m_eNextScene)
	{
		return;	//処理中断
	}

	// =============== シーン削除 =====================
	if (m_pScene)	//ヌルチェック
	{
		//BGMの削除
		m_pBGMSpeaker->Stop();
		m_pBGMSpeaker->DestroyVoice();	//BGMの削除
		//シーンの削除
		m_ePastScene = m_pScene->GetType();	//現在シーン種退避
		delete m_pScene;					//メモリ解放
		m_pScene = nullptr;					//空アドレス
	}

	// =============== シーン切換 =====================
	MakeNewScene();	//新シーン作成
	
	// =============== フェード系 ===================
	if (m_pFade)	//ヌルチェック
	{
		delete m_pFade;		//メモリ開放
		m_pFade = nullptr;	//空アドレス代入
	}
	if (m_pScene)	//新規シーンが作られている
	{
		m_pFade = new CFade(m_pScene->GetCamera());	//動的確保
	}
}

/* ========================================
	新シーン作成関数
	----------------------------------------
	内容：次シーン情報を元に、シーンの動的確保分岐処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CSceneManager::MakeNewScene()
{
	// =============== シーン検査 =====================
	if (m_pScene)	//すでにシーンがあるか
	{
		return;	//処理中断
	}

	// =============== シーン作成 =====================
	switch (m_eNextScene)	//分岐
	{
		// =============== タイトルシーン =====================
	case CScene::E_TYPE_TITLE:		//遷移先：タイトル
		m_pScene = new CTitle();	//動的確保
		PlayBGM(m_eNextScene);		//BGMの再生
		break;						//分岐処理終了

		// =============== ステージセレクト =====================
	case CScene::E_TYPE_SELECT_STAGE:	//遷移先：ステージセレクト
		m_pScene = new CSelectStage();	//動的確保
		PlayBGM(m_eNextScene);		//BGMの再生

		break;							//分岐処理終了

		// =============== ステージ1 =====================
	case CScene::E_TYPE_STAGE1:		//遷移先：ステージ1
		m_pScene = new CStage1();	//動的確保
		PlayBGM(m_eNextScene);		//BGMの再生
		break;						//分岐処理終了

		// =============== ステージ2 =====================
	case CScene::E_TYPE_STAGE2:		//遷移先：ステージ2
		m_pScene = new CStage2();	//動的確保
		PlayBGM(m_eNextScene);		//BGMの再生
		break;						//分岐処理終了

		// =============== ステージ3 =====================
	case CScene::E_TYPE_STAGE3:		//遷移先：ステージ3
		m_pScene = new CStage3();	//動的確保
		PlayBGM(m_eNextScene);		//BGMの再生
		break;						//分岐処理終了

		// =============== リザルトシーン =====================
	case CScene::E_TYPE_RESULT:					//遷移先：リザルト
		m_pScene = new CResult();				//動的確保
		PlayBGM(m_eNextScene);					//BGMの再生
		break;									//分岐処理終了

		// =============== 前のシーン =====================
	case CScene::E_TYPE_PAST:			//遷移：戻る
		m_eNextScene = m_ePastScene;	//過去シーンを次シーンに登録
		MakeNewScene();					//処理をやり直す
		break;							//分岐処理終了

		// =============== 新規シーンは作らない =====================
	case CScene::E_TYPE_FINISH_ALL:		//遷移：アプリ終了
		m_bFinish = true;				//シーン管理終了予約
		break;							//分岐処理終了

		// =============== その他 =====================
	default:	//該当なし
#if _DEBUG
		MessageBox(nullptr, "存在しないシーンが呼び出されました", "SceneManager.cpp->Error", MB_OK);	//エラー通知
#endif
		break;	//分岐処理終了
	}

	// =============== 遷移先更新 =====================
	m_eNextScene = CScene::E_TYPE_NONE;	//移動先クリア
}

/* ========================================
	BGM読み込み関数
	----------------------------------------
	内容：BGMのサウンドファイルを読み込む
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CSceneManager::LoadSound()
{
	m_pBGM[CScene::E_TYPE_TITLE] = CSound::LoadSound(BGM_FILE[CScene::E_TYPE_TITLE].c_str(), true);			//タイトル用
	m_pBGM[CScene::E_TYPE_SELECT_STAGE] = CSound::LoadSound(BGM_FILE[CScene::E_TYPE_SELECT_STAGE].c_str(), true);	//セレクトステージ用
	m_pBGM[CScene::E_TYPE_STAGE1] = CSound::LoadSound(BGM_FILE[CScene::E_TYPE_STAGE1].c_str(), true);		//ステージ1用
	m_pBGM[CScene::E_TYPE_STAGE2] = CSound::LoadSound(BGM_FILE[CScene::E_TYPE_STAGE2].c_str(), true);		//ステージ2用
	m_pBGM[CScene::E_TYPE_STAGE3] = CSound::LoadSound(BGM_FILE[CScene::E_TYPE_STAGE3].c_str(), true);		//ステージ3用
	m_pBGM[CScene::E_TYPE_RESULT] = CSound::LoadSound(BGM_FILE[CScene::E_TYPE_RESULT].c_str(), true);		//リザルト用
}

void CSceneManager::SoundUpdate()
{
	SoundFade();	//BGMのフェード
}

/* ========================================
	BGMフェード関数
	----------------------------------------
	内容：BGMのフェード
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CSceneManager::SoundFade()
{
	if (!m_pFade || !m_pBGMSpeaker) { return; }	//nullチェック
	//フェードインだったらだんだん大きくなる
	if (m_pFade->IsFadeIn())	
	{
		m_pBGMSpeaker->SetVolume((1.0f - m_pFade->GetFrameRate()) * BGM_VOLUME);
	}
	//フェードアウトだったらだんだん小さくなる
	else if (m_pFade->IsFadeOut())
	{
		m_pBGMSpeaker->SetVolume(m_pFade->GetFrameRate() * BGM_VOLUME);
	}
}

/* ========================================
	BGM再生関数
	----------------------------------------
	内容：BGMの再生
	----------------------------------------
	引数1：Sceneの種類
	----------------------------------------
	戻値：なし
=========================================== */
void CSceneManager::PlayBGM(CScene::E_TYPE Scene)
{
	m_pBGMSpeaker = CSound::PlaySound(m_pBGM[Scene]);
	m_pBGMSpeaker->SetVolume(0.0f);
}