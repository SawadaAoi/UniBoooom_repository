/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	���������N���X��`�w�b�_
	---------------------------------------
	Expplosion.h

	�쐬�� �A �F��

	�ύX����
	�E2023/11/03 �w�b�_�[�쐬 Tei
	�E2023/11/05 �p�����[�^�ݒ� Tei
	�E2023/11/07 �ϐ��^TriType��CSphere�� Tei
	�E2023/11/08 �ϐ��A�֐��̕ύX Sawada
	�E2023/11/10 �J�����|�C���^��ǉ� Ymashita
	�E2023/11/13 �R���X�g���N�^��time��ǉ� Suzumura
	�E2023/11/13 ���������Ԃ̕ϐ���ǉ� Suzumura
	�E2023/11/14 SphereInfo�̕ύX�ɑΉ� Takagi
	�E2023/11/15 Object�N���X���p�������̂ŏC���@yamamoto
	�E2023/11/20 �R���{���z��Y�����̒ǉ� Sawada

======================================== */
#ifndef __EXPLOSION_H__	//Explosion.h�C���N���[�h�K�[�h
#define __EXPLOSION_H__

// =============== �C���N���[�h ===================
#include "Model.h"			//model�N���X��`�w�b�_�\
#include "Shader.h"			//�V�F�[�_�[�N���X��`�w�b�_�[
#include "Sphereinfo.h"		//���̏��p�w�b�_�[
#include "Transform3d.h"	//���[���h���W�n���w�b�_�[
#include "Sphere.h"			//����`�w�b�_�[
#include "Camera.h"			//�J������`�w�b�_�[
#include "Object.h"			//

//=============== �N���X��` =====================
class CExplosion
	:public CObject
{
public:
	// ===�����o�֐��錾===
	CExplosion(TPos3d<float> fPos, float fSize, float fTime, int comboNum);	//�R���X�g���N�^
	~CExplosion();												// �f�X�g���N�^
	void Update();												// �X�V�֐�
	void Draw();												// �`��֐�
	void DisplayTimeAdd();										// �����\���J�E���g���Z�����֐�

	bool GetDelFlg();							// �폜�t���O�擾�����֐�
	int GetComboNum();							// �R���{�z��ԍ��擾
	void SetCamera(const CCamera* m_pCamera);	// ���̃I�u�W�F�N�g�Ɠ���̃J�������Z�b�g


private:
	// ===�����o�ϐ��錾===
	float			m_fMaxSize;
	TTriType<float>	m_fSizeAdd;
	int				m_fDelFrame;		// �����\���J�E���g
	bool			m_bDelFlg;			// �����I���t���O
	float			m_fExplodeTime;		// ����������

	CGeometry*		m_3dModel;		// ������3D���f��
	const CCamera*	m_pCamera;	//�J�����̃|�C���^

	int m_dComboNum;			// �R���{�z��ԍ�


};

#endif // __EXPLOSION_H__
