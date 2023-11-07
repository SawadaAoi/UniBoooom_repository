//�w�b�_�[�p�@----------------------------------------------------
/*========================================
HEW/UniBoooom!!
---------------------------------------
�����p�w�b�_
---------------------------------------
Expplosion.h

TeiUon

�ύX����
�E2023/11/03 �w�b�_�[�쐬�@�A�F��
�E2023/11/05 �p�����[�^�ݒ�@�A�F��

======================================== */

#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__
#include "Model.h"
#include "Shader.h"
#include "TriType.h"


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
	void SetPos(TTriType<float> pos);
	bool GetExplode();
	TTriType<float> GetPos();
	

protected:
	Model* m_pModel;
	VertexShader* m_pVS;
	TTriType<float> m_pos;
	float m_fSize;
	bool m_bExploded;	//���������̃t���O

private:
};

#endif // __EXPLOSION_H__

