#include "Obj.h"

const TPos3d<float> INIT_POS(640.0f, 360.0f, 0.0f);	//�ʒu������
const TTriType<float> INIT_SCALE(1.0f, 1.0f, 0.0f);	//�����g�k
const TTriType<float> INIT_RADIAN(0.0f);			//������]

CObj::CObj()
	:m_Transform(INIT_POS, INIT_SCALE, INIT_RADIAN)	//���[���h���W
{
}

const float & CObj::GetPosZ()
{
	// TODO: return �X�e�[�g�����g�������ɑ}�����܂�
}
