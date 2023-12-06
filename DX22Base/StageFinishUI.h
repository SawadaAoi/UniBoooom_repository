/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	StageFinishUI�p�w�b�_
	------------------------------------
	StageFinishUI.h
	------------------------------------
	�쐬��
		yamashita
	�ύX����
	�E2023/11/20 h,�쐬 Yamashita
	�E2023/11/20 �Q�[���̃v���C��Ԃ�� yamashita

========================================== */
#ifndef __STAGE_FINISH_UI_H__
#define __STAGE_FINISH_UI_H__

// =============== �C���N���[�h ===================
#include "Texture.h"
#include "GameParameter.h"

class CStageFinish
{
public:
	enum GAME_STATE
	{
		GAME_NONE,

		GAME_PLAY,
		GAME_CLEAR,
		GAME_OVER,

		MAX_STATE
	};

	CStageFinish(int* pPlayerHp,int* pTimeCnt);
	~CStageFinish();
	void Update();
	void Draw();
	bool GetDispFlg();

private:
	void EditSprite(int);

	bool m_bDispFlg;
	GAME_STATE m_eGameState;
	const int* m_pPlayerHp;
	const int* m_pTimeCnt;
	bool m_bDeleteDisp;

	Texture* m_pTexGameClear;
	Texture* m_pTexGameOver;

	TPos2d<float> m_fUVPos;	// UV���W�ۑ��p
	int m_nCntSwitch;		// �A�j���[�V�����؂�ւ��J�E���g�p
	int m_nCntW;			// ���J�E���g�p
	int m_nCntH;			// �c�J�E���g�p
};

#endif // !__STAGE_FINISH_UI_H__