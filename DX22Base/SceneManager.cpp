/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	シーン管理実装
	---------------------------------------
	SceneManager.cpp
	---------------------------------------
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
	・2023/12/12 最初のシーンをタイトルに変更 takagi
	・2023/12/14 BGMの管理をScene毎から移動 yamashita
	・2023/12/14 BGM用の定数定義 yamashita
	・2023/12/14 BGMをフェードするように変更 yamashita
	・2023/12/15 アプリ終了実装 takagi
	・2024/01/18 CScene->GetType()関数を使用しない形に変更などリファクタリング takagi
	・2024/01/20 音関係リファクタリング takagi
	・2024/01/21 コメント改修・bgmバグ修正・MessageBox改善 takagi
	・2024/01/25 オブジェクトチェック追加
	・2024/02/09 カメラ削除 takagi

========================================== */

// =============== デバッグモード ===================
#if _DEBUG
#define KEY_CHANGE_SCENE (true)	//キー入力でシーンを変える
#endif

// =============== インクルード ===================
#include "SceneManager.h"	//自身のヘッダ
#include "HitStop.h"		//ヒットストップ
#include "ModelManager.h"	// モデルの一括管理クラスの最初のインスタンス用
#include "BattleData.h"		//データ

#if _DEBUG
#include <Windows.h>		//メッセージボックス用
#endif
#if KEY_CHANGE_SCENE
#include <string>			//文字列操作
#include "Input.h"			//キー入力
#endif

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
	:m_pScene(nullptr)						//シーン
	, m_ePastScene(CScene::E_TYPE_NONE)		//前のシーン
	, m_eNextScene(CScene::E_TYPE_TITLE)	//シーン遷移先
	, m_pFade(nullptr)						//フェード
	, m_pBGMSpeaker(nullptr)				//BGMを聞き取る側
{
	GetModelMng;	// モデルマネージャーを作成してシーン遷移を早くする

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
	SAFE_DELETE(m_pScene);			//シーン削除
	SAFE_DELETE(m_pFade);			//フェード削除
	UNLOAD_SOUND(m_pBGMSpeaker);	//BGMの再生を停止し、その音データの紐づけを破棄		※このとき中身のポインターがデータを持たないとエラーとなる
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
			if (IsKeyPress(VK_SHIFT) & IsKeyTrigger(*std::to_string(nIdx).c_str()))	//shiftを押しながらシーン番号が入力された
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
			if (m_UcFlag.Check(E_BIT_FLAG_START_FADE_OUT))	//フェードアウトが開始していたとき
			{
				ChangeScene();								//シーン変更
				m_UcFlag.Down(E_BIT_FLAG_START_FADE_OUT);	//このフラグは役目を終えた
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
					m_pFade->Start();						//フェード開始
					m_UcFlag.Up(E_BIT_FLAG_START_FADE_OUT);	//フェードアウトが開始
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
	SoundUpdate();	//サウンド更新
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
	return m_UcFlag.Check(E_BIT_FLAG_FINISH);	//終了要求フラグ
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
		m_eNextScene = m_pScene->GetNext();	//遷移先取得
	}

	// =============== 遷移先検査 =====================
	if (CScene::E_TYPE_NONE == m_eNextScene || CScene::E_TYPE_MAX == m_eNextScene)
	{
		return;	//処理中断
	}

	// =============== シーン削除 =====================
	if (m_pScene)	//ヌルチェック
	{
		m_ePastScene = MAP_SCENE_TYPE.at(typeid(*m_pScene).hash_code());	//現在シーン種退避
		delete m_pScene;													//メモリ解放
		m_pScene = nullptr;													//空アドレス
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
		m_pFade = new CFade();	//動的確保
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
		break;						//分岐処理終了

		// =============== ステージセレクト =====================
	case CScene::E_TYPE_SELECT_STAGE:	//遷移先：ステージセレクト
		m_pScene = new CSelectStage();	//動的確保
		break;							//分岐処理終了

		// =============== ステージ1 =====================
	case CScene::E_TYPE_STAGE1:		//遷移先：ステージ1
		m_pScene = new CStage1();	//動的確保
		break;						//分岐処理終了

		// =============== ステージ2 =====================
	case CScene::E_TYPE_STAGE2:		//遷移先：ステージ2
		m_pScene = new CStage2();	//動的確保
		break;						//分岐処理終了

		// =============== ステージ3 =====================
	case CScene::E_TYPE_STAGE3:		//遷移先：ステージ3
		m_pScene = new CStage3();	//動的確保
		break;						//分岐処理終了

		// =============== リザルトシーン =====================
	case CScene::E_TYPE_RESULT:		//遷移先：リザルト
		m_pScene = new CResult();	//動的確保
		break;						//分岐処理終了

		// =============== 前のシーン =====================
	case CScene::E_TYPE_PAST:			//遷移：戻る
		m_eNextScene = m_ePastScene;	//過去シーンを次シーンに登録
		MakeNewScene();					//処理をやり直す
		break;							//分岐処理終了

		// =============== 新規シーンは作らない =====================
	case CScene::E_TYPE_FINISH_ALL:		//遷移：アプリ終了
		m_UcFlag.Up(E_BIT_FLAG_FINISH);	//シーン管理終了予約
		break;							//分岐処理終了

		// =============== 例外 ===================
	default:	//上記以外
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error：";	//エラー箇所
		MessageBox(nullptr, (ErrorSpot + "存在しないシーンが呼び出されました").c_str(), "Error", MB_OK | MB_ICONERROR);						//エラー通知
#endif
		break;	//分岐処理終了
	}

	// =============== BGM再生 ===================
	if (m_eNextScene != CScene::E_TYPE_FINISH_ALL)	//シーンを終了しない場合
	{
		PlayBGM();	//新規シーンに対応したBGMの再生
	}

	// =============== 遷移先更新 =====================
	m_eNextScene = CScene::E_TYPE_NONE;	//移動先クリア
}

