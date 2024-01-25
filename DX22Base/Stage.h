/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�X�e�[�W�p���ۃN���X��`
	---------------------------------------
	Stage.h
	---------------------------------------
	�쐬��
			takagi
			nieda

	�ύX����
	�E2023/11/16 ���� takagi
	�E2023/11/22 �����o�ϐ���ʒǉ� nieda
	�E2023/12/04 �|�[�Y�N���X�ǉ��E�f�X�g���N�^���� takagi
	�E2023/12/05 �R�����g�C�� takagi
	�E2023/12/06 pose��pause�C���A�|�[�Y�����\�� takagi
	�E2023/12/08 �V�[���J�ڗp�ɕϐ��ǉ� takagi
	�E2023/12/12 Stage1���烁���o�ϐ����ړ� yamashita
	�E2023/12/14 BGM�̊Ǘ���SceneManager�Ɉړ� yamashita
	�E2023/12/15 �t�F�[�h�폜 takagi
	�E2023/12/16 �s�v�ȕϐ��ȂǍ폜 nieda
	�E2023/12/28 BattleData�i�[�������܂Ƃ߂��֐���ǉ�	sawada
	�E2024/01/01 �X�e�[�W���� takagi
	�E2024/01/15 GameFinish()�֐��̈����C���ERecordData()�֐��ǉ� takagi
	�E2024/01/19 GetType()�֐��폜�E���̑����t�@�N�^�����O takagi
	�E2024/01/20 ���t�@�N�^�����O���� takagi
	�E2024/01/21 �R�����g���C takagi

========================================== */

#ifndef __STAGE_H__	//Stage.h�C���N���[�h�K�[�h
#define __STAGE_H__

// =============== �C���N���[�h ===================
#include "Scene.h"				//�e�̃w�b�_
#include "Shader.h"
#include "Collision.h"
#include "Player.h"
#include "SlimeManager.h"
#include "ExplosionManager.h"
#include "Floor.h"
#include "Timer.h"
#include "StageFinishUI.h"
#include "Combo.h"
#include "HP_UI.h"
#include "DirectWrite.h"
#include "Timer.h"
#include "Pause.h"				//�����o�̃w�b�_
#include "BossGauge.h"
#include "ScoreOHManager.h"
#include "TotalScore.h"
#include "Sound.h"
#include "UIStageManager.h"
#include "BattleData.h"			//�����o�̃w�b�_
#include "GameStartText.h"
#include "BossArrow.h"

// =============== �N���X��` =====================
class CStage :public CScene	//�V�[��
{
public:
	// ===�v���g�^�C�v�錾===
	CStage();				//�R���X�g���N�^
	virtual ~CStage();		//�f�X�g���N�^
	virtual void Update() override;	//�X�V
	virtual void Draw() const override;	//�`��
	void Collision();		//�����蔻��
protected:
	// ===�����o�ϐ��錾===
	CPause* m_pPause;							//�|�[�Y���
	BattleData m_Data;							//�퓬�f�[�^�L�^�p�ϐ�


	CHP_UI* m_pHpMng;
	CTimer* m_pTimer;
	CCombo* m_pCombo;
	CBossGauge* m_pBossGauge;
	CTotalScore* m_pTotalScore;
	CScoreOHManager* m_pScoreOHMng;
	CStageFinish* m_pStageFin;
	CBossArrow* m_pBossArrow;

	CFloor* m_pFloor;
	CPlayer* m_pPlayer;
	CGeometry* m_pBox;
	CSlimeManager* m_pSlimeMng;
	CCollision* m_pCollision;
	CExplosionManager* m_pExplosionMng;
	Texture* m_pTexture;
	CHealItemManager* m_pHealItemMng;
	CStartText* m_pStartText;	// �Q�[���X�^�[�g�`��

	// ===�v���g�^�C�v�錾===
	virtual void RecordData() = 0;	//�f�[�^�L�^
private:
	// ===�v���g�^�C�v�錾===
	void PlayerSlimeCollision();			//�v���C���[�ƃX���C���̓����蔻��
	void PlayerBossCollision();				//�v���C���[�ƃ{�X�̓����蔻��
	void PlayerHealItemCollision();			//�v���C���[�Ɖ񕜃A�C�e���̓����蔻��
	void HammerSlimeCollision();			//�n���}�[�Ɖ񕜃A�C�e���̓����蔻��
	void HammerBossCollision();				//�n���}�[�ƃ{�X�̓����蔻��
	void SlimeSlimeCollision();				//�X���C���ƃX���C���̓����蔻��
	void SlimeBossCollision();				//�X���C���ƃ{�X�̓����蔻��
	void BossSlimeCollision();				//�{�X�ƃX���C���̓����蔻��
	void BossBossCollision();				//�{�X�ƃ{�X�̓����蔻��
	void ExplosionBossCollision();			//�����ƃ{�X�̓����蔻��
	void ExplosionSlimeCollision();			//�����ƃX���C���̓����蔻��
	void SlimeSlimeNormalMoveCollision();	//�X���C���ƃX���C���̏d������
	void SlimeBossNormalMoveCollision();	//�X���C������{�X�ւ̏d������
	void BossSlimeNormalMoveCollision();	//�{�X����X���C���ւ̏d������
	void BossBossNormalMoveCollision();		//�{�X����{�X�ւ̏d������
};	//�X�e�[�W

#endif	//!__STAGE_H__