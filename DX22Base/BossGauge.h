/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	boss�o���p�w�b�_
	------------------------------------
	BossGauge.h
	------------------------------------
	�쐬��
		�A�F��
	�ύX����
	�E2023/11/17 h,�쐬 Tei
	�E2023/11/19 �{�X�Q�[�W��������ϐ��A�֐����쐬 Tei
	�E2023/11/22 �{�X�Q�[�W�t�F�[�h�p�ϐ��ǉ� Tei
	�E2023/11/26 �X���C���Ǘ������o�ϐ��ǉ�	Sawada
	�E2024/02/16 �{�X�Q�[�W�X�P�[�����[�V�����ǉ� Tei

========================================== */
#ifndef __BOSS_GAUGE_H__
#define __BOSS_GAUGE_H__

// =============== �C���N���[�h ===================
#include "Sprite.h"
#include <Texture.h>
#include "Pos3d.h"
#include "Timer.h"
#include "SlimeManager.h"
#include "2dPolygon.h"	//���ʃ|���S��
#include <vector>
#include "Camera.h"
#include "ShowWarning.h"

// =============== �N���X��` =====================
class CBossgauge
{
public:
	// ===�񋓒�`===========
	typedef struct
	{
		int	 nBossNum;			// �����{�X���
		bool bDelFlg;			// �폜�t���O
		bool bFadeFlg;			// �t�F�[�h�t���O
		int	nStartFrame;		// �J�n����Frame
		int nMaxGaugeFrame;		// �ő�lFrame
		int nGaugeCnt;			// �Q�[�W���Z
		int nFadeCnt;			// �t�F�[�h���Z
		float fGaugeDispPer;	// �\������ 

	}BossGauge;	// �{�X�Q�[�W�p�����[�^

public:
	// ===�v���g�^�C�v�錾===
	CBossgauge(CTimer* pTimer);
	~CBossgauge();
	void Update();
	void Draw();

	void DrawFrame(std::vector<BossGauge>::iterator itr);	// �{�X�Q�[�W�g�\��
	void DrawGauge(std::vector<BossGauge>::iterator itr);	// �{�X�Q�[�W�����ʕ`��֐�

	void SetSlimeManager(CSlimeManager* pSlimeMng);
	void SetShowWarning(CShowWarning* pShowWarn);

	void AddBossGauge(int BossNum, float fStartTime, float fMaxTime);
	void BossGaugeScaleMotion(float fSize, int nFlame);	//�{�X�Q�[�W�X�P�[���֐�

private:
	// ===�����o�ϐ��錾===
	Texture* m_pTexFrame;
	Texture* m_pTexGauge;
	CTimer* m_pTimer;						// �c�莞�Ԃ̃|�C���^
	CSlimeManager* m_pSlimeMng;				// �X���C���Ǘ�(�{�X�����Ŏg�p����)
	std::vector<BossGauge> m_BossGauges;	// �{�X�Q�[�W�Ǘ��z��(�X�e�[�W���ɐ������鐔�z��Ɋi�[����)

	CShowWarning* m_pShowWarn;				// �{�X�x��

	float m_fBossgaugeScale;				// �{�X�Q�[�W�X�P�[���{��
	int m_nBossgaugeScaleCnt;				// �{�X�Q�[�W�X�P�[���̃t���[���J�E���g
};


#endif // __BOSS_GAUGE_H__