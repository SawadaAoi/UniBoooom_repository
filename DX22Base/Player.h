/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�v���C���[�p�w�b�_
	------------------------------------
	Player.h
	------------------------------------
	�쐬��	yamamoto

	�ύX����
	�E2023/11/03 h,�쐬 yamamoto
	�E2023/11/06 �_���[�W�����ǉ�,�R�����g�ǉ� yamamoto
	�E2023/11/08 Pos.h���C���N���[�h yamashita
	�E2023/11/08 �����蔻��p�̋���m_sphere��ǉ� yamashita
	�E2023/11/08 �v���C���[���W������ϐ���TTriType����TPos�ɕύX yamashita
	�E2023/11/09 GetPosAddress�ǉ��A�J�����ǉ� takagi
	�E2023/11/09 �v���C���[�̖��G���Ԃ��J�E���g�̕ϐ��Ɩ��G��Ԃ̃t���O��ǉ� yamashita
	�E2023/11/09 �v���C���[�̖��G��Ԃ��擾����Q�b�g�֐���ǉ� yamashita
	�E2023/11/11 �v���C���[�̓_�ŏ����ǉ� tei
	�E2023/11/14 SphereInfo�̕ύX�ɑΉ� takagi
	�E2023/11/14 �L�[�{�[�h�̓��͈ړ��������e��K�؂Ȍ`�ɕύX sawada
	�E2023/11/15 Object�N���X���p�������̂ŏC���@yamamoto
	�E2023/11/19 �ړ���SE���Đ� yamashita
	�E2023/11/19 ��_���[�W���ƃn���}�[��U��SE���Đ� yamashita
	�E2023/11/19 �T�E�h�t�@�C���ǂݍ��݊֐����쐬 yamashita
	�E2023/11/27 �n���}�[�U��Ԋu�p�J�E���g�ǉ� tei	
	�E2023/11/28 �_���[�W�����Ɏ󂯂�_���[�W�ʂ�ǉ� sawada
	�E2023/12/03 �J�����̍X�V��S�����߁A�|�C���^��const���d���Ȃ����� takagi
	�E2023/12/14 �A�j���[�V�����p�̗񋓂��쐬 yamashita
	�E2023/12/14 SE�p�̗񋓂��쐬 yamashita
	�E2023/12/15 SE���O����Đ��ł���悤�ɕύX yamashita
	�E2023/12/15 ��SE�ǉ� yamashita
	�E2024/01/20 ���t�@�N�^�����O takagi
	�E2024/01/21 �R�����g���C�E�ĉ���� takagi

========================================== */

#ifndef __PLAYER_H__	//Player.h�C���N���[�h�K�[�h
#define __PLAYER_H__

// =============== �C���N���[�h ===================
#include "Shader.h"
#include "hammer.h"
#include "Geometry.h"
#include "SphereInfo.h"
#include "Transform3d.h"
#include "Pos3d.h"
#include "Camera.h"
#include "3dObject.h"		//3D�I�u�W�F�N�g
#include "Model.h"
#include "Shadow.h"

// =============== �N���X��` =====================
class CPlayer :public C3dObject
{
public:
	// === �� ===
	enum E_SE
	{
		E_SE_SWING,			//�n���}�[��U��SE
		E_SE_RUN,			//�ړ���SE
		E_SE_DAMAGED,		//��_���[�W��SE
		E_SE_HIT_HAMMER,	//�n���}�[�ƃX���C���̐ڐGSE
		E_SE_HEAL,			//�񕜂�SE
		E_SE_MAX			//SE�̑���
	};	//SE
private:
	enum E_MOTION
	{
		E_MOTION_STOP,	//�ҋ@
		E_MOTION_MOVE,	//�ړ�
		E_MOTION_SWING,	//�n���}�[��U��
		E_MOTION_MAX,	//���[�V�����̑���
	};	//���[�V����
	// ===�萔��`===========
	const std::map<int, XAUDIO2_BUFFER*> MAP_SE = {
	{E_SE_SWING, CSound::LoadSound("Assets/Sound/SE/Swing.mp3", true)},				//�n���}�[��U��
	{ E_SE_RUN, CSound::LoadSound("Assets/Sound/SE/Run.mp3", true) },				//�ړ���SE
	{ E_SE_DAMAGED, CSound::LoadSound("Assets/Sound/SE/PlayerDamage.mp3", true) },	//�v���C���[�̔�_���[�W��
	{ E_SE_HIT_HAMMER, CSound::LoadSound("Assets/Sound/BGM/BGM_maou.mp3", true) },	//�n���}�[�ƃX���C���̐ڐGSE
	{ E_SE_HEAL, CSound::LoadSound("Assets/Sound/SE/��1.mp3", true) },			//�񕜃A�C�e���擾��
	};	//SE�f�[�^
	const std::map<int, std::string> MAP_ANIMATION_PASS = {
	{E_MOTION_STOP, "Assets/Model/player/Player.FBX"},	//�ҋ@
	{E_MOTION_MOVE, "Assets/Model/player/Dash.FBX"},	//�ړ�
	{E_MOTION_SWING, "Assets/Model/player/pow.FBX"},	//�X�C���O
	};	//�A�j���[�V�����̃t�@�C��
	const std::string MODEL_PASS = "Assets/Model/player/POW.fbx";	//���f���̃t�@�C��
public:
	// ===�v���g�^�C�v�錾===
	CPlayer();					//�R���X�g���N�^
	~CPlayer();					//�f�X�g���N�^
	void Update();				//�X�V
	void Draw() const;			//�`��
	void Damage(int DmgNum);	//���g��HP�����炷
	void MoveKeyboard();			// �L�[�{�[�h�p���͈ړ�
	void MoveController();								// �R���g���[���p���͈ړ�
	void MoveSizeInputSet(TPos3d<float> fInput);
	void DamageAnimation();
	void MoveCheck();
	void Healing();
	tagSphereInfo GetHammerSphere();	//�����蔻�����邽�߃Q�b�^�[
	TPos3d<float>* GetPosAddress();
	CHammer* GetHammerPtr();
	bool GetCollide();							//�����蔻�肪���邩�̊m�F
	int* GetHpPtr();
	bool GetAttackFlg();
	virtual void SetCamera(const CCamera* pCamera) override;			//�J�����Z�b�^
	virtual void PlaySe(const E_SE& eKey, const float& fVolume = 1.0f);	//SE�����o�^
private:
	// ===�����o�ϐ��錾=====
	TPos3d<float> m_fMove;	//�ړ���
	int m_nHp;				//�v���C���[�̗̑�
	bool m_bAttackFlg;		//�U�������ǂ����̃t���O
	int m_nNoDamageCnt;		//�v���C���[�̖��G���Ԃ��J�E���g
	bool m_bCollide;		//�v���C���[�̖��G��Ԃ̃t���O(�����蔻���OFF)
	CHammer* m_pHammer;		//�n���}�[�N���X�̃|�C���^(�v���C���[���Ǘ�����)
	bool m_DrawFlg;			//�v���C���[���_���[�W���󂯂���_�ł���t���O
	int m_FlashCnt;			//�_�ł̎��Ԃ̒���
	int m_nMoveCnt;			//�v���C���[�̈ړ��ɂ��SE�̊Ԋu
	bool m_bIntFlg;			//�n���}�[�Ԋu���ԃt���O
	float m_fIntCnt;		//�n���}�[�Ԋu���ԃJ�E���g
	float m_fTick;			//���[���J�E���^(0to60)
	CShadow* m_pShadow;		//�e
};

#endif	//!__PLAYER_H__