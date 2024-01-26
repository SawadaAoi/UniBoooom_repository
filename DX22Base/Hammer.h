/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	Hammer�p�w�b�_
	------------------------------------
	Hammer.h
	------------------------------------
	�쐬��
		�R�{�M��
	�ύX����
	�E2023/11/08 �v���C���[���W������ϐ���TTriType����TPos�ɕύX Yamashita
	�E2023/11/08 �߂��Ⴍ����R�����g�ǉ����� Yamashita
	�E2023/11/08 ��]�ɂ��ړ���Swing�֐��ǉ� Yamashita
	�E2023/11/10 �����蔻��p��Sphere�ϐ���ǉ� Yamashita
	�E2023/11/10 �����蔻��p��Sphere�̃Q�b�g�֐���ǉ� Yamashita
	�E2023/11/14 �S�̓I�ɏ����̗��ꂪ������Â炩�����̂ŏC�� Sawada
	�E2023/11/14 SphereInfo�̕ύX�ɑΉ� Takagi
	�E2023/11/15 Object�N���X���p�������̂ŏC���@yamamoto
	�E2023/11/23 �W�I���g���[���烂�f���ɍ����ւ��@yamashita
	�E2023/11/29 Interval�̕ϐ��A�֐��ǉ��@yamamoto
	�E2023/12/01 Interval��SwingSpeed�ɕύX�@yamamoto
========================================== */

#ifndef __HAMMER_H__
#define __HAMMER_H__

// =============== �C���N���[�h ===================
#include "Shader.h"
#include "SphereInfo.h"
#include "Transform3d.h"
#include "Geometry.h"
#include <DirectXMath.h>
#include "Camera.h"
#include "Object.h"
#include "Model.h"
#include "Sphere.h"

// =============== �萔��` =======================
const float SwingSpeed_MIN = 9.0f;		// �n���}�[�̐U��̍ő��l


// =============== �N���X��` =====================
class CHammer
	: public CObject
{
public:
	// ===�v���g�^�C�v�錾===
	
	CHammer();	//�R���X�g���N�^
	~CHammer();	//�f�X�g���N�^

	bool Update();			// �X�V�֐�
	void Draw();			// �`��֐�
	void Swing();											// �ړ��ɂ���]�ړ�
	void AttackStart(TPos3d<float>pPos, float angle);		// �U���J�n����
	void SwingSpeedAdd();
	void SwingSpeedSubtract();
	float GetInterval();
	void SetCamera(const CCamera* pCamera);
private:
	// ===�����o�ϐ��錾=====
	Model* m_pModel;				//�v���C���[�̃��f��
	VertexShader* m_pVS;			//���_�V�F�[�_�[�̃|�C���^
	TPos3d<float> m_tPlayerPos;		// ���݂̃v���C���[���W
	float m_fAngleNow;				// ���̊p�x
	int m_dAddAngleCnt;				// �p�x���Z�t���[���l
	const CCamera* m_pCamera;		//	
	float m_fSwingSpeed;			//�n���}�[��U�鎞��
	float m_fAddAngle;				// 1�t���[���ňړ�����p�x��

	CSphere* m_pSphere;
};

#endif // !__HAMMER_H__

