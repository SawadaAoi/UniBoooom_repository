#ifndef __EXPLOSION_H__	//Explosion.h�C���N���[�h�K�[�h
#define __EXPLOSION_H__
/*========================================
	HEW/UniBoooom!!
	---------------------------------------
	���������N���X��`�w�b�_
	---------------------------------------
	Expplosion.h

	�쐬�� �A �F��

	�ύX����
	�E2023/11/03 �w�b�_�[�쐬 / �A �F��
	�E2023/11/05 �p�����[�^�ݒ� /�@�A �F��
	�E2023/11/07 �ϐ��^TriType��CSphere�� /�A �F��
	�E2023/11/08 �ϐ��A�֐��̕ύX / �V�c����

======================================== */

// =============== �C���N���[�h ===================
#include "Model.h"		//model�N���X��`�w�b�_�\
#include "Shader.h"		//�V�F�[�_�[�N���X��`�w�b�_�[
#include "Sphereinfo.h"	//���̏��p�w�b�_�[
#include "Sphere.h"		//����`�w�b�_�[


//=============== �N���X��` =====================
class CExplosion
{
public:
	// ===�����o�֐��錾===
	CExplosion(TTriType<float> pos);	//�R���X�g���N�^
	~CExplosion();						//�f�X�g���N�^
	void Update();						//�X�V�֐�
	void Draw();						//�`��֐�
	void DisplayTimeAdd();				//�����\���J�E���g���Z�����֐�

	void SetPos(TTriType<float> pos);	//�������W�ݒ�֐�
	TTriType<float> GetPos();			//�g���ĂȂ��֐�
	CSphereInfo::Sphere GetSphere();	//Sphere���擾�����֐�
	void SetSphere(CSphereInfo::Sphere sphere);	//Sphere���ݒ菈���֐�
	bool GetDelFlg();					//�폜�t���O�擾�����֐�

private:
	// ===�����o�ϐ��錾===
	CSphereInfo::Sphere m_Sphere;	// ���W�Ɠ����蔻��̑傫��������
	float	m_fSize;				// �����̑傫���i�H
	int	m_fDelFrame;				// �����\���J�E���g
	bool	m_bDelFlg;				// �����I���t���O
	CGeometry* m_3dModel;			// ������3D���f��

};

#endif // __EXPLOSION_H__
