/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�^�C�g���p�A�j���w�i��`(�v���C���[�p�^�[��)
	---------------------------------------
	TitleBgPlayer.h

	�쐬��	takagi

	�ύX����
	�E2024/01/29 ���� takagi
	�E2024/02/06 ����i�s takagi
	�E2024/02/12 �e�N�X�`��delete�n�ύX takagi

========================================== */

#ifndef __TITLE_BG_PLAYER_H__	//TitleBgPlayer.h�C���N���[�h�K�[�h
#define __TITLE_BG_PLAYER_H__

// =============== �C���N���[�h =====================
#include "DrawAnimation.h"	//�e�̃w�b�_
#include <list>				//�o������A�N�Z�X���z��R���e�i
#include <Texture.h>		//�e�N�X�`���Ǘ�

// =============== �N���X��` =====================
class CTitleBgPlayer :public CDrawAnim	//�w�i�A�j���[�V����
{
private:
	// ===�萔��`===========
	const std::list<std::string> LIST_ANIMATION_DUSH = {
		"Assets/Texture/Title/PlayerToRight.png",	//������E��
		"Assets/Texture/Title/PlayerToLeft.png"		//�E���獶��
	};	//����A�j���[�V�����̃t�@�C����
public:
	// ===�v���g�^�C�v�錾===
	CTitleBgPlayer();													//�R���X�g���N�^
	virtual ~CTitleBgPlayer();											//�f�X�g���N�^
	virtual void Update() final;										//�X�V
	virtual void Draw(const E_DRAW_MODE& = E_DRAW_MODE_NORMAL) final;	//�`��
private:
	// ===�ϐ��錾===========
	std::shared_ptr<CFrameCnt> m_pCounter;						//�J�E���^
	std::list<Texture*> m_pDushAnimeTexture;					//����A�j���[�V�����p�e�N�X�`���Ǘ�	TODO:shared_ptr�ɂ���
	std::list<Texture*>::const_iterator m_DushAnimeIterator;	//����A�j���[�V�����p�C�e���[�^
};	//�^�C�g���J�n�f��

#endif	//!__TITLE_BG_PLAYER_H__