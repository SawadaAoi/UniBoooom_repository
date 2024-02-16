/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	���G�t�F�N�g�N���X��`
	------------------------------------
	SweatEffect.h
	------------------------------------
	�쐬��	�A�F��

	�ύX����
	�E2024/02/02 ���G�t�F�N�g�N���X�쐬 Tei
	�E2024/02/13 �J�����폜 takagi

========================================== */
#ifndef __SWEAT_EFFECT_H__
#define __SWEAT_EFFECT_H__

// =============== �C���N���[�h ===================
#include "Shader.h"			//�V�F�[�_�[�N���X��`�w�b�_�[
#include "Transform3d.h"	//���[���h���W�n���w�b�_�[
#include "LibEffekseer.h"	//effekseer�p�w�b�_�[

class CSweatEffect
{
public:
	CSweatEffect(TPos3d<float> fPos, TPos3d<float> fRadian, float fTime, Effekseer::EffectRef sweatEffect);
	~CSweatEffect();
	void Update(TPos3d<float> fPos);
	void Draw();
	void DisplayTimeAdd();					// ���G�t�F�N�g�\���J�E���g���Z�����֐�

	// �Q�b�g�֐�
	bool GetDelFlg();						// �폜�t���O�擾�����֐�

private:
	
	// ===�����o�ϐ��錾===
	tagTransform3d m_Transform;
	bool			m_bDelFlg;			// �q�b�g�G�t�F�N�g�I���t���O
	int				m_nDelFrame;		// �q�b�g�G�t�F�N�g�\���J�E���g
	float			m_fEffectTime;		// �q�b�g�G�t�F�N�g������

	//=======Effekseer=======
	Effekseer::EffectRef m_SweatEffect;
	Effekseer::Handle m_efcSweatHnadle;
};

#endif //_SWEAT_EFFECT_H__