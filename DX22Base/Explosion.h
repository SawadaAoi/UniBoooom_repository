//�w�b�_�[�p�@----------------------------------------------------
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
======================================== */

#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__
#include "Model.h"
#include "Shader.h"
#include "Sphereinfo.h"


//=============== �\���̒�` =====================

//=============== �N���X��` =====================

//=============== �񋓒�` =======================

class CExplosion
{
public:
	CExplosion();
	~CExplosion();
	void Update();
	void Draw();

	void SetExplode(bool YN);
	void SetPos(CSphereInfo::Sphere pos);
	bool GetExplode();
	CSphereInfo::Sphere GetPos();


protected:
	Model* m_pModel;
	VertexShader* m_pVS;
	CSphereInfo::Sphere m_Sphere;
	float m_fSize;
	bool m_bExploded;	//���������̃t���O

private:
};

#endif // __EXPLOSION_H__
