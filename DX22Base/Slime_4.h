#ifndef __SLIME_4__H__
#define __SLIME_4__H__
/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�X���C���T�C�Y4�p�w�b�_
	------------------------------------
	Slime_4.h
	------------------------------------
	�쐬�ҁ@�R�����C

	�ύX����
	�E2023/11/08 �쐬 �R�����C
	�E2023/11/08 �X���C���̈ړ����x��ݒ肷��֐����p�� �R�����C
	�E2023/11/16 �����t���R���X�g���N�^�̈����ɒ��_�V�F�[�_�[�ƃ��f���̃|�C���^��ǉ� �R�����C

========================================== */

// =============== �C���N���[�h ===================
#include "SlimeBase.h"
#include "AnimeModel.h"
// =============== �N���X��` =====================
class CSlime_4 :
	public CSlimeBase
{
public:
	// ===�v���g�^�C�v�錾===
	CSlime_4();
	CSlime_4(TPos3d<float> pos, AnimeModel* pModel);
	~CSlime_4();
	void Update(tagTransform3d playerTransform, float fSlimeMoveSpeed) override;
	void Draw()override;

	void NormalMove() override;

	void SetNormalSpeed() override;
private:
	

};


#endif __SLIME_4__H__
