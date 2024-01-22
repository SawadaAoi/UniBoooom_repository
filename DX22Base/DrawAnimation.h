/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	UI�A�j���[�V�����`��p�w�b�_
	---------------------------------------
	DrawAnimation.h
	---------------------------------------
	�쐬��	nieda

	�ύX����
	�E2023/12/08 �V�K�쐬 nieda
	�E2023/12/09 ���� nieda
	�E2023/12/11 ���� nieda
	�E2023/12/12 tkg�搶�̎w���ɂ��2dpolygon�ɑΉ� nieda
	�E2023/12/15 �`��T�C�Y�֘A�̕ϐ��ǉ��A�R���X�g���N�^�C�� nieda
	�E2023/12/16 �`��ʒu�ǉ� nieda
	�E2023/12/16 �R���X�g���N�^�̈������ŏ����E�s�v�ȃ|�C���^�폜 takagi
	�E2023/12/17 �ꕔ�����Q�Ɖ� takagi
	�E2024/01/20 ���t�@�N�^�����O takagi
	�E2024/01/21 �R�����g���C takagi
	�E2024/01/22 Draw()�֐�const�� takagi

========================================== */

#ifndef __DRAW_ANIMATION_H__	//DrawAnimation.h�C���N���[�h�K�[�h
#define __DRAW_ANIMATION_H__

// =============== �C���N���[�h ===================
#include "Texture.h"
#include "CameraChase.h"
#include "Pos2d.h"
#include "2dObject.h"

// =============== �N���X��` =====================
class CDrawAnim :public C2dObject	//���ʃI�u�W�F
{
public:
	// ===�v���g�^�C�v�錾===
	CDrawAnim(int, TDiType<int>, int = 1);	//�R���X�g���N�^
	~CDrawAnim() {};						//�f�X�g���N�^
	void Update();							//�X�V�֐�
	void Draw() const override;				//�`��֐�
	void SetLoopFlg(bool);					//���[�v�Đ��t���O���Z�b�g
	bool GetAnimFlg();						//�t���O�擾

protected:
	// ===�����o�ϐ��錾=====
	int m_nNumAnim;				//�A�j���[�V�����ԍ�
	int m_nNumAnimMax;			//�A�j���[�V�����̍ő吔
	TDiType<int> m_nSplitNum;	//������
	TDiType<float> m_fUvPos;	//UV���W
	TDiType<float> m_fUvScale;	//UV�����T�C�Y�i�[�p
	int m_nFrameCnt;			//�A�j���[�V�����̐ؑ֊Ԋu�J�E���g�p�p
	int m_nSwitchCnt;			//�A�j���[�V�����̐ؑ֊Ԋu�i�[�p
	bool m_bLoop;				//���[�v����t���O
	bool m_bAnim;				//�`�攻��t���O
};	//2D�A�j���[�V����

#endif	//!__DRAW_ANIMATION_H__