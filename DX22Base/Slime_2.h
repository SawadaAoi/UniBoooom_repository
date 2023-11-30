#ifndef __SLIME_2__H__
#define __SLIME_2__H__
/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�X���C���T�C�Y2�p�w�b�_
	------------------------------------
	Slime_2.h
	------------------------------------
	�쐬�ҁ@�R�����C

	�ύX����
	�E2023/11/08 �쐬 �R�����C
	�E2023/11/08 �X���C���̈ړ����x��ݒ肷��֐����p�� �R�����C
	�E2023/11/16 �����t���R���X�g���N�^�̈����ɒ��_�V�F�[�_�[�ƃ��f���̃|�C���^��ǉ� �R�����C

========================================== */

// =============== �C���N���[�h ===================
#include "SlimeBase.h"

// =============== �N���X��` =====================
class CSlime_2 :
	public CSlimeBase
{

public:
	enum ATTACK_MOVE_TYPE
	{
		ATTACK_CHARGE,	// �ːi�O�̗���
		ATTACK_TACKLE,	// �ːi
	};
public:
	// ===�v���g�^�C�v�錾===
	CSlime_2();
	CSlime_2(TPos3d<float> pos, VertexShader* pVS, Model* pModel);
	~CSlime_2();
	void Update(tagTransform3d playerTransform) override;
	void NormalMove(tagTransform3d playerTransform) override;

	void SetNormalSpeed() override;
private:
	ATTACK_MOVE_TYPE m_AtcMoveType;
	int m_nChargeCnt;
	int m_nTackleCnt;
};


#endif __SLIME_2__H__