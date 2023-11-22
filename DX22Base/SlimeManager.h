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

   ======================================== */
#ifndef __SLIME_MANAGER_H__
#define __SLIME_MANAGER_H__

// =============== �C���N���[�h ===================
#include "TriType.h"
//#include "SlimeBase.h"
#include "ExplosionManager.h"
#include "Camera.h"
#include "ExplosionManager.h"
#include "Slime_BossBase.h"
#include "GameParameter.h"		//�萔��`�p�w�b�_�[


// =============== �萔��` =======================
#if MODE_GAME_PARAMETER

#else
const int MAX_SLIME_NUM = 30;			// �X���C���̍ő吶����
const int MAX_BOSS_SLIME_NUM = 5;		// �{�X�X���C���̍ő吶����

#endif
// =============== �N���X��` =====================
class CSlimeManager
{
public:
	// ===�v���g�^�C�v�錾===
	CSlimeManager();
	~CSlimeManager();

	void Update(CExplosionManager* pExpMng);
	void Draw();
	void Create(E_SLIME_LEVEL level);

	//-- �m�[�}���A���̑�
	void HitBranch(int HitSlimeArrayNum,int standSlimeArrayNum,CExplosionManager* pExpMng);			// �X���C���̐ڐG���N�����ۂ̕��򏈗�
	bool HitFlameBranch(int HitSlimeNum, int StandSlimeNum, CExplosionManager* pExpMng);			// �t���C���X���C���Ƃ̐ڐG���N�����ۂ̕��򏈗�
	void UnionSlime(E_SLIME_LEVEL level, TPos3d<float> pos);										// �X���C���̌�������
	void TouchExplosion(int DelSlime, CExplosionManager* pExpMng);									// �X���C���̔�������

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

	// �Q�b�g�֐�
	CSlimeBase* GetSlimePtr(int num);
	CSlime_BossBase* GetBossSlimePtr(int num);

	// �Z�b�g�֐�
	void SetCamera(CCamera* pCamera);		//�X���C�����ڂ��J�����̃|�C���^���Z�b�g
	void SetPlayerPos(TPos3d<float> pos);
private:
	// ===�����o�ϐ��錾=====
	int GetRandom(int min, int max);

	CSlimeBase* m_pSlime[MAX_SLIME_NUM];
	CSlime_BossBase* m_pBoss[MAX_BOSS_SLIME_NUM];
	CCamera* m_pCamera;

	TPos3d<float> m_pPlayerPos;	// �v���C���[�̍��W
	VertexShader* m_pVS;
	Model* m_pBlueModel;
	Model* m_pGreenModel;
	Model* m_pYellowModel;
	Model* m_pRedModel;
	Model* m_pFlameModel;
	Model* m_pBossModel;


	int m_CreateCnt;	// �����Ԋu�p�J�E���g

	
};

#endif // __SLIME_MANAGER_H__