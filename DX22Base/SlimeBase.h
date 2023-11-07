/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   スライムベース クラス定義
   ---------------------------------------
   SlimeBase.h

   作成者 鈴村 朋也

   変更履歴
   ・2023/11/04 スライムベースクラス作成 /鈴村 朋也

   ・2023/11/06 吹き飛び移動と吹き飛び移動関数を作成 変更者名：山下凌佑
   ・2023/11/06 m_fSpped(敵の移動速度)とm_fVecAngle(敵の吹き飛ぶ方向)のメンバ変数を追加 変更者名：山下凌佑
   ・2023/11/06 定数SPEED_DOWN_RATIO(ぶつかった先のスライムに速度を渡す際に減少する割合)を追加 変更者名：山下凌佑
   ・2023/11/06 定数MOVE_RESIST(吹き飛び移動中のスライムの移動速度に毎フレームかかる減算数値)を追加 変更者名：山下凌佑
   ・2023/11/07 HitBranch関数(スライムとの接触分岐処理)をSlimeManagerに移動するために削除 変更者名：山下凌佑
   ・2023/11/08 スライムのサイズを表す列挙を定義　変更者：山下凌佑
   ・2023/11/08 スライムのサイズを返す関数を作成　変更者：山下凌佑
   ・2023/11/08 GetPos→GetSphereに名前を変更 / 山下凌佑
   ・2023/11/08 スライムの移動速度を取得する関数を作成 / 山下凌佑

   ======================================== */

#ifndef __SLIME_BASE_H__
#define __SLIME_BASE_H__


#include "Model.h"
#include "Shader.h"
//#include "TriType.h"
#include "SphereInfo.h"

const float ENEMY_MOVE_SPEED = 0.01f;
const float SPEED_DOWN_RATIO = 0.6f;	//スライムからスライムの吹き飛び移動を
const float MOVE_RESIST = 0.1f;		//吹き飛び移動中のスライムの移動速度に毎フレームかかる減算数値

// =============== 列挙定義 =======================
enum E_SLIME_LEVEL
{
	LEVEL_NONE,

	LEVEL_1,
	LEVEL_2,
	LEVEL_3,
	LEVEL_4,

	MAX_LEVEL = LEVEL_4
};


class CSlimeBase
{
public:
	CSlimeBase();
	~CSlimeBase();
	void Update();
	void Draw();

	virtual void Union() = 0;
	virtual void Explosion() = 0;
	void HitMove();
	void HitMoveStart(float speed, float angle);

	//setter
	//void SetPos(TTriType<float> pos);
	void SetPos(CSphereInfo::Sphere sphere);
	void SetUse(bool onoff);
	void SetPlayer(CSphereInfo::Sphere player);

	//getter
	//TTriType<float> GetPos();
	CSphereInfo::Sphere GetSphere();
	bool GetUse();
	E_SLIME_LEVEL GetSlimeLevel();	//スライムのサイズを取得
	float GetSlimeSpeed();			//スライムの移動速度を取得

protected:
	Model* m_pModel;
	VertexShader* m_pVS;

	//TTriType<float> m_pos;
	CSphereInfo::Sphere m_sphere;
	TTriType<float> m_move;
	TTriType<float> m_scale;
	float m_fVecAngle;	//敵の吹き飛ぶ方向
	bool m_bUse;	//使用中かフラグ
	float m_fSpeed;       //スライムの移動速度
	E_SLIME_LEVEL m_eSlimeSize; //スライムの大きさの列挙


	float m_distancePlayer;	//プレイヤーまでの距離
	float m_anglePlayer;	//プレイヤーからエネミーのアークタンジェント
	bool m_bHitMove;	//吹っ飛び中かどうか

	// 仮
	//TTriType<float> m_playerPos;
	CSphereInfo::Sphere m_playerSphere;

private:

};


#endif // __SLIME_BASE_H__