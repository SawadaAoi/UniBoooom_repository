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
	�E2023/12/07 �����ŃV�[���J�ڂ����邽�߂̃t���O�擾�֐��ǉ� nieda
	�E2023/12/16 �s�v�ȕϐ��ȂǍ폜 nieda	
	�E2024/01/28 �����̗�����C�� Sawada


========================================== */
#ifndef __STAGE_FINISH_UI_H__
#define __STAGE_FINISH_UI_H__

// =============== �C���N���[�h ===================
#include "Texture.h"
#include "GameParameter.h"
#include "GameClearText.h"
#include "GameOverText.h"
#include "Player.h"

class CStageFinish
{
public:
	enum GAME_STATE
	{
		GAME_PLAY,	// �v���C��
		GAME_CLEAR,
		GAME_OVER,

		MAX_STATE
	};

	CStageFinish(CCamera* pCamera, CPlayer* pPlayer,int* pTimeCnt);
	~CStageFinish();
	void Update();
	void Draw();
	bool GetGameEndFlg();	// ��ʑJ�ڃt���O�擾�p

	bool GetClearFlg();

private:
	void ChangeGameState();

	GAME_STATE m_eGameState;
	const CPlayer* m_pPlayer;
	const int* m_pTimeCnt;
	bool m_bGameEnd;

	CClearText* m_pClear;
	COverText* m_pOver;
};

#endif // !__STAGE_FINISH_UI_H__