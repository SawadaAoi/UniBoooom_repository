/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	StageFinishUI�p�w�b�_
	------------------------------------
	StageFinishUI.h
	------------------------------------
	�쐬��	yamashita

	�ύX����
	�E2023/11/20 h,�쐬 yamashita
	�E2023/11/20 �Q�[���̃v���C��Ԃ�� yamashita
	�E2023/12/07 �����ŃV�[���J�ڂ����邽�߂̃t���O�擾�֐��ǉ� nieda
	�E2023/12/16 �s�v�ȕϐ��ȂǍ폜 nieda
	�E2024/01/20 �R�����g���C takagi
	�E2024/01/21 �R�����g���C takagi

========================================== */

#ifndef __STAGE_FINISH_UI_H__	//StageFinishUI.h�C���N���[�h�K�[�h
#define __STAGE_FINISH_UI_H__

// =============== �C���N���[�h ===================
#include "Texture.h"
#include "GameParameter.h"
#include "GameClearText.h"
#include "GameOverText.h"

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

	CStageFinish(CCamera* pCamera, int* pPlayerHp,int* pTimeCnt);
	~CStageFinish();
	void Update();
	void Draw();
	bool GetGameEndFlg();	// ��ʑJ�ڃt���O�擾�p

	bool GetClearFlg();

private:
	GAME_STATE m_eGameState;
	const int* m_pPlayerHp;
	const int* m_pTimeCnt;
	bool m_bGameEnd;

	CClearText* m_pClear;
	COverText* m_pOver;
};

#endif	//!__STAGE_FINISH_UI_H__