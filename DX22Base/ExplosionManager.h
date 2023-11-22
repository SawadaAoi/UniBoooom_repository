/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   爆発管理ヘッダー
   ---------------------------------------
   ExplosionManager.h

   作成者 鄭 宇恩

   変更履歴
	・2023/11/06 爆発マネージャークラス作成 tei
	・2023/11/09 爆発配列を返す処理の追加 sawada
	・2023/11/10 他のオブジェクトと同一のカメラをセットするようにした yamashita
	・2023/11/13 Create関数の引数にtimeを追加 Suzumura
	・2023/11/18 サウンド用のメンバ変数を追加 yamashita
	・2023/11/20 コンボ数機能追加 Sawada
	・2023/11/21 コンボ数機能の一部をコンボクラスに移動 Sawada

========================================== */
#ifndef __EXPLOSION_MANAGER_H__	//ExplosionManager.hインクルードガード
#define __EXPLOSION_MANAGER_H__

// =============== インクルード ===================
#include "Explosion.h"			//爆発処理ヘッダー
#include "GameParameter.h"		//定数定義用ヘッダー
#include "SlimeBase.h"
#include "Sound.h"
#include "Combo.h"

// =============== 定数定義 =======================
#if MODE_GAME_PARAMETER
#else
const int MAX_EXPLOSION_NUM = 20;	//最大爆発数
const float EXPLODE_BASE_RATIO = 1.5f;			// スライムの爆発接触での爆発の大きさのベース
const float MAX_SIZE_EXPLODE = 5.0f;			// スライム4同士の爆発の大きさ
const float LEVEL_1_EXPLODE_TIME = 0.5f * 60.0f;	// スライム_1の爆発総時間
const float LEVEL_2_EXPLODE_TIME = 1.0f * 60.0f;	// スライム_2の爆発総時間
const float LEVEL_3_EXPLODE_TIME = 2.0f * 60.0f;	// スライム_3の爆発総時間
const float LEVEL_4_EXPLODE_TIME = 3.0f * 60.0f;	// スライム_4の爆発総時間

#endif
// =============== クラス定義 =====================
class CExplosionManager
{
public:
	// ===メンバ関数宣言===
	CExplosionManager();		//コンストラクタ
	~CExplosionManager();		//デストラクタ

	void Update();		 		//更新関数
	void Draw();		 		//描画関数
	
	void Create(TTriType<float> pos,float size, float time);   	//爆発生成関数
	void Create(TTriType<float> pos,float size, float time, int comboNum);   	//爆発生成関数
	void DeleteCheck();							   				// 時間より爆発を削除関数
	void ComboEndCheck();										// 爆発の連鎖が途切れたかチェックする
	void SwitchExplode(E_SLIME_LEVEL slimeLevel, TPos3d<float> pos, TTriType<float> slimeSize);					//スライムのレベルに応じて爆発を変更
	void SwitchExplode(E_SLIME_LEVEL slimeLevel, TPos3d<float> pos, TTriType<float> slimeSize, int comboNum);					//スライムのレベルに応じて爆発を変更



	CExplosion* GetExplosionPtr(int num);
	
	void SetCamera(const CCamera* pCamera);	//他のオブジェクトと同一のカメラをセット
	void SetCombo(CCombo* pCombo);


private:
	// ===メンバ変数宣言===
	CExplosion* m_pExplosion[MAX_EXPLOSION_NUM];	// 爆発の配列
	CCombo* m_pCombo;								// コンボ処理用
	const CCamera* m_pCamera;
	XAUDIO2_BUFFER* m_pSEExplode;
	IXAudio2SourceVoice* m_pSEExplodeSpeaker;


};

#endif // __EXPLOSION_MANAGER_H__