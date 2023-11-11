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
	・2023/11/09 Update,NormalMoveの引数変更　変更者：澤田蒼生
	
	・2023/11/08 スライムの移動速度の定数をcppからhに移動　変更者：澤田蒼生
	・2023/11/10 カメラポインタを追加 /山下凌佑
	・2023/11/10 他のオブジェクトと同一のカメラをセットするようにした 山下凌佑
	DirectX::XMMATRIX m_Ry;				//回転
	・2023/11/12　m_Ryを追加（スライムの向きを変える時に使用） YamamotoKaito
========================================== */
#ifndef __SLIME_BASE_H__
#define __SLIME_BASE_H__

// =============== インクルード ===================
#include "Model.h"
#include "Shader.h"
#include "SphereInfo.h"
#include "Pos3d.h"
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

// =============== 定数定義 =======================
const float ENEMY_MOVE_SPEED = 0.01f;	//継承先でも使いたいのでヘッダーに書きます	山下凌佑

// =============== クラス定義 =====================

class CSlimeBase
{
public:
	// ===プロトタイプ宣言===
	CSlimeBase();
	~CSlimeBase();
	void Update(TPos3d<float> playerPos);
	void Draw(const CCamera* pCamera);

	void NormalMove(TPos3d<float> playerSphere);	// 通常時の移動処理
	void HitMove();									//スライムが吹き飛び移動状態の時に毎フレーム呼び出して移動させる
	void HitMoveStart(float speed, float angle);	//スライムが吹き飛ばされたときに速度と角度を決める
	void Reflect();									//スライムとぶつかって吹き飛ばした際に自分の移動量を減らす

	// ゲット関数
	TPos3d<float> GetPos();
	CSphereInfo::Sphere GetSphere();	//スライムの座標と半径を取得
	float GetSpeed();				//スライムの移動速度を取得
	E_SLIME_LEVEL GetSlimeLevel();		//スライムのサイズを取得
	//セット関数
	void SetSphere(CSphereInfo::Sphere Sphere);
	void SetPos(TPos3d<float> pos);
	virtual void SetSpeed() = 0;
	void SetCamera(const CCamera* pCamera);
	bool GetHitMoveFlg();
protected:
	Model* m_pModel;				//3Dモデル
	VertexShader* m_pVS;			//バーテックスシェーダーのポインタ
	TPos3d<float> m_pos;			//位置座標
	TTriType<float> m_move;			//移動量
	TTriType<float> m_scale;		//サイズ？

	float m_fVecAngle;				//敵の吹き飛ぶ方向
	float m_fSpeed;					//スライムの移動速度
	bool m_bHitMove;				//吹っ飛び中かどうか

	CSphereInfo::Sphere m_sphere;	// 当たり判定の座標および半径を保存する

	E_SLIME_LEVEL m_eSlimeSize;		//スライムの大きさの列挙
	const CCamera* m_pCamera;		//カメラのポインタ
	
	DirectX::XMMATRIX m_Ry;				//回転
private:

};


#endif // __SLIME_BASE_H__