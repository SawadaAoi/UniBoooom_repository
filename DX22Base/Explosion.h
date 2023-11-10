#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__
/*========================================
	HEW/UniBoooom!!
	---------------------------------------
	�����p�w�b�_
	---------------------------------------
	Expplosion.h
	
	�쐬�� �A �F��
	
	�ύX����
	�E2023/11/03 �w�b�_�[�쐬 / �A �F��
	�E2023/11/05 �p�����[�^�ݒ� /�@�A �F��
	�E2023/11/07 �ϐ��^TriType��CSphere�� /�A �F��
	�E2023/11/08 �ϐ��A�֐��̕ύX / �V�c����
	�E2023/11/10 �J�����|�C���^��ǉ� /�R�����C
======================================== */

// =============== �C���N���[�h ===================
#include "Model.h"
#include "Shader.h"
#include "Sphereinfo.h"
#include "Sphere.h"
#include "Camera.h"

//=============== �N���X��` =====================
class CExplosion
{
public:
// ===�����o�֐��錾===
	CExplosion(TTriType<float> pos,float size);
	~CExplosion();
	void Update();
	void Draw();
	void DisplayTimeAdd();

	void SetPos(TTriType<float> pos);
	//TTriType<float> GetPos();
	CSphereInfo::Sphere GetSphere();
	void SetSphere(CSphereInfo::Sphere sphere);
	bool GetDelFlg();
	void SetCamera(const CCamera* m_pCamera);	//���̃I�u�W�F�N�g�Ɠ���̃J�������Z�b�g

private:
// ===�����o�ϐ��錾===
	CSphereInfo::Sphere m_Sphere;	// ���W�Ɠ����蔻��̑傫��������
	float			m_fSize;
	float			m_fMaxSize;
	float			m_fSizeAdd;
	int				m_fDelFrame;	// �����\���J�E���g
	bool			m_bDelFlg;		// �����I���t���O
	CGeometry*		m_3dModel;		// ������3D���f��
	const CCamera*	m_pCamera;	//�J�����̃|�C���^
};

#endif // __EXPLOSION_H__
