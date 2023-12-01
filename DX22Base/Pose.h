/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�|�[�Y��ʒ�`
	---------------------------------------
	Pose.h

	�쐬��	takagi

	�ύX����
	�E2023/12/01 ���� takagi

========================================== */

#ifndef __RESULT_H__	//Pose.h�C���N���[�h�K�[�h
#define __RESULT_H__

#include "Sound.h"		//��
#include "Camera.h"		//�J����
#include "2dPolygon.h"	//���ʃ|���S��
#include <vector>		//�z��R���e�i

// =============== �N���X��` =====================
class CPose
{
public:
	// ===�v���g�^�C�v�錾===
	CPose(CCamera* pCamera);	//�R���X�g���N�^
	~CPose();					//�f�X�g���N�^
	void Update();				//�X�V
	void Draw();				//�`��
	bool IsFin() const;			//�I���m�F
protected:
	// ===�����o�ϐ��錾=====
	bool m_bFinish;									//�I���\��p(true�ŏI��)
	std::vector<C2dPolygon*> m_2dObj;				//���ʃ|���S��
	PixelShader* m_pBgPs;							//�w�i�p�s�N�Z���V�F�[�_
	VertexShader* m_pBgVs;							//�w�i�p���_�V�F�[�_
	CCamera* m_pCamera;								//�J����
	XAUDIO2_BUFFER* m_pBGM;							//BGM�̉����f�[�^
	XAUDIO2_BUFFER* m_pSEHitHammer;					//SE�̉����f�[�^
	IXAudio2SourceVoice* m_pSpeaker;				//BGM�𕷂���鑤
	IXAudio2SourceVoice* m_pSEHitHammerSpeaker;		//SE�𕷂���鑤
};	//���U���g

#endif	//!__RESULT_H__