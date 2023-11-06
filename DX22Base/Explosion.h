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
	void DeleteExplosion();

private:
	
	DirectX::XMMATRIX Position;
	float m_fSize;

};

#endif // __EXPLOSION_H__

