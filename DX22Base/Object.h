/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	オブジェクト定義
	------------------------------------
	Object.h
	------------------------------------
	作成者	takagi

	変更履歴
	・2024/01/18 作成 takagi
	・2024/01/21 コメント改修・リファクタリング・汎化作業 takagi
	・2024/01/22 Draw()関数const化・音対応 takagi

========================================== */

#ifndef __OBJECT_H__	//Object.hインクルードガード
#define __OBJECT_H__

// =============== インクルード ===================
#include "Transform3d.h"	//メンバのヘッダ
#include "Camera.h"			//メンバのヘッダ
#include "Shader.h"			//シェーダー使用
#include "Sound.h"			//音再生

// =============== クラス定義 =====================
class CObject
{
private:
	// ===定数定義===========
	const TPos3d<float> INIT_POS = { 0.0f, 0.0f, 0.0f };		//初期位置
	const TTriType<float> INIT_SCALE = { 1.0f, 1.0f, 1.0f };	//初期拡縮
	const TTriType<float> INIT_RADIAN = 0.0f;					//初期回転
public:
	// ===プロトタイプ宣言===
	CObject();															//コンストラクタ
	CObject(const CObject& Obj);										//コピーコンストラクタ
	virtual ~CObject();													//デストラクタ
	virtual void Update() = 0;											//更新
	virtual void Draw() const = 0;										//描画
	virtual TPos3d<float> GetPos() const final;							//位置ゲッタ
	virtual const float& GetPosZ() const final;							//Z座標ゲッタ
	virtual void SetPos(const TPos3d<float>& fPos) final;				//位置セッタ
	virtual void SetSize(const TTriType<float>& fScale) final;			//大きさセッタ
	virtual void SetRotate(const TTriType<float>& fRotate) final;		//回転セッタ
	virtual void SetTransform(const tagTransform3d& Transform) final;	//ワールド座標セッタ
	virtual void SetCamera(const CCamera* pCamera);						//カメラセッタ
	virtual void PlaySe(const std::map<int, XAUDIO2_BUFFER*>& pSe,
		const int& nKey, const float& fVolume = 1.0f);					//SE音源登録
	virtual void SetVertexShader(VertexShader* pVs) = 0;				//頂点シェーダセッタ
	virtual void SetPixelShader(PixelShader* pPs) = 0;					//ピクセルシェーダセッタ
	//void* operator new(size_t _Size);									//"new"演算子オーバーロード
	//void operator delete(void* pPointer);								//"delete"演算子オーバーロード
protected:
	// ===メンバ変数宣言=====
	tagTransform3d m_Transform;	//ワールド座標
	std::map<int, IXAudio2SourceVoice*> m_pListener;	//音再生部(各シーンで定義したSEの列挙をキーとする)
	const CCamera* m_pCamera;							//カメラ追跡
	static const CCamera* ms_pCameraDef;				//疑似カメラ
private:
	static int ms_nCntObject;	//自身の生成数
	unsigned int m_unMyNum;		//オブジェクト番号(ObjectDrawer用)
};	//オブジェクト

#endif	//!__OBJECT_H__