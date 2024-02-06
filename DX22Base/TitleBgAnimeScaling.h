/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�^�C�g���p�g�k�t���A�j���w�i��`
	---------------------------------------
	TitleBgAnimeScaling.h

	�쐬��	takagi

	�ύX����
	�E2024/02/06 ���� takagi

========================================== */

#ifndef __TITLE_BG_ANIME_SCALING_H__	//BgTitle.h�C���N���[�h�K�[�h
#define __TITLE_BG_ANIME_SCALING_H__

// =============== �C���N���[�h =====================
#include "DrawAnimation.h"	//�e�̃w�b�_
#include <memory.h>			//ptr�Ǘ�
#include "DiType.h"			//�����^��`
#include <array>			//�z��R���e�i

// =============== �N���X��` =====================
class CTitleBgAnimeScaling :public CDrawAnim	//�A�j���[�V����
{
public:
	// ===�v���g�^�C�v�錾===
	virtual ~CTitleBgAnimeScaling();		//�f�X�g���N�^
	virtual void Update() override;	//�X�V
protected:
	CTitleBgAnimeScaling(int, TDiType<int>, int = 1);									//�R���X�g���N�^
	virtual void SetSize(const TTriType<float>& fScale) final;							//�傫���Z�b�^
	virtual void SetScaleRate(const std::array<TTriType<float>, 2>& fScaleRate) final;	//�g�k���Z�b�^
private:
	// ===�ϐ��錾===========
	std::shared_ptr <TTriType<float>> m_pfScaleShort;		//�g�k�Ǘ��F�ŏ�
	std::shared_ptr <TTriType<float>> m_pfScaleLarge;		//�g�k�Ǘ��F�ő�
	std::shared_ptr <TTriType<float>> m_pfScaleRateShort;	//�g�k���Ǘ��F�ŏ�
	std::shared_ptr <TTriType<float>> m_pfScaleRateLarge;	//�g�k���Ǘ��F�ő�
};	//�J�n���Y�[���A�E�g����^�C�g���p�I�u�W�F�N�g

#endif	//!__TITLE_BG_ANIME_SCALING_H__