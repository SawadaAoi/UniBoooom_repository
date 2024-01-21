/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�n���}�[�p�w�b�_
	------------------------------------
	Hammer.h
	------------------------------------
	�쐬��	yamamoto

	�ύX����
	�E2023/11/08 �v���C���[���W������ϐ���TTriType����TPos�ɕύX yamashita
	�E2023/11/08 �߂��Ⴍ����R�����g�ǉ����� yamashita
	�E2023/11/08 ��]�ɂ��ړ���Swing�֐��ǉ� yamashita
	�E2023/11/10 �����蔻��p��Sphere�ϐ���ǉ� yamashita
	�E2023/11/10 �����蔻��p��Sphere�̃Q�b�g�֐���ǉ� yamashita
	�E2023/11/14 �S�̓I�ɏ����̗��ꂪ������Â炩�����̂ŏC�� sawada
	�E2023/11/14 SphereInfo�̕ύX�ɑΉ� takagi
	�E2023/11/15 Object�N���X���p�������̂ŏC���@yamamoto
	�E2023/11/23 �W�I���g���[���烂�f���ɍ����ւ��@yamashita
	�E2023/11/29 Interval�̕ϐ��A�֐��ǉ��@yamamoto
	�E2023/12/01 Interval��SwingSpeed�ɕύX�@yamamoto
	�E2024/01/20 ���t�@�N�^�����O takagi
	�E2024/01/21 �R�����g���C takagi

========================================== */

#ifndef __HAMMER_H__	//Hammer.h�C���N���[�h�K�[�h
#define __HAMMER_H__

// =============== �C���N���[�h ===================
#include "Shader.h"
#include "SphereInfo.h"
#include "Transform3d.h"
#include "Geometry.h"
#include <DirectXMath.h>
#include "Camera.h"
#include "Model.h"
#include "Sphere.h"
#include "3dObject.h"

// =============== �萔��` =======================
const float SwingSpeed_MIN = 9.0f;								//�n���}�[�̃t�U��̍ő��l


// =============== �N���X��` =====================
class CHammer
	: public C3dObject
{
public:
	// ===�v���g�^�C�v�錾===
	
	CHammer();	//�R���X�g���N�^
	~CHammer();	//�f�X�g���N�^

	void Update();			// �X�V�֐�
	void Draw();			// �`��֐�
	void Swing();											// �ړ��ɂ���]�ړ�
	void AttackStart(TPos3d<float>pPos, float angle);		// �U���J�n����
	void SwingSpeedAdd();
	void SwingSpeedSubtract();
	float GetInterval();
	bool IsExist();
	void SetCamera(const CCamera* pCamera);
private:
	// ===�����o�ϐ��錾=====
	Model* m_pModel;			//�v���C���[�̃��f��
	VertexShader* m_pVS;		//���_�V�F�[�_�[�̃|�C���^
	TPos3d<float> m_tPlayerPos;	//���݂̃v���C���[���W
	float m_fAngleNow;			//���̊p�x
	int m_dAddAngleCnt;			//�p�x���Z�t���[���l
	const CCamera* m_pCamera;	//	
	float m_fSwingSpeed;		//�n���}�[��U�鎞��
	float m_fAddAngle;			//1�t���[���ňړ�����p�x��
	bool m_bExist;				//�n���}�[�����݂��邩
	CSphere* m_pSphere;
};

#endif	//!__HAMMER_H__

