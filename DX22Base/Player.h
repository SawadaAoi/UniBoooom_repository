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
	�E2023/11/08 Pos.h���C���N���[�h /�R�����C
	�E2023/11/08 �����蔻��p�̋���m_sphere��ǉ� /�R�����C
	�E2023/11/08 �v���C���[���W������ϐ���TTriType����TPos�ɕύX /�R�����C


========================================== */

#ifndef __PLAYER_H__
#define __PLAYER_H_

// =============== �C���N���[�h ===================
#include "Shader.h"
#include"hammer.h"
#include "Geometry.h"
#include "SphereInfo.h"
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
	void Move();	//�ړ��֐�
	CSphereInfo::Sphere GetPlayerSphere();	//�����蔻�����邽�߃Q�b�^�[
	CSphereInfo::Sphere GetHammerSphere();	//�����蔻�����邽�߃Q�b�^�[
	TPos<float> GetPos();	//�v���C���[�̍��W���擾

private:
	// ===============�����o�֐��錾===============
	DirectX::XMMATRIX m_T;				//�ʒu
	DirectX::XMMATRIX m_S;				//�g�k
	DirectX::XMMATRIX m_Ry;				//��]
	//TTriType<float> m_playerPosition;	//�v���C���[�̈ʒu
	TPos<float> m_pos;					//�v���C���[�̍��W
	CSphereInfo::Sphere m_sphere;		//�v���C���[�̓����蔻��p�̋���
	TTriType<float> m_playerForward;	// �v���C���[�̏����i�s����
	float m_playerRotation;				// �v���C���[�̉�]�p�x
	int m_nHp;							//�v���C���[�̗̑�
	CHammer* m_pHammer;
	CGeometry* m_pPlayerGeo;
	bool m_bHammer;						//�U�������ǂ����̃t���O
};


#endif // !__PLAYER_H__



