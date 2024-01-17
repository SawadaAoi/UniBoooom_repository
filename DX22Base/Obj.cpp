#include "Obj.h"

const TPos3d<float> INIT_POS(640.0f, 360.0f, 0.0f);	//位置初期化
const TTriType<float> INIT_SCALE(1.0f, 1.0f, 0.0f);	//初期拡縮
const TTriType<float> INIT_RADIAN(0.0f);			//初期回転

CObj::CObj()
	:m_Transform(INIT_POS, INIT_SCALE, INIT_RADIAN)	//ワールド座標
{
}

const float & CObj::GetPosZ()
{
	// TODO: return ステートメントをここに挿入します
}
