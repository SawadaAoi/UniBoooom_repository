/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	シーン管理定義
	---------------------------------------
	SceneManager.h
	---------------------------------------
	作成者	takagi

	変更履歴
	・2023/10/24 仮制作 takagi
	・2023/11/05 現段階のコーディング規約適用 takagi
	・2023/11/07 コメント修正 takagi
	・2023/11/16 シーン遷移の流れを実装 takagi
	・2023/11/17 過去シーンに戻る処理を追加 takagi
	・2023/11/23 フェード機能追加 takagi
	・2023/12/01 フェードの仕様変更 takagi
	・2024/01/18 CScene->GetType()関数を使用しない形に変更などリファクタリング takagi
	・2024/01/20 音関係リファクタリング takagi
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __SCENE_MANAGER_H__	//SceeneManager.hインクルードガード
#define __SCENE_MANAGER_H__

// =============== インクルード ===================
#include "Scene.h"			//メンバのヘッダ
#include "Fade.h"			//メンバのヘッダ
#include "Sound.h"			//メンバのヘッダ
#include "UcFlag.h"			//メンバのヘッダ
#include "Title.h"			//インスタンス候補
#include "SelectStage.h"	//インスタンス候補
#include "Stage1.h"			//インスタンス候補
#include "Stage2.h"			//インスタンス候補
#include "Stage3.h"			//インスタンス候補
#include "Result.h"			//インスタンス候補
#include <map>				//連想型コンテナ

// =============== クラス定義 =====================
class CSceneManager
{
private:
	// ===列挙定義===========
	enum E_BIT_FLAG
	{
		E_BIT_FLAG_FINISH = 0x01,			//シーン終了予約用フラグ(オンで終了)
		E_BIT_FLAG_START_FADE_OUT = 0x02,	//フェードアウトが開始したか
		E_BIT_FLAG_END_FADE_OUT = 0x04,		//フェードアウトが終了したか
		E_BIT_FLAG_4 = 0x08,				//
		E_BIT_FLAG_5 = 0x10,				//
		E_BIT_FLAG_6 = 0x20,				//
		E_BIT_FLAG_7 = 0x40,				//
		E_BIT_FLAG_8 = 0x80,				//
	};	//フラグ管理
	// ===定数定義===========
	const std::map<size_t, CScene::E_TYPE> MAP_SCENE_TYPE = {
		{typeid(CTitle).hash_code(), CScene::E_TYPE_TITLE},					//タイトル
		{typeid(CSelectStage).hash_code(), CScene::E_TYPE_SELECT_STAGE},	//ステージ選択
		{typeid(CStage1).hash_code(), CScene::E_TYPE_STAGE1},				//ステージ1
		{typeid(CStage2).hash_code(), CScene::E_TYPE_STAGE2},				//ステージ2
		{typeid(CStage3).hash_code(), CScene::E_TYPE_STAGE3},				//ステージ3
		{typeid(CResult).hash_code(), CScene::E_TYPE_RESULT},				//リザルト
	};	//シーン種
	const std::map<size_t, XAUDIO2_BUFFER*> MAP_BGM = {
		{typeid(CTitle).hash_code(), CSound::LoadSound("Assets/Sound/BGM/BGM_maou.mp3", true)},			//タイトル
		{typeid(CSelectStage).hash_code(), CSound::LoadSound("Assets/Sound/BGM/BGM_maou.mp3", true)},	//ステージ選択
		{typeid(CStage1).hash_code(), CSound::LoadSound("Assets/Sound/BGM/BGM_maou.mp3", true)},		//ステージ1
		{typeid(CStage2).hash_code(), CSound::LoadSound("Assets/Sound/BGM/BGM_maou.mp3", true)},		//ステージ2
		{typeid(CStage3).hash_code(), CSound::LoadSound("Assets/Sound/BGM/BGM_maou.mp3", true)},		//ステージ3
		{typeid(CResult).hash_code(), CSound::LoadSound("Assets/Sound/BGM/BGM_maou.mp3", true)},		//リザルト
	};	//BGMデータ
public:
	// ===プロトタイプ宣言===
	CSceneManager();	//コンストラクタ
	~CSceneManager();	//デストラクタ
	void Update();		//更新
	void Draw();		//描画
	bool IsFin() const;	//終了確認
private:
	// ===メンバ変数宣言=====
	CScene* m_pScene;					//シーン
	CScene::E_TYPE m_ePastScene;		//前のシーン
	CScene::E_TYPE m_eNextScene;		//シーン遷移先
	CUcFlag m_UcFlag;					//フラグ
	CFade* m_pFade;						//フェード
	IXAudio2SourceVoice* m_pBGMSpeaker;	//BGMを聞き取る側
	// ===プロトタイプ宣言===
	void ChangeScene();		//シーン変更
	void MakeNewScene();	//新シーン動的確保
	void SoundUpdate();		//BGMの更新
	void SoundFade();		//BGMのフェード
	void PlayBGM();			//BGMの再生
};	//シーン管理

#endif	//!__SCENE_MANAGER_H__