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

========================================== */

#ifndef __HAMMER_H__
#define __HAMMER_H__

// =============== �C���N���[�h ===================
#include "Shader.h"
#include "Pos3d.h"
#include "SphereInfo.h"
#include "Geometry.h"
#include <DirectXMath.h>
#include "Camera.h"

// =============== �N���X��` =====================
class CHammer
{
public:
	// ===�v���g�^�C�v�錾===
	
	CHammer();	//�R���X�g���N�^
	~CHammer();	//�f�X�g���N�^

	bool Update();	// �X�V�֐�
	void Draw(const CCamera* pCamera);				// �`��֐�
	void Swing();									// �ړ��ɂ���]�ړ�
	void AttackStart(TPos3d<float>pPos, float angle);								// �U���J�n����

	CSphereInfo::Sphere GetSphere();				// �����蔻��擾
private:
	// ===�����o�ϐ��錾=====
	TPos3d<float> m_pos;			// �n���}�[�̈ʒu���W
	CSphereInfo::Sphere m_sphere;	// �n���}�[�̓����蔻��p�̋���
	TTriType<float> m_scale;		// �T�C�Y

	CGeometry* m_pHammerGeo;		// �n���}�[�����\������}�`
	TPos3d<float> m_tPlayerPos;		// ���݂̃v���C���[���W

	float m_fAngleNow;				// ���̊p�x
	int m_dAddAngleCnt;				// �p�x���Z�t���[���l

};

#endif // !__HAMMER_H__