/* ========================================
	BGM更新関数
	----------------------------------------
	内容：BGM更新
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CSceneManager::SoundUpdate()
{
	// =============== フェード時対応 =====================
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
	// =============== 検査 =====================
	if (!m_pFade || !m_pBGMSpeaker)	//ヌルチェック
	{
		// =============== 終了 =====================
		return;	//処理中断
	}

	// =============== 音量更新 =====================
	if (m_pFade->IsFadeIn())	//フェードイン中
	{
		m_pBGMSpeaker->SetVolume((1.0f - m_pFade->GetFrameRate()) * BGM_VOLUME);	//フェードイン中、音量をだんだん大きくする
	}
	else if (m_pFade->IsFadeOut())	//フェードアウト中
	{
		m_pBGMSpeaker->SetVolume(m_pFade->GetFrameRate() * BGM_VOLUME);				//フェードアウト中、音量をだんだん小さくする
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
void CSceneManager::PlayBGM()
{
	// =============== 音設定 =====================
	if (m_pScene && MAP_BGM.find(typeid(*m_pScene).hash_code()) != MAP_BGM.end() && MAP_BGM.at(typeid(*m_pScene).hash_code()))	//アクセスチェック・ヌルチェック
	{
		UNLOAD_SOUND(m_pBGMSpeaker);													//BGMの再生を停止し、その音データの紐づけを破棄	※ここ以外で削除するとヌルチェックできない中身のポインターがヌルとなりデストラクタで停止する
		if (typeid(CResult).hash_code() == typeid(*m_pScene).hash_code())
		{
			BattleData Data;
			Data.Load();
			if (Data.bClearFlg)
			{
				m_pBGMSpeaker = CSound::PlaySound(MAP_BGM.at(typeid(*m_pScene).hash_code()));	//BGM登録・再生
				m_pBGMSpeaker->SetVolume(0.0f);													//再生音量設定
			}
			else
			{
				m_pBGMSpeaker = CSound::PlaySound(CSound::LoadSound("Assets/Sound/BGM/Result_GameOver.mp3", true));	//BGM登録・再生
				m_pBGMSpeaker->SetVolume(0.0f);													//再生音量設定
			}
		}
		else
		{
			m_pBGMSpeaker = CSound::PlaySound(MAP_BGM.at(typeid(*m_pScene).hash_code()));	//BGM登録・再生
			m_pBGMSpeaker->SetVolume(0.0f);													//再生音量設定
		}
	}
#if _DEBUG
	else
	{
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error：";	//エラー箇所
		MessageBox(nullptr, (ErrorSpot + "音のデータが不足しています").c_str(), "Error", MB_OK | MB_ICONERROR);								//エラー通知
	}
#endif
}