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
	�E2023/11/27 �n���}�[�U��Ԋu�p�J�E���g�ǉ� Tei	
	�E2023/11/28 �_���[�W�����Ɏ󂯂�_���[�W�ʂ�ǉ� Sawada
	�E2023/12/03 �J�����̍X�V��S�����߁A�|�C���^��const���d���Ȃ����� takagi
	�E2023/12/14 �A�j���[�V�����p�̗񋓂��쐬 yamashita
	�E2023/12/14 SE�p�̗񋓂��쐬 yamashita
	�E2023/12/15 SE���O����Đ��ł���悤�ɕύX yamashita
	�E2023/12/15 ��SE�ǉ� yamashita
	�E2023/01/25 �ҋ@���[�V������ύX takagi

========================================== */
#ifndef __PLAYER_H__
#define __PLAYER_H__

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
#include "Model.h"
#include "Shadow.h"
#include "AnimeModel.h"
#include "FrameCnt.h"
// =============== �N���X��` =====================
class CPlayer
	: public CObject
{
public:
	// === �� ===
	enum SE
	{
		SE_SWING,	//�n���}�[��U��SE
		SE_RUN,			//�ړ���SE
		SE_DAMAGED,		//��_���[�W��SE
		SE_HIT_HAMMER,	//�n���}�[�ƃX���C���̐ڐGSE
		SE_HEAL,

		SE_MAX			//SE�̑���
	};
private:
	// ===�萔��`===========
	const int CNT_START_WAIT = 100;	//�ҋ@���[�V�������n�߂�܂ł̎���
public:
	// ===�v���g�^�C�v�錾===
	CPlayer();		//�R���X�g���N�^
	~CPlayer();		//�f�X�g���N�^

	void Update();	//�X�V
	void Draw();	//�`��
	void Damage(int DmgNum);	//���g��HP�����炷
	void MoveKeyboard();	// �L�[�{�[�h�p���͈ړ�
	void MoveController();	// �R���g���[���p���͈ړ�
	void MoveSizeInputSet(TPos3d<float> fInput);
	void DamageAnimation();
	void MoveCheck();
	void LoadSound();	//�T�E���h�ǂݍ��݊֐�
	void PlaySE(SE se, float volume = 1.0f);
	void Healing();

	// �Q�b�g�֐�
	tagSphereInfo GetHammerSphere();	//�����蔻�����邽�߃Q�b�^�[
	TPos3d<float>* GetPosAddress();
	CHammer* GetHammerPtr();
	bool GetCollide();							//�����蔻�肪���邩�̊m�F
	int* GetHpPtr();
	// �Z�b�g�֐�
	void SetCamera(CCamera* pCamera);
	bool GetAttackFlg();
	

private:
	// ===�v���g�^�C�v�錾===
	void LoadAnime();	//�A�j���[�V�����ǂݍ��݊֐�

	// ===�����o�ϐ��錾=====
	TPos3d<float> m_fMove;				// �ړ���
	AnimeModel* m_pModel;				//�v���C���[�̃��f��
	int m_nHp;							// �v���C���[�̗̑�
	bool m_bAttackFlg;					// �U�������ǂ����̃t���O
	int m_nNoDamageCnt;					// �v���C���[�̖��G���Ԃ��J�E���g
	bool m_bCollide;					// �v���C���[�̖��G��Ԃ̃t���O(�����蔻���OFF)
	CHammer* m_pHammer;					// �n���}�[�N���X�̃|�C���^(�v���C���[���Ǘ�����)
	CCamera* m_pCamera;					// �v���C���[��Ǐ]����J����
	bool m_DrawFlg;						// �v���C���[���_���[�W���󂯂���_�ł���t���O
	int m_FlashCnt;						// �_�ł̎��Ԃ̒���
	int m_nMoveCnt;						// �v���C���[�̈ړ��ɂ��SE�̊Ԋu
	bool m_bIntFlg;						// �n���}�[�Ԋu���ԃt���O
	float m_fIntCnt;					// �n���}�[�Ԋu���ԃJ�E���g
	float m_fTick;						//�t���[���J�E���^(0to60)
	CShadow* m_pShadow;
	CFrameCnt* m_pWaitFrameCnt;			//�ҋ@���[�V�����p�t���[���J�E���g�_�E��

	// ===��===
	enum MOTION
	{
		MOTION_STOP,	//�ҋ@
		MOTION_MOVE,	//�ړ�
		MOTION_SWING,	//�n���}�[��U��
		MOTION_MAX,	//���[�V�����̑���
	};

	//=====SE�֘A=====
	XAUDIO2_BUFFER* m_pSE[SE_MAX];
	IXAudio2SourceVoice* m_pSESpeaker[SE_MAX];
	const std::string m_sSEFile[SE_MAX] = {
		"Assets/Sound/SE/Swing.mp3",			//�n���}�[��U��
		"Assets/Sound/SE/Run.mp3",				//�ړ���SE
		"Assets/Sound/SE/PlayerDamage.mp3",		//�v���C���[�̔�_���[�W��
		"Assets/Sound/SE/HammerHit.mp3",			//�n���}�[�ƃX���C���̐ڐGSE
		"Assets/Sound/SE/HealSE.mp3" };			//�񕜃A�C�e���擾��

	//=====�A�j���[�V�����֘A=====
	AnimeModel::AnimeNo m_Anime[MOTION_MAX];		//�v���C���[�̃A�j���[�V����
	const std::string m_sAnimeFile[MOTION_MAX] = {	//�A�j���[�V�����̃t�@�C��
		"Assets/Model/player/wait_end.FBX",			//�ҋ@
		"Assets/Model/player/Dash.FBX",				//�ړ�
		"Assets/Model/player/pow.FBX",				//�X�C���O
	};			
};


#endif // !__PLAYER_H__



