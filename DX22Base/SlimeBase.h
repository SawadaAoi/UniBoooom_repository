/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   スライムベース クラス定義
   ---------------------------------------
   SlimeBase.h

   作成者 鈴村 朋也

   変更履歴
   ・2023/11/04 スライムベースクラス作成 /鈴村 朋也


   ======================================== */

#ifndef __SLIME_BASE_H__
#define __SLIME_BASE_H__


#include "Model.h"
#include "Shader.h"
#include "TriType.h"
#include "SphereInfo.h"

#define ENEMY_MOVE_SPEED (0.01f)
const float SPEED_DOWN_RATIO = 0.6f;

/*
enum E_SLIME_LEVEL
{
	LEVEL_1,
	LEVEL_2,
	LEVEL_3,
	LEVEL_4
};
*/

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
	void SetPos(TTriType<float> pos);
	void SetUse(bool onoff);
	//getter
	TTriType<float> GetPos();
	bool GetUse();

protected:
	Model* m_pModel;
	VertexShader* m_pVS;

	TTriType<float> m_pos;
	TTriType<float> m_move;
	TTriType<float> m_scale;
	float m_fSpeed;
	float m_fVecAngle;
	bool m_bUse;	//使用中かフラグ
	CSphereInfo::Sphere m_sphere;
	bool m_bHitMove;	//吹っ飛び中かどうか

	// 仮
	TTriType<float> m_playerPos;


private:

};


#endif // __SLIME_BASE_H__