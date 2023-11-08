/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	player�p�w�b�_
	------------------------------------
	player.h
	------------------------------------
	�쐬��
		�R�{�M��
	�ύX����
	�E2023/11/03 h,�쐬 �R�{�M��
	�E2023/11/06 �_���[�W�����ǉ�,�R�����g�ǉ� �R�{�M��


========================================== */

#ifndef __PLAYER_H__
#define __PLAYER_H_

// =============== �C���N���[�h ===================
#include "Shader.h"
#include"hammer.h"
#include "Geometry.h"
#include "Pos.h"
// =============== �N���X��` =====================
class CPlayer
{
public:
	// =============== �v���g�^�C�v�錾 ===============
	CPlayer();
	~CPlayer();

	void Update();	//�X�V
	void Draw();	//�`��
	void Damege();	//���g��HP�����炷
	void Move();

	TPos<float> GetPos() { return m_playerPosition; }

	CHammer* GetHammer() { return m_pHammer; }

private:
	// ===============�����o�֐��錾===============
	DirectX::XMMATRIX m_T;				//�ʒu
	DirectX::XMMATRIX m_S;				//�g�k
	DirectX::XMMATRIX m_Ry;				//��]
	TPos<float> m_playerPosition;	//�v���C���[�̈ʒu
	TTriType<float> m_playerForward;	// �v���C���[�̏����i�s����
	float m_playerRotation;				// �v���C���[�̉�]�p�x
	int m_nHp;							//�v���C���[�̗̑�
	CHammer* m_pHammer;
	CGeometry* m_pPlayer;
	bool m_bHammer;						//�U�������ǂ����̃t���O
};


#endif // !__PLAYER_H__



