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

//=============== �N���X��` =====================
class CExplosion
{
public:
	// ===�����o�֐��錾===
	CExplosion(TPos3d<float> fPos, float fSize, float fTime);	//�R���X�g���N�^
	~CExplosion();												//�f�X�g���N�^
	void Update();												//�X�V�֐�
	void Draw();												//�`��֐�
	void DisplayTimeAdd();										//�����\���J�E���g���Z�����֐�

	void SetPos(TPos3d<float> pos);	//�������W�ݒ�֐�
	TPos3d<float> GetPos();			//�g���ĂȂ��֐�
	tagSphereInfo GetSphere();	//Sphere���擾�����֐�
	void SetSphere(tagSphereInfo sphere);	//Sphere���ݒ菈���֐�
	bool GetDelFlg();					//�폜�t���O�擾�����֐�
	void SetCamera(const CCamera* m_pCamera);	//���̃I�u�W�F�N�g�Ɠ���̃J�������Z�b�g


private:
	// ===�����o�ϐ��錾===
	tagSphereInfo m_Sphere;	// ���W�Ɠ����蔻��̑傫��������
	tagTransform3d m_Transform;	//���[���h���W�n�ɕK�v�ȏ��
	float			m_fMaxSize;
	TTriType<float>	m_fSizeAdd;
	int				m_fDelFrame;		// �����\���J�E���g
	bool			m_bDelFlg;			// �����I���t���O
	float			m_fExplodeTime;		// ����������

	CGeometry*		m_3dModel;		// ������3D���f��
	const CCamera*	m_pCamera;	//�J�����̃|�C���^
};

#endif // __EXPLOSION_H__
