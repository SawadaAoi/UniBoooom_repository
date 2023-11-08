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
   ・2023/11/08 定数定義がヘッダーにあったのでcppに移動 / 山下凌佑

   ======================================== */

#ifndef __SLIME_BASE_H__
#define __SLIME_BASE_H__


#include "Model.h"
#include "Shader.h"
//#include "TriType.h"
#include "SphereInfo.h"

// =============== 列挙定義 =======================
enum E_SLIME_LEVEL
{
	LEVEL_NONE,	//SlimeBaseで生成してまだポリモーフィズムしていない状態

	LEVEL_1,	//1段階目
	LEVEL_2,	//2段階目
	LEVEL_3,	//3段階目
	LEVEL_4,	//4段階目

	MAX_LEVEL = LEVEL_4	//最大レベルを設定	(スライムの段階が増えたら変更)
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
	void HitMove();									//スライムが吹き飛び移動状態の時に毎フレーム呼び出して移動させる
	void HitMoveStart(float speed, float angle);	//スライムが吹き飛ばされたときに速度と角度を決める
	void Reflect();									//スライムとぶつかって吹き飛ばした際に自分の移動量を減らす

	//setter
	//void SetPos(TTriType<float> pos);
	void SetPos(CSphereInfo::Sphere sphere);
	void SetUse(bool onoff);
	void SetPlayer(CSphereInfo::Sphere player);

	//getter
	//TTriType<float> GetPos();
	CSphereInfo::Sphere GetSphere();	//スライムの座標と半径を取得
	bool GetUse();
	E_SLIME_LEVEL GetSlimeLevel();	//スライムのサイズを取得
	float GetSlimeSpeed();			//スライムの移動速度を取得

protected:
	Model* m_pModel;
	VertexShader* m_pVS;

	//TTriType<float> m_pos;
	CSphereInfo::Sphere m_sphere;	//スライムの座標および半径を保存する(当たり判定も取る)
	TTriType<float> m_move;
	TTriType<float> m_scale;	
	float m_fVecAngle;			//敵の吹き飛ぶ方向
	bool m_bUse;				//使用中かフラグ
	float m_fSpeed;				//スライムの移動速度
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