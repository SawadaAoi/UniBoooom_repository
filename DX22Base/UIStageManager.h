/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	UI�Ǘ��p�w�b�_
	------------------------------------
	UIManager.h
	------------------------------------
	�쐬�� Tei

	�ύX����
	�E2023/11/28 �w�b�_�쐬UI�p�w�b�_�A�����o�|�C���^�����܂� Tei

========================================== */

#ifndef __UI_MANAGER_H__
#define __UI_MANAGER_H__

// =============== �C���N���[�h ===================
#include "TotalScore.h"
#include "BossGauge.h"
#include "StageFinishUI.h"
#include "HP_UI.h"
#include "Player.h"
#include "SlimeManager.h"

// =============== �N���X��` =====================
class CUIStageManager
{
public:
	// ===�����o�֐��錾===
	CUIStageManager(CPlayer* pPlayer,const CCamera* pCamera, CSlimeManager* pSlimeMng);
	~CUIStageManager();
	void Update();
	void Draw();
	CScoreOHManager* GetScoreMng();	//�X�R�A�}�l�[�W���[�|�C���^���擾
	CCombo* GetCombo();	//�R���{�̃|�C���^���擾
	CTimer* GetTimer();	//�^�C�}�[�̃|�C���^���擾

	
private:
	
	// ===�����o�ϐ��錾===

	//�e�K�v�ȃ����o�[�|�C���^��		
	CHP_UI* m_pHpMng;
	CTimer* m_pTimer;
	CCombo* m_pCombo;
	CBossgauge* m_pBossgauge;
	CTotalScore* m_pTotalScore;
	CScoreOHManager* m_pScoreOHMng;
	CStageFinish* m_pStageFin;
};

#endif // __UI_MANAGER_H__