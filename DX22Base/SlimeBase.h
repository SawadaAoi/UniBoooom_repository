/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   スライムベース クラス定義
   ---------------------------------------
   SlimeBase.h

   作成者 鈴村 朋也

   変更履歴
   ・2023/11/04 スライムベースクラス作成 /鈴村 朋也
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
const float SPEED_DOWN_RATIO = 0.6f;
const float MOVE_RESIST = 0.05f;

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
	virtual void HitBranch() = 0;

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
	float m_fVecAngle;
	bool m_bUse;	//使用中かフラグ
	float m_fSpeed;
	E_SLIME_LEVEL m_eSlimeSize;

	float m_distancePlayer;	//プレイヤーまでの距離
	float m_anglePlayer;	//プレイヤーからエネミーのアークタンジェント
	bool m_bHitMove;	//吹っ飛び中かどうか

	// 仮
	//TTriType<float> m_playerPos;
	CSphereInfo::Sphere m_playerSphere;

private:

};


#endif // __SLIME_BASE_H__