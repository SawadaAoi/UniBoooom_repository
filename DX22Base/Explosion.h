/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	���������N���X��`�w�b�_
	---------------------------------------
	Expplosion.h

	�쐬�� �A �F��

	�ύX����
	�E2023/11/03 �w�b�_�[�쐬 Tei
	�E2023/11/05 �p�����[�^�ݒ� Tei
	�E2023/11/07 �ϐ��^TriType��CSphere�� Tei
	�E2023/11/08 �ϐ��A�֐��̕ύX Sawada
	�E2023/11/10 �J�����|�C���^��ǉ� Ymashita
	�E2023/11/13 �R���X�g���N�^��time��ǉ� Suzumura
	�E2023/11/13 ���������Ԃ̕ϐ���ǉ� Suzumura
	�E2023/11/14 SphereInfo�̕ύX�ɑΉ� Takagi
	�E2023/11/15 Object�N���X���p�������̂ŏC���@yamamoto
	�E2023/11/19 �{�X�ɗ^����_���[�W�ϐ���ǉ� Suzumura
	�E2023/11/20 �R���{���z��Y�����̒ǉ� Sawada
	�E2023/11/21 �����l�̐ݒ�ƁA�x�������̒ǉ� Sawada
	�E2023/11/21 �{�X�Ɉ�x�G�������𔻒�p�̊֐��A�ϐ��ǉ� Suzumura
	�E2023/12/04 �����̃G�t�F�N�g������ yamasita
	�E2023/12/04 �����̉��\��3D���f�����폜 yamasita
======================================== */
#ifndef __EXPLOSION_H__	//Explosion.h�C���N���[�h�K�[�h
#define __EXPLOSION_H__

// =============== �C���N���[�h ===================
#include "Shader.h"			//�V�F�[�_�[�N���X��`�w�b�_�[
#include "Sphereinfo.h"		//���̏��p�w�b�_�[
#include "Transform3d.h"	//���[���h���W�n���w�b�_�[
#include "CameraChase.h"	//�J������`�w�b�_�[
#include "Object.h"			//
#include "BoooomUI.h"
#include "LibEffekseer.h"

//=============== �N���X��` =====================
class CExplosion
	:public CObject
{
public:
	// ===�����o�֐��錾===
	CExplosion(TPos3d<float> fPos, float fSize, float fTime, int comboNum, bool delayFlg, int nDamage, Effekseer::EffectRef explodeEffect,const CCamera* pCamera);	//�R���X�g���N�^
	~CExplosion();												// �f�X�g���N�^
	void Update();												// �X�V�֐�
	void Draw();												// �`��֐�
	void DisplayTimeAdd();										// �����\���J�E���g���Z�����֐�
	void Delay();
	void BossTouched();											//�{�X�ɐG�����Ƃ��ɌĂяo���֐�

	// �Z�b�g�֐�
	void SetCamera(const CCamera* m_pCamera);	// ���̃I�u�W�F�N�g�Ɠ���̃J�������Z�b�g

	// �Q�b�g�֐�
	bool GetDelFlg();				// �폜�t���O�擾�����֐�
	int GetDamage();				// �_���[�W�ʎ擾�֐�
	bool GetBossTouched();			// ���Ƀ{�X�Ɠ������Ă��邩�ǂ����擾�֐�
	int GetComboNum();				// �R���{�z��ԍ��擾

private:
	// ===�����o�ϐ��錾===
	float			m_fMaxSize;
	TTriType<float>	m_fSizeAdd;
	int				m_nDelFrame;		// �����\���J�E���g
	bool			m_bDelFlg;			// �����I���t���O
	float			m_fExplodeTime;		// ����������
	float			m_fDamage;			// �{�X�ɗ^����_���[�W��
	bool			m_bBossTouched;		// ���Ƀ{�X�ƐڐG���邩�ǂ���

	const CCamera*	m_pCamera;	//�J�����̃|�C���^
	int m_dComboNum;			// �R���{�z��ԍ�

	bool m_bDelayFlg;		// �����x���t���O
	int m_dDelayCnt;		// �J�E���g�_�E���J�n�t���[�����Z�l

	Effekseer::EffectRef m_explodeEffect;
	Effekseer::Handle m_efcHnadle;
};

#endif // __EXPLOSION_H__
