/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�|�[�Y��ʒ�`
	---------------------------------------
	Pose.h

	�쐬��	takagi

	�ύX����
	�E2023/12/01 ���� takagi
	�E2023/12/04 ���� takagi

========================================== */

#ifndef __POSE_H__	//Pose.h�C���N���[�h�K�[�h
#define __POSE_H__

#include "Sound.h"		//��
#include "Camera.h"		//�J����
#include "2dPolygon.h"	//���ʃ|���S��
#include <vector>		//�z��R���e�i

// =============== �N���X��` =====================
class CPose
{
private:
	enum E_FLAG
	{
		E_FLAG_POSEMODE = 0x00, //�|�[�Y���[�h
	};	//�t���O
public:
	// ===�v���g�^�C�v�錾===
	CPose(const CCamera* pCamera);						//�R���X�g���N�^
	~CPose();											//�f�X�g���N�^
	void Update();										//�X�V
	void Draw();										//�`��
	bool IsFin() const;									//�I���m�F
	void SetCamera(const CCamera* pCamera = nullptr);	//�J�����Z�b�^
	bool IsPose() const;								//�|�[�Y����
private:
	// ===�����o�ϐ��錾=====
	unsigned char m_ucFlag;							//�t���O
	bool m_bFinish;									//�I���\��p(true�ŏI��)
	std::vector<C2dPolygon*> m_2dObj;				//���ʃ|���S��
	PixelShader* m_pBgPs;							//�w�i�p�s�N�Z���V�F�[�_
	VertexShader* m_pBgVs;							//�w�i�p���_�V�F�[�_
	//const CCamera* m_pCamera;						//�J����
	const CCamera* m_pCameraDef;					//�^���J����
	XAUDIO2_BUFFER* m_pBGM;							//BGM�̉����f�[�^
	XAUDIO2_BUFFER* m_pSEHitHammer;					//SE�̉����f�[�^
	IXAudio2SourceVoice* m_pSpeaker;				//BGM�𕷂���鑤
	IXAudio2SourceVoice* m_pSEHitHammerSpeaker;		//SE�𕷂���鑤
};	//���U���g

#endif	//!__POSE_H__