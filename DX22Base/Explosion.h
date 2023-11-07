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
	
======================================== */

// =============== �C���N���[�h ===================
#include "Model.h"
#include "Shader.h"
#include "Sphereinfo.h"
#include "Sphere.h"


//=============== �N���X��` =====================
class CExplosion
{
public:
// ===�����o�֐��錾===
	CExplosion(TTriType<float> pos);
	~CExplosion();
	void Update();
	void Draw();
	void DisplayTimeAdd();

	void SetPos(TTriType<float> pos);
	TTriType<float> GetPos();
	CSphereInfo::Sphere GetSphere();
	void SetSphere(CSphereInfo::Sphere sphere);
	bool GetDelFlg();

private:
// ===�����o�ϐ��錾===
	CSphereInfo::Sphere m_Sphere;	// ���W�Ɠ����蔻��̑傫��������
	float	m_fSize;
	int	m_fDelFrame;	// �����\���J�E���g
	bool	m_bDelFlg;		// �����I���t���O
	CGeometry* m_3dModel;		// ������3D���f��

};

#endif // __EXPLOSION_H__
