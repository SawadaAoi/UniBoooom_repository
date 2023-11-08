#ifndef __SLIME_BASE_H__
#define __SLIME_BASE_H__
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
	・2023/11/08 UnionとExplosionを削除(マネージャーに移動させたので) 変更者：澤田蒼生
	・2023/11/08 m_bUse、n_playerDistance、m_playerAngleを削除(一か所でしか使用していない為)変更者：澤田蒼生
	・2023/11/08 m_Playerを追加　変更者：澤田蒼生
	・2023/11/08 座標をTPos<Pos>に変更　変更者：澤田蒼生
	
========================================== */


// =============== インクルード ===================
#include "Model.h"
#include "Shader.h"
#include "SphereInfo.h"
#include "Pos.h"
#include "Camera.h"

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
	void Update(CSphereInfo::Sphere playerSphere);
	void Draw(const CCamera* pCamera);

	void NormalMove(CSphereInfo::Sphere playerSphere);								// 通常時の移動処理
	void HitMove();									//スライムが吹き飛び移動状態の時に毎フレーム呼び出して移動させる
	void HitMoveStart(float speed, float angle);	//スライムが吹き飛ばされたときに速度と角度を決める
	void Reflect();									//スライムとぶつかって吹き飛ばした際に自分の移動量を減らす

	void SetPos(TPos<float> pos);
	TPos<float> GetPos();


	void SetSphere(CSphereInfo::Sphere Sphere);
	CSphereInfo::Sphere GetSphere();	//スライムの座標と半径を取得


	float GetSpeed();				//スライムの移動速度を取得

	E_SLIME_LEVEL GetSlimeLevel();		//スライムのサイズを取得

protected:
	Model* m_pModel;				// 3Dモデル
	VertexShader* m_pVS;

	TPos<float> m_pos;				// 位置座標
	TTriType<float> m_move;
	TTriType<float> m_scale;	
	float m_fVecAngle;				//敵の吹き飛ぶ方向
	float m_fSpeed;					//スライムの移動速度
	bool m_bHitMove;				//吹っ飛び中かどうか

	CSphereInfo::Sphere m_sphere;	// 当たり判定の座標および半径を保存する

	E_SLIME_LEVEL m_eSlimeSize;		//スライムの大きさの列挙
	
	

private:

};


#endif // __SLIME_BASE_H__