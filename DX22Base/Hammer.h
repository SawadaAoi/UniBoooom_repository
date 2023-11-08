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

#include "Shader.h"
#include "Pos.h"
#include "SphereInfo.h"
#include "Geometry.h"
#include <DirectXMath.h>


class CHammer
{
public:
	CHammer();	//�R���X�g���N�^
	~CHammer();	//�f�X�g���N�^

	void Update(TPos<float> pPos, float angle);	//�X�V�֐�
	void Draw();								//�`��֐�
	bool Gethammer();							//�n���}�[���g�p�����ǂ����̃t���O���擾
	void Swing(TPos<float>pPos,float angle);	//�ړ��ɂ���]�ړ�
	CSphereInfo::Sphere GetSphere();			//�n���}�[�̃v���C���[
private:
	DirectX::XMMATRIX m_T;			//�ړ��̕ϊ��s��
	DirectX::XMMATRIX m_S;			//�g�k�̕ϊ��s��
	DirectX::XMMATRIX m_Ry;			//Y���̉�]������ϊ��s��
	TPos<float> m_pos;	//�n���}�[�̈ʒu���W
	CSphereInfo::Sphere m_sphere;	//�n���}�[�̓����蔻��p�̋���
	float m_nowangle;				//���̊p�x
	float m_stateangle;				//
	bool m_bHammer;					//�n���}�[���g�p���̃t���O
	CGeometry* m_pHammerGeo;		//�n���}�[�����\������}�`
};

#endif // !__HAMMER_H__

