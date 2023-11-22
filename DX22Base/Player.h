/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	player�p�w�b�_
	------------------------------------
	player.h
	------------------------------------
	�쐬��
		�R�{�M��
	�ύX����
	�E2023/11/03 h,�쐬 �R�{�M��
	�E2023/11/06 �_���[�W�����ǉ�,�R�����g�ǉ� �R�{�M��
	�E2023/11/08 Pos.h���C���N���[�h /�R�����C
	�E2023/11/08 �����蔻��p�̋���m_sphere��ǉ� /�R�����C
	�E2023/11/08 �v���C���[���W������ϐ���TTriType����TPos�ɕύX /�R�����C
	�E2023/11/09 GetPosAddress�ǉ��A�J�����ǉ� ���؏x��
	�E2023/11/09 �v���C���[�̖��G���Ԃ��J�E���g�̕ϐ��Ɩ��G��Ԃ̃t���O��ǉ� �R�����C
	�E2023/11/09 �v���C���[�̖��G��Ԃ��擾����Q�b�g�֐���ǉ� �R�����C
	�E2023/11/11 �v���C���[�̓_�ŏ����ǉ� Tei
	�E2023/11/14 SphereInfo�̕ύX�ɑΉ� Takagi
	�E2023/11/14 �L�[�{�[�h�̓��͈ړ��������e��K�؂Ȍ`�ɕύX Sawada
	�E2023/11/15 Object�N���X���p�������̂ŏC���@yamamoto
	�E2023/11/19 �ړ���SE���Đ� yamashita
	�E2023/11/19 ��_���[�W���ƃn���}�[��U��SE���Đ� yamashita
	�E2023/11/19 �T�E�h�t�@�C���ǂݍ��݊֐����쐬 yamashita
========================================== */

#ifndef __PLAYER_H__
#define __PLAYER_H_

// =============== �C���N���[�h ===================
#include "Shader.h"
#include "hammer.h"
#include "Geometry.h"
#include "SphereInfo.h"
#include "Transform3d.h"
#include "Pos3d.h"
#include "Camera.h"
#include "Object.h"
#include "Sound.h"
// =============== �N���X��` =====================
class CPlayer
	: public CObject
{
public:
	// ===�v���g�^�C�v�錾===
	CPlayer();		//�R���X�g���N�^
	~CPlayer();		//�f�X�g���N�^

	void Update();	//�X�V
	void Draw();	//�`��
	void Damage();	//���g��HP�����炷
	void MoveKeyboard();	// �L�[�{�[�h�p���͈ړ�
	void MoveController();	// �R���g���[���p���͈ړ�
	void MoveSizeInputSet(TPos3d<float> fInput);
	void DamageAnimation();
	void SE_Move();
	void LoadSound();	//�T�E���h�ǂݍ��݊֐�

	// �Q�b�g�֐�
	tagSphereInfo GetHammerSphere();	//�����蔻�����邽�߃Q�b�^�[
	TPos3d<float>* GetPosAddress();
	CHammer* GetHammerPtr();
	bool GetCollide();							//�����蔻�肪���邩�̊m�F
	int* GetHP();
	// �Z�b�g�֐�
	void SetCamera(const CCamera* pCamera);
	bool GetAttackFlg();
	

private:
	// ===�����o�ϐ��錾=====
	

	TPos3d<float> m_fMove;				// �ړ���
	
	int m_nHp;							// �v���C���[�̗̑�
	bool m_bAttackFlg;					// �U�������ǂ����̃t���O
	int m_nNoDamageCnt;					// �v���C���[�̖��G���Ԃ��J�E���g
	bool m_bCollide;					// �v���C���[�̖��G��Ԃ̃t���O(�����蔻���OFF)
	CHammer* m_pHammer;					// �n���}�[�N���X�̃|�C���^(�v���C���[���Ǘ�����)
	CGeometry* m_pPlayerGeo;			// �v���C���[�����\������W�I���g���[
	const CCamera* m_pCamera;			// �v���C���[��Ǐ]����J����
	CGeometry* m_pGameOver;				// �Q�[���I�[�o�[�����\������W�I���g���[
	bool m_DrawFlg;						// �v���C���[���_���[�W���󂯂���_�ł���t���O
	int m_FlashCnt;						// �_�ł̎��Ԃ̒���
	int m_nMoveCnt;						// �v���C���[�̈ړ��ɂ��SE�̊Ԋu

	XAUDIO2_BUFFER* m_pSESwingHammer;
	XAUDIO2_BUFFER* m_pSERun;
	XAUDIO2_BUFFER* m_pSEDamaged;
	IXAudio2SourceVoice* m_pSESwingHamSpeaker;
	IXAudio2SourceVoice* m_pSERunSpeaker;
	IXAudio2SourceVoice* m_pSEDamagedSpeaker;
};


#endif // !__PLAYER_H__



