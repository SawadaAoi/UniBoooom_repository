/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   �X���C���x�[�X �N���X��`
   ---------------------------------------
   SlimeManager.h

   �쐬�� �鑺 ����

   �ύX����
	�E2023/11/05 �X���C���}�l�[�W���[�N���X�쐬 Suzumura
	�E2023/11/08 �X���C�����m���ڐG�����ۂ̕��򏈗����쐬(���򂵂���ɍs�������͖������@��TODO�����Ă�����)�� Yamashita
	�E2023/11/08 �����������쐬(������̐��������͖����� Slime_2�`Slime_4���܂���������) Yamashita
	�E2023/11/09 �X���C�������֐��̖��O�ύX Sawada
	�E2023/11/09 �X���C���̂̐����������_���ɕύX Yamashita
	�E2023/11/09 �v���C���[���W�擾�̌^��TPos3d<float>�ɕύX Sawada
	�E2023/11/11 �X���C�����m���d�Ȃ�Ȃ��悤�ɂ���֐����쐬 Yamashita
	�E2023/11/14 ���X���C���̐ڐG���������쐬 Suzumura
	�E2023/11/15 �e�X���C���̃��f���̃|�C���^�ƒ��_�V�F�[�_�[�̃|�C���^��base����ړ� yamashita
	�E2023/11/15 �e���f���̓ǂݍ��݂��֐��� yamashita
	�E2023/11/19 �{�X�X���C���p�̔z���ǉ� Suzumura
	�E2023/11/21 BoooomUI�p�ϐ��ǉ� Tei
	�E2023/11/26 �{�X�����p�֐��ǉ�	Sawada
	�E2023/11/26 �X���C���Ɣ����̋����𒲂ד����邩���肷��֐����쐬 yamashita
	�E2023/11/29 �v���C���[�̃|�C���^���擾 yamashita
	�E2023/12/08 �퓢�����̃J�E���^��ǉ� takagi
	�E2023/12/15 SE�܂��𐮗� yamashita
	�E2023/12/20 UNION�ǉ� takagi
	�E2024/01/01 �{�X�����̃X���C���d���Ă��ǉ� Tei

   ======================================== */

#ifndef __SLIME_MANAGER_H__
#define __SLIME_MANAGER_H__

// =============== �C���N���[�h ===================
#include "TriType.h"
//#include "SlimeBase.h"
#include "Camera.h"
#include "ExplosionManager.h"
#include "Slime_BossBase.h"
#include "GameParameter.h"		//�萔��`�p�w�b�_�[
#include "Sound.h"
#include "ScoreOHManager.h"
#include "HealItemManager.h"
#include "UnionManager.h"		//UNION
#include "Player.h"
#include "Timer.h"
#include "Sound.h"
// =============== �萔��` =======================
#if MODE_GAME_PARAMETER
#else
const int MAX_SLIME_NUM = 50;			// �X���C���̍ő吶����
const int MAX_BOSS_SLIME_NUM = 5;		// �{�X�X���C���̍ő吶����
#endif

// =============== �N���X��` =====================
class CSlimeManager
{
public:
	enum SE
	{
		SE_HIT,				//�X���C�����m���Ԃ���SE
		SE_UNION,			//�X���C�����m��������SE
		SE_BOSS_DAMAGED,	//��_���[�W��SE
		SE_MAX				//SE�̑���
	};

	// ===�v���g�^�C�v�錾===
	CSlimeManager(CPlayer* pPlayer);
	~CSlimeManager();

	void Update(CExplosionManager* pExpMng);
	void Draw();
	void Create(E_SLIME_LEVEL level);
	void CreateBoss(int BossNum);
	bool IsBossPtrExist();

	//-- �m�[�}���A���̑�
	void HitBranch(int HitSlimeArrayNum,int standSlimeArrayNum,CExplosionManager* pExpMng);			// �X���C���̐ڐG���N�����ۂ̕��򏈗�
	bool HitFlameBranch(int HitSlimeNum, int StandSlimeNum, CExplosionManager* pExpMng);			// �t���C���X���C���Ƃ̐ڐG���N�����ۂ̕��򏈗�
	bool HitHealBranch(int HitSlimeNum, int StandSlimeNum, CExplosionManager* pExpMng);				// �t���C���X���C���Ƃ̐ڐG���N�����ۂ̕��򏈗�
	void UnionSlime(E_SLIME_LEVEL level, TPos3d<float> pos);										// �X���C���̌�������
	void TouchExplosion(int DelSlime, CExplosionManager* pExpMng, int comboNum);					// �X���C���̔�������

	//-- �{�X
	void HitSlimeBossBranch(int HitSlimeNum, int StandBossNum, CExplosionManager* pExpMng);
	void HitBossSlimeBranch(int HitBossNum, int StandSlimeNum, CExplosionManager* pExpMng);
	void HitBossBossBranch(int HitBossNum, int StandBossNum, CExplosionManager* pExpMng);
	void TouchBossExplosion(int BossSlime, CExplosionManager* pExpMng, int ExpNum);

	E_SLIME_LEVEL GetRandomLevel();																	// �����_���ȃX���C���̃��x����Ԃ�(1�`3���׃�)
	void PreventSlimeSlimeOverlap(CSlimeBase* pMoveSlime, CSlimeBase* pStandSlime);							// �X���C�����m���ړ����ɐڐG�������̏���
	void PreventSlimeBossOverlap(CSlimeBase* pMoveSlime, CSlime_BossBase* pStandBoss);							// �X���C�����m���ړ����ɐڐG�������̏���
	void PreventBossSlimeOverlap(CSlime_BossBase* pMoveBoss, CSlimeBase* pStandSlime);							// �X���C�����m���ړ����ɐڐG�������̏���
	void PreventBossBossOverlap(CSlime_BossBase* pMoveBoss, CSlime_BossBase* pStandBoss);							// �X���C�����m���ړ����ɐڐG�������̏���
	void LoadModel();
	void OutOfRange();
	void CheckExplosion();

	void PlaySE(SE se,float volume = 1.0f);
	void RigidCheck(CSlime_BossBase* pBossSlime);	//�{�X�X���C���Ƒ��̃X���C���̋����v�Z
	void ScreenShake();
	//�Q�b�g�֐�
	CSlimeBase* GetSlimePtr(int num);
	CSlime_BossBase* GetBossSlimePtr(int num);

	// �Z�b�g�֐�
	void SetCamera(CCamera* pCamera);		//�X���C�����ڂ��J�����̃|�C���^���Z�b�g
	void SetScoreOHMng(CScoreOHManager* pScoreMng);
	void SetHealMng(CHealItemManager* pHealItemMng);
	void SetExplosionMng(CExplosionManager* pExpMng);
	void SetTimer(CTimer* pTimer);
	int GetKillCnt();									//�퓢�����Q�b�^
private:
	// ===�����o�ϐ��錾=====
	int GetRandom(int min, int max);

	CSlimeBase* m_pSlime[MAX_SLIME_NUM];
	CSlime_BossBase* m_pBoss[MAX_BOSS_SLIME_NUM];
	CCamera* m_pCamera;

	CPlayer* m_pPlayer;	// �v���C���[�̍��W
	VertexShader* m_pVS;
	// �X���C���̃��f��
	Model* m_pBlueModel;
	Model* m_pGreenModel;
	Model* m_pYellowModel;
	Model* m_pRedModel;
	Model* m_pFlameModel;
	Model* m_pHealModel;
	Model* m_pBossModel;
	Model* m_pBossRockModel;

	CScoreOHManager* m_pScoreOHMng;		// �X�R�A�}�l�[�W���\�|�C���^
	CHealItemManager* m_pHealItemMng;	// �񕜃A�C�e���}�l�[�W���[�|�C���^
	CUnionManager* m_pUnionMng;			// UNION�Ǘ�
	CTimer* m_pTimer;					// �^�C�}�[�|�C���^

	int m_CreateCnt;			// �����Ԋu�p�J�E���g
	TPos3d<float> m_oldCreatePos;	//1�O�̃X���C���̐����ꏊ
	CExplosionManager* m_pExpMng;
	
	int m_nKill;	//�퓢����
	bool m_bIsRigid;	//�d�����ǂ����t���O
	int m_nVibrateCnt;	//�U�����ԃJ�E���g

	bool m_bBossPtrExist;		// �{�X�̃|�C���^�����݂��邩�ǂ���
	// ===�v���g�^�C�v�錾===
	void CntKill(const CSlimeBase* pSlime);	//�퓢�����J�E���^

	void LoadSE();
	//========== SE ==========
	const std::string m_sSEFile[SE_MAX] = {
		"Assets/Sound/SE/SlimeHitSlime.mp3",	//�X���C�����m���Ԃ���SE
		"Assets/Sound/SE/Union.mp3",			//�X���C�����m��������SE
		"Assets/Sound/SE/BossDamaged.mp3" };	//��_���[�W��SE
	XAUDIO2_BUFFER* m_pSE[SE_MAX];
	IXAudio2SourceVoice* m_pSESpeaker[SE_MAX];
};

#endif // __SLIME_MANAGER_H__