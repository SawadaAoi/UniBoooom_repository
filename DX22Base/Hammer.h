/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	Hammer用ヘッダ
	------------------------------------
	Hammer.h
	------------------------------------
	作成者
		山本凱翔
	変更履歴
	・2023/11/08 プレイヤー座標を入れる変数をTTriTypeからTPosに変更 /山下凌佑
	・2023/11/08 めちゃくちゃコメント追加した /山下凌佑
	・2023/11/08 回転による移動のSwing関数追加 /山下凌佑
	・当たり判定用のSphere変数を追加 /山下凌佑
	・当たり判定用のSphereのゲット関数を追加 /山下凌佑

========================================== */

#ifndef __HAMMER_H__
#define __HAMMER_H__

#include "Shader.h"
#include "Pos.h"
#include "SphereInfo.h"
#include "Geometry.h"
#include <DirectXMath.h>


class CHammer
{
public:
	CHammer();	//コンストラクタ
	~CHammer();	//デストラクタ

	void Update(TPos<float> pPos, float angle);	//更新関数
	void Draw();								//描画関数
	bool Gethammer();							//ハンマーを使用中かどうかのフラグを取得
	void Swing(TPos<float>pPos,float angle);	//移動による回転移動
	CSphereInfo::Sphere GetSphere();			//ハンマーのプレイヤー
private:
	DirectX::XMMATRIX m_T;			//移動の変換行列
	DirectX::XMMATRIX m_S;			//拡縮の変換行列
	DirectX::XMMATRIX m_Ry;			//Y軸の回転をする変換行列
	TPos<float> m_pos;	//ハンマーの位置座標
	CSphereInfo::Sphere m_sphere;	//ハンマーの当たり判定用の球体
	float m_nowangle;				//今の角度
	float m_stateangle;				//
	bool m_bHammer;					//ハンマーを使用中のフラグ
	CGeometry* m_pHammerGeo;		//ハンマーを仮表示する図形
};

#endif // !__HAMMER_H__

