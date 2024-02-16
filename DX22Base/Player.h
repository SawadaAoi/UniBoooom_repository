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
	�E2024/01/25 �ҋ@���[�V������ύX takagi
	�E2024/01/26 �x��SE�ǉ� suzumura
	�E2024/01/28 ���S���[�V�����ǉ� Sawada
	�E2024/01/30 �v���C���[�ړ��G�t�F�N�g�p�ϐ��A�֐��ǉ�
	�E2024/02/02 ���G�t�F�N�g�����ǉ� Tei
	�E2024/02/09 �J�����폜 takagi

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
#include "Object.h"
#include "Sound.h"
#include "Model.h"
#include "Shadow.h"
#include "AnimeModel.h"
#include "FrameCnt.h"
#include "WalkEffectManager.h"
#include "SweatEffectManager.h"

// =============== �N���X��` =====================
class CPlayer: public CObject
{
public:
	// === �� ===
	enum SE
	{
		SE_SWING,		// �n���}�[��U��SE
		SE_RUN,			// �ړ���SE
		SE_DAMAGED,		// ��_���[�W��SE
		SE_HIT_HAMMER,	// �n���}�[�ƃX���C���̐ڐGSE
		SE_HEAL,		// ��SE
		SE_WARNING,		// �c��̗͂P
		SE_CHARGED,		// �`���[�W������

		SE_MAX			// SE�̑���
	};

	// ===��===
	enum PLAYER_MOTION
	{
		MOTION_PLAYER_STOP,		// �ҋ@
		MOTION_PLAYER_MOVE,		// �ړ�
		MOTION_PLAYER_SWING,	// �n���}�[��U��
		MOTION_PLAYER_CHARGE,	// �`���[�W���
		MOTION_PLAYER_DIE,		// ���S

		MOTION_PLAYER_MAX,		//���[�V�����̑���
	};

	enum PLAYER_CHARGE_STATE {
		PLAYER_CHARGE_NONE,
		PLAYER_CHARGING,
		PLAYER_CHARGED,
		

	};

private:
	// ===�萔��`===========
	const int CNT_START_WAIT = 10;	//�ҋ@���[�V�������n�߂�܂ł̎���
public:
	// ===�v���g�^�C�v�錾===
	CPlayer();		//�R���X�g���N�^
	~CPlayer();		//�f�X�g���N�^

	void Update();	//�X�V
	void Draw();	//�`��
	void Damage(int DmgNum);	//���g��HP�����炷
	
	void DamageAnimation();
	void MoveCheck();
	void LoadSound();	//�T�E���h�ǂݍ��݊֐�
	void PlaySE(SE se, float volume = 1.0f);
	void Healing();
	void CheckCharge();
	void EffectStart();
	void UpdateEffect();

	// �Q�b�g�֐�
	tagSphereInfo GetHammerSphere();	//�����蔻�����邽�߃Q�b�^�[
	TPos3d<float>* GetPosAddress();
	CHammer* GetHammerPtr();
	bool GetSafeTime();					//�����蔻�肪���邩�̊m�F
	int* GetHpPtr();
	bool GetDieFlg() const;
	bool GetAttackFlg();
	bool GetCharge();

	// �Z�b�g�֐�
	void SetSweatEffectMng(CSweatEffectManager* pSweatefcMng);

private:
	void MoveKeyboard();	// �L�[�{�[�h�p���͈ړ�
	void MoveController();	// �R���g���[���p���͈ړ�
	void MoveSizeInputSet(TPos3d<float> fInput);
	void DisplaySweatEffect();

	// ===�v���g�^�C�v�錾===
	void LoadAnime();	//�A�j���[�V�����ǂݍ��݊֐�

	// ===�����o�ϐ��錾=====
	TPos3d<float> m_fMove;				// �ړ���
	AnimeModel* m_pModel;				// �v���C���[�̃��f��

	CHammer* m_pHammer;					// �n���}�[�N���X�̃|�C���^(�v���C���[���Ǘ�����)

	CShadow* m_pShadow;
	CFrameCnt* m_pWaitFrameCnt;				// �ҋ@���[�V�����p�t���[���J�E���g�_�E��
	CWalkEffectManager* m_pWalkEffectMng;	// �v���C���[�ړ��G�t�F�N�g�p
	CSweatEffectManager* m_pSweatEffectMng;

	int m_nHp;							// �v���C���[�̗̑�
	bool m_bDieFlg;						// �v���C���[���S�t���O(true�̏ꍇ���S)

	bool m_bAttackFlg;					// �U�������ǂ����̃t���O

	int m_nSafeTimeCnt;					// �v���C���[�̖��G���Ԃ��J�E���g
	bool m_bSafeTimeFlg;				// �v���C���[�̖��G��Ԃ̃t���O(�����蔻���OFF)

	bool m_DrawFlg;						// �v���C���[���_���[�W���󂯂���_�ł���t���O(true�̏ꍇ�\��)
	int m_FlashCnt;						// �_�ł̎��Ԃ̒���

	int m_nWalkSECnt;					// �v���C���[�̈ړ��ɂ��SE�̊Ԋu

	bool m_bHumInvFlg;					// �n���}�[�Ԋu���ԃt���O
	float m_fHumInvCnt;					// �n���}�[�Ԋu���ԃJ�E���g

	bool m_bDieInvFlg;					// ���S�P�\���ԃt���O
	float m_fDieInvCnt;					// ���S�P�\���ԃJ�E���g

	float m_fRotate_x;					// �v���C���[�̕\���p�X��
	float m_fChargeCnt;					// �v���C���[�̃`���[�W�n���}�[�̃J�E���g
	bool m_bCharge;						// �`���[�W���������Ă��邩

	int m_nWalkEffeCnt;					// �������G�t�F�N�g�̕\���Ԋu���Z�l
	int m_nSweatEffeCnt;				// ���G�t�F�N�g�̕\���Ԋu���Z�l
	int m_nSwingFastCnt;				// �n���}�[��U�鎞�Ԃ̉��Z�Ԋu

	//=====SE�֘A=====
	XAUDIO2_BUFFER* m_pSE[SE_MAX];
	IXAudio2SourceVoice* m_pSESpeaker[SE_MAX];
	const std::string m_sSEFile[SE_MAX] = {
		"Assets/Sound/SE/Swing.mp3",			//�n���}�[��U��
		"Assets/Sound/SE/Run.mp3",				//�ړ���SE
		"Assets/Sound/SE/PlayerDamage.mp3",		//�v���C���[�̔�_���[�W��
		"Assets/Sound/SE/HammerHit.mp3",		//�n���}�[�ƃX���C���̐ڐGSE
		"Assets/Sound/SE/HealSE.mp3",			//�񕜃A�C�e���擾��
		"Assets/Sound/SE/Warning.mp3",			//�c��HP���P�̎�
		"Assets/Sound/SE/charge.mp3"			//�`���[�W����
	};

	//=====�A�j���[�V�����֘A=====
	const std::string m_sAnimeFile[MOTION_PLAYER_MAX] = {	//�A�j���[�V�����̃t�@�C��
		"Assets/Model/player/wait_end.FBX",			//�ҋ@
		"Assets/Model/player/Dash.FBX",				//�ړ�
		"Assets/Model/player/pow.FBX",				//�X�C���O
		"Assets/Model/player/down.fbx",				//���S
	};			

	//�G�t�F�N�g������
	Effekseer::EffectRef m_chargeEfc = LibEffekseer::Create("Assets/Effect/charge/charge.efkefc");
	Effekseer::Handle m_chgEfcHandle;
	
	PLAYER_CHARGE_STATE m_ChargeState;
};

#endif // !__PLAYER_H__