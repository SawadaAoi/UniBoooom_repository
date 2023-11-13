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
	�E2023/11/08 �v���C���[���W������ϐ���TTriType����TPos�ɕύX /�R�����C
	�E2023/11/08 �߂��Ⴍ����R�����g�ǉ����� /�R�����C
	�E2023/11/08 ��]�ɂ��ړ���Swing�֐��ǉ� /�R�����C
	�E�����蔻��p��Sphere�ϐ���ǉ� /�R�����C
	�E�����蔻��p��Sphere�̃Q�b�g�֐���ǉ� /�R�����C

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

	void Update(TPos3d<float> pPos, float angle);	// �X�V�֐�
	void Draw(const CCamera* pCamera);				// �`��֐�
	void Swing(TPos3d<float>pPos,float angle);		// �ړ��ɂ���]�ړ�
	void AttackStart();								// �U���J�n����

	bool GetAttackFlg();								// �n���}�[���g�p�����ǂ����̃t���O���擾
	CSphereInfo::Sphere GetSphere();				// �����蔻��擾
private:
	// ===�����o�ϐ��錾=====
	TPos3d<float> m_pos;			// �n���}�[�̈ʒu���W
	CSphereInfo::Sphere m_sphere;	// �n���}�[�̓����蔻��p�̋���
	TTriType<float> m_scale;		// �T�C�Y

	float m_nowangle;				// ���̊p�x
	float m_stateangle;				//
	bool m_bAttackFlg;				//�n���}�[���g�p���̃t���O
	CGeometry* m_pHammerGeo;		//�n���}�[�����\������}�`
};

#endif // !__HAMMER_H__

